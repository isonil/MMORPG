#include "Editor.hpp"

/**
* @brief Main init method.
*
* Initializes all components.\n
* Calls init methods from DataModule.
*/
void Editor::init()
{
    if(!logManager.create("log.txt")) {
        error("Could not create log file 'log.txt'.");
    }
    sf::err().rdbuf((std::streambuf*)&logManager);

    if(sf::Texture::getMaximumSize() < SUPPORTED_TEXTURE_SIZE_REQUIREMENT) {
        error("Your graphics card does not support %dp textures.", SUPPORTED_TEXTURE_SIZE_REQUIREMENT);
    }
    info("Detected graphics card support %dp textures.", sf::Texture::getMaximumSize());

    info("Loading tiles.");
    loadClientTileTypes("ClientData/tiles.dat");
    loadServerTileTypes("ServerData/tiles.dat");

    info("Loading sceneries.");
    loadClientSceneryTypes("ClientData/sceneries.dat");
    loadServerSceneryTypes("ServerData/sceneries.dat");

    info("Loading objects.");
    loadClientObjectSlotDefaultSprites();
    loadClientObjectTypes("ClientData/objects.dat");
    loadServerObjectTypes("ServerData/objects.dat");

    info("Loading lights.");
    loadClientLightTypes("ClientData/lights.dat");

    info("Loading static light sources.");
    loadClientStaticLightSources("ClientData/light_sources.dat");

    info("Loading scripts.");
    loadServerScripts("ServerData/scripts.dat", "ServerData/scripts/");

    info("Loading quests.");
    loadClientQuests("ClientData/quests.dat", "ClientData/quests/");
    loadServerQuests("ServerData/quests.dat");

    info("Loading NPC types.");
    loadServerNPCTypes("ServerData/npc_types.dat", "ServerData/npc_types/");

    info("Loading NPCs.");
    loadServerNPCs("ServerData/npcs.dat");

    info("Loading interface/misc sprites.");
    loadTexture(missingTexture, "gfx/misc/missingTexture.png");
    loadTexture(penumbraTexture, "gfx/misc/penumbra.png");
    loadTexture(minimapTexture, "gfx/misc/minimap.png");
    loadTexture(mouseTexture, "gfx/interface/mouse.png");
    loadTexture(waterColorMapTexture, "gfx/misc/water[colorMap].png");
    loadTexture(waterNormalMapTexture, "gfx/misc/water[normalMap].png");
    loadTexture(waterNoiseTexture, "gfx/misc/waterNoise.png");
    loadTexture(skyTexture, "gfx/misc/sky.png");
    waterSprite.setTexture(waterColorMapTexture);
    loadTexture(lightIconTexture, "gfx/misc/lightIcon.png");
    lightIconSprite.setTexture(lightIconTexture);

    info("Loading map.");
    loadClientMap("ClientData/map.dat");
    validateNPCMovementCheckpoints(NPC);

    info("Loading texts.");
    loadClientTexts("ClientData/texts.dat");

    info("Assigning texts to NPC types dialogues.");
    for(size_t i=0; i<NPCType.size(); ++i) {
        for(size_t j=0; j<NPCType[i].dialogueBlock.size(); ++j) {
            if(NPCType[i].dialogueBlock[j].NPCTextIndex >= 0) {
                _assert(NPCType[i].dialogueBlock[j].NPCTextIndex < (int)Text.size(),
                        "NPC type dialogue text index out of bounds in init.");
                NPCType[i].dialogueBlock[j].NPCText = Text[NPCType[i].dialogueBlock[j].NPCTextIndex].str;
            }
            for(size_t k=0; k<NPCType[i].dialogueBlock[j].option.size(); ++k) {
                if(NPCType[i].dialogueBlock[j].option[k].textIndex >= 0) {
                    _assert(NPCType[i].dialogueBlock[j].option[k].textIndex < (int)Text.size(),
                            "NPC type dialogue option text index out of bounds in init.");
                    NPCType[i].dialogueBlock[j].option[k].text = Text[NPCType[i].dialogueBlock[j].option[k].textIndex].str;
                }
            }
        }
    }

    info("Creating frame buffer objects.");
    colorMapFBO.create(window.getSize().x, window.getSize().y);
    normalMapFBO.create(window.getSize().x, window.getSize().y);
    heightMapFBO.create(window.getSize().x, window.getSize().y);

    info("Initializing misc variables.");
    applyMissingTexture();
    applyTextureSmoothing();
    for(int i=0; i<10; ++i) {
        for(int j=0; j<10; ++j) {
            randomArray[i][j] = rand()%1120;
        }
    }
    mx = window.getSize().x/2;
    my = window.getSize().y/2;
    srand(time(0));
    View.x = 1400.f;
    View.y = 920.f;
    View.distance = 0.8f;
	addRenderState = sf::RenderStates::Default;
	addRenderState.blendMode = sf::BlendAdd;

    info("Updating error log (compiling scripts, etc).");
    updateErrorLog();

    info("Adding texts/quests/scripts to list boxes.");
    for(size_t i=0; i<Text.size(); ++i) {
        if(!Text[i].isLoaded) continue;
        wxTextsListBox->Append(Text[i].str);
    }
    for(size_t i=0; i<Quest.size(); ++i) {
        if(!Quest[i].isLoaded) continue;
        wxQuestsListBox->Append(Quest[i].IDName);
    }
    for(size_t i=0; i<Script.size(); ++i) {
        if(!Script[i].isLoaded) continue;
        wxScriptsListBox->Append(Script[i].IDName);
    }

    info("Initializing done.");
}

