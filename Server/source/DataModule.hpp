#ifndef DATA_MODULE_HPP
#define DATA_MODULE_HPP

#include <vector>
#include "Classes.hpp"
#include "utility.hpp"

class DataModule
{
    public:
        std::vector <CharacterClass> Player;
        std::vector <CharacterClass> NPC;
        std::vector <TileTypeClass> TileType;
        std::vector <SceneryTypeClass> SceneryType;
        std::vector <ObjectTypeClass> ObjectType;
        std::vector <NPCTypeClass> NPCType;
        std::vector <std::vector <TileClass> > Tile;
        std::vector <std::vector <ViewSegmentClass> > ViewSegment;
        std::list <ProjectileClass> Projectile;
        std::vector <ScriptClass> Script;
        std::vector <QuestClass> Quest;
        std::vector <FactionClass> Faction;
        WeatherClass Weather;

        int nextProjectileId;

        int getScriptIDByIDName(const std::string &IDName);
        int getQuestIDByIDName(const std::string &IDName);

        void loadMap(const std::string &path);
        void loadNPCTypes(const std::string &path, const std::string &NPCTypesPath);
        void loadNPCs(const std::string &path);
        void loadObjectTypes(const std::string &path);
        void loadQuests(const std::string &path);
        void loadSceneryTypes(const std::string &path);
        void loadScripts(const std::string &path, const std::string &scriptsPath);
        void loadTileTypes(const std::string &path);

        DataModule()
            :   nextProjectileId(0) {
        }
};

const ObjectSlotClass objectSlot[CHARACTER_OBJECT_SLOTS_QUANTITY] = {
    ObjectSlotClass(OBJECT_BASE_TYPE_WEAPON, EQUIPMENT_TYPE_NONE),
    ObjectSlotClass(OBJECT_BASE_TYPE_EQUIPMENT, EQUIPMENT_TYPE_BOOTS),
    ObjectSlotClass(OBJECT_BASE_TYPE_EQUIPMENT, EQUIPMENT_TYPE_VEST),
    ObjectSlotClass(OBJECT_BASE_TYPE_EQUIPMENT, EQUIPMENT_TYPE_GLOVES),
    ObjectSlotClass(OBJECT_BASE_TYPE_EQUIPMENT, EQUIPMENT_TYPE_HELMET)
};

const WeaponAttachmentSlotClass weaponAttachmentSlot[WEAPON_ATTACHMENTS_QUANTITY] = {
    WeaponAttachmentSlotClass(ATTACHMENT_TYPE_SIGHT),
    WeaponAttachmentSlotClass(ATTACHMENT_TYPE_BARREL),
    WeaponAttachmentSlotClass(ATTACHMENT_TYPE_MISC)
};

#endif
