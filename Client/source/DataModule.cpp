#include "DataModule.hpp"
#include "ini.hpp"
#include "utility.hpp"

ObjectSlotClass objectSlot[CHARACTER_OBJECT_SLOTS_QUANTITY] = {
    ObjectSlotClass(OBJECT_BASE_TYPE_WEAPON, EQUIPMENT_TYPE_NONE, 0.f, 60.f, ""),
    ObjectSlotClass(OBJECT_BASE_TYPE_EQUIPMENT, EQUIPMENT_TYPE_BOOTS, 60.f, 120.f, ""),
    ObjectSlotClass(OBJECT_BASE_TYPE_EQUIPMENT, EQUIPMENT_TYPE_VEST, 60.f, 60.f, "gfx/misc/defaultVest"),
    ObjectSlotClass(OBJECT_BASE_TYPE_EQUIPMENT, EQUIPMENT_TYPE_GLOVES, 120.f, 60.f, "gfx/misc/defaultGloves"),
    ObjectSlotClass(OBJECT_BASE_TYPE_EQUIPMENT, EQUIPMENT_TYPE_HELMET, 60.f, 0.f, "gfx/misc/defaultHelmet")
};

void DataModule::loadTileTypes(const std::string &path)
{
    TileType.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load tile types file '%s'.", path.c_str());
    }

    std::string name, resourcesName;
    int index, isPassable;

    while(in >> name >> index >> resourcesName >> isPassable) {
        if(index >= (int)TileType.size()) TileType.resize(index+1);

        for(size_t i=0; i<name.size(); ++i) {
            if(name[i] == '_') name[i] = ' ';
        }
        TileType[index].name = name;
        TileType[index].resourcesName = resourcesName;
        TileType[index].isPassable = isPassable;
        TileType[index].isLoaded = true;
    }
    _assert(TILE_SIZE, "TILE_SIZE is 0 in loadTileTypes.");
    for(size_t i=0; i<TileType.size(); ++i) {
        if(!TileType[i].isLoaded) continue;

        sf::Image wholeSprite, wholeNormalMap;
        loadImage(wholeSprite, "gfx/tiles/"+TileType[i].resourcesName+"[colorMap].png");
        loadImage(wholeNormalMap, "gfx/tiles/"+TileType[i].resourcesName+"[normalMap].png", true);

        int widthQuantity = wholeSprite.getSize().x/TILE_SIZE;
        int heightQuantity = wholeSprite.getSize().y/TILE_SIZE;
        if(widthQuantity <= 0 || heightQuantity <= 0) {
            error("Tile size too small  - '%s' (from '%s').", ("gfx/tiles/"+TileType[i].resourcesName+".png").c_str(), path.c_str());
        }
        TileType[i].colorMapTexture.resize(widthQuantity, std::vector <sf::Texture> (heightQuantity));
        TileType[i].normalMapTexture.resize(widthQuantity, std::vector <sf::Texture> (heightQuantity));
        TileType[i].colorMapSprite.resize(widthQuantity, std::vector <sf::Sprite> (heightQuantity));
        TileType[i].normalMapSprite.resize(widthQuantity, std::vector <sf::Sprite> (heightQuantity));
        for(int j=0; j<widthQuantity; ++j) {
            for(int k=0; k<heightQuantity; ++k) {
                const sf::IntRect rect(j*TILE_SIZE, k*TILE_SIZE, TILE_SIZE, TILE_SIZE);
                TileType[i].colorMapTexture[j][k].loadFromImage(wholeSprite, rect);
                TileType[i].colorMapSprite[j][k].setTexture(TileType[i].colorMapTexture[j][k]);
                if(wholeNormalMap.getSize().x) {
                    TileType[i].normalMapTexture[j][k].loadFromImage(wholeNormalMap, rect);
                    TileType[i].normalMapSprite[j][k].setTexture(TileType[i].normalMapTexture[j][k]);
                }
            }
        }
        TileType[i].widthQuantity = widthQuantity;
        TileType[i].heightQuantity = heightQuantity;
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

    int index, layer, isPassable;
    std::string name, resourcesName, natureType;
    float offsetX, offsetY;

    while(in >> name >> index >> resourcesName >> natureType >> layer >> isPassable >> offsetX >> offsetY) {
        if(index >= (int)SceneryType.size()) SceneryType.resize(index+1);

        if(natureType == "NATURE_TYPE_NONE") SceneryType[index].natureType = NATURE_TYPE_NONE;
        else if(natureType == "NATURE_TYPE_TREE") SceneryType[index].natureType = NATURE_TYPE_TREE;
        else if(natureType == "NATURE_TYPE_WATER_FLOAT") SceneryType[index].natureType = NATURE_TYPE_WATER_FLOAT;
        else if(natureType == "NATURE_TYPE_WATER_FLOAT_STATIC") SceneryType[index].natureType = NATURE_TYPE_WATER_FLOAT_STATIC;
        else if(natureType == "NATURE_TYPE_FERN") SceneryType[index].natureType = NATURE_TYPE_FERN;
        else if(natureType == "NATURE_TYPE_STONE") SceneryType[index].natureType = NATURE_TYPE_STONE;
        else if(natureType == "NATURE_TYPE_GRASS") SceneryType[index].natureType = NATURE_TYPE_GRASS;
        else {
            error("Unknown nature type '%s' (in '%s').", natureType.c_str(), path.c_str());
        }
        for(size_t i=0; i<name.size(); ++i) {
            if(name[i] == '_') name[i] = ' ';
        }
        SceneryType[index].name = name;
        SceneryType[index].resourcesName = resourcesName;
        SceneryType[index].layer = layer;
        SceneryType[index].isPassable = isPassable;
        SceneryType[index].offsetX = offsetX;
        SceneryType[index].offsetY = offsetY;
        SceneryType[index].isLoaded = true;
    }
    for(size_t i=0; i<SceneryType.size(); ++i) {
        if(!SceneryType[i].isLoaded) continue;

        loadTexture(SceneryType[i].colorMapTexture, "gfx/sceneries/"+SceneryType[i].resourcesName+"[colorMap].png");
        SceneryType[i].colorMapSprite.setTexture(SceneryType[i].colorMapTexture);

        loadTexture(SceneryType[i].normalMapTexture, "gfx/sceneries/"+SceneryType[i].resourcesName+"[normalMap].png", true);
        SceneryType[i].normalMapSprite.setTexture(SceneryType[i].normalMapTexture);

        loadTexture(SceneryType[i].heightMapTexture, "gfx/sceneries/"+SceneryType[i].resourcesName+"[heightMap].png", true);
        SceneryType[i].heightMapSprite.setTexture(SceneryType[i].heightMapTexture);

        loadTexture(SceneryType[i].shadowTexture, "gfx/sceneries/"+SceneryType[i].resourcesName+"[shadow].png", true);
        SceneryType[i].shadowSprite.setTexture(SceneryType[i].shadowTexture);
    }
    in.close();
}