void Editor::renderAll()
{
    globalTime = globalClock.getElapsedTime().asMilliseconds();

    normalMapFBO.clear(sf::Color(128, 128, 255));
    heightMapFBO.clear(sf::Color(50, 50, 50));

    shadowCaster.clear();
    renderMapLayerOne();
    renderAllCharacters();
    renderMapLayerTwo();
    renderMapLayerThree();
    renderLights();
    renderInterface();

    if(saved_timer > globalTime) {
        float alpha = 255.f;
        if(saved_timer-globalTime > 3000.0) {
            alpha = (1.0-(saved_timer-globalTime-3000.0)/1000.0)*255.0;
        }
        else if(saved_timer-globalTime < 1000.0) {
            alpha = (saved_timer-globalTime)/1000.0*255.0;
        }
        sf::Text text;
        text.setCharacterSize(14);
        text.setPosition(11.f, (float)window.getSize().y-24.f);
        text.setColor(sf::Color(0, 0, 0, alpha));
        text.setString("Saved");
        colorMapFBO.draw(text);
        text.setPosition(10.f, (float)window.getSize().y-25.f);
        text.setColor(sf::Color(255, 255, 255, alpha));
        colorMapFBO.draw(text);
    }

    colorMapFBO.display();
    normalMapFBO.display();
    heightMapFBO.display();

    if(wxDisplaySelection->GetSelection() == 0) {
        window.draw(sf::Sprite(colorMapFBO.getTexture()));
    }
    else if(wxDisplaySelection->GetSelection() == 1) {
        window.draw(sf::Sprite(colorMapFBO.getTexture()));
    }
    else if(wxDisplaySelection->GetSelection() == 2) {
        window.draw(sf::Sprite(normalMapFBO.getTexture()));
    }
    else if(wxDisplaySelection->GetSelection() == 3) {
        window.draw(sf::Sprite(heightMapFBO.getTexture()));
    }
}

