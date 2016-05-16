#include "UtilityModule.hpp"
#include <sstream>
#include <stack>

bool UtilityModule::isOutOfMap(int tile_x, int tile_y)
{
    if(tile_x < 0 || tile_y < 0 || tile_x >= (int)Tile.size()) return true;
    if(tile_y >= (int)Tile[tile_x].size()) return true;
    return false;
}

bool UtilityModule::isStackable(int objectType)
{
    _assert(objectType >= 0 && objectType < (int)ObjectType.size(), "Object type out of bounds in isStackable.");
    if(ObjectType[objectType].baseType == OBJECT_BASE_TYPE_AMMUNITION) return true;
    return false;
}

bool UtilityModule::isPassable(int tile_x, int tile_y)
{
    if(isOutOfMap(tile_x, tile_y)) return false;

    if(Tile[tile_x][tile_y].tileType >= 0) {
        _assert(Tile[tile_x][tile_y].tileType < (int)TileType.size(), "TileType out of bounds in isPassable.");
        if(!TileType[Tile[tile_x][tile_y].tileType].isPassable) return false;
    }
    else return false;

    if(Tile[tile_x][tile_y].sceneryType >= 0) {
        _assert(Tile[tile_x][tile_y].sceneryType < (int)SceneryType.size(), "SceneryType out of bounds in isPassable.");
        if(!SceneryType[Tile[tile_x][tile_y].sceneryType].isPassable) return false;
    }

    for(std::list <ObjectClass>::const_iterator it=Tile[tile_x][tile_y].object.begin(); it!=Tile[tile_x][tile_y].object.end(); ++it) {
        _assert(it->type < (int)ObjectType.size(), "ObjectType out of bounds in isPassable.");
        if(!ObjectType[it->type].isPassable) return false;
    }

    return true;
}

void UtilityModule::compileAndVerifyAllScripts()
{
    for(size_t i=0; i<Script.size(); ++i) {
        if(!Script[i].isLoaded) continue;

        std::string err;
        if(!compileScript(Script[i], err)) {
            wxString str = wxErrorLogEditBox->GetLabel()+err.c_str()+"\r\n";
            wxErrorLogEditBox->SetLabel(str);
        }
    }
}

void UtilityModule::updateDelta()
{
    sf::Int64 currentTime = globalClock.getElapsedTime().asMicroseconds();
    static sf::Int64 lastTime = currentTime;
    deltaTime = (currentTime-lastTime)/(1000000.0/30.0);
    lastTime = currentTime;
}