void DataModule::loadObjectSlotDefaultSprites()
{
    for(size_t i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
        if(objectSlot[i].spritesPath.empty()) continue;

        std::string path;

        path = objectSlot[i].spritesPath+"[onCharacter][noWeapon][colorMap].png";
        loadTexture(objectSlot[i].defaultOnCharacterNoWeaponColorMapTexture, path);
        path = objectSlot[i].spritesPath+"[onCharacter][noWeapon][normalMap].png";
        loadTexture(objectSlot[i].defaultOnCharacterNoWeaponNormalMapTexture, path, true);
        path = objectSlot[i].spritesPath+"[onCharacter][noWeapon][heightMap].png";
        loadTexture(objectSlot[i].defaultOnCharacterNoWeaponHeightMapTexture, path, true);

        objectSlot[i].defaultOnCharacterNoWeaponColorMapSprite.setTexture(objectSlot[i].defaultOnCharacterNoWeaponColorMapTexture);
        objectSlot[i].defaultOnCharacterNoWeaponNormalMapSprite.setTexture(objectSlot[i].defaultOnCharacterNoWeaponNormalMapTexture);
        objectSlot[i].defaultOnCharacterNoWeaponHeightMapSprite.setTexture(objectSlot[i].defaultOnCharacterNoWeaponHeightMapTexture);

        path = objectSlot[i].spritesPath+"[onCharacter][smallWeapon][colorMap].png";
        loadTexture(objectSlot[i].defaultOnCharacterSmallWeaponColorMapTexture, path);
        path = objectSlot[i].spritesPath+"[onCharacter][smallWeapon][normalMap].png";
        loadTexture(objectSlot[i].defaultOnCharacterSmallWeaponNormalMapTexture, path, true);
        path = objectSlot[i].spritesPath+"[onCharacter][smallWeapon][heightMap].png";
        loadTexture(objectSlot[i].defaultOnCharacterSmallWeaponHeightMapTexture, path, true);

        objectSlot[i].defaultOnCharacterSmallWeaponColorMapSprite.setTexture(objectSlot[i].defaultOnCharacterSmallWeaponColorMapTexture);
        objectSlot[i].defaultOnCharacterSmallWeaponNormalMapSprite.setTexture(objectSlot[i].defaultOnCharacterSmallWeaponNormalMapTexture);
        objectSlot[i].defaultOnCharacterSmallWeaponHeightMapSprite.setTexture(objectSlot[i].defaultOnCharacterSmallWeaponHeightMapTexture);

        path = objectSlot[i].spritesPath+"[onCharacter][bigWeapon][colorMap].png";
        loadTexture(objectSlot[i].defaultOnCharacterBigWeaponColorMapTexture, path);
        path = objectSlot[i].spritesPath+"[onCharacter][bigWeapon][normalMap].png";
        loadTexture(objectSlot[i].defaultOnCharacterBigWeaponNormalMapTexture, path, true);
        path = objectSlot[i].spritesPath+"[onCharacter][bigWeapon][heightMap].png";
        loadTexture(objectSlot[i].defaultOnCharacterBigWeaponHeightMapTexture, path, true);

        objectSlot[i].defaultOnCharacterBigWeaponColorMapSprite.setTexture(objectSlot[i].defaultOnCharacterBigWeaponColorMapTexture);
        objectSlot[i].defaultOnCharacterBigWeaponNormalMapSprite.setTexture(objectSlot[i].defaultOnCharacterBigWeaponNormalMapTexture);
        objectSlot[i].defaultOnCharacterBigWeaponHeightMapSprite.setTexture(objectSlot[i].defaultOnCharacterBigWeaponHeightMapTexture);
    }
}

