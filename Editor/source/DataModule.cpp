#include "DataModule.hpp"
#include <stack>
#include <sstream>

ObjectSlotClass objectSlot[CHARACTER_OBJECT_SLOTS_QUANTITY] = {
    ObjectSlotClass(OBJECT_BASE_TYPE_WEAPON, EQUIPMENT_TYPE_NONE, ""),
    ObjectSlotClass(OBJECT_BASE_TYPE_EQUIPMENT, EQUIPMENT_TYPE_BOOTS, ""),
    ObjectSlotClass(OBJECT_BASE_TYPE_EQUIPMENT, EQUIPMENT_TYPE_VEST, "gfx/misc/defaultVest"),
    ObjectSlotClass(OBJECT_BASE_TYPE_EQUIPMENT, EQUIPMENT_TYPE_GLOVES, "gfx/misc/defaultGloves"),
    ObjectSlotClass(OBJECT_BASE_TYPE_EQUIPMENT, EQUIPMENT_TYPE_HELMET, "gfx/misc/defaultHelmet")
};

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

void DataModule::loadClientTileTypes(const std::string &path)
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
        for(size_t j=0; j<widthQuantity; ++j) {
            for(size_t k=0; k<heightQuantity; ++k) {
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

void DataModule::loadClientSceneryTypes(const std::string &path)
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
    }
    in.close();
}

void DataModule::loadClientObjectSlotDefaultSprites()
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

void DataModule::loadClientObjectTypes(const std::string &path)
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

    while(in >> index >> name >> resourcesName >> baseType >> weaponType >> equipmentType >> attachmentType >> offsetX >> offsetY >> spriteScale >> layer >> isPassable >> isAutomatic >> isStackable >> baseDamage >> baseShotDelay >> value) {
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
    }

    in.close();
}

void DataModule::loadClientLightTypes(const std::string &path)
{
    LightType.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load light types file '%s'.", path.c_str());
    }

    std::string newTextureName;
    int newOriginX, newOriginY;

    while(in >> newTextureName >> newOriginX >> newOriginY) {
        LightType.resize(LightType.size()+1);
        loadTexture(LightType.back().texture, "gfx/lights/"+newTextureName+".png");
        LightType.back().sprite.setTexture(LightType.back().texture);

        if(newOriginX < 0) newOriginX = LightType.back().texture.getSize().x/2;
        if(newOriginY < 0) newOriginY = LightType.back().texture.getSize().y/2;

        LightType.back().sprite.setOrigin(newOriginX, newOriginY);
        LightType.back().textureName = newTextureName;
        LightType.back().originX = newOriginX;
        LightType.back().originY = newOriginY;
    }

    in.close();
}

void DataModule::loadClientStaticLightSources(const std::string &path)
{
    StaticLightSource.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load static light sources file '%s'.", path.c_str());
    }

    float newX, newY;
    int newType;
    float r, g, b;
    while(in >> newX >> newY >> newType >> r >> g >> b) {
        StaticLightSource.push_back(LightSourceClass(newX, newY, newType, sf::Vector3f(r, g, b)));
        _assert(newType >= 0 && newType < (int)LightType.size(),
                "Light type index out of bounds in loadClientStaticLightSource.");
    }

    in.close();
}

void DataModule::loadClientMap(const std::string &path)
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

void DataModule::loadClientTexts(const std::string &path)
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
        if(index >= (int)Text.size()) Text.resize(index+1);
        Text[index].str = line;
        Text[index].isLoaded = true;
    }
    in.close();
}

void DataModule::loadClientQuests(const std::string &path, const std::string &questsPath)
{
    Quest.clear();
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load quests file '%s'.", path.c_str());
    }
    int index;
    std::string name, questType;
    while(in >> index >> name >> questType) {
        if(index >= (int)Quest.size()) Quest.resize(index+1);

        for(size_t i=0; i<name.size(); ++i) {
            if(name[i] == '_') name[i] = ' ';
        }
        Quest[index].name = name;
        Quest[index].isLoaded = true;

        if(questType == "QUEST_TYPE_NONE") Quest[index].questType = QUEST_TYPE_NONE;
        else if(questType == "QUEST_TYPE_MAIN") Quest[index].questType = QUEST_TYPE_MAIN;
        else if(questType == "QUEST_TYPE_SIDE") Quest[index].questType = QUEST_TYPE_SIDE;
        else {
            error("Unknown quest type '%s' (in '%s').", questType.c_str(), path.c_str());
        }
        std::ostringstream oss;
        oss << questsPath << index;
        std::string path2 = oss.str();
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
            std::string text;
            if(cutIndex >= 0) {
                text = line.substr(cutIndex);
                util::clamp_ws(text);
            }
            Quest[index].questProgressText.push_back(QuestClass::QuestProgressTextClass(progressFrom, progressTo, text));
        }
        in2.close();
    }
    in.close();
}

void DataModule::loadServerQuests(const std::string &path)
{
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
    }
    in.close();
}

void DataModule::loadServerTileTypes(const std::string &path)
{
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load tile types file '%s'.", path.c_str());
    }
    std::string ignoreStr;
    int index, isShootThroughAble, ignoreInt;
    while(in >> ignoreStr >> index >> ignoreInt >> isShootThroughAble) {
        _assert(index >= 0 && index < (int)TileType.size(), "Tile type index out of bounds in loadServerTileTypes.");
        TileType[index].isShootThroughAble = isShootThroughAble;
    }
    in.close();
}

void DataModule::loadServerSceneryTypes(const std::string &path)
{
    std::ifstream in(path.c_str());
    if(!in) {
        error("Could not load scenery types file '%s'.", path.c_str());
    }
    std::string ignoreStr;
    int index, isShootThroughAble, ignoreInt;
    while(in >> ignoreStr >> index >> ignoreInt >> isShootThroughAble) {
        _assert(index >= 0 && index < (int)SceneryType.size(), "Scenery type index out of bounds in loadServerSceneryTypes.");
        SceneryType[index].isShootThroughAble = isShootThroughAble;
    }
    in.close();
}

void DataModule::loadServerObjectTypes(const std::string &path)
{
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

void DataModule::loadServerScripts(const std::string &path, const std::string &scriptsPath)
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

        Script[newIndex].isLoaded = true;
        Script[newIndex].IDName = newIDName;
        std::ostringstream oss;
        oss << scriptsPath << newIndex;
        std::string path2 = oss.str();
        std::ifstream in2(path2.c_str());
        if(!in2) {
            error("Could not load script file '%s'.", path2.c_str());
        }
        std::string line;
        while(std::getline(in2, line)) {
            Script[newIndex].script += line+"\n";
        }
    }
    in.close();
}

void DataModule::loadServerNPCTypes(const std::string &path, const std::string &NPCTypesPath)
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

        NPCType[newIndex].isLoaded = true;
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
                        for(size_t i=0; i<name.size(); ++i) {
                            if(name[i] == '_') name[i] = ' ';
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

void DataModule::loadServerNPCs(const std::string &path)
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
}
