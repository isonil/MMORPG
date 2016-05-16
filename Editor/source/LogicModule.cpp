#include "LogicModule.hpp"
#include "../NPCTypeEditor.h"

void LogicModule::logicInterface()
{
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
       !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            View.y -= deltaTime*20.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            View.y += deltaTime*20.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            View.x -= deltaTime*20.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            View.x += deltaTime*20.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            View.y -= deltaTime*80.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            View.y += deltaTime*80.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
            View.x -= deltaTime*80.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            View.x += deltaTime*80.f;
        }
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(sf::Mouse::getPosition(window).x >= 0 && sf::Mouse::getPosition(window).x <= window.getSize().x &&
           sf::Mouse::getPosition(window).y >= 0 && sf::Mouse::getPosition(window).y <= window.getSize().y) {
            onClick(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        }
    }

    mx = sf::Mouse::getPosition(window).x;
    my = sf::Mouse::getPosition(window).y;
}

void LogicModule::onClick(int x, int y)
{
    vPoint pos = getWorldPosition(x, y, View);
    if(isOutOfMap(pos.x/TILE_SIZE, pos.y/TILE_SIZE) || pos.x < 0.f || pos.y < 0.f) return;

    if(selectionEntityType == ENTITY_TYPE_TILE_TYPE) {
        Tile[pos.x/TILE_SIZE][pos.y/TILE_SIZE].tileType = selectionEntityIndex;
    }
    else if(selectionEntityType == ENTITY_TYPE_SCENERY_TYPE) {
        Tile[pos.x/TILE_SIZE][pos.y/TILE_SIZE].sceneryType = selectionEntityIndex;
    }
    else if(selectionEntityType == ENTITY_TYPE_OBJECT_TYPE) {
        Tile[pos.x/TILE_SIZE][pos.y/TILE_SIZE].object.clear();
        Tile[pos.x/TILE_SIZE][pos.y/TILE_SIZE].object.resize(1);
        Tile[pos.x/TILE_SIZE][pos.y/TILE_SIZE].object.back().type = selectionEntityIndex;
    }
    else if(selectionEntityType == ENTITY_TYPE_NPC_TYPE) {
        bool deny = false;
        for(size_t i=0; i<NPC.size(); ++i) {
            if(getDistance(NPC[i].x, NPC[i].y, pos.x, pos.y) <= 2.f*CHARACTER_RADIUS) {
                deny = true;
                break;
            }
        }
        if(!deny) {
            NPC.resize(NPC.size()+1);
            NPC.back().NPCType = selectionEntityIndex;
            NPC.back().x = pos.x;
            NPC.back().y = pos.y;
        }
    }
    else if(selectionEntityType == ENTITY_TYPE_LIGHT_SOURCE_TYPE) {
        bool deny = false;
        for(size_t i=0; i<StaticLightSource.size(); ++i) {
            if(getDistance(StaticLightSource[i].x, StaticLightSource[i].y, pos.x, pos.y) <= 50.f) {
                deny = true;
                break;
            }
        }
        if(!deny) {
            StaticLightSource.push_back(LightSourceClass(pos.x, pos.y, selectionEntityIndex, sf::Vector3f(1.f, 1.f, 1.f)));
        }
    }
}