void DataModule::loadObjectTypes(const std::string &path)
{
    ObjectType.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load object types file '%s'.", path.c_str());
    }

    std::string name, resourcesName;
    std::string baseType, weaponType, equipmentType, attachmentType;
    int index, layer, isPassable, isAutomatic, isStackable, baseShotDelay, baseDamage, value;
    float offsetX, offsetY, spriteScale;

    while(in >> name >> index >> resourcesName >> baseType >> weaponType >> equipmentType >> attachmentType >> offsetX >> offsetY >> spriteScale >> layer >> isPassable >> isAutomatic >> isStackable >> baseDamage >> baseShotDelay >> value) {
        if(index >= (int)ObjectType.size()) ObjectType.resize(index+1);

        if(baseType == "OBJECT_BASE_TYPE_NONE") ObjectType[index].baseType = OBJECT_BASE_TYPE_NONE;
        else if(baseType == "OBJECT_BASE_TYPE_WEAPON") ObjectType[index].baseType = OBJECT_BASE_TYPE_WEAPON;
        else if(baseType == "OBJECT_BASE_TYPE_EQUIPMENT") ObjectType[index].baseType = OBJECT_BASE_TYPE_EQUIPMENT;
        else if(baseType == "OBJECT_BASE_TYPE_STRUCTURE") ObjectType[index].baseType = OBJECT_BASE_TYPE_STRUCTURE;
        else if(baseType == "OBJECT_BASE_TYPE_ADDON") ObjectType[index].baseType = OBJECT_BASE_TYPE_ADDON;
        else if(baseType == "OBJECT_BASE_TYPE_MISC") ObjectType[index].baseType = OBJECT_BASE_TYPE_MISC;
        else if(baseType == "OBJECT_BASE_TYPE_AMMUNITION") ObjectType[index].baseType = OBJECT_BASE_TYPE_AMMUNITION;
        else {
            error("Unknown object base type '%s' (in '%s').", baseType.c_str(), path.c_str());
        }
        if(weaponType == "WEAPON_TYPE_NONE") ObjectType[index].weaponType = WEAPON_TYPE_NONE;
        else if(weaponType == "WEAPON_TYPE_SMALL_GUN") ObjectType[index].weaponType = WEAPON_TYPE_SMALL_GUN;
        else if(weaponType == "WEAPON_TYPE_BIG_GUN") ObjectType[index].weaponType = WEAPON_TYPE_BIG_GUN;
        else if(weaponType == "WEAPON_TYPE_ROCKET_LAUNCHER") ObjectType[index].weaponType = WEAPON_TYPE_ROCKET_LAUNCHER;
        else {
            error("Unknown weapon type '%s' (in '%s').", weaponType.c_str(), path.c_str());
        }
        if(equipmentType == "EQUIPMENT_TYPE_NONE") ObjectType[index].equipmentType = EQUIPMENT_TYPE_NONE;
        else if(equipmentType == "EQUIPMENT_TYPE_HELMET") ObjectType[index].equipmentType = EQUIPMENT_TYPE_HELMET;
        else if(equipmentType == "EQUIPMENT_TYPE_VEST") ObjectType[index].equipmentType = EQUIPMENT_TYPE_VEST;
        else if(equipmentType == "EQUIPMENT_TYPE_BOOTS") ObjectType[index].equipmentType = EQUIPMENT_TYPE_BOOTS;
        else if(equipmentType == "EQUIPMENT_TYPE_GLOVES") ObjectType[index].equipmentType = EQUIPMENT_TYPE_GLOVES;
        else {
            error("Unknown equipment type '%s' (in '%s').", equipmentType.c_str(), path.c_str());
        }
        if(attachmentType == "ATTACHMENT_TYPE_NONE") ObjectType[index].attachmentType = ATTACHMENT_TYPE_NONE;
        else if(attachmentType == "ATTACHMENT_TYPE_SIGHT") ObjectType[index].attachmentType = ATTACHMENT_TYPE_SIGHT;
        else if(attachmentType == "ATTACHMENT_TYPE_BARREL") ObjectType[index].attachmentType = ATTACHMENT_TYPE_BARREL;
        else if(attachmentType == "ATTACHMENT_TYPE_MISC") ObjectType[index].attachmentType = ATTACHMENT_TYPE_MISC;
        else {
            error("Unknown attachment type '%s' (in '%s').", attachmentType.c_str(), path.c_str());
        }
        for(size_t i=0; i<name.size(); ++i) {
            if(name[i] == '_') name[i] = ' ';
        }
        ObjectType[index].name = name;
        ObjectType[index].resourcesName = resourcesName;
        ObjectType[index].offsetX = offsetX;
        ObjectType[index].offsetY = offsetY;
        ObjectType[index].spriteScale = spriteScale;
        ObjectType[index].layer = layer;
        ObjectType[index].isPassable = (bool)isPassable;
        ObjectType[index].isAutomatic = (bool)isAutomatic;
        ObjectType[index].isStackable = (bool)isStackable;
        ObjectType[index].baseDamage = baseDamage;
        ObjectType[index].baseShotDelay = baseShotDelay;
        ObjectType[index].value = value;
        ObjectType[index].isLoaded = true;
    }
    for(size_t i=0; i<ObjectType.size(); ++i) {
        if(!ObjectType[i].isLoaded) continue;

        std::string type = getObjectCatalogueName(ObjectType[i].baseType);
        std::string name = ObjectType[i].resourcesName;

        loadTexture(ObjectType[i].colorMapTexture, "gfx/objects/"+type+"/"+name+"[colorMap].png");
        loadTexture(ObjectType[i].normalMapTexture, "gfx/objects/"+type+"/"+name+"[normalMap].png", true);
        loadTexture(ObjectType[i].heightMapTexture, "gfx/objects/"+type+"/"+name+"[heightMap].png", true);

        ObjectType[i].colorMapSprite.setTexture(ObjectType[i].colorMapTexture);
        ObjectType[i].normalMapSprite.setTexture(ObjectType[i].normalMapTexture);
        ObjectType[i].heightMapSprite.setTexture(ObjectType[i].heightMapTexture);

        loadTexture(ObjectType[i].onCharacterColorMapTexture, "gfx/objects/"+type+"/"+name+"[onCharacter][colorMap].png", true);
        loadTexture(ObjectType[i].onCharacterNormalMapTexture, "gfx/objects/"+type+"/"+name+"[onCharacter][normalMap].png", true);
        loadTexture(ObjectType[i].onCharacterHeightMapTexture, "gfx/objects/"+type+"/"+name+"[onCharacter][heightMap].png", true);

        ObjectType[i].onCharacterColorMapSprite.setTexture(ObjectType[i].onCharacterColorMapTexture);
        ObjectType[i].onCharacterNormalMapSprite.setTexture(ObjectType[i].onCharacterNormalMapTexture);
        ObjectType[i].onCharacterHeightMapSprite.setTexture(ObjectType[i].onCharacterHeightMapTexture);

        loadTexture(ObjectType[i].onWeaponColorMapTexture, "gfx/objects/"+type+"/"+name+"[onWeapon][colorMap].png", true);
        loadTexture(ObjectType[i].onWeaponNormalMapTexture, "gfx/objects/"+type+"/"+name+"[onWeapon][normalMap].png", true);
        loadTexture(ObjectType[i].onWeaponHeightMapTexture, "gfx/objects/"+type+"/"+name+"[onWeapon][heightMap].png", true);

        ObjectType[i].onWeaponColorMapSprite.setTexture(ObjectType[i].onWeaponColorMapTexture);
        ObjectType[i].onWeaponNormalMapSprite.setTexture(ObjectType[i].onWeaponNormalMapTexture);
        ObjectType[i].onWeaponHeightMapSprite.setTexture(ObjectType[i].onWeaponHeightMapTexture);

        loadTexture(ObjectType[i].onCharacterNoWeaponColorMapTexture, "gfx/objects/"+type+"/"+name+"[onCharacter][noWeapon][colorMap].png", true);
        loadTexture(ObjectType[i].onCharacterNoWeaponNormalMapTexture, "gfx/objects/"+type+"/"+name+"[onCharacter][noWeapon][normalMap].png", true);
        loadTexture(ObjectType[i].onCharacterNoWeaponHeightMapTexture, "gfx/objects/"+type+"/"+name+"[onCharacter][noWeapon][heightMap].png", true);

        ObjectType[i].onCharacterNoWeaponColorMapSprite.setTexture(ObjectType[i].onCharacterNoWeaponColorMapTexture);
        ObjectType[i].onCharacterNoWeaponNormalMapSprite.setTexture(ObjectType[i].onCharacterNoWeaponNormalMapTexture);
        ObjectType[i].onCharacterNoWeaponHeightMapSprite.setTexture(ObjectType[i].onCharacterNoWeaponHeightMapTexture);

        loadTexture(ObjectType[i].onCharacterSmallWeaponColorMapTexture, "gfx/objects/"+type+"/"+name+"[onCharacter][smallWeapon][colorMap].png", true);
        loadTexture(ObjectType[i].onCharacterSmallWeaponNormalMapTexture, "gfx/objects/"+type+"/"+name+"[onCharacter][smallWeapon][normalMap].png", true);
        loadTexture(ObjectType[i].onCharacterSmallWeaponHeightMapTexture, "gfx/objects/"+type+"/"+name+"[onCharacter][smallWeapon][heightMap].png", true);

        ObjectType[i].onCharacterSmallWeaponColorMapSprite.setTexture(ObjectType[i].onCharacterSmallWeaponColorMapTexture);
        ObjectType[i].onCharacterSmallWeaponNormalMapSprite.setTexture(ObjectType[i].onCharacterSmallWeaponNormalMapTexture);
        ObjectType[i].onCharacterSmallWeaponHeightMapSprite.setTexture(ObjectType[i].onCharacterSmallWeaponHeightMapTexture);

        loadTexture(ObjectType[i].onCharacterBigWeaponColorMapTexture, "gfx/objects/"+type+"/"+name+"[onCharacter][bigWeapon][colorMap].png", true);
        loadTexture(ObjectType[i].onCharacterBigWeaponNormalMapTexture, "gfx/objects/"+type+"/"+name+"[onCharacter][bigWeapon][normalMap].png", true);
        loadTexture(ObjectType[i].onCharacterBigWeaponHeightMapTexture, "gfx/objects/"+type+"/"+name+"[onCharacter][bigWeapon][heightMap].png", true);

        ObjectType[i].onCharacterBigWeaponColorMapSprite.setTexture(ObjectType[i].onCharacterBigWeaponColorMapTexture);
        ObjectType[i].onCharacterBigWeaponNormalMapSprite.setTexture(ObjectType[i].onCharacterBigWeaponNormalMapTexture);
        ObjectType[i].onCharacterBigWeaponHeightMapSprite.setTexture(ObjectType[i].onCharacterBigWeaponHeightMapTexture);

        loadSample(&ObjectType[i].useSound, "sfx/objects/"+type+"/"+name+".wav", true);
    }

    in.close();
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
            if(newTileType >= 0) {
                _assert(newTileType < (int)TileType.size(), "Tile type out of bounds in loadMap.");
                _assert(TileType[newTileType].isLoaded, "Tile type is not loaded in loadMap.");
            }
            if(newSceneryType >= 0) {
                _assert(newSceneryType < (int)SceneryType.size(), "Scenery type out of bounds in loadMap.");
                _assert(SceneryType[newSceneryType].isLoaded, "Scenery type is not loaded in loadMap.");
            }
            Tile[j][i].tileType = newTileType;
            Tile[j][i].sceneryType = newSceneryType;
        }
    }
    in.close();
}

