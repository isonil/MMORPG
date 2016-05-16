#include "DataModule.hpp"

#include <sstream>
#include <stack>

int DataModule::getScriptIDByIDName(const std::string &IDName)
{
    for(size_t i=0; i<Script.size(); ++i) {
        if(Script[i].isLoaded && Script[i].IDName == IDName) return i;
    }
    return -1;
}

int DataModule::getQuestIDByIDName(const std::string &IDName)
{
    for(size_t i=0; i<Quest.size(); ++i) {
        if(Quest[i].isLoaded && Quest[i].IDName == IDName) return i;
    }
    return -1;
}

void DataModule::loadMap(const std::string &path)
{
    Tile.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load map file '%s'.", path.c_str());
    }
    int w = 0, h = 0;
    in >> w >> h;
    if(w <= 0 || h <= 0) error("Map size is too small.");
    if(w > 10000 || h > 10000) error("Map is too large (max 10000 x 10000).");

    info("Allocating map, size: %d MiB.", ((int)sizeof(TileClass)*w*h)/(1024*1024));
    Tile.resize(w);
    for(int i=0; i<w; ++i) {
        Tile[i].resize(h);
    }

    for(int i=0; i<h; ++i) {
        for(int j=0; j<w; ++j) {
            int newTileType = -1, newSceneryType = -1;
            in >> newTileType >> newSceneryType;
            if(newTileType >= 0 && (newTileType < 0 || newTileType >= (int)TileType.size())) {
                error("Tile type out of bounds in LoadMap.");
            }
            if(newSceneryType >= 0 && (newSceneryType < 0 || newSceneryType >= (int)SceneryType.size())) {
                error("Scenery type out of bounds in LoadMap.");
            }
            Tile[j][i].tileType = newTileType;
            Tile[j][i].sceneryType = newSceneryType;
        }
    }
    in.close();
}