float UtilityModule::getDistance(float x1, float y1, float x2, float y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

float UtilityModule::getDistance(const CharacterClass &ch1, const CharacterClass &ch2)
{
    return getDistance(ch1.x, ch1.y, ch2.x, ch2.y);
}

vPoint UtilityModule::getScreenPosition(float posX, float posY, const ViewClass &View)
{
    return vPoint(
        posX*View.distance-(View.x-(float)window.getSize().x/2.f)+(1-View.distance)*View.x,
        posY*View.distance-(View.y-(float)window.getSize().y/2.f)+(1-View.distance)*View.y
    );
}

vPoint UtilityModule::getWorldPosition(float posX, float posY, const ViewClass &View)
{
    return vPoint(
        (posX+View.x-(float)window.getSize().x/2.f-(1-View.distance)*View.x)/View.distance,
        (posY+View.y-(float)window.getSize().y/2.f-(1-View.distance)*View.y)/View.distance
    );
}

std::string UtilityModule::intToString(int val)
{
    std::ostringstream oss;
    oss << val;
    return oss.str();
}

std::string UtilityModule::floatToString(float val)
{
    std::ostringstream oss;
    oss.precision(2);
    oss << val;
    return oss.str();
}

std::string UtilityModule::spacesToUnderscores(const std::string &str)
{
    std::string ret = str;
    for(size_t i=0; i<ret.size(); ++i) {
        if(ret[i] == ' ') ret[i] = '_';
    }
    return ret;
}

std::string UtilityModule::underscoresToSpaces(const std::string &str)
{
    std::string ret = str;
    for(size_t i=0; i<ret.size(); ++i) {
        if(ret[i] == '_') ret[i] = ' ';
    }
    return ret;
}

bool UtilityModule::compileScript(ScriptClass &script, std::string &errorOutput)
{
    errorOutput.clear();
    std::istringstream script_iss(script.script);
    int lineNumber = 0;
    std::string line, instruction;
    std::stack <int> ifStatementInstructionIndex;
    while(std::getline(script_iss, line)) {
        ++lineNumber;
        util::clamp_ws(line);
        size_t comment = line.find("//");
        if(comment != std::string::npos) {
            line = line.substr(0, comment);
        }
        if(line.empty()) continue;
        std::istringstream line_iss(line);
        line_iss >> instruction;
        if(instruction == "if") {
            script.instruction.push_back(ScriptClass::InstructionClass());
            script.instruction.back().ifStatement = true;
            ifStatementInstructionIndex.push(script.instruction.size()-1);
            std::string ifFunc;
            line_iss >> ifFunc;
            if(ifFunc.empty()) {
                char buff[1000];
                sprintf(buff, "Parse error in script file '%s' line %d: If statement with no condition.", script.IDName.c_str(), lineNumber);
                errorOutput = buff;
                return false;
            }
            if(ifFunc == "QuestProgress") {
                int p1int = -1, p2int = -1, p3int = -1;
                std::string questIDName;
                line_iss >> questIDName >> p2int >> p3int;
                p1int = getQuestIDByIDName(questIDName);
                if(p1int < 0) {
                    char buff[1000];
                    sprintf(buff, "Parse error in script file '%s' line %d: Quest '%s' not found.", script.IDName.c_str(), lineNumber, questIDName.c_str());
                    errorOutput = buff;
                    return false;
                }
                if(p2int < 0 || p3int < 0 || p2int > 100 || p3int > 100) {
                    char buff[1000];
                    sprintf(buff, "Parse error in script file '%s' line %d: Incorrect or missing value.", script.IDName.c_str(), lineNumber);
                    errorOutput = buff;
                    return false;
                }
                script.instruction.back().callFunc = SCRIPT_IF_FUNC_QUEST_PROGRESS;
                script.instruction.back().p1int = p1int;
                script.instruction.back().p2int = p2int;
                script.instruction.back().p3int = p3int;
            }
            else {
                char buff[1000];
                sprintf(buff, "Parse error in script file '%s' line %d: Unknown if statement function '%s'.", script.IDName.c_str(), lineNumber, ifFunc.c_str());
                errorOutput = buff;
                return false;
            }
        }
        else if(instruction == "endif") {
            if(ifStatementInstructionIndex.empty()) {
                char buff[1000];
                sprintf(buff, "Parse error in script file '%s' line %d: endif with no if statement.", script.IDName.c_str(), lineNumber);
                errorOutput = buff;
                return false;
            }
            script.instruction[ifStatementInstructionIndex.top()].ifStatementJumpToInstruction = script.instruction.size();
            ifStatementInstructionIndex.pop();
        }
        else if(instruction == "AddExp") {
            int p1int = -1;
            line_iss >> p1int;
            if(p1int < 0) {
                char buff[1000];
                sprintf(buff, "Parse error in script file '%s' line %d: Incorrect or missing value.", script.IDName.c_str(), lineNumber);
                errorOutput = buff;
                return false;
            }
            script.instruction.push_back(ScriptClass::InstructionClass());
            script.instruction.back().callFunc = SCRIPT_FUNC_ADD_EXP;
            script.instruction.back().p1int = p1int;
        }
        else if(instruction == "AddMoney") {
            int p1int = -1;
            line_iss >> p1int;
            if(p1int < 0) {
                char buff[1000];
                sprintf(buff, "Parse error in script file '%s' line %d: Incorrect or missing value.", script.IDName.c_str(), lineNumber);
                errorOutput = buff;
                return false;
            }
            script.instruction.push_back(ScriptClass::InstructionClass());
            script.instruction.back().callFunc = SCRIPT_FUNC_ADD_MONEY;
            script.instruction.back().p1int = p1int;
        }
        else if(instruction == "SetQuestProgress") {
            int p1int = -1, p2int = -1;
            std::string questIDName;
            line_iss >> questIDName >> p2int;
            p1int = getQuestIDByIDName(questIDName);
            if(p1int < 0) {
                char buff[1000];
                sprintf(buff, "Parse error in script file '%s' line %d: Quest '%s' not found.", script.IDName.c_str(), lineNumber, questIDName.c_str());
                errorOutput = buff;
                return false;
            }
            if(p2int < 0 || p2int > 100) {
                char buff[1000];
                sprintf(buff, "Parse error in script file '%s' line %d: Incorrect or missing value.", script.IDName.c_str(), lineNumber);
                errorOutput = buff;
                return false;
            }
            script.instruction.push_back(ScriptClass::InstructionClass());
            script.instruction.back().callFunc = SCRIPT_FUNC_SET_QUEST_PROGRESS;
            script.instruction.back().p1int = p1int;
            script.instruction.back().p2int = p2int;
        }
        else if(instruction == "EndDialogue") {
            script.instruction.push_back(ScriptClass::InstructionClass());
            script.instruction.back().callFunc = SCRIPT_FUNC_END_DIALOGUE;
        }
        else {
            char buff[1000];
            sprintf(buff, "Parse error in script file '%s' line %d: Unknown instruction '%s'.", script.IDName.c_str(), lineNumber, instruction.c_str());
            errorOutput = buff;
            return false;
        }
        if(!line_iss.eof()) {
            char buff[1000];
            sprintf(buff, "Parse error in script file '%s' line %d: Incorrect number of parameters.", script.IDName.c_str(), lineNumber);
            errorOutput = buff;
            return false;
        }
    }
    if(!ifStatementInstructionIndex.empty()) {
        char buff[1000];
        sprintf(buff, "Parse error in script file '%s' line %d: Unexpected end of file - missing endif.", script.IDName.c_str(), lineNumber);
        errorOutput = buff;
        return false;
    }
    return true;
}

void UtilityModule::changeEntityValue(wxGridEvent& event)
{
    std::string newVal = ((wxGrid*)event.GetEventObject())->GetCellValue(event.GetRow(),
                                                                         event.GetCol()).c_str();
    for(size_t i=0; i<newVal.size(); ++i) {
        if(newVal[i] == ' ') newVal[i] = '_';
    }

    if(selectionEntityType == ENTITY_TYPE_TILE_TYPE) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)TileType.size(),
                "Script index out of bounds.");
        if(event.GetRow() == 0) {
            if(newVal.empty()) {event.Veto(); return;}
            TileType[selectionEntityIndex].name = newVal;
        }
        else if(event.GetRow() == 1) {
            if(newVal.empty()) {event.Veto(); return;}
            TileType[selectionEntityIndex].resourcesName = newVal;
        }
        else if(event.GetRow() == 2) {
            if(newVal.empty()) TileType[selectionEntityIndex].isPassable = false;
            else TileType[selectionEntityIndex].isPassable = true;
        }
        else if(event.GetRow() == 3) {
            if(newVal.empty()) TileType[selectionEntityIndex].isShootThroughAble = false;
            else TileType[selectionEntityIndex].isShootThroughAble = true;
        }
    }
    else if(selectionEntityType == ENTITY_TYPE_SCENERY_TYPE) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)SceneryType.size(),
                "Script index out of bounds.");
        if(event.GetRow() == 0) {
            if(newVal.empty()) {event.Veto(); return;}
            SceneryType[selectionEntityIndex].name = newVal;
        }
        else if(event.GetRow() == 1) {
            if(newVal.empty()) {event.Veto(); return;}
            SceneryType[selectionEntityIndex].resourcesName = newVal;
        }
        else if(event.GetRow() == 2) {
            if(newVal.empty()) {event.Veto(); return;}
            int val = -1;
            sscanf(newVal.c_str(), "%d", &val);
            if(val < 0 || val > 6) {event.Veto(); return;}
            SceneryType[selectionEntityIndex].natureType = val;
        }
        else if(event.GetRow() == 3) {
            if(newVal.empty()) {event.Veto(); return;}
            int val = -1;
            sscanf(newVal.c_str(), "%d", &val);
            if(val < 0 || val > 2) {event.Veto(); return;}
            SceneryType[selectionEntityIndex].layer = val;
        }
        else if(event.GetRow() == 4) {
            if(newVal.empty()) {event.Veto(); return;}
            float val = 0.f;
            sscanf(newVal.c_str(), "%f", &val);
            SceneryType[selectionEntityIndex].offsetX = val;
        }
        else if(event.GetRow() == 5) {
            if(newVal.empty()) {event.Veto(); return;}
            float val = 0.f;
            sscanf(newVal.c_str(), "%f", &val);
            SceneryType[selectionEntityIndex].offsetY = val;
        }
        else if(event.GetRow() == 6) {
            if(newVal.empty()) SceneryType[selectionEntityIndex].isPassable = false;
            else SceneryType[selectionEntityIndex].isPassable = true;
        }
        else if(event.GetRow() == 7) {
            if(newVal.empty()) SceneryType[selectionEntityIndex].isShootThroughAble = false;
            else SceneryType[selectionEntityIndex].isShootThroughAble = true;
        }
    }
    else if(selectionEntityType == ENTITY_TYPE_OBJECT_TYPE) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)ObjectType.size(),
                "Script index out of bounds.");
        if(event.GetRow() == 0) {
            if(newVal.empty()) {event.Veto(); return;}
            ObjectType[selectionEntityIndex].name = newVal;
        }
        else if(event.GetRow() == 1) {
            if(newVal.empty()) {event.Veto(); return;}
            ObjectType[selectionEntityIndex].resourcesName = newVal;
        }
        else if(event.GetRow() == 2) {
            if(newVal.empty()) {event.Veto(); return;}
            int val = -1;
            sscanf(newVal.c_str(), "%d", &val);
            if(val < 0 || val > 6) {event.Veto(); return;}
            ObjectType[selectionEntityIndex].baseType = val;
        }
        else if(event.GetRow() == 3) {
            if(newVal.empty()) {event.Veto(); return;}
            int val = -1;
            sscanf(newVal.c_str(), "%d", &val);
            if(val < 0 || val > 3) {event.Veto(); return;}
            ObjectType[selectionEntityIndex].weaponType = val;
        }
        else if(event.GetRow() == 4) {
            if(newVal.empty()) {event.Veto(); return;}
            int val = -1;
            sscanf(newVal.c_str(), "%d", &val);
            if(val < 0 || val > 4) {event.Veto(); return;}
            ObjectType[selectionEntityIndex].equipmentType = val;
        }
        else if(event.GetRow() == 5) {
            if(newVal.empty()) {event.Veto(); return;}
            int val = -1;
            sscanf(newVal.c_str(), "%d", &val);
            if(val < 0 || val > 3) {event.Veto(); return;}
            ObjectType[selectionEntityIndex].attachmentType = val;
        }
        else if(event.GetRow() == 6) {
            if(newVal.empty()) {event.Veto(); return;}
            int val = -1;
            sscanf(newVal.c_str(), "%d", &val);
            if(val < 0 || val > 2) {event.Veto(); return;}
            ObjectType[selectionEntityIndex].layer = val;
        }
        else if(event.GetRow() == 7) {
            if(newVal.empty()) {event.Veto(); return;}
            float val = 0.f;
            sscanf(newVal.c_str(), "%f", &val);
            ObjectType[selectionEntityIndex].offsetX = val;
        }
        else if(event.GetRow() == 8) {
            if(newVal.empty()) {event.Veto(); return;}
            float val = 0.f;
            sscanf(newVal.c_str(), "%f", &val);
            ObjectType[selectionEntityIndex].offsetY = val;
        }
        else if(event.GetRow() == 9) {
            if(newVal.empty()) {event.Veto(); return;}
            float val = 0.f;
            sscanf(newVal.c_str(), "%f", &val);
            ObjectType[selectionEntityIndex].spriteScale = val;
        }
        else if(event.GetRow() == 10) {
            if(newVal.empty()) ObjectType[selectionEntityIndex].isPassable = false;
            else ObjectType[selectionEntityIndex].isPassable = true;
        }
        else if(event.GetRow() == 11) {
            if(newVal.empty()) ObjectType[selectionEntityIndex].isShootThroughAble = false;
            else ObjectType[selectionEntityIndex].isShootThroughAble = true;
        }
        else if(event.GetRow() == 12) {
            if(newVal.empty()) ObjectType[selectionEntityIndex].isAutomatic = false;
            else ObjectType[selectionEntityIndex].isAutomatic = true;
        }
        else if(event.GetRow() == 13) {
            if(newVal.empty()) {event.Veto(); return;}
            int val = -1;
            sscanf(newVal.c_str(), "%d", &val);
            if(val < 0 || val > 1000) {event.Veto(); return;}
            ObjectType[selectionEntityIndex].baseDamage = val;
        }
        else if(event.GetRow() == 14) {
            if(newVal.empty()) {event.Veto(); return;}
            int val = -1;
            sscanf(newVal.c_str(), "%d", &val);
            if(val < 0 || val > 10000) {event.Veto(); return;}
            ObjectType[selectionEntityIndex].baseShotDelay = val;
        }
        else if(event.GetRow() == 15) {
            if(newVal.empty()) {event.Veto(); return;}
            int val = -1;
            sscanf(newVal.c_str(), "%d", &val);
            if(val < 0 || val > 1000000) {event.Veto(); return;}
            ObjectType[selectionEntityIndex].value = val;
        }
    }
    else if(selectionEntityType == ENTITY_TYPE_SCRIPT) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)Script.size(),
                "Script index out of bounds.");
        if(event.GetRow() == 0) {
            if(newVal.empty()) {
                event.Veto();
                return;
            }
            bool isOk = true;
            for(size_t i=0; i<Script.size(); ++i) {
                if(Script[i].IDName == newVal) {
                    isOk = false;
                    break;
                }
            }
            if(isOk) {
                Script[selectionEntityIndex].IDName = newVal;
                wxScriptsListBox->SetString(selectionListBoxSelectionIndex, newVal);
                updateErrorLog();
            }
            else event.Veto();
        }
    }
    else if(selectionEntityType == ENTITY_TYPE_QUEST) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)Quest.size(),
                "Quest index out of bounds.");
        if(event.GetRow() == 0) {
            if(newVal.empty()) {
                event.Veto();
                return;
            }
            bool isOk = true;
            for(size_t i=0; i<Quest.size(); ++i) {
                if(Quest[i].IDName == newVal) {
                    isOk = false;
                    break;
                }
            }
            if(isOk) {
                Quest[selectionEntityIndex].IDName = newVal;
                wxQuestsListBox->SetString(selectionListBoxSelectionIndex, newVal);
                updateErrorLog();
            }
            else event.Veto();
        }
        else if(event.GetRow() == 1) {
            if(newVal.empty()) {
                event.Veto();
                return;
            }
            Quest[selectionEntityIndex].name = newVal;
        }
        else if(event.GetRow() == 2) {
            if(newVal.empty()) {event.Veto(); return;}
            int val = -1;
            sscanf(newVal.c_str(), "%d", &val);
            if(val < 0 || val > 2) {event.Veto(); return;}
            Quest[selectionEntityIndex].questType = val;
        }
    }
    else if(selectionEntityType == ENTITY_TYPE_TEXT) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)Text.size(),
                "Text index out of bounds.");
    }
    else if(selectionEntityType == ENTITY_TYPE_NPC) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)NPC.size(),
                "NPC index out of bounds.");

        if(event.GetRow() == 0) {
            if(newVal.empty()) NPC[selectionEntityIndex].AI_staticDirection = false;
            else NPC[selectionEntityIndex].AI_staticDirection = true;
        }
        else if(event.GetRow() == 1) {
            if(newVal.empty()) {event.Veto(); return;}
            int val = -1;
            sscanf(newVal.c_str(), "%d", &val);
            if(val < 0 || val > 2) {event.Veto(); return;}
            NPC[selectionEntityIndex].AI_movementType = val;
        }
        else if(event.GetRow() == 2) {
            if(newVal.empty()) {event.Veto(); return;}
            int val = -1;
            sscanf(newVal.c_str(), "%d", &val);
            if(val < 0 || val > 10000) {event.Veto(); return;}
            NPC[selectionEntityIndex].AI_movementDistance = val;
        }
    }
}