void DataModule::loadTexts(const std::string &path)
{
    Text.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load texts file '%s'.", path.c_str());
    }

    std::string line;
    while(std::getline(in, line)) {
        util::clamp_ws(line);
        if(line.empty()) continue;
        int index = -1;
        sscanf(line.c_str(), "%d", &index);
        if(index < 0) error("Incorrect text index (%d) or corrupted file '%s'.", index, path.c_str());
        int numberCharacterQuantity = 0;
        for(size_t i=0; i<line.size(); ++i) {
            if(isdigit(line[i])) ++numberCharacterQuantity;
            else break;
        }
        if(numberCharacterQuantity < (int)line.size()) {
            line = line.substr(numberCharacterQuantity);
        }
        else line = "";
        util::clamp_ws(line);
        if(index >= (int)Text.size()) Text.resize(index+1, "undefined");
        Text[index] = line;
    }
    in.close();
}

void DataModule::loadQuests(const std::string &path, const std::string &questsPath)
{
    Quest.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load quests file '%s'.", path.c_str());
    }
    int index;
    std::string name, resourcesName, questType;
    while(in >> index >> name >> resourcesName >> questType) {
        if(index >= (int)Quest.size()) Quest.resize(index+1);

        for(size_t i=0; i<name.size(); ++i) {
            if(name[i] == '_') name[i] = ' ';
        }
        Quest[index].name = name;
        Quest[index].resourcesName = resourcesName;

        if(questType == "QUEST_TYPE_NONE") Quest[index].questType = QUEST_TYPE_NONE;
        else if(questType == "QUEST_TYPE_MAIN") Quest[index].questType = QUEST_TYPE_MAIN;
        else if(questType == "QUEST_TYPE_SIDE") Quest[index].questType = QUEST_TYPE_SIDE;
        else {
            error("Unknown quest type '%s' (in '%s').", questType.c_str(), path.c_str());
        }
        std::string path2 = questsPath+resourcesName+".txt";
        std::ifstream in2(path2.c_str());
        if(!in2) {
            error("Could not load quest file '%s'.", path2.c_str());
        }
        std::string line;
        while(std::getline(in2, line)) {
            util::clamp_ws(line);
            if(line.empty()) continue;

            int progressFrom = -1, progressTo = -1;
            sscanf(line.c_str(), "%d %d", &progressFrom, &progressTo);
            if(progressFrom < 0 || progressTo < 0 || progressFrom > 100 || progressTo > 100) {
                error("Incorrect or missing progress value in '%s'.", path2.c_str());
            }
            int cutIndex = -1;
            bool spaceEncountered = false;
            bool secondNumberEncountered = false;
            for(size_t i=0; i<line.size(); ++i) {
                if(line[i] == ' ' && secondNumberEncountered) {
                    cutIndex = i;
                    break;
                }
                if(line[i] == ' ') spaceEncountered = true;
                if(isdigit(line[i]) && spaceEncountered) secondNumberEncountered = true;
            }
            if(cutIndex < 0) {
                error("Missing text in '%s'.", path2.c_str());
            }
            std::string text = line.substr(cutIndex);
            util::clamp_ws(text);
            Quest[index].questProgressText.push_back(QuestClass::QuestProgressTextClass(progressFrom, progressTo, text));
        }
        in2.close();
    }
    in.close();
}