void DataModule::loadNPCTypes(const std::string &path, const std::string &NPCTypesPath)
{
    NPCType.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load NPC types file '%s'.", path.c_str());
    }

    int newIndex;

    while(in >> newIndex) {
        if(newIndex < 0) continue;
        if(newIndex >= (int)NPCType.size()) NPCType.resize(newIndex+1);

        std::ostringstream oss;
        oss << NPCTypesPath << newIndex;
        std::string path2 = oss.str();
        std::ifstream in2(path2.c_str());
        if(!in2) {
            error("Could not load NPC type file '%s'.", path2.c_str());
        }

        std::string tag, line;
        int lineNumber = 0;
        int currentDialogueBlock = -1;

        while(std::getline(in2, tag)) {
            ++lineNumber;
            util::clamp_ws(tag);
            if(tag.empty()) continue;
            if(tag[0] != '(' || tag[tag.size()-1] != ')')
                error("Parse error in NPC type file '%s' line %d: Expected a tag.", path2.c_str(), lineNumber);
            if(tag != "(Params)" && tag != "(Slots)" && tag != "(Movement)" && tag != "(Loot)" && tag != "(Trade)" && tag != "(Dialogue)")
                error("Parse error in NPC type file '%s' line %d: Unknown tag '%s'.", path2.c_str(), lineNumber, tag.c_str());

            bool endedCorrectly = false;
            while(std::getline(in2, line)) {
                ++lineNumber;
                util::clamp_ws(line);
                if(line.empty()) continue;
                if(line[0] == ';') {
                    if(line.size() > 1) error("Parse error in NPC type file '%s' line %d: Extra characters after ';'.", path2.c_str(), lineNumber);
                    endedCorrectly = true;
                    break;
                }
                else if(line[line.size()-1] == ';') {
                    error("Parse error in NPC type file '%s' line %d: Extra characters before ';'.", path2.c_str(), lineNumber);
                }
                else if(line[0] == '(' && line[line.size()-1] == ')') error("Parse error in NPC type file '%s' line %d: Missing ';'.", path2.c_str(), lineNumber);

                std::istringstream line_iss(line);
                if(tag == "(Params)") {
                    std::string param;
                    line_iss >> param;
                    if(param == "Name") {
                        std::string name;
                        line_iss >> name;
                        if(name.empty()) {
                            error("Parse error in NPC type file '%s' line %d: Missing value.", path2.c_str(), lineNumber);
                        }
                        NPCType[newIndex].name = name;
                    }
                    else if(param == "Team") {
                        int team = -1;
                        line_iss >> team;
                        if(team < 0) {
                            error("Parse error in NPC type file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                        }
                        NPCType[newIndex].team = team;
                    }
                    else if(param == "MaxHealth") {
                        int maxHealth = -1;
                        line_iss >> maxHealth;
                        if(maxHealth < 0) {
                            error("Parse error in NPC type file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                        }
                        NPCType[newIndex].maxHealth = maxHealth;
                    }
                    else {
                        error("Parse error in NPC type file '%s' line %d: Unknown param '%s'.", path2.c_str(), lineNumber, param.c_str());
                    }
                }
                else if(tag == "(Slots)") {
                    int slot = -1, object = -1;
                    line_iss >> slot >> object;
                    if(slot < 0 || object < 0) {
                        error("Parse error in NPC type file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                    }
                    if(slot >= CHARACTER_OBJECT_SLOTS_QUANTITY) {
                        error("Parse error in NPC type file '%s' line %d: Slot index out of bounds.", path2.c_str(), lineNumber);
                    }
                    if(object >= (int)ObjectType.size()) {
                        error("Parse error in NPC type file '%s' line %d: Object type out of bounds.", path2.c_str(), lineNumber);
                    }
                    NPCType[newIndex].objectTypeOnSlot[slot] = object;
                }
                else if(tag == "(Movement)") {
                    // deprecated

                    /*
                    std::string key;
                    line_iss >> key;
                    if(key == "StaticDirection") {
                        NPCType[newIndex].AI_staticDirection = true;
                    }
                    else if(key == "RandomInRadius") {
                        int radius = -1;
                        line_iss >> radius;
                        if(radius < 0) {
                            error("Parse error in NPC type file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                        }
                    }
                    else {
                        error("Parse error in NPC type file '%s' line %d: Unknown movement key '%s'.", path2.c_str(), lineNumber, key.c_str());
                    }
                    */
                }
                else if(tag == "(Loot)") {
                    int object = -1, quantityFrom = -1, quantityTo = -1, chance = -1;
                    line_iss >> object >> quantityFrom >> quantityTo >> chance;
                    if(object < 0 || quantityFrom < 0 || quantityTo < 0 || chance < 0) {
                        error("Parse error in NPC type file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                    }
                    if(object >= (int)ObjectType.size()) {
                        error("Parse error in NPC type file '%s' line %d: Object type out of bounds.", path2.c_str(), lineNumber);
                    }
                    NPCType[newIndex].lootObject.push_back(NPCTypeClass::LootObjectClass(object, quantityFrom, quantityTo, chance));
                }
                else if(tag == "(Trade)") {
                    int object = -1;
                    line_iss >> object;
                    if(object < 0) {
                        error("Parse error in NPC type file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                    }
                    if(object >= (int)ObjectType.size()) {
                        error("Parse error in NPC type file '%s' line %d: Object type out of bounds.", path2.c_str(), lineNumber);
                    }
                    NPCType[newIndex].tradeObject.push_back(NPCTypeClass::TradeObjectClass(object));
                }
                else if(tag == "(Dialogue)") {
                    std::string key;
                    line_iss >> key;
                    if(key == "Block") {
                        int block = -1;
                        line_iss >> block;
                        if(block < 0) {
                            error("Parse error in NPC type file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                        }
                        currentDialogueBlock = block;
                        if(block >= (int)NPCType[newIndex].dialogueBlock.size()) {
                            NPCType[newIndex].dialogueBlock.resize(block+1);
                        }
                    }
                    else if(key == "NPCText") {
                        if(currentDialogueBlock < 0) {
                            error("Parse error in NPC type file '%s' line %d: No dialogue block specified.", path2.c_str(), lineNumber);
                        }
                        int textIndex = -1;
                        line_iss >> textIndex;
                        if(textIndex < 0) {
                            error("Parse error in NPC type file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                        }
                        NPCType[newIndex].dialogueBlock[currentDialogueBlock].NPCTextIndex = textIndex;
                    }
                    else if(key == "RunScript") {
                        if(currentDialogueBlock < 0) {
                            error("Parse error in NPC type file '%s' line %d: No dialogue block specified.", path2.c_str(), lineNumber);
                        }
                        int scriptIndex=-1;
                        line_iss >> scriptIndex;
                        if(scriptIndex < 0) {
                            error("Parse error in NPC type file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                        }
                        if(scriptIndex >= (int)Script.size()) {
                            error("Parse error in NPC type file '%s' line %d: Script id out of bounds.", path2.c_str(), lineNumber);
                        }
                        NPCType[newIndex].dialogueBlock[currentDialogueBlock].scriptIndex = scriptIndex;
                    }
                    else if(key == "Option") {
                        if(currentDialogueBlock < 0) {
                            error("Parse error in NPC type file '%s' line %d: No dialogue block specified.", path2.c_str(), lineNumber);
                        }
                        int requiredQuestProgressIndex = -1;
                        int requiredQuestProgressFrom = -1;
                        int requiredQuestProgressTo = -1;
                        int textIndex = -1;
                        std::string leadToBlockStr;
                        line_iss >> requiredQuestProgressIndex >> requiredQuestProgressFrom >> requiredQuestProgressTo >> textIndex >> leadToBlockStr;
                        if(textIndex < 0 || leadToBlockStr.empty()) {
                            error("Parse error in NPC type file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                        }
                        if(requiredQuestProgressIndex >= 0) {
                            if(requiredQuestProgressIndex >= (int)Quest.size()) {
                                error("Parse error in NPC type file '%s' line %d: Quest index out of bounds.", path2.c_str(), lineNumber);
                            }
                            if(requiredQuestProgressFrom < 0 || requiredQuestProgressTo < 0 ||
                               requiredQuestProgressFrom > 100 || requiredQuestProgressTo > 100) {
                                error("Parse error in NPC type file '%s' line %d: Incorrect or missing quest progress value.", path2.c_str(), lineNumber);
                            }
                        }
                        NPCType[newIndex].dialogueBlock[currentDialogueBlock].option.push_back(NPCTypeClass::DialogueBlockClass::OptionClass());
                        NPCType[newIndex].dialogueBlock[currentDialogueBlock].option.back().requiredQuestProgressIndex = requiredQuestProgressIndex;
                        NPCType[newIndex].dialogueBlock[currentDialogueBlock].option.back().requiredQuestProgressFrom = requiredQuestProgressFrom;
                        NPCType[newIndex].dialogueBlock[currentDialogueBlock].option.back().requiredQuestProgressTo = requiredQuestProgressTo;
                        NPCType[newIndex].dialogueBlock[currentDialogueBlock].option.back().textIndex = textIndex;
                        if(leadToBlockStr == "trade") {
                            NPCType[newIndex].dialogueBlock[currentDialogueBlock].option.back().leadToBlock = -1;
                            NPCType[newIndex].dialogueBlock[currentDialogueBlock].option.back().startTrade = true;
                        }
                        else {
                            int leadToBlock = -1;
                            sscanf(leadToBlockStr.c_str(), "%d", &leadToBlock);
                            NPCType[newIndex].dialogueBlock[currentDialogueBlock].option.back().leadToBlock = leadToBlock;
                        }
                    }
                    else {
                        error("Parse error in NPC type file '%s' line %d: Unknown dialogue key '%s'.", path2.c_str(), lineNumber, key.c_str());
                    }
                }
            }
            if(!endedCorrectly) error("Parse error in NPC type file '%s' line %d: Unexpected end of file - missing ';'.", path2.c_str(), lineNumber);
        }
        in2.close();
    }
    in.close();

    for(size_t i=0; i<NPCType.size(); ++i) {
        for(size_t j=0; j<NPCType[i].dialogueBlock.size(); ++j) {
            for(size_t k=0; k<NPCType[i].dialogueBlock[j].option.size(); ++k) {
                if(NPCType[i].dialogueBlock[j].option[k].leadToBlock >= (int)NPCType[i].dialogueBlock.size()) {
                    error("Dialogue option %d (indexed from 0) in dialogueBlock %d in NPCType %d leads out of bounds (%d).", k, j, i, NPCType[i].dialogueBlock[j].option[k].leadToBlock);
                }
            }
        }
    }
}

void DataModule::loadNPCs(const std::string &path)
{
    NPC.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load NPCs file '%s'.", path.c_str());
    }

    int newNPCType = -1;
    float newX, newY, newDir;
    int newAI_staticDirection;
    std::string newAI_movementType;
    int newAI_movementDistance;

    while(in >> newNPCType >> newX >> newY >> newDir >> newAI_staticDirection >> newAI_movementType >> newAI_movementDistance) {
        NPC.push_back(CharacterClass());
        if(newNPCType < 0 || newNPCType >= (int)NPCType.size()) error("NPC type out of bounds (%d) in '%s'.", newNPCType, path.c_str());
        NPC.back().NPCType = newNPCType;
        NPC.back().name = NPCType[newNPCType].name;
        NPC.back().team = NPCType[newNPCType].team;
        NPC.back().param[CHARACTER_PARAM_MAX_HEALTH] = NPCType[newNPCType].maxHealth;
        NPC.back().param[CHARACTER_PARAM_HEALTH] = NPCType[newNPCType].maxHealth;
        NPC.back().x = newX;
        NPC.back().y = newY;
        NPC.back().respawn_x = newX;
        NPC.back().respawn_y = newY;
        NPC.back().dir = newDir;
        NPC.back().respawn_dir = NPC.back().dir;
        NPC.back().AI_staticDirection = newAI_staticDirection;

        if(newAI_movementType == "AI_MOVEMENT_TYPE_STAND") NPC.back().AI_movementType = AI_MOVEMENT_TYPE_STAND;
        else if(newAI_movementType == "AI_MOVEMENT_TYPE_MOVE_BY_CHECKPOINTS") NPC.back().AI_movementType = AI_MOVEMENT_TYPE_MOVE_BY_CHECKPOINTS;
        else if(newAI_movementType == "AI_MOVEMENT_TYPE_MOVE_BY_DISTANCE") NPC.back().AI_movementType = AI_MOVEMENT_TYPE_MOVE_BY_DISTANCE;
        else error("Unknown AI movement type in '%s'.", path.c_str());

        NPC.back().AI_movementDistance = newAI_movementDistance;

        std::string checkpointsStr;
        getline(in, checkpointsStr);
        std::vector <int> checkpointsVec;
        checkpointsVec = util::getNumbers(checkpointsStr, path.c_str());
        if(checkpointsVec.size()%2) error("Missing checkpoint position value in '%s'.", path.c_str());
        for(size_t i=0; i<checkpointsVec.size(); i+=2) {
            NPC.back().AI_movementCheckpoint.push_back(TilePositionClass(checkpointsVec[i], checkpointsVec[i+1]));
        }

        for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
            NPC.back().objectOnSlot[i].type = NPCType[newNPCType].objectTypeOnSlot[i];
            if(NPC.back().objectOnSlot[i].type < 0) continue;
            if(NPC.back().objectOnSlot[i].type >= (int)ObjectType.size()) {
                error("NPC slot object type out of bounds (%d) in '%s'.", NPC.back().objectOnSlot[i].type, path.c_str());
            }
            if(ObjectType[NPC.back().objectOnSlot[i].type].baseType != objectSlot[i].baseType) {
                error("NPC slot object base type does not match required base type in '%s'.", path.c_str());
            }
            if(ObjectType[NPC.back().objectOnSlot[i].type].baseType == OBJECT_BASE_TYPE_EQUIPMENT) {
                if(ObjectType[NPC.back().objectOnSlot[i].type].equipmentType != objectSlot[i].equipmentType) {
                    error("NPC slot object equipment type does not match required equipment type in '%s'.", path.c_str());
                }
            }
        }
    }
    in.close();
}

void DataModule::loadObjectTypes(const std::string &path)
{
    ObjectType.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load object types file '%s'.", path.c_str());
    }

    std::string newIDName, newName, newBaseType, newWeaponType, newEquipmentType, newAttachmentType;
    int newIndex, newIsPassable, newIsShootThroughAble, newIsAutomatic, newIsStackable, newBaseDamage, newBaseShotDelay, newValue;

    while(in >> newIndex >> newIDName >> newName >> newBaseType >> newWeaponType >> newEquipmentType >> newAttachmentType >> newIsPassable >> newIsShootThroughAble >> newIsAutomatic >> newIsStackable >> newBaseDamage >> newBaseShotDelay >> newValue) {
        if(newIndex < 0) continue;
        if(newIndex >= (int)ObjectType.size()) ObjectType.resize(newIndex+1);

        if(newBaseType == "OBJECT_BASE_TYPE_NONE") ObjectType[newIndex].baseType = OBJECT_BASE_TYPE_NONE;
        else if(newBaseType == "OBJECT_BASE_TYPE_WEAPON") ObjectType[newIndex].baseType = OBJECT_BASE_TYPE_WEAPON;
        else if(newBaseType == "OBJECT_BASE_TYPE_EQUIPMENT") ObjectType[newIndex].baseType = OBJECT_BASE_TYPE_EQUIPMENT;
        else if(newBaseType == "OBJECT_BASE_TYPE_STRUCTURE") ObjectType[newIndex].baseType = OBJECT_BASE_TYPE_STRUCTURE;
        else if(newBaseType == "OBJECT_BASE_TYPE_ADDON") ObjectType[newIndex].baseType = OBJECT_BASE_TYPE_ADDON;
        else if(newBaseType == "OBJECT_BASE_TYPE_MISC") ObjectType[newIndex].baseType = OBJECT_BASE_TYPE_MISC;
        else if(newBaseType == "OBJECT_BASE_TYPE_AMMUNITION") ObjectType[newIndex].baseType = OBJECT_BASE_TYPE_AMMUNITION;
        else {
            error("Unknown object base type '%s' (in '%s').", newBaseType.c_str(), path.c_str());
        }
        if(newWeaponType == "WEAPON_TYPE_NONE") ObjectType[newIndex].weaponType = WEAPON_TYPE_NONE;
        else if(newWeaponType == "WEAPON_TYPE_SMALL_GUN") ObjectType[newIndex].weaponType = WEAPON_TYPE_SMALL_GUN;
        else if(newWeaponType == "WEAPON_TYPE_BIG_GUN") ObjectType[newIndex].weaponType = WEAPON_TYPE_BIG_GUN;
        else if(newWeaponType == "WEAPON_TYPE_ROCKET_LAUNCHER") ObjectType[newIndex].weaponType = WEAPON_TYPE_ROCKET_LAUNCHER;
        else {
            error("Unknown weapon type '%s' (in '%s').", newWeaponType.c_str(), path.c_str());
        }
        if(newEquipmentType == "EQUIPMENT_TYPE_NONE") ObjectType[newIndex].equipmentType = EQUIPMENT_TYPE_NONE;
        else if(newEquipmentType == "EQUIPMENT_TYPE_HELMET") ObjectType[newIndex].equipmentType = EQUIPMENT_TYPE_HELMET;
        else if(newEquipmentType == "EQUIPMENT_TYPE_VEST") ObjectType[newIndex].equipmentType = EQUIPMENT_TYPE_VEST;
        else if(newEquipmentType == "EQUIPMENT_TYPE_BOOTS") ObjectType[newIndex].equipmentType = EQUIPMENT_TYPE_BOOTS;
        else if(newEquipmentType == "EQUIPMENT_TYPE_GLOVES") ObjectType[newIndex].equipmentType = EQUIPMENT_TYPE_GLOVES;
        else {
            error("Unknown equipment type '%s' (in '%s').", newEquipmentType.c_str(), path.c_str());
        }
        if(newAttachmentType == "ATTACHMENT_TYPE_NONE") ObjectType[newIndex].attachmentType = ATTACHMENT_TYPE_NONE;
        else if(newAttachmentType == "ATTACHMENT_TYPE_SIGHT") ObjectType[newIndex].attachmentType = ATTACHMENT_TYPE_SIGHT;
        else if(newAttachmentType == "ATTACHMENT_TYPE_BARREL") ObjectType[newIndex].attachmentType = ATTACHMENT_TYPE_BARREL;
        else if(newAttachmentType == "ATTACHMENT_TYPE_MISC") ObjectType[newIndex].attachmentType = ATTACHMENT_TYPE_MISC;
        else {
            error("Unknown attachment type '%s' (in '%s').", newAttachmentType.c_str(), path.c_str());
        }
        ObjectType[newIndex].name = newName;
        ObjectType[newIndex].IDName = newIDName;
        ObjectType[newIndex].isPassable = (bool)newIsPassable;
        ObjectType[newIndex].isShootThroughAble = (bool)newIsShootThroughAble;
        ObjectType[newIndex].isAutomatic = (bool)newIsAutomatic;
        ObjectType[newIndex].isStackable = (bool)newIsStackable;
        ObjectType[newIndex].baseDamage = newBaseDamage;
        ObjectType[newIndex].isAutomatic = newIsAutomatic;
        ObjectType[newIndex].baseShotDelay = newBaseShotDelay;
        ObjectType[newIndex].value = newValue;
    }
    in.close();
}

void DataModule::loadQuests(const std::string &path)
{
    Quest.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load quests file '%s'.", path.c_str());
    }
    int newIndex;
    std::string newIDName, newName;
    while(in >> newIndex >> newIDName >> newName) {
        if(newIndex < 0) continue;
        if(newIndex >= (int)Quest.size()) Quest.resize(newIndex+1);
        Quest[newIndex].name = newName;
        Quest[newIndex].IDName = newIDName;
        Quest[newIndex].isLoaded = true;
    }
    in.close();
}

void DataModule::loadSceneryTypes(const std::string &path)
{
    SceneryType.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load scenery types file '%s'.", path.c_str());
    }
    std::string newName;
    int newIndex, newIsPassable, newIsShootThroughAble;
    while(in >> newName >> newIndex >> newIsPassable >> newIsShootThroughAble) {
        if(newIndex < 0) continue;
        if(newIndex >= (int)SceneryType.size()) SceneryType.resize(newIndex+1);

        SceneryType[newIndex].name = newName;
        SceneryType[newIndex].isPassable = newIsPassable;
        SceneryType[newIndex].isShootThroughAble = newIsShootThroughAble;
    }
    in.close();
}

void DataModule::loadScripts(const std::string &path, const std::string &scriptsPath)
{
    Script.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load scripts file '%s'.", path.c_str());
    }

    int newIndex;
    std::string newIDName;

    while(in >> newIndex >> newIDName) {
        if(newIndex < 0) continue;
        if(newIndex >= (int)Script.size()) Script.resize(newIndex+1);

        Script[newIndex].IDName = newIDName;
        Script[newIndex].isLoaded = true;
        std::ostringstream oss;
        oss << scriptsPath << newIndex;
        std::string path2 = oss.str();
        std::ifstream in2(path2.c_str());
        if(!in2) {
            error("Could not load script file '%s'.", path2.c_str());
        }
        std::string line, instruction;
        int lineNumber = 0;
        std::stack <int> ifStatementInstructionIndex;
        while(std::getline(in2, line)) {
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
                Script[newIndex].instruction.push_back(ScriptClass::InstructionClass());
                Script[newIndex].instruction.back().ifStatement = true;
                ifStatementInstructionIndex.push(Script[newIndex].instruction.size()-1);
                std::string ifFunc;
                line_iss >> ifFunc;
                if(ifFunc.empty()) {
                    error("Parse error in script file '%s' line %d: If statement with no condition.", path2.c_str(), lineNumber);
                }
                if(ifFunc == "QuestProgress") {
                    int p1int = -1, p2int = -1, p3int = -1;
                    std::string questIDName;
                    line_iss >> questIDName >> p2int >> p3int;
                    p1int = getQuestIDByIDName(questIDName);
                    if(p1int < 0) {
                        error("Parse error in script file '%s' line %d: Quest '%s' not found.", path2.c_str(), lineNumber, questIDName.c_str());
                    }
                    if(p2int < 0 || p3int < 0 || p2int > 100 || p3int > 100) {
                        error("Parse error in script file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                    }
                    Script[newIndex].instruction.back().callFunc = SCRIPT_IF_FUNC_QUEST_PROGRESS;
                    Script[newIndex].instruction.back().p1int = p1int;
                    Script[newIndex].instruction.back().p2int = p2int;
                    Script[newIndex].instruction.back().p3int = p3int;
                }
                else {
                    error("Parse error in script file '%s' line %d: Unknown if statement function '%s'.", path2.c_str(), lineNumber, ifFunc.c_str());
                }
            }
            else if(instruction == "endif") {
                if(ifStatementInstructionIndex.empty()) {
                    error("Parse error in script file '%s' line %d: endif with no if statement.", path2.c_str(), lineNumber);
                }
                Script[newIndex].instruction[ifStatementInstructionIndex.top()].ifStatementJumpToInstruction = Script[newIndex].instruction.size();
                ifStatementInstructionIndex.pop();
            }
            else if(instruction == "AddExp") {
                int p1int = -1;
                line_iss >> p1int;
                if(p1int < 0) {
                    error("Parse error in script file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                }
                Script[newIndex].instruction.push_back(ScriptClass::InstructionClass());
                Script[newIndex].instruction.back().callFunc = SCRIPT_FUNC_ADD_EXP;
                Script[newIndex].instruction.back().p1int = p1int;
            }
            else if(instruction == "AddMoney") {
                int p1int = -1;
                line_iss >> p1int;
                if(p1int < 0) {
                    error("Parse error in script file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                }
                Script[newIndex].instruction.push_back(ScriptClass::InstructionClass());
                Script[newIndex].instruction.back().callFunc = SCRIPT_FUNC_ADD_MONEY;
                Script[newIndex].instruction.back().p1int = p1int;
            }
            else if(instruction == "SetQuestProgress") {
                int p1int = -1, p2int = -1;
                std::string questIDName;
                line_iss >> questIDName >> p2int;
                p1int = getQuestIDByIDName(questIDName);
                if(p1int < 0) {
                    error("Parse error in script file '%s' line %d: Quest '%s' not found.", path2.c_str(), lineNumber, questIDName.c_str());
                }
                if(p2int < 0 || p2int > 100) {
                    error("Parse error in script file '%s' line %d: Incorrect or missing value.", path2.c_str(), lineNumber);
                }
                Script[newIndex].instruction.push_back(ScriptClass::InstructionClass());
                Script[newIndex].instruction.back().callFunc = SCRIPT_FUNC_SET_QUEST_PROGRESS;
                Script[newIndex].instruction.back().p1int = p1int;
                Script[newIndex].instruction.back().p2int = p2int;
            }
            else if(instruction == "EndDialogue") {
                Script[newIndex].instruction.push_back(ScriptClass::InstructionClass());
                Script[newIndex].instruction.back().callFunc = SCRIPT_FUNC_END_DIALOGUE;
            }
            else {
                error("Parse error in script file '%s' line %d: Unknown instruction '%s'.", path2.c_str(), lineNumber, instruction.c_str());
            }
            if(!line_iss.eof()) {
                error("Parse error in script file '%s' line %d: Incorrect number of parameters.", path2.c_str(), lineNumber);
            }
        }
        if(!ifStatementInstructionIndex.empty()) {
            error("Parse error in script file '%s' line %d: Unexpected end of file - missing endif.", path2.c_str(), lineNumber);
        }
    }
    in.close();
}

void DataModule::loadTileTypes(const std::string &path)
{
    TileType.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load tile types file '%s'.", path.c_str());
    }
    std::string newName;
    int newIndex, newIsPassable, newIsShootThroughAble;
    while(in >> newName >> newIndex >> newIsPassable >> newIsShootThroughAble) {
        if(newIndex < 0) continue;
        if(newIndex >= (int)TileType.size()) TileType.resize(newIndex+1);

        TileType[newIndex].name = newName;
        TileType[newIndex].isPassable = newIsPassable;
        TileType[newIndex].isShootThroughAble = newIsShootThroughAble;
    }
    in.close();
}