void LogicModule::onRClick(int x, int y)
{
    if(x >= (int)window.getSize().x-180 && y >= (int)window.getSize().y-180) {
        _assert(!Tile.empty() && !Tile[0].empty(), "Map is empty in onRClick.");
        View.x = ((float)x-((float)window.getSize().x-180.f))*Tile[0].size()*TILE_SIZE/180.f;
        View.y = ((float)y-((float)window.getSize().y-180.f))*Tile.size()*TILE_SIZE/180.f;
        return;
    }

    vPoint pos = getWorldPosition(x, y, View);
    if(isOutOfMap(pos.x/TILE_SIZE, pos.y/TILE_SIZE)) return;

    for(size_t i=0; i<NPC.size(); ++i) {
        if(getDistance(pos.x, pos.y, NPC[i].x, NPC[i].y) < CHARACTER_RADIUS) {
            selectionEntityType = ENTITY_TYPE_NPC;
            selectionEntityIndex = i;

            if(NPC[i].NPCType < 0) wxEntityText->SetLabel("NPC (no type)");
            else {
                _assert(NPC[i].NPCType < (int)NPCType.size(),
                        "NPC type out of bounds in onRClick");
                wxEntityText->SetLabel("NPC ("+NPCType[NPC[i].NPCType].name+")");
            }

            if(wxEntityGrid->GetNumberRows()) {
                wxEntityGrid->DeleteRows(0, wxEntityGrid->GetNumberRows());
            }
            wxEntityGrid->InsertRows(0, 3);
            for(int j=0; j<3; ++j) {
                wxEntityGrid->SetReadOnly(j, 0);
            }
            wxEntityGrid->SetCellValue(0, 0, _("AI_staticDirection"));
            wxEntityGrid->SetCellRenderer(0, 1, new wxGridCellBoolRenderer);
            wxEntityGrid->SetCellEditor(0, 1, new wxGridCellBoolEditor);
            wxEntityGrid->SetCellValue(0, 1, NPC[i].AI_staticDirection?"1":"");
            wxEntityGrid->SetCellValue(1, 0, _("AI_movementType"));
            wxEntityGrid->SetCellRenderer(1, 1, new wxGridCellNumberRenderer);
            wxEntityGrid->SetCellEditor(1, 1, new wxGridCellNumberEditor);
            wxEntityGrid->SetCellValue(1, 1, intToString(NPC[i].AI_movementType));
            wxEntityGrid->SetCellValue(2, 0, _("AI_movementDistance"));
            wxEntityGrid->SetCellRenderer(2, 1, new wxGridCellNumberRenderer);
            wxEntityGrid->SetCellEditor(2, 1, new wxGridCellNumberEditor);
            wxEntityGrid->SetCellValue(2, 1, intToString(NPC[i].AI_movementDistance));

            return;
        }
    }

    if(Tile[pos.x/TILE_SIZE][pos.y/TILE_SIZE].sceneryType >= 0) {
        selectionEntityType = ENTITY_TYPE_SCENERY;
        selectionEntityX = pos.x/TILE_SIZE;
        selectionEntityY = pos.y/TILE_SIZE;

        wxEntityText->SetLabel("Scenery preferences");
        if(wxEntityGrid->GetNumberRows()) {
            wxEntityGrid->DeleteRows(0, wxEntityGrid->GetNumberRows());
        }
    }
    else if(Tile[pos.x/TILE_SIZE][pos.y/TILE_SIZE].object.size()) {
        selectionEntityType = ENTITY_TYPE_OBJECT;
        selectionEntityX = pos.x/TILE_SIZE;
        selectionEntityY = pos.y/TILE_SIZE;

        wxEntityText->SetLabel("Object preferences");
        if(wxEntityGrid->GetNumberRows()) {
            wxEntityGrid->DeleteRows(0, wxEntityGrid->GetNumberRows());
        }
        wxEntityGrid->InsertRows(0, 1);
        for(int j=0; j<1; ++j) {
            wxEntityGrid->SetReadOnly(j, 0);
        }
        wxEntityGrid->SetCellValue(0, 0, _("test"));
    }
}

void LogicModule::onEntitySelectClick(int x, int y, bool doubleClick)
{
    if(wxEntitySelection1->GetSelection() == 0) {
        tileTypesClick(x, y);
    }
    else if(wxEntitySelection1->GetSelection() == 1) {
        sceneryTypesClick(x, y);
    }
    else if(wxEntitySelection1->GetSelection() == 2) {
        objectTypesClick(x, y);
    }
    else if(wxEntitySelection1->GetSelection() == 3) {
        NPCTypesClick(x, y, doubleClick);
    }
    else if(wxEntitySelection1->GetSelection() == 4) {
        lightSourceTypesClick(x, y);
    }
    else if(wxEntitySelection1->GetSelection() == 5) {
        triggersClick(x, y);
    }
    else if(wxEntitySelection1->GetSelection() == 6) {
        effectsClick(x, y);
    }
    else if(wxEntitySelection1->GetSelection() == 7) {
        zoneTypesClick(x, y);
    }
}