void DataModule::loadGameSettings(const std::string &path)
{
    IniFileClass IniFile;
    if(IniFile.read(path)) {
        GameSettings.loaded = true;
        std::string fullscreen_str = IniFile.group["Settings"].value["fullscreen"];
        if(!fullscreen_str.empty()) {
            int fullscreen = 0;
            sscanf(fullscreen_str.c_str(), "%d", &fullscreen);
            GameSettings.fullscreen = (bool)fullscreen;
        }
        std::string screenWidth_str = IniFile.group["Settings"].value["screenWidth"];
        if(!screenWidth_str.empty()) {
            int screenWidth = -1;
            sscanf(screenWidth_str.c_str(), "%d", &screenWidth);
            GameSettings.screenWidth = screenWidth;
        }
        std::string screenHeight_str = IniFile.group["Settings"].value["screenHeight"];
        if(!screenHeight_str.empty()) {
            int screenHeight = -1;
            sscanf(screenHeight_str.c_str(), "%d", &screenHeight);
            GameSettings.screenHeight = screenHeight;
        }
        std::string sound_str = IniFile.group["Settings"].value["sound"];
        if(!sound_str.empty()) {
            int sound = 1;
            sscanf(sound_str.c_str(), "%d", &sound);
            GameSettings.sound = (bool)sound;
        }
    }
    else {
        info("Could not load settings file '%s'. File will be created.", path.c_str());
    }
}