void UtilityModule::updateErrorLog()
{
    wxErrorLogEditBox->SetLabel("");
    compileAndVerifyAllScripts();
    if(wxErrorLogEditBox->GetLabel().empty()) {
        wxErrorLogEditBox->SetLabel("No errors");
    }
}

void UtilityModule::removeTileType(int index)
{
    _assert(index >= 0 && index < (int)TileType.size(),
            "Tile type index out of bounds in removeTileType.");
    TileType[index].isLoaded = false;
    for(size_t i=0; i<Tile.size(); ++i) {
        for(size_t j=0; j<Tile[i].size(); ++j) {
            if(Tile[i][j].tileType == index) {
                Tile[i][j].tileType = -1;
            }
        }
    }
}

void UtilityModule::removeSceneryType(int index)
{
    _assert(index >= 0 && index < (int)SceneryType.size(),
            "Scenery type index out of bounds in removeSceneryType.");
    SceneryType[index].isLoaded = false;
    for(size_t i=0; i<Tile.size(); ++i) {
        for(size_t j=0; j<Tile[i].size(); ++j) {
            if(Tile[i][j].sceneryType == index) {
                Tile[i][j].sceneryType = -1;
            }
        }
    }
}

void UtilityModule::removeObjectType(int index)
{
    _assert(index >= 0 && index < (int)ObjectType.size(),
            "Object type index out of bounds in removeObjectType.");
    ObjectType[index].isLoaded = false;
    for(size_t i=0; i<Tile.size(); ++i) {
        for(size_t j=0; j<Tile[i].size(); ++j) {
            for(std::list <ObjectClass>::iterator it=Tile[i][j].object.begin(); it!=Tile[i][j].object.end();) {
                if(it->type == index) {
                    it = Tile[i][j].object.erase(it);
                }
                else ++it;
            }
        }
    }
    for(size_t i=0; i<Player.size(); ++i) {

    }
    for(size_t i=0; i<NPC.size(); ++i) {

    }
    for(size_t i=0; i<NPCType.size(); ++i) {

    }
}