void LogicModule::tileTypesClick(int x, int y)
{
    int num = 0;
    for(size_t i=0; i<TileType.size(); ++i) {
        if(!TileType[i].isLoaded) continue;

        if(x >= (num%3)*55 && x < (num%3)*55+55 &&
           y >= (num/3)*55 && y < (num/3)*55+55) {
            selectionEntityType = ENTITY_TYPE_TILE_TYPE;
            selectionEntityIndex = i;

            wxEntityText->SetLabel("Tile type preferences");
            if(wxEntityGrid->GetNumberRows()) {
                wxEntityGrid->DeleteRows(0, wxEntityGrid->GetNumberRows());
            }
            wxEntityGrid->InsertRows(0, 4);
            for(int j=0; j<4; ++j) {
                wxEntityGrid->SetReadOnly(j, 0);
            }
            wxEntityGrid->SetCellValue(0, 0, _("name"));
            wxEntityGrid->SetCellValue(0, 1, TileType[i].name);
            wxEntityGrid->SetCellValue(1, 0, _("resourcesName"));
            wxEntityGrid->SetCellValue(1, 1, TileType[i].resourcesName);
            wxEntityGrid->SetCellValue(2, 0, _("isPassable"));
            wxEntityGrid->SetCellRenderer(2, 1, new wxGridCellBoolRenderer);
            wxEntityGrid->SetCellEditor(2, 1, new wxGridCellBoolEditor);
            wxEntityGrid->SetCellValue(2, 1, TileType[i].isPassable?"1":"");
            wxEntityGrid->SetCellValue(3, 0, _("isShootThroughAble"));
            wxEntityGrid->SetCellRenderer(3, 1, new wxGridCellBoolRenderer);
            wxEntityGrid->SetCellEditor(3, 1, new wxGridCellBoolEditor);
            wxEntityGrid->SetCellValue(3, 1, TileType[i].isShootThroughAble?"1":"");
            return;
        }
        ++num;
    }
}

void LogicModule::sceneryTypesClick(int x, int y)
{
    int num = 0;
    for(size_t i=0; i<SceneryType.size(); ++i) {
        if(!SceneryType[i].isLoaded) continue;

        if(x >= (num%3)*55 && x < (num%3)*55+55 &&
           y >= (num/3)*55 && y < (num/3)*55+55) {
            selectionEntityType = ENTITY_TYPE_SCENERY_TYPE;
            selectionEntityIndex = i;

            wxEntityText->SetLabel("Scenery type preferences");
            if(wxEntityGrid->GetNumberRows()) {
                wxEntityGrid->DeleteRows(0, wxEntityGrid->GetNumberRows());
            }
            wxEntityGrid->InsertRows(0, 8);
            for(int j=0; j<8; ++j) {
                wxEntityGrid->SetReadOnly(j, 0);
            }
            wxEntityGrid->SetCellValue(0, 0, _("name"));
            wxEntityGrid->SetCellValue(0, 1, SceneryType[i].name);
            wxEntityGrid->SetCellValue(1, 0, _("resourcesName"));
            wxEntityGrid->SetCellValue(1, 1, SceneryType[i].resourcesName);
            wxEntityGrid->SetCellValue(2, 0, _("natureType"));
            wxEntityGrid->SetCellRenderer(2, 1, new wxGridCellNumberRenderer);
            wxEntityGrid->SetCellEditor(2, 1, new wxGridCellNumberEditor);
            wxEntityGrid->SetCellValue(2, 1, intToString(SceneryType[i].natureType));
            wxEntityGrid->SetCellValue(3, 0, _("layer"));
            wxEntityGrid->SetCellRenderer(3, 1, new wxGridCellNumberRenderer);
            wxEntityGrid->SetCellEditor(3, 1, new wxGridCellNumberEditor);
            wxEntityGrid->SetCellValue(3, 1, intToString(SceneryType[i].layer));
            wxEntityGrid->SetCellValue(4, 0, _("offsetX"));
            wxEntityGrid->SetCellRenderer(4, 1, new wxGridCellFloatRenderer);
            wxEntityGrid->SetCellEditor(4, 1, new wxGridCellFloatEditor);
            wxEntityGrid->SetCellValue(4, 1, floatToString((int)SceneryType[i].offsetX));
            wxEntityGrid->SetCellValue(5, 0, _("offsetY"));
            wxEntityGrid->SetCellRenderer(5, 1, new wxGridCellFloatRenderer);
            wxEntityGrid->SetCellEditor(5, 1, new wxGridCellFloatEditor);
            wxEntityGrid->SetCellValue(5, 1, floatToString((int)SceneryType[i].offsetY));
            wxEntityGrid->SetCellValue(6, 0, _("isPassable"));
            wxEntityGrid->SetCellRenderer(6, 1, new wxGridCellBoolRenderer);
            wxEntityGrid->SetCellEditor(6, 1, new wxGridCellBoolEditor);
            wxEntityGrid->SetCellValue(6, 1, SceneryType[i].isPassable?"1":"");
            wxEntityGrid->SetCellValue(7, 0, _("isShootThroughAble"));
            wxEntityGrid->SetCellRenderer(7, 1, new wxGridCellBoolRenderer);
            wxEntityGrid->SetCellEditor(7, 1, new wxGridCellBoolEditor);
            wxEntityGrid->SetCellValue(7, 1, SceneryType[i].isShootThroughAble?"1":"");

            return;
        }
        ++num;
    }
}