void Editor::save()
{
    // Generate texts and dialogue texts indexes.
    Text.clear();
    for(size_t i=0; i<NPCType.size(); ++i) {
        for(size_t j=0; j<NPCType[i].dialogueBlock.size(); ++j) {
            Text.push_back(NPCType[i].dialogueBlock[j].NPCText);
            Text.back().isLoaded = true;
            NPCType[i].dialogueBlock[j].NPCTextIndex = Text.size()-1;
            for(size_t k=0; k<NPCType[i].dialogueBlock[j].option.size(); ++k) {
                Text.push_back(NPCType[i].dialogueBlock[j].option[k].text);
                Text.back().isLoaded = true;
                NPCType[i].dialogueBlock[j].option[k].textIndex = Text.size()-1;
            }
        }
    }

    std::ofstream out;

    // CLIENT //

    out.open("ClientData/map.dat");
    if(!out) error("Could not create file 'ClientData/map.dat'.");
    _assert(Tile.size(), "Map is empty in save.");
    out << Tile.size() << ' ' << Tile[0].size() << std::endl;
    for(size_t i=0; i<Tile[0].size(); ++i) {
        for(size_t j=0; j<Tile.size(); ++j) {
            out << Tile[j][i].tileType << ' ' << Tile[j][i].sceneryType;
            if(j != Tile.size()-1) out << ' ';
        }
        out << std::endl;
    }
    out.close();

    out.open("ClientData/lights.dat");
    if(!out) error("Could not create file 'ClientData/lights.dat'.");
    for(size_t i=0; i<LightType.size(); ++i) {
        out << LightType[i].textureName << ' '
            << LightType[i].originX << ' '
            << LightType[i].originY << std::endl;
    }
    out.close();

    out.open("ClientData/light_sources.dat");
    if(!out) error("Could not create file 'ClientData/light_sources.dat'.");
    for(size_t i=0; i<StaticLightSource.size(); ++i) {
        out << StaticLightSource[i].x << ' '
            << StaticLightSource[i].y << ' '
            << StaticLightSource[i].type << ' '
            << StaticLightSource[i].color.x << ' '
            << StaticLightSource[i].color.y << ' '
            << StaticLightSource[i].color.z << std::endl;
    }
    out.close();

    out.open("ClientData/tiles.dat");
    if(!out) error("Could not create file 'ClientData/tiles.dat'.");
    for(size_t i=0; i<TileType.size(); ++i) {
        if(!TileType[i].isLoaded) continue;

        out << spacesToUnderscores(TileType[i].name) << ' '
            << i << ' '
            << TileType[i].resourcesName << ' '
            << (int)TileType[i].isPassable << std::endl;
    }
    out.close();

    out.open("ClientData/sceneries.dat");
    if(!out) error("Could not create file 'ClientData/sceneries.dat'.");
    for(size_t i=0; i<SceneryType.size(); ++i) {
        if(!SceneryType[i].isLoaded) continue;

        out << spacesToUnderscores(SceneryType[i].name) << ' '
            << i << ' '
            << SceneryType[i].resourcesName << ' ';

        if(SceneryType[i].natureType == NATURE_TYPE_NONE) out << "NATURE_TYPE_NONE";
        else if(SceneryType[i].natureType == NATURE_TYPE_TREE) out << "NATURE_TYPE_TREE";
        else if(SceneryType[i].natureType == NATURE_TYPE_WATER_FLOAT) out << "NATURE_TYPE_WATER_FLOAT";
        else if(SceneryType[i].natureType == NATURE_TYPE_WATER_FLOAT_STATIC) out << "NATURE_TYPE_WATER_FLOAT_STATIC";
        else if(SceneryType[i].natureType == NATURE_TYPE_FERN) out << "NATURE_TYPE_FERN";
        else if(SceneryType[i].natureType == NATURE_TYPE_STONE) out << "NATURE_TYPE_STONE";
        else if(SceneryType[i].natureType == NATURE_TYPE_GRASS) out << "NATURE_TYPE_GRASS";
        else {
            error("Unknown nature type '%d'.", SceneryType[i].natureType);
        }
        out << ' ';

        out << SceneryType[i].layer << ' '
            << (int)SceneryType[i].isPassable << ' '
            << (int)SceneryType[i].offsetX << ' '
            << (int)SceneryType[i].offsetY << std::endl;
    }
    out.close();

    out.open("ClientData/objects.dat");
    if(!out) error("Could not create file 'ClientData/objects.dat'.");
    for(size_t i=0; i<ObjectType.size(); ++i) {
        if(!ObjectType[i].isLoaded) continue;

        out << i << ' '
            << spacesToUnderscores(ObjectType[i].name) << ' '
            << ObjectType[i].resourcesName << ' ';

        if(ObjectType[i].baseType == OBJECT_BASE_TYPE_NONE) out << "OBJECT_BASE_TYPE_NONE";
        else if(ObjectType[i].baseType == OBJECT_BASE_TYPE_WEAPON) out << "OBJECT_BASE_TYPE_WEAPON";
        else if(ObjectType[i].baseType == OBJECT_BASE_TYPE_EQUIPMENT) out << "OBJECT_BASE_TYPE_EQUIPMENT";
        else if(ObjectType[i].baseType == OBJECT_BASE_TYPE_STRUCTURE) out << "OBJECT_BASE_TYPE_STRUCTURE";
        else if(ObjectType[i].baseType == OBJECT_BASE_TYPE_ADDON) out << "OBJECT_BASE_TYPE_ADDON";
        else if(ObjectType[i].baseType == OBJECT_BASE_TYPE_MISC) out << "OBJECT_BASE_TYPE_MISC";
        else if(ObjectType[i].baseType == OBJECT_BASE_TYPE_AMMUNITION) out << "OBJECT_BASE_TYPE_AMMUNITION";
        else {
            error("Unknown object base type '%d'.", ObjectType[i].baseType);
        }
        out << ' ';

        if(ObjectType[i].weaponType == WEAPON_TYPE_NONE) out << "WEAPON_TYPE_NONE";
        else if(ObjectType[i].weaponType == WEAPON_TYPE_SMALL_GUN) out << "WEAPON_TYPE_SMALL_GUN";
        else if(ObjectType[i].weaponType == WEAPON_TYPE_BIG_GUN) out << "WEAPON_TYPE_BIG_GUN";
        else if(ObjectType[i].weaponType == WEAPON_TYPE_ROCKET_LAUNCHER) out << "WEAPON_TYPE_ROCKET_LAUNCHER";
        else {
            error("Unknown object weapon type '%d'.", ObjectType[i].weaponType);
        }
        out << ' ';

        if(ObjectType[i].equipmentType == EQUIPMENT_TYPE_NONE) out << "EQUIPMENT_TYPE_NONE";
        else if(ObjectType[i].equipmentType == EQUIPMENT_TYPE_HELMET) out << "EQUIPMENT_TYPE_HELMET";
        else if(ObjectType[i].equipmentType == EQUIPMENT_TYPE_VEST) out << "EQUIPMENT_TYPE_VEST";
        else if(ObjectType[i].equipmentType == EQUIPMENT_TYPE_BOOTS) out << "EQUIPMENT_TYPE_BOOTS";
        else if(ObjectType[i].equipmentType == EQUIPMENT_TYPE_GLOVES) out << "EQUIPMENT_TYPE_GLOVES";
        else {
            error("Unknown object equipment type '%d'.", ObjectType[i].equipmentType);
        }
        out << ' ';

        if(ObjectType[i].attachmentType == ATTACHMENT_TYPE_NONE) out << "ATTACHMENT_TYPE_NONE";
        else if(ObjectType[i].attachmentType == ATTACHMENT_TYPE_SIGHT) out << "ATTACHMENT_TYPE_SIGHT";
        else if(ObjectType[i].attachmentType == ATTACHMENT_TYPE_BARREL) out << "ATTACHMENT_TYPE_BARREL";
        else if(ObjectType[i].attachmentType == ATTACHMENT_TYPE_MISC) out << "ATTACHMENT_TYPE_MISC";
        else {
            error("Unknown object attachment type '%d'.", ObjectType[i].attachmentType);
        }
        out << ' ';

        out << (int)ObjectType[i].offsetX << ' '
            << (int)ObjectType[i].offsetY << ' '
            << ObjectType[i].spriteScale << ' '
            << ObjectType[i].layer << ' '
            << (int)ObjectType[i].isPassable << ' '
            << (int)ObjectType[i].isAutomatic << ' '
            << (int)ObjectType[i].isStackable << ' '
            << ObjectType[i].baseDamage << ' '
            << ObjectType[i].baseShotDelay << ' '
            << ObjectType[i].value << std::endl;
    }
    out.close();

    out.open("ClientData/quests.dat");
    if(!out) error("Could not create file 'ClientData/quests.dat'.");
    for(size_t i=0; i<Quest.size(); ++i) {
        if(!Quest[i].isLoaded) continue;

        out << i << ' '
            << spacesToUnderscores(Quest[i].name) << ' ';

        if(Quest[i].questType == QUEST_TYPE_NONE) out << "QUEST_TYPE_NONE";
        else if(Quest[i].questType == QUEST_TYPE_MAIN) out << "QUEST_TYPE_MAIN";
        else if(Quest[i].questType == QUEST_TYPE_SIDE) out << "QUEST_TYPE_SIDE";
        else {
            error("Unknown quest type '%d'.", Quest[i].questType);
        }

        out << std::endl;

        std::ofstream out2(("ClientData/quests/"+intToString(i)).c_str());
        if(!out2) {
            error("Could not create file 'ClientData/quests/%d'.", i);
        }
        for(size_t j=0; j<Quest[i].questProgressText.size(); ++j) {
            out2 << Quest[i].questProgressText[j].progressFrom << ' '
                 << Quest[i].questProgressText[j].progressTo << ' '
                 << Quest[i].questProgressText[j].text << std::endl;
        }
        out2.close();
    }
    out.close();

    out.open("ClientData/texts.dat");
    if(!out) error("Could not create file 'ClientData/texts.dat'.");
    for(size_t i=0; i<Text.size(); ++i) {
        if(!Text[i].isLoaded) continue;

        out << i << ' '
            << Text[i].str << std::endl;
    }
    out.close();

    // SERVER //

    out.open("ServerData/map.dat");
    if(!out) error("Could not create file 'ServerData/map.dat'.");
    out << Tile.size() << ' ' << Tile[0].size() << std::endl;
    for(size_t i=0; i<Tile[0].size(); ++i) {
        for(size_t j=0; j<Tile.size(); ++j) {
            out << Tile[j][i].tileType << ' ' << Tile[j][i].sceneryType;
            if(j != Tile.size()-1) out << ' ';
        }
        out << std::endl;
    }
    out.close();

    out.open("ServerData/tiles.dat");
    if(!out) error("Could not create file 'ServerData/tiles.dat'.");
    for(size_t i=0; i<TileType.size(); ++i) {
        if(!TileType[i].isLoaded) continue;

        out << spacesToUnderscores(TileType[i].name) << ' '
            << i << ' '
            << (int)TileType[i].isPassable << ' '
            << (int)TileType[i].isShootThroughAble << std::endl;
    }
    out.close();

    out.open("ServerData/sceneries.dat");
    if(!out) error("Could not create file 'ServerData/sceneries.dat'.");
    for(size_t i=0; i<SceneryType.size(); ++i) {
        if(!SceneryType[i].isLoaded) continue;

        out << spacesToUnderscores(SceneryType[i].name) << ' '
            << i << ' '
            << (int)SceneryType[i].isPassable << ' '
            << (int)SceneryType[i].isShootThroughAble << std::endl;
    }
    out.close();

    out.open("ServerData/objects.dat");
    if(!out) error("Could not create file 'ServerData/objects.dat'.");
    for(size_t i=0; i<ObjectType.size(); ++i) {
        if(!ObjectType[i].isLoaded) continue;

        out << i << ' '
            << "ID_"+intToString(i) << ' '
            << spacesToUnderscores(ObjectType[i].name) << ' ';

        if(ObjectType[i].baseType == OBJECT_BASE_TYPE_NONE) out << "OBJECT_BASE_TYPE_NONE";
        else if(ObjectType[i].baseType == OBJECT_BASE_TYPE_WEAPON) out << "OBJECT_BASE_TYPE_WEAPON";
        else if(ObjectType[i].baseType == OBJECT_BASE_TYPE_EQUIPMENT) out << "OBJECT_BASE_TYPE_EQUIPMENT";
        else if(ObjectType[i].baseType == OBJECT_BASE_TYPE_STRUCTURE) out << "OBJECT_BASE_TYPE_STRUCTURE";
        else if(ObjectType[i].baseType == OBJECT_BASE_TYPE_ADDON) out << "OBJECT_BASE_TYPE_ADDON";
        else if(ObjectType[i].baseType == OBJECT_BASE_TYPE_MISC) out << "OBJECT_BASE_TYPE_MISC";
        else if(ObjectType[i].baseType == OBJECT_BASE_TYPE_AMMUNITION) out << "OBJECT_BASE_TYPE_AMMUNITION";
        else {
            error("Unknown object base type '%d'.", ObjectType[i].baseType);
        }
        out << ' ';

        if(ObjectType[i].weaponType == WEAPON_TYPE_NONE) out << "WEAPON_TYPE_NONE";
        else if(ObjectType[i].weaponType == WEAPON_TYPE_SMALL_GUN) out << "WEAPON_TYPE_SMALL_GUN";
        else if(ObjectType[i].weaponType == WEAPON_TYPE_BIG_GUN) out << "WEAPON_TYPE_BIG_GUN";
        else if(ObjectType[i].weaponType == WEAPON_TYPE_ROCKET_LAUNCHER) out << "WEAPON_TYPE_ROCKET_LAUNCHER";
        else {
            error("Unknown object weapon type '%d'.", ObjectType[i].weaponType);
        }
        out << ' ';

        if(ObjectType[i].equipmentType == EQUIPMENT_TYPE_NONE) out << "EQUIPMENT_TYPE_NONE";
        else if(ObjectType[i].equipmentType == EQUIPMENT_TYPE_HELMET) out << "EQUIPMENT_TYPE_HELMET";
        else if(ObjectType[i].equipmentType == EQUIPMENT_TYPE_VEST) out << "EQUIPMENT_TYPE_VEST";
        else if(ObjectType[i].equipmentType == EQUIPMENT_TYPE_BOOTS) out << "EQUIPMENT_TYPE_BOOTS";
        else if(ObjectType[i].equipmentType == EQUIPMENT_TYPE_GLOVES) out << "EQUIPMENT_TYPE_GLOVES";
        else {
            error("Unknown object equipment type '%d'.", ObjectType[i].equipmentType);
        }
        out << ' ';

        if(ObjectType[i].attachmentType == ATTACHMENT_TYPE_NONE) out << "ATTACHMENT_TYPE_NONE";
        else if(ObjectType[i].attachmentType == ATTACHMENT_TYPE_SIGHT) out << "ATTACHMENT_TYPE_SIGHT";
        else if(ObjectType[i].attachmentType == ATTACHMENT_TYPE_BARREL) out << "ATTACHMENT_TYPE_BARREL";
        else if(ObjectType[i].attachmentType == ATTACHMENT_TYPE_MISC) out << "ATTACHMENT_TYPE_MISC";
        else {
            error("Unknown object attachment type '%d'.", ObjectType[i].attachmentType);
        }
        out << ' ';

        out << (int)ObjectType[i].isPassable << ' '
            << (int)ObjectType[i].isShootThroughAble << ' '
            << (int)ObjectType[i].isAutomatic << ' '
            << (int)ObjectType[i].isStackable << ' '
            << ObjectType[i].baseDamage << ' '
            << ObjectType[i].baseShotDelay << ' '
            << ObjectType[i].value << std::endl;
    }
    out.close();

    out.open("ServerData/quests.dat");
    if(!out) error("Could not create file 'ServerData/quests.dat'.");
    for(size_t i=0; i<Quest.size(); ++i) {
        if(!Quest[i].isLoaded) continue;

        out << i << ' '
            << Quest[i].IDName << ' '
            << spacesToUnderscores(Quest[i].name) << std::endl;
    }
    out.close();

    out.open("ServerData/scripts.dat");
    if(!out) error("Could not create file 'ServerData/scripts.dat'.");
    for(size_t i=0; i<Script.size(); ++i) {
        if(!Script[i].isLoaded) continue;

        out << i << ' '
            << Script[i].IDName << std::endl;

        std::ofstream out2(("ServerData/scripts/"+intToString(i)).c_str());
        if(!out2) {
            error("Could not create file '%s'.", ("ServerData/scripts/"+intToString(i)).c_str());
        }
        out2 << Script[i].script;
        out2.close();
    }
    out.close();

    out.open("ServerData/npc_types.dat");
    if(!out) error("Could not create file 'ServerData/npc_types.dat'.");
    for(size_t i=0; i<NPCType.size(); ++i) {
        if(!NPCType[i].isLoaded) continue;

        out << i << std::endl;

        std::ofstream out2(("ServerData/npc_types/"+intToString(i)).c_str());
        if(!out2) {
            error("Could not create file 'ServerData/npc_types/%d'.", i);
        }

        out2 << "(Params)" << std::endl
             << "Name " << spacesToUnderscores(NPCType[i].name) << std::endl
             << "Team " << NPCType[i].team << std::endl
             << "MaxHealth " << NPCType[i].maxHealth << std::endl
             << ';' << std::endl << std::endl;

        out2 << "(Slots)" << std::endl;
        for(size_t j=0; j<CHARACTER_OBJECT_SLOTS_QUANTITY; ++j) {
            if(NPCType[i].objectTypeOnSlot[j] >= 0) {
                out2 << j << ' ' << NPCType[i].objectTypeOnSlot[j] << std::endl;
            }
        }
        out2 << ';' << std::endl << std::endl;

        out2 << "(Loot)" << std::endl;
        for(size_t j=0; j<NPCType[i].lootObject.size(); ++j) {
            out2 << NPCType[i].lootObject[j].objectType << ' '
                 << NPCType[i].lootObject[j].quantityFrom << ' '
                 << NPCType[i].lootObject[j].quantityTo << ' '
                 << NPCType[i].lootObject[j].chance << std::endl;
        }
        out2 << ';' << std::endl << std::endl;

        out2 << "(Trade)" << std::endl;
        for(size_t j=0; j<NPCType[i].tradeObject.size(); ++j) {
            out2 << NPCType[i].tradeObject[j].objectType << std::endl;
        }
        out2 << ';' << std::endl << std::endl;

        out2 << "(Dialogue)" << std::endl;
        for(size_t j=0; j<NPCType[i].dialogueBlock.size(); ++j) {
            out2 << "Block " << j << std::endl;
            if(NPCType[i].dialogueBlock[j].NPCTextIndex >= 0) {
                out2 << "  NPCText " << NPCType[i].dialogueBlock[j].NPCTextIndex << std::endl;
            }
            if(NPCType[i].dialogueBlock[j].scriptIndex >= 0) {
                out2 << "  RunScript " << NPCType[i].dialogueBlock[j].scriptIndex << std::endl;
            }
            for(size_t k=0; k<NPCType[i].dialogueBlock[j].option.size(); ++k) {
                out2 << "  Option "
                     << NPCType[i].dialogueBlock[j].option[k].requiredQuestProgressIndex << ' '
                     << NPCType[i].dialogueBlock[j].option[k].requiredQuestProgressFrom << ' '
                     << NPCType[i].dialogueBlock[j].option[k].requiredQuestProgressTo << ' '
                     << NPCType[i].dialogueBlock[j].option[k].textIndex << ' ';
                if(NPCType[i].dialogueBlock[j].option[k].startTrade) {
                    out2 << "trade" << std::endl;
                }
                else out2 << NPCType[i].dialogueBlock[j].option[k].leadToBlock << std::endl;
            }
        }
        out2 << ';' << std::endl;

        out2.close();
    }
    out.close();

    out.open("ServerData/npcs.dat");
    if(!out) error("Could not create file 'ServerData/npcs.dat'.");
    for(size_t i=0; i<NPC.size(); ++i) {
        out << NPC[i].NPCType << ' ' << NPC[i].x << ' ' << NPC[i].y << ' ' << NPC[i].dir << ' '
            << (int)NPC[i].AI_staticDirection << ' ';
        if(NPC[i].AI_movementType == AI_MOVEMENT_TYPE_STAND) out << "AI_MOVEMENT_TYPE_STAND";
        else if(NPC[i].AI_movementType == AI_MOVEMENT_TYPE_MOVE_BY_CHECKPOINTS) out << "AI_MOVEMENT_TYPE_MOVE_BY_CHECKPOINTS";
        else if(NPC[i].AI_movementType == AI_MOVEMENT_TYPE_MOVE_BY_DISTANCE) out << "AI_MOVEMENT_TYPE_MOVE_BY_DISTANCE";
        else error("Unknown AI movement type in save.");
        out << ' ' << NPC[i].AI_movementDistance << ' '
            << '{';
        for(size_t j=0; j<NPC[i].AI_movementCheckpoint.size(); ++j) {
            out << NPC[i].AI_movementCheckpoint[j].x << ", " << NPC[i].AI_movementCheckpoint[j].y;
            if(j != NPC[i].AI_movementCheckpoint.size()-1) out << ", ";
        }
        out << '}' << std::endl;
    }
    out.close();
}