void UtilityModule::removeNPCType(int index)
{
    //todo
}

void UtilityModule::resetEntityPreferencesGrid()
{
    wxEntityText->SetLabel("None");
    if(wxEntityGrid->GetNumberRows()) {
        wxEntityGrid->DeleteRows(0, wxEntityGrid->GetNumberRows());
    }
}

void UtilityModule::validateNPCMovementCheckpoints(const std::vector <CharacterClass> &NPC)
{
    for(size_t i=0; i<NPC.size(); ++i) {
        for(size_t j=0; j<NPC[i].AI_movementCheckpoint.size(); ++j) {
            if(isOutOfMap(NPC[i].AI_movementCheckpoint[j].x, NPC[i].AI_movementCheckpoint[j].y)) {
                error("NPC (%d) movement checkpoint position (%d, %d) is out of map in validateNPCMovementCheckpoints.",
                      i, NPC[i].AI_movementCheckpoint[j].x, NPC[i].AI_movementCheckpoint[j].y);
            }
        }
    }
}

void UtilityModule::changeNPCMovementCheckpoint(int NPCIndex, int checkpointIndex)
{
    _assert(NPCIndex >= 0 && NPCIndex < (int)NPC.size(),
            "NPC index out of bounds in addNPCMovementCheckpoint.");
    _assert(checkpointIndex >= 0,
            "Negative checkpoint index in addNPCMovementCheckpoint.");

    float currX = NPC[NPCIndex].x;
    float currY = NPC[NPCIndex].y;
    if(!NPC[NPCIndex].AI_movementCheckpoint.empty()) {
        currX = NPC[NPCIndex].AI_movementCheckpoint.back().x*TILE_SIZE+TILE_SIZE/2.f;
        currY = NPC[NPCIndex].AI_movementCheckpoint.back().y*TILE_SIZE+TILE_SIZE/2.f;
    }
    vPoint pos = getWorldPosition(mx, my, View);
    int checkpointsQuantity = (int)NPC[NPCIndex].AI_movementCheckpoint.size();
    float dist = getDistance(currX, currY, pos.x, pos.y);
    float angle = atan2(pos.y-currY, pos.x-currX);

    for(int i=0; i<checkpointIndex-checkpointsQuantity; ++i) {
        currX += dist/(checkpointIndex-checkpointsQuantity+1)*cos(angle);
        currY += dist/(checkpointIndex-checkpointsQuantity+1)*sin(angle);
        if(!isOutOfMap(currX/TILE_SIZE, currY/TILE_SIZE) && currX >= 0.f && currY >= 0.f) {
            NPC[NPCIndex].AI_movementCheckpoint.push_back(TilePositionClass(currX/TILE_SIZE, currY/TILE_SIZE));
        }
    }
    if(!isOutOfMap(pos.x/TILE_SIZE, pos.y/TILE_SIZE) && pos.x >= 0.f && pos.y >= 0.f) {
        if(checkpointIndex >= NPC[NPCIndex].AI_movementCheckpoint.size()) {
            NPC[NPCIndex].AI_movementCheckpoint.push_back(TilePositionClass(pos.x/TILE_SIZE, pos.y/TILE_SIZE));
        }
        else {
            NPC[NPCIndex].AI_movementCheckpoint[checkpointIndex].x = pos.x/TILE_SIZE;
            NPC[NPCIndex].AI_movementCheckpoint[checkpointIndex].y = pos.y/TILE_SIZE;
        }
    }
    printf("ADDED\n");
}