void LogicModule::objectTypesClick(int x, int y)
{
    int num = 0;
    for(size_t i=0; i<ObjectType.size(); ++i) {
        if(!ObjectType[i].isLoaded) continue;

        if(x >= (num%3)*55 && x < (num%3)*55+55 &&
           y >= (num/3)*55 && y < (num/3)*55+55) {
            selectionEntityType = ENTITY_TYPE_OBJECT_TYPE;
            selectionEntityIndex = i;

            wxEntityText->SetLabel("Object type preferences");
            if(wxEntityGrid->GetNumberRows()) {
                wxEntityGrid->DeleteRows(0, wxEntityGrid->GetNumberRows());
            }
            wxEntityGrid->InsertRows(0, 16);
            for(int j=0; j<16; ++j) {
                wxEntityGrid->SetReadOnly(j, 0);
            }
            wxEntityGrid->SetCellValue(0, 0, _("name"));
            wxEntityGrid->SetCellValue(0, 1, ObjectType[i].name);
            wxEntityGrid->SetCellValue(1, 0, _("resourcesName"));
            wxEntityGrid->SetCellValue(1, 1, ObjectType[i].resourcesName);
            wxEntityGrid->SetCellValue(2, 0, _("baseType"));
            wxEntityGrid->SetCellRenderer(2, 1, new wxGridCellNumberRenderer);
            wxEntityGrid->SetCellEditor(2, 1, new wxGridCellNumberEditor);
            wxEntityGrid->SetCellValue(2, 1, intToString(ObjectType[i].baseType));
            wxEntityGrid->SetCellValue(3, 0, _("weaponType"));
            wxEntityGrid->SetCellRenderer(3, 1, new wxGridCellNumberRenderer);
            wxEntityGrid->SetCellEditor(3, 1, new wxGridCellNumberEditor);
            wxEntityGrid->SetCellValue(3, 1, intToString(ObjectType[i].weaponType));
            wxEntityGrid->SetCellValue(4, 0, _("equipmentType"));
            wxEntityGrid->SetCellRenderer(4, 1, new wxGridCellNumberRenderer);
            wxEntityGrid->SetCellEditor(4, 1, new wxGridCellNumberEditor);
            wxEntityGrid->SetCellValue(4, 1, intToString(ObjectType[i].equipmentType));
            wxEntityGrid->SetCellValue(5, 0, _("attachmentType"));
            wxEntityGrid->SetCellRenderer(5, 1, new wxGridCellNumberRenderer);
            wxEntityGrid->SetCellEditor(5, 1, new wxGridCellNumberEditor);
            wxEntityGrid->SetCellValue(5, 1, intToString(ObjectType[i].attachmentType));
            wxEntityGrid->SetCellValue(6, 0, _("layer"));
            wxEntityGrid->SetCellRenderer(6, 1, new wxGridCellNumberRenderer);
            wxEntityGrid->SetCellEditor(6, 1, new wxGridCellNumberEditor);
            wxEntityGrid->SetCellValue(6, 1, intToString(ObjectType[i].layer));
            wxEntityGrid->SetCellValue(7, 0, _("offsetX"));
            wxEntityGrid->SetCellRenderer(7, 1, new wxGridCellFloatRenderer);
            wxEntityGrid->SetCellEditor(7, 1, new wxGridCellFloatEditor);
            wxEntityGrid->SetCellValue(7, 1, floatToString((int)ObjectType[i].offsetX));
            wxEntityGrid->SetCellValue(8, 0, _("offsetY"));
            wxEntityGrid->SetCellRenderer(8, 1, new wxGridCellFloatRenderer);
            wxEntityGrid->SetCellEditor(8, 1, new wxGridCellFloatEditor);
            wxEntityGrid->SetCellValue(8, 1, floatToString((int)ObjectType[i].offsetY));
            wxEntityGrid->SetCellValue(9, 0, _("spriteScale"));
            wxEntityGrid->SetCellRenderer(9, 1, new wxGridCellFloatRenderer);
            wxEntityGrid->SetCellEditor(9, 1, new wxGridCellFloatEditor);
            wxEntityGrid->SetCellValue(9, 1, floatToString(ObjectType[i].spriteScale));
            wxEntityGrid->SetCellValue(10, 0, _("isPassable"));
            wxEntityGrid->SetCellRenderer(10, 1, new wxGridCellBoolRenderer);
            wxEntityGrid->SetCellEditor(10, 1, new wxGridCellBoolEditor);
            wxEntityGrid->SetCellValue(10, 1, ObjectType[i].isPassable?"1":"");
            wxEntityGrid->SetCellValue(11, 0, _("isShootThroughAble"));
            wxEntityGrid->SetCellRenderer(11, 1, new wxGridCellBoolRenderer);
            wxEntityGrid->SetCellEditor(11, 1, new wxGridCellBoolEditor);
            wxEntityGrid->SetCellValue(11, 1, ObjectType[i].isShootThroughAble?"1":"");
            wxEntityGrid->SetCellValue(12, 0, _("isAutomatic"));
            wxEntityGrid->SetCellRenderer(12, 1, new wxGridCellBoolRenderer);
            wxEntityGrid->SetCellEditor(12, 1, new wxGridCellBoolEditor);
            wxEntityGrid->SetCellValue(12, 1, ObjectType[i].isAutomatic?"1":"");
            wxEntityGrid->SetCellValue(13, 0, _("baseDamage"));
            wxEntityGrid->SetCellRenderer(13, 1, new wxGridCellNumberRenderer);
            wxEntityGrid->SetCellEditor(13, 1, new wxGridCellNumberEditor);
            wxEntityGrid->SetCellValue(13, 1, intToString(ObjectType[i].baseDamage));
            wxEntityGrid->SetCellValue(14, 0, _("baseShotDelay"));
            wxEntityGrid->SetCellRenderer(14, 1, new wxGridCellNumberRenderer);
            wxEntityGrid->SetCellEditor(14, 1, new wxGridCellNumberEditor);
            wxEntityGrid->SetCellValue(14, 1, intToString(ObjectType[i].baseShotDelay));
            wxEntityGrid->SetCellValue(15, 0, _("value"));
            wxEntityGrid->SetCellRenderer(15, 1, new wxGridCellNumberRenderer);
            wxEntityGrid->SetCellEditor(15, 1, new wxGridCellNumberEditor);
            wxEntityGrid->SetCellValue(15, 1, intToString(ObjectType[i].value));

            return;
        }
        ++num;
    }
}