void DataModule::applyMissingTexture()
{
    for(size_t i=0; i<ObjectType.size(); ++i) {
        sf::Sprite *spr[6] = {
            &ObjectType[i].colorMapSprite,
            &ObjectType[i].onCharacterColorMapSprite,
            &ObjectType[i].onWeaponColorMapSprite,
            &ObjectType[i].onCharacterNoWeaponColorMapSprite,
            &ObjectType[i].onCharacterSmallWeaponColorMapSprite,
            &ObjectType[i].onCharacterBigWeaponColorMapSprite
        };
        for(int j=0; j<6; ++j) {
            if(!spr[j]->getTexture() || !spr[j]->getTexture()->getSize().x || !spr[j]->getTexture()->getSize().y) {
                spr[j]->setTexture(missingTexture);
            }
        }
    }
}

void DataModule::applyTextureSmoothing()
{
    for(size_t i=0; i<TileType.size(); ++i) {
        for(size_t j=0; j<TileType[i].colorMapTexture.size(); ++j) {
            for(size_t k=0; k<TileType[i].colorMapTexture[j].size(); ++k) {
                TileType[i].colorMapTexture[j][k].setSmooth(true);
            }
        }
    }
    for(size_t i=0; i<SceneryType.size(); ++i) {
        SceneryType[i].colorMapTexture.setSmooth(true);
    }
    for(size_t i=0; i<ObjectType.size(); ++i) {
        ObjectType[i].colorMapTexture.setSmooth(true);
        ObjectType[i].onCharacterColorMapTexture.setSmooth(true);
        ObjectType[i].onWeaponColorMapTexture.setSmooth(true);
        ObjectType[i].onCharacterNoWeaponColorMapTexture.setSmooth(true);
        ObjectType[i].onCharacterSmallWeaponColorMapTexture.setSmooth(true);
        ObjectType[i].onCharacterBigWeaponColorMapTexture.setSmooth(true);
    }
    for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
        objectSlot[i].defaultOnCharacterNoWeaponColorMapTexture.setSmooth(true);
        objectSlot[i].defaultOnCharacterSmallWeaponColorMapTexture.setSmooth(true);
        objectSlot[i].defaultOnCharacterBigWeaponColorMapTexture.setSmooth(true);
    }
    missingTexture.setSmooth(true);
    penumbraTexture.setSmooth(true);
    for(int i=0; i<PARTICLE_TEXTURES_QUANTITY; ++i) {
        particleTexture[i].setSmooth(true);
    }
    missileTexture.setSmooth(true);
    grenadeLauncherGrenadeTexture.setSmooth(true);
    grenadeTexture.setSmooth(true);
}