void LogicModule::NPCTypesClick(int x, int y, bool doubleClick)
{
    int num = 0;
    for(size_t i=0; i<NPCType.size(); ++i) {
        if(!NPCType[i].isLoaded) continue;

        if(x >= (num%3)*55 && x < (num%3)*55+55 &&
           y >= (num/3)*55 && y < (num/3)*55+55) {
            selectionEntityType = ENTITY_TYPE_NPC_TYPE;
            selectionEntityIndex = i;

            wxEntityText->SetLabel("NPC type (double click to edit)");
            if(wxEntityGrid->GetNumberRows()) {
                wxEntityGrid->DeleteRows(0, wxEntityGrid->GetNumberRows());
            }
            if(doubleClick) {
                editingNPCTypeIndex = i;
                NPCTypeEditor dialog(wxMainWindow);
                dialog.ShowModal();
            }
            return;
        }
        ++num;
    }
}

void LogicModule::lightSourceTypesClick(int x, int y)
{
    for(size_t i=0; i<LightType.size(); ++i) {
        if(x >= (i%3)*55 && x < (i%3)*55+55 &&
           y >= (i/3)*55 && y < (i/3)*55+55) {
            selectionEntityType = ENTITY_TYPE_LIGHT_SOURCE_TYPE;
            selectionEntityIndex = i;

            wxEntityText->SetLabel("Light source type");
            if(wxEntityGrid->GetNumberRows()) {
                wxEntityGrid->DeleteRows(0, wxEntityGrid->GetNumberRows());
            }
            return;
        }
    }
}

void LogicModule::triggersClick(int x, int y)
{

}

void LogicModule::effectsClick(int x, int y)
{

}

void LogicModule::zoneTypesClick(int x, int y)
{

}
