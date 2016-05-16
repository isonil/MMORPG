#include "UtilityModule.hpp"

#include <sstream>
#include "Line.hpp"
#include "Master.hpp"

bool UtilityModule::isDead(const CharacterClass &ch)
{
    if(ch.param[CHARACTER_PARAM_HEALTH] <=0) return true;
    else return false;
}

bool UtilityModule::isProjectileExplosive(int projectileType)
{
    if(projectileType == PROJECTILE_TYPE_MISSILE ||
       projectileType == PROJECTILE_TYPE_GRENADE_LAUNCHER_GRENADE ||
       projectileType == PROJECTILE_TYPE_GRENADE) return true;
    else return false;
}

bool UtilityModule::isOutOfMap(int tile_x, int tile_y)
{
    if(tile_x < 0 || tile_y < 0 || tile_x >= (int)Tile.size()) return true;
    if(tile_y >= (int)Tile[tile_x].size()) return true;
    return false;
}

bool UtilityModule::isViewSegmentOutOfBounds(int viewSegment_x, int viewSegment_y)
{
    if(viewSegment_x < 0 || viewSegment_y < 0 || viewSegment_x >= (int)ViewSegment.size()) return true;
    if(viewSegment_y >= (int)ViewSegment[viewSegment_x].size()) return true;
    return false;
}

bool UtilityModule::isValidCharacterSet(char characterSet)
{
    if(characterSet == CHARACTER_PLAYER ||
       characterSet == CHARACTER_NPC) return true;
    else return false;
}

bool UtilityModule::isStackable(int objectType)
{
    _assert_return_value(objectType >= 0 && objectType < (int)ObjectType.size(), NULL, 0,
                         "Object type out of bounds in isStackable.", false);
    if(ObjectType[objectType].baseType == OBJECT_BASE_TYPE_AMMUNITION) return true;
    else return false;
}

bool UtilityModule::isPickUpAble(int objectType)
{
    _assert_return_value(objectType >= 0 && objectType < (int)ObjectType.size(), NULL, 0,
                         "Object type out of bounds in isPickUpAble.", false);
    if(ObjectType[objectType].baseType == OBJECT_BASE_TYPE_WEAPON ||
       ObjectType[objectType].baseType == OBJECT_BASE_TYPE_EQUIPMENT ||
       ObjectType[objectType].baseType == OBJECT_BASE_TYPE_ADDON ||
       ObjectType[objectType].baseType == OBJECT_BASE_TYPE_MISC) return true;
    else return false;
}

bool UtilityModule::isPassable(int tile_x, int tile_y)
{
    if(isOutOfMap(tile_x, tile_y)) return false;

    if(Tile[tile_x][tile_y].tileType >= 0) {
        _assert_return_value(Tile[tile_x][tile_y].tileType < (int)TileType.size(), NULL, 0,
                             "tileType out of bounds in isPassable.", false);
        if(!TileType[Tile[tile_x][tile_y].tileType].isPassable) return false;
    }
    else return false;

    if(Tile[tile_x][tile_y].sceneryType >= 0) {
        _assert_return_value(Tile[tile_x][tile_y].sceneryType < (int)SceneryType.size(), NULL, 0,
                             "sceneryType out of bounds in isPassable.", false);
        if(!SceneryType[Tile[tile_x][tile_y].sceneryType].isPassable) return false;
    }

    for(std::list <ObjectClass>::iterator it=Tile[tile_x][tile_y].object.begin(); it!=Tile[tile_x][tile_y].object.end(); ++it) {
        _assert_return_value(it->type < (int)ObjectType.size(), NULL, 0,
                             "ObjectType out of bounds in isPassable.", false);
        if(!ObjectType[it->type].isPassable) return false;
    }

    return true;
}

bool UtilityModule::isShootThroughAble(int tile_x, int tile_y)
{
    if(isOutOfMap(tile_x, tile_y)) return false;

    if(Tile[tile_x][tile_y].tileType >= 0) {
        _assert_return_value(Tile[tile_x][tile_y].tileType < (int)TileType.size(), NULL, 0,
                             "tileType out of bounds in isShootThroughAble.", false);
        if(!TileType[Tile[tile_x][tile_y].tileType].isShootThroughAble) return false;
    }
    if(Tile[tile_x][tile_y].sceneryType >= 0) {
        _assert_return_value(Tile[tile_x][tile_y].sceneryType < (int)SceneryType.size(), NULL, 0,
                             "sceneryType out of bounds in isShootThroughAble.", false);
        if(!SceneryType[Tile[tile_x][tile_y].sceneryType].isShootThroughAble) return false;
    }
    for(std::list <ObjectClass>::iterator it=Tile[tile_x][tile_y].object.begin(); it!=Tile[tile_x][tile_y].object.end(); ++it) {
        _assert_return_value(it->type < (int)ObjectType.size(), NULL, 0,
                             "ObjectType out of bounds in isShootThroughAble.", false);
        if(!ObjectType[it->type].isShootThroughAble) return false;
    }
    return true;
}

bool UtilityModule::isOnSight(const CharacterClass &ch1, const CharacterClass &ch2)
{
    int tile_x1 = int(ch1.x/TILE_SIZE);
    int tile_y1 = int(ch1.y/TILE_SIZE);
    int tile_x2 = int(ch2.x/TILE_SIZE);
    int tile_y2 = int(ch2.y/TILE_SIZE);
    return abs(tile_x1-tile_x2) <= PLAYER_TILES_VIEW_DISTANCE && abs(tile_y1-tile_y2) <= PLAYER_TILES_VIEW_DISTANCE;
}

bool UtilityModule::isPassableBetween(float first_x, float first_y, float second_x, float second_y)
{
    float angle = atan2(second_y-first_y, second_x-first_x);
    float step_x = cos(angle)*TILE_SIZE;
    float step_y = sin(angle)*TILE_SIZE;
    int steps = int(getDistance(first_x, first_y, second_x, second_y)/TILE_SIZE)+1;
    Line line(first_x, first_y, second_x, second_y);
    float x = first_x, y = first_y;
    for(int i=0; i<steps; ++i) {
        int tmp_tile_x = int(x/TILE_SIZE);
        int tmp_tile_y = int(y/TILE_SIZE);
        int tile_x = tmp_tile_x, tile_y = tmp_tile_y;
        for(int j=0; j<5; ++j) {
            if(j == 0)      {tile_x = tmp_tile_x; tile_y = tmp_tile_y;}
            else if(j == 1) {tile_x = tmp_tile_x; tile_y = tmp_tile_y-1;}
            else if(j == 2) {tile_x = tmp_tile_x; tile_y = tmp_tile_y+1;}
            else if(j == 3) {tile_x = tmp_tile_x-1; tile_y = tmp_tile_y;}
            else if(j == 4) {tile_x = tmp_tile_x+1; tile_y = tmp_tile_y;}
            if(!isPassable(tile_x, tile_y)) {
                if(line.collidesWith(Line(tile_x*TILE_SIZE, tile_y*TILE_SIZE, tile_x*TILE_SIZE+TILE_SIZE, tile_y*TILE_SIZE))) return false;
                else if(line.collidesWith(Line(tile_x*TILE_SIZE+TILE_SIZE, tile_y*TILE_SIZE,tile_x*TILE_SIZE+TILE_SIZE, tile_y*TILE_SIZE+TILE_SIZE))) return false;
                else if(line.collidesWith(Line(tile_x*TILE_SIZE+TILE_SIZE, tile_y*TILE_SIZE+TILE_SIZE, tile_x*TILE_SIZE, tile_y*TILE_SIZE+TILE_SIZE))) return false;
                else if(line.collidesWith(Line(tile_x*TILE_SIZE, tile_y*TILE_SIZE+TILE_SIZE, tile_x*TILE_SIZE, tile_y*TILE_SIZE))) return false;
            }
        }
        x += step_x;
        y += step_y;
    }
    return true;
}

bool UtilityModule::isShootThroughAbleBetween(float first_x, float first_y, float second_x, float second_y)
{
    float angle = atan2(second_y-first_y, second_x-first_x);
    float step_x = cos(angle)*TILE_SIZE;
    float step_y = sin(angle)*TILE_SIZE;
    int steps = int(getDistance(first_x, first_y, second_x, second_y)/TILE_SIZE)+1;
    Line line(first_x, first_y, second_x, second_y);
    float x = first_x, y = first_y;
    for(int i=0; i<steps; ++i) {
        int tmp_tile_x = int(x/TILE_SIZE);
        int tmp_tile_y = int(y/TILE_SIZE);
        int tile_x = tmp_tile_x, tile_y = tmp_tile_y;
        for(int j=0; j<5; ++j) {
            if(j == 0)      {tile_x = tmp_tile_x; tile_y = tmp_tile_y;}
            else if(j == 1) {tile_x = tmp_tile_x; tile_y = tmp_tile_y-1;}
            else if(j == 2) {tile_x = tmp_tile_x; tile_y = tmp_tile_y+1;}
            else if(j == 3) {tile_x = tmp_tile_x-1; tile_y = tmp_tile_y;}
            else if(j == 4) {tile_x = tmp_tile_x+1; tile_y = tmp_tile_y;}
            if(!isShootThroughAble(tile_x, tile_y)) {
                if(line.collidesWith(Line(tile_x*TILE_SIZE, tile_y*TILE_SIZE, tile_x*TILE_SIZE+TILE_SIZE, tile_y*TILE_SIZE))) return false;
                else if(line.collidesWith(Line(tile_x*TILE_SIZE+TILE_SIZE, tile_y*TILE_SIZE,tile_x*TILE_SIZE+TILE_SIZE, tile_y*TILE_SIZE+TILE_SIZE))) return false;
                else if(line.collidesWith(Line(tile_x*TILE_SIZE+TILE_SIZE, tile_y*TILE_SIZE+TILE_SIZE, tile_x*TILE_SIZE, tile_y*TILE_SIZE+TILE_SIZE))) return false;
                else if(line.collidesWith(Line(tile_x*TILE_SIZE, tile_y*TILE_SIZE+TILE_SIZE, tile_x*TILE_SIZE, tile_y*TILE_SIZE))) return false;
            }
        }
        x += step_x;
        y += step_y;
    }
    return true;
}

bool UtilityModule::canObjectBePlacedOnSlot(int objectType, int slotIndex)
{
    if(objectType < 0) return false;
    _assert_return_value(objectType < (int)ObjectType.size(), NULL, 0,
                         "Object type out of bounds in canObjectBePlacedOnSlot.", false);
    _assert_return_value(slotIndex >= 0 && slotIndex < CHARACTER_OBJECT_SLOTS_QUANTITY, NULL, 0,
                         "Object slot index out of bounds in canObjectBePlacedOnSlot.", false);
    if(ObjectType[objectType].baseType != objectSlot[slotIndex].baseType) return false;

    if(objectSlot[slotIndex].baseType == OBJECT_BASE_TYPE_EQUIPMENT) {
        if(ObjectType[objectType].equipmentType == objectSlot[slotIndex].equipmentType)
            return true;
        else return false;
    }
    return true;
}

bool UtilityModule::NPCCollides(int NPCIndex)
{
    _assert_return_value(NPCIndex >= 0 && NPCIndex < (int)NPC.size(), NULL, 0,
                         "NPCIndex out of bounds in NPCCollides.", true);

    int tile_x = int(NPC[NPCIndex].x/TILE_SIZE);
    int tile_y = int(NPC[NPCIndex].y/TILE_SIZE);

    for(int i=tile_x-1; i<=tile_x+1; ++i) {
        for(int j=tile_y-1; j<=tile_y+1; ++j) {
            if(isOutOfMap(i, j)) continue;
            for(size_t k=0; k<Tile[i][j].playerIndex.size(); ++k) {
                int playerIndex = Tile[i][j].playerIndex[k];
                if(getDistance((int)Player[playerIndex].x, (int)Player[playerIndex].y, (int)NPC[NPCIndex].x, (int)NPC[NPCIndex].y) <= 2*CHARACTER_RADIUS) {
                    return true;
                }
            }
            for(size_t k=0; k<Tile[i][j].NPCIndex.size(); ++k) {
                int NPCIndexFromTile = Tile[i][j].NPCIndex[k];
                if(NPCIndexFromTile == NPCIndex) continue;
                if(getDistance((int)NPC[NPCIndexFromTile].x, (int)NPC[NPCIndexFromTile].y, (int)NPC[NPCIndex].x, (int)NPC[NPCIndex].y) <= 2*CHARACTER_RADIUS) {
                    return true;
                }
            }
        }
    }
    for(int i=int(NPC[NPCIndex].x/TILE_SIZE-1); i<=NPC[NPCIndex].x/TILE_SIZE+1; ++i) {
        for(int j=int(NPC[NPCIndex].y/TILE_SIZE-1); j<=NPC[NPCIndex].y/TILE_SIZE+1; ++j) {
            if(!isPassable(i, j) &&
                NPC[NPCIndex].x-CHARACTER_RADIUS<i*TILE_SIZE+TILE_SIZE &&
                NPC[NPCIndex].x+CHARACTER_RADIUS>i*TILE_SIZE &&
                NPC[NPCIndex].y-CHARACTER_RADIUS<j*TILE_SIZE+TILE_SIZE &&
                NPC[NPCIndex].y+CHARACTER_RADIUS>j*TILE_SIZE) {
                    return true;
            }
        }
    }
    return false;
}

bool UtilityModule::playerCollides(int playerIndex)
{
    _assert(playerIndex >= 0 && playerIndex < (int)Player.size(), NULL, 0,
            "playerIndex out of bounds in playerCollides.");

    int tile_x = int(Player[playerIndex].x/TILE_SIZE);
    int tile_y = int(Player[playerIndex].y/TILE_SIZE);

    for(int i=tile_x-1; i<=tile_x+1; ++i) {
        for(int j=tile_y-1; j<=tile_y+1; ++j) {
            if(isOutOfMap(i, j)) continue;
            for(size_t k=0; k<Tile[i][j].playerIndex.size(); ++k) {
                int playerIndexFromTile = Tile[i][j].playerIndex[k];
                if(playerIndexFromTile == playerIndex) continue;
                if(getDistance((int)Player[playerIndexFromTile].x, (int)Player[playerIndexFromTile].y, (int)Player[playerIndex].x, (int)Player[playerIndex].y) <= 2*CHARACTER_RADIUS) {
                    return true;
                }
            }
            for(size_t k=0; k<Tile[i][j].NPCIndex.size(); ++k) {
                int NPCIndex = Tile[i][j].NPCIndex[k];
                if(getDistance((int)NPC[NPCIndex].x, (int)NPC[NPCIndex].y, (int)Player[playerIndex].x, (int)Player[playerIndex].y) <= 2*CHARACTER_RADIUS) {
                    return true;
                }
            }
        }
    }
    for(int i=int(Player[playerIndex].x/TILE_SIZE-1); i<=Player[playerIndex].x/TILE_SIZE+1; ++i) {
        for(int j=int(Player[playerIndex].y/TILE_SIZE-1); j<=Player[playerIndex].y/TILE_SIZE+1; ++j) {
            if(!isPassable(i, j) &&
                Player[playerIndex].x-CHARACTER_RADIUS<i*TILE_SIZE+TILE_SIZE &&
                Player[playerIndex].x+CHARACTER_RADIUS>i*TILE_SIZE &&
                Player[playerIndex].y-CHARACTER_RADIUS<j*TILE_SIZE+TILE_SIZE &&
                Player[playerIndex].y+CHARACTER_RADIUS>j*TILE_SIZE) {
                    return true;
            }
        }
    }
    return false;
}

void UtilityModule::updateDelta()
{
    sf::Int64 currentTime = globalClock.getElapsedTime().asMicroseconds();
    static sf::Int64 lastTime = currentTime;
    deltaTime = (currentTime-lastTime)/(1000000.0/30.0);
    lastTime = currentTime;
}

void UtilityModule::getObjectParams(std::ostringstream &oss, const ObjectClass &object)
{
    _assert_return(object.type < (int)ObjectType.size(), NULL, 0,
                   "Object type out of bounds in getObjectParams.");
    if(object.type >= 0) {
        if(ObjectType[object.type].baseType == OBJECT_BASE_TYPE_WEAPON) {
            oss
                << object.type << " "
                << object.param[OBJECT_PARAM_ADDON_1] << " "
                << object.param[OBJECT_PARAM_ADDON_2] << " "
                << object.param[OBJECT_PARAM_ADDON_3] << " ";
        }
        else if(ObjectType[object.type].baseType == OBJECT_BASE_TYPE_STRUCTURE) {
            oss
                << object.type << " "
                << object.param[OBJECT_PARAM_OWNER] << " "
                << object.param[OBJECT_PARAM_CONDITION] << " "
                << 0 << " ";
        }
        else if(isStackable(object.type)) {
            oss
                << object.type << " "
                << object.param[OBJECT_PARAM_QUANTITY] << " "
                << 0 << " "
                << 0 << " ";
        }
        else {
            oss
                << object.type << " "
                << 0 << " "
                << 0 << " "
                << 0 << " ";
        }
    }
    else {
        oss << "-1 0 0 0 ";
    }
}

void UtilityModule::runScript(int playerIndex, int scriptIndex)
{
    _assert_return(scriptIndex >= 0 && scriptIndex < (int)Script.size(), NULL, 0,
                   "Script index out of bounds in runScript.");
    _assert_return(playerIndex >= 0 && playerIndex < (int)Player.size(), NULL, 0,
                   "Player index out of bounds in runScript.");

    for(size_t i=0; i<Script[scriptIndex].instruction.size(); ++i) {
        if(Script[scriptIndex].instruction[i].ifStatement) {
            bool res = false;
            if(Script[scriptIndex].instruction[i].callFunc == SCRIPT_IF_FUNC_QUEST_PROGRESS) {
                res = false;
            }
            else {
                _assert_return(0, NULL, 0, "Unknown script callFunc in runScript.");
            }
            if(!res) i = Script[scriptIndex].instruction[i].ifStatementJumpToInstruction-1;
        }
        else {
            if(Script[scriptIndex].instruction[i].callFunc == SCRIPT_FUNC_ADD_EXP) {
                changePlayerExpBy(playerIndex, Script[scriptIndex].instruction[i].p1int);
            }
            else if(Script[scriptIndex].instruction[i].callFunc == SCRIPT_FUNC_ADD_MONEY) {
                changeCharacterParamBy(Player[playerIndex], CHARACTER_PLAYER, playerIndex, CHARACTER_PARAM_MONEY, Script[scriptIndex].instruction[i].p1int, false);
            }
            else if(Script[scriptIndex].instruction[i].callFunc == SCRIPT_FUNC_SET_QUEST_PROGRESS) {
                _assert_return(Script[scriptIndex].instruction[i].p1int >= 0 &&
                               Script[scriptIndex].instruction[i].p1int < (int)Quest.size(),
                               NULL, 0, "Quest index out of bounds in runScript.");
                Player[playerIndex].questProgress[Script[scriptIndex].instruction[i].p1int] = Script[scriptIndex].instruction[i].p2int;

                std::string packet = Packet <PACKET_QUEST_PROGRESS_CHANGE>::construct(M.Script[scriptIndex].instruction[i].p1int,
                                                                                      M.Player[playerIndex].questProgress[M.Script[scriptIndex].instruction[i].p1int]);
                M.Player[playerIndex].sendPacket(packet);
            }
            else if(Script[scriptIndex].instruction[i].callFunc == SCRIPT_FUNC_END_DIALOGUE) {
                endNPCInteraction(Player[playerIndex]);
            }
            else {
                _assert_return(0, NULL, 0, "Unknown script callFunc in runScript.");
            }
        }
    }
}

int UtilityModule::logInToAccount(const std::string &name, const std::string &password)
{
    for(size_t i=0; i<Player.size(); ++i) {
        if(Player[i].name == name && Player[i].password == password) {
            if(Player[i].isOnline) return LOG_IN_ERROR_ALREADY_LOGGED_IN;
            if(globalTime < Player[i].timeout_logIn) return LOG_IN_ERROR_TIMEOUT;
            Player[i].timeout_logIn = globalTime+10000.0;
            return i;
        }
    }
    return LOG_IN_ERROR_WRONG_NAME_OR_PASSWORD;
}

bool UtilityModule::characterShoot(const CharacterClass &character, char shooterCharacterSet, int shooterIndex)
{
    const ObjectClass *weapon = &character.objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX];
    if(weapon->type < 0) return false;
    _assert_return_value(weapon->type < (int)ObjectType.size(), NULL, 0,
                         "Weapon object type out of bounds in characterShoot.", false);
    if(ObjectType[weapon->type].baseType != OBJECT_BASE_TYPE_WEAPON) return false;

    int x = (int)character.x;
    int y = (int)character.y;
    if(ObjectType[weapon->type].weaponType == WEAPON_TYPE_SMALL_GUN) {
        x += int(cos(character.dir)*34.f+cos(character.dir+M_PI/2.f)*2.f);
        y += int(sin(character.dir)*34.f+sin(character.dir+M_PI/2.f)*2.f);
    }
    else if(ObjectType[weapon->type].weaponType == WEAPON_TYPE_BIG_GUN) {
        x += int(cos(character.dir)*35.f+cos(character.dir+M_PI/2.f)*11.f);
        y += int(sin(character.dir)*35.f+sin(character.dir+M_PI/2.f)*11.f);
    }
    else if(ObjectType[weapon->type].weaponType == WEAPON_TYPE_ROCKET_LAUNCHER) {
        x += int(cos(character.dir)*35.f+cos(character.dir+M_PI/2.f)*11.f);
        y += int(sin(character.dir)*35.f+sin(character.dir+M_PI/2.f)*11.f);
    }
    int dir = int((character.dir+(rand()%21-10)/100.f)*100.f);
    int damage = ObjectType[weapon->type].baseDamage;
    for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
        /*
        to do:
        if(i!=CHARACTER_OBJECT_SLOT_WEAPON_INDEX)
            damage+=ObjectType[Character.objectOnSlot[i].type].damage_bonus? base_damage?
            if damage_bonus no if(i!=CHARACTER_OBJECT_SLOT_WEAPON_INDEX)
        */
    }
    int projectileType = PROJECTILE_TYPE_BULLET;
    if(ObjectType[weapon->type].weaponType == WEAPON_TYPE_ROCKET_LAUNCHER)
        projectileType = PROJECTILE_TYPE_MISSILE;
    Projectile.push_back(ProjectileClass(shooterCharacterSet, shooterIndex, x, y, dir/100.f, nextProjectileId, projectileType, character.team, damage, false));

    std::string packet = Packet <PACKET_SHOT>::construct(shooterCharacterSet, shooterIndex, x, y, dir, nextProjectileId, weapon->type);
    sendToAllPlayersInView(packet.c_str(), 2, character.x, character.y, -1);

    ++nextProjectileId;
    return true;
}

bool UtilityModule::characterShootGrenadeLauncher(const CharacterClass &character, char shooterCharacterSet, int shooterIndex, int target_x, int target_y)
{
    const ObjectClass *weapon = &character.objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX];
    if(weapon->type < 0) return false;
    _assert_return_value(weapon->type < (int)ObjectType.size(), NULL, 0,
                         "Weapon object type out of bounds in characterShootGrenadeLauncher.", false);
    if(ObjectType[weapon->type].baseType != OBJECT_BASE_TYPE_WEAPON) return false;

    int x = (int)character.x;
    int y = (int)character.y;
    if(ObjectType[weapon->type].weaponType == WEAPON_TYPE_SMALL_GUN) {
        x += int(cos(character.dir)*34.f+cos(character.dir+M_PI/2.f)*2.f);
        y += int(sin(character.dir)*34.f+sin(character.dir+M_PI/2.f)*2.f);
    }
    else if(ObjectType[weapon->type].weaponType == WEAPON_TYPE_BIG_GUN) {
        x += int(cos(character.dir)*35.f+cos(character.dir+M_PI/2.f)*11.f);
        y += int(sin(character.dir)*35.f+sin(character.dir+M_PI/2.f)*11.f);
    }
    else if(ObjectType[weapon->type].weaponType == WEAPON_TYPE_ROCKET_LAUNCHER) {
        x += int(cos(character.dir)*35.f+cos(character.dir+M_PI/2.f)*11.f);
        y += int(sin(character.dir)*35.f+sin(character.dir+M_PI/2.f)*11.f);
    }
    float dir = atan2(target_y-y, target_x-x);
    int damage=0; //to do: calculate damage
    Projectile.push_back(ProjectileClass(shooterCharacterSet, shooterIndex, x, y, dir, nextProjectileId, PROJECTILE_TYPE_GRENADE_LAUNCHER_GRENADE, character.team, damage, false));
    Projectile.back().target_x = target_x;
    Projectile.back().target_y = target_y;

    std::string packet = Packet <PACKET_GRENADE_LAUNCHER_SHOT>::construct(shooterCharacterSet, shooterIndex, x, y, int(dir*100.f), nextProjectileId, weapon->type);
    sendToAllPlayersInView(packet.c_str(), 2, character.x, character.y, -1);

    ++nextProjectileId;
    return true;
}

bool UtilityModule::characterThrowGrenade(const CharacterClass &character, char shooterCharacterSet, int shooterIndex, int target_x, int target_y)
{
    int x = (int)character.x;
    int y = (int)character.y;
    float dir = atan2(target_y-y,target_x-x);
    int damage = 0; //to do: calculate damage
    Projectile.push_back(ProjectileClass(shooterCharacterSet, shooterIndex, x, y, dir, nextProjectileId, PROJECTILE_TYPE_GRENADE, character.team, damage, false));
    Projectile.back().target_x = target_x;
    Projectile.back().target_y = target_y;
    Projectile.back().grenadeThrowDistance = getDistance(x, y, target_x, target_y);
    Projectile.back().timeout_grenadeExplode = globalTime+3000.0;

    std::string packet = Packet <PACKET_GRENADE_THROW>::construct(shooterCharacterSet, shooterIndex, x, y, int(dir*100.f), nextProjectileId, target_x, target_y);
    sendToAllPlayersInView(packet.c_str(), 2, character.x, character.y, -1);

    ++nextProjectileId;
    return true;
}

void UtilityModule::changePlayerExpBy(int playerIndex, int value)
{
    if(!value) return;
    _assert_return(playerIndex >= 0 && playerIndex < (int)Player.size(), NULL, 0,
                   "Player index out of bounds in changePlayerExpBy.");

    int levelBefore = Player[playerIndex].param[CHARACTER_PARAM_LEVEL];
    Player[playerIndex].param[CHARACTER_PARAM_EXPERIENCE] += value;
    if(Player[playerIndex].param[CHARACTER_PARAM_EXPERIENCE] < 0)
        Player[playerIndex].param[CHARACTER_PARAM_EXPERIENCE] = 0;
    for(int i=0; i<EXP_TABLE_SIZE; ++i) {
        if(Player[playerIndex].param[CHARACTER_PARAM_EXPERIENCE] >= EXP_TABLE[i]) {
            Player[playerIndex].param[CHARACTER_PARAM_LEVEL] = i;
        }
    }
    int levelAfter = Player[playerIndex].param[CHARACTER_PARAM_LEVEL];

    std::string packet = Packet <PACKET_CHARACTER_PARAM_CHANGE>::construct(CHARACTER_PLAYER, playerIndex, CHARACTER_PARAM_EXPERIENCE, M.Player[playerIndex].param[CHARACTER_PARAM_EXPERIENCE]);
    M.Player[playerIndex].sendPacket(packet);

    if(levelBefore != levelAfter) {
        packet = Packet <PACKET_CHARACTER_PARAM_CHANGE>::construct(CHARACTER_PLAYER, playerIndex, CHARACTER_PARAM_LEVEL, M.Player[playerIndex].param[CHARACTER_PARAM_LEVEL]);
        M.sendToAllPlayersInView(packet.c_str(), 1, M.Player[playerIndex].x, M.Player[playerIndex].y, -1);
    }
}

void UtilityModule::changeCharacterParamTo(CharacterClass &character, char characterSet, int characterIndex, int param, int value, bool sendToAllInView)
{
    _assert_return(isValidCharacterSet(characterSet), NULL, 0,
                   "Invalid characterSet in changeCharacterParamTo.");
    _assert_return(param >= 0 && param < CHARACTER_PARAMS_QUANTITY, NULL, 0,
                   "Character param out of bounds in changeCharacterParamTo.");

    character.param[param] = value;

    std::string packet = Packet <PACKET_CHARACTER_PARAM_CHANGE>::construct(characterSet, characterIndex, param, character.param[param]);
    if(characterSet == CHARACTER_PLAYER && !sendToAllInView) {
        character.sendPacket(packet);
    }
    if(sendToAllInView) {
        sendToAllPlayersInView(packet.c_str(), 1, character.x, character.y, -1);
    }
}

void UtilityModule::changeCharacterParamBy(CharacterClass &character, char characterSet, int characterIndex, int param, int value, bool sendToAllInView)
{
    if(!value) return;
    _assert_return(isValidCharacterSet(characterSet), NULL, 0,
                   "Invalid characterSet in changeCharacterParamBy.");
    _assert_return(param >= 0 && param < CHARACTER_PARAMS_QUANTITY, NULL, 0,
                   "Character param out of bounds in changeCharacterParamBy.");

    character.param[param] += value;

    std::string packet = Packet <PACKET_CHARACTER_PARAM_CHANGE>::construct(characterSet, characterIndex, param, character.param[param]);
    if(characterSet == CHARACTER_PLAYER && !sendToAllInView) {
        character.sendPacket(packet);
    }
    if(sendToAllInView) {
        sendToAllPlayersInView(packet.c_str(), 1, character.x, character.y, -1);
    }
}

bool UtilityModule::changeCharacterPosition(char characterSet, int characterIndex, float x, float y, bool searchFreeSpace)
{
    _assert_return_value(isValidCharacterSet(characterSet), NULL, 0,
                         "Invalid characterSet in changeCharacterPosition.", false);

    CharacterClass *character;
    if(characterSet == CHARACTER_PLAYER) {
        _assert_return_value(characterIndex < (int)Player.size(), NULL, 0,
                             "Player index out of bounds in changeCharacterPosition.", false);
        character = &Player[characterIndex];
    }
    else {
        _assert_return_value(characterIndex < (int)NPC.size(), NULL, 0,
                             "NPC index out of bounds in changeCharacterPosition.", false);
        character = &NPC[characterIndex];
    }

    int tile_startX = int(character->x/TILE_SIZE);
    int tile_startY = int(character->y/TILE_SIZE);
    int viewSegment_startX = int(character->x/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));
    int viewSegment_startY = int(character->y/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));
    float start_x = character->x;
    float start_y = character->y;

    _assert_return_value(!isOutOfMap(tile_startX, tile_startY), NULL, 0,
                         "Starting position out of bounds in changeCharacterPosition.", false)
    _assert_return_value(!isViewSegmentOutOfBounds(viewSegment_startX, viewSegment_startY), NULL, 0,
                         "Starting view segment out of bounds in changeCharacterPosition.", false);

    if(searchFreeSpace) {
        for(int i=0; i<5; ++i) {
            character->x = x ;
            character->y = y;
            if(i == 1)      {character->x = x+TILE_SIZE; character->y = y;}
            else if(i == 2) {character->x = x-TILE_SIZE; character->y = y;}
            else if(i == 3) {character->x = x; character->y = y+TILE_SIZE;}
            else if(i == 4) {character->x = x; character->y = y-TILE_SIZE;}
            bool collides = false;
            if(isOutOfMap(int(character->x/TILE_SIZE), int(character->y/TILE_SIZE))) collides = true;
            else if(characterSet == CHARACTER_PLAYER) collides = playerCollides(characterIndex);
            else if(characterSet == CHARACTER_NPC) collides = NPCCollides(characterIndex);
            if(!collides) break;
            else if(i == 4) {
                character->x = start_x;
                character->y = start_y;
                return false;
            }
        }
    }
    else {
        character->x = x;
        character->y = y;
        bool collides = false;
        if(characterSet == CHARACTER_PLAYER) collides = playerCollides(characterIndex);
        else if(characterSet == CHARACTER_NPC) collides = NPCCollides(characterIndex);
        if(collides) {
            character->x = start_x;
            character->y = start_y;
            return false;
        }
    }

    int tile_x = int(character->x/TILE_SIZE);
    int tile_y = int(character->y/TILE_SIZE);
    int viewSegment_x = int(character->x/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));
    int viewSegment_y = int(character->y/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));

    if(tile_startX != tile_x || tile_startY != tile_y) {
        _assert_return_value(!isOutOfMap(tile_x, tile_y), NULL, 0,
                             "Position after move out of bounds in changeCharacterPosition.", false);
        if(characterSet == CHARACTER_PLAYER) {
            removePlayerIndexFromTile(tile_startX, tile_startY, characterIndex);
            Tile[tile_x][tile_y].playerIndex.push_back(characterIndex);
        }
        else if(characterSet == CHARACTER_NPC) {
            removeNPCIndexFromTile(tile_startX, tile_startY, characterIndex);
            Tile[tile_x][tile_y].NPCIndex.push_back(characterIndex);
        }
    }

    if(viewSegment_startX != viewSegment_x || viewSegment_startY != viewSegment_y) {
        _assert_return_value(!isViewSegmentOutOfBounds(viewSegment_x, viewSegment_y), NULL, 0,
                             "View segment after move out of bounds in changeCharacterPosition.", false);
        if(characterSet == CHARACTER_PLAYER) {
            removePlayerIndexFromViewSegment(viewSegment_startX, viewSegment_startY, characterIndex);
            ViewSegment[viewSegment_x][viewSegment_y].playerIndex.push_back(characterIndex);
        }
        else if(characterSet == CHARACTER_NPC) {
            removeNPCIndexFromViewSegment(viewSegment_startX, viewSegment_startY, characterIndex);
            ViewSegment[viewSegment_x][viewSegment_y].NPCIndex.push_back(characterIndex);
        }
    }

    float end_x = character->x;
    float end_y = character->y;
    for(int i=viewSegment_startX-1; i<=viewSegment_startX+1; ++i) {
        for(int j=viewSegment_startY-1; j<=viewSegment_startY+1; ++j) {
            if(isViewSegmentOutOfBounds(i, j)) continue;
            for(size_t k=0; k<ViewSegment[i][j].playerIndex.size(); ++k) {
                int playerIndex = ViewSegment[i][j].playerIndex[k];
                if(characterSet == CHARACTER_PLAYER && characterIndex == playerIndex) continue;
                character->x = start_x;
                character->y = start_y;
                bool startOnSight = isOnSight(*character, Player[playerIndex]);
                character->x = end_x;
                character->y = end_y;
                bool endOnSight = isOnSight(*character, Player[playerIndex]);
                if(startOnSight && !endOnSight) {
                    std::string packet = Packet <PACKET_CHARACTER_LOST_SIGHT>::construct(characterSet, characterIndex);
                    Player[playerIndex].sendPacket(packet);
                    if(characterSet == CHARACTER_PLAYER) {
                        packet = Packet <PACKET_CHARACTER_LOST_SIGHT>::construct(CHARACTER_PLAYER, playerIndex);
                        Player[characterIndex].sendPacket(packet);
                    }
                }
            }
            if(characterSet == CHARACTER_PLAYER) {
                for(size_t k=0; k<ViewSegment[i][j].NPCIndex.size(); ++k) {
                    int NPCIndex = ViewSegment[i][j].NPCIndex[k];
                    character->x = start_x;
                    character->y = start_y;
                    bool startOnSight = isOnSight(*character, NPC[NPCIndex]);
                    character->x = end_x;
                    character->y = end_y;
                    bool endOnSight = isOnSight(*character, NPC[NPCIndex]);
                    if(startOnSight && !endOnSight) {
                        std::string packet = Packet <PACKET_CHARACTER_LOST_SIGHT>::construct(CHARACTER_NPC, NPCIndex);
                        M.Player[characterIndex].sendPacket(packet);
                    }
                }
            }
        }
    }
    for(int i=viewSegment_x-1; i<=viewSegment_x+1; ++i) {
        for(int j=viewSegment_y-1; j<=viewSegment_y+1; ++j) {
            if(isViewSegmentOutOfBounds(i, j)) continue;
            for(size_t k=0; k<ViewSegment[i][j].playerIndex.size(); ++k) {
                int playerIndex = ViewSegment[i][j].playerIndex[k];
                if(characterSet == CHARACTER_PLAYER && characterIndex == playerIndex) continue;
                character->x = start_x;
                character->y = start_y;
                bool startOnSight = isOnSight(*character, Player[playerIndex]);
                character->x = end_x;
                character->y = end_y;
                bool endOnSight = isOnSight(*character, Player[playerIndex]);
                if(!startOnSight && endOnSight) {
                    std::string packet;
                    if(characterSet == CHARACTER_PLAYER)
                        packet = Packet <PACKET_CHARACTER_PARAMS>::construct(Player[characterIndex], CHARACTER_PLAYER, characterIndex);
                    else if(characterSet == CHARACTER_NPC)
                        packet = Packet <PACKET_CHARACTER_PARAMS>::construct(NPC[characterIndex], CHARACTER_NPC, characterIndex);
                    M.Player[playerIndex].sendPacket(packet);
                    if(characterSet == CHARACTER_PLAYER) {
                        packet = Packet <PACKET_CHARACTER_PARAMS>::construct(Player[playerIndex], CHARACTER_PLAYER, playerIndex);
                        M.Player[characterIndex].sendPacket(packet);
                    }
                }
            }
            if(characterSet == CHARACTER_PLAYER) {
                for(size_t k=0; k<ViewSegment[i][j].NPCIndex.size(); ++k) {
                    int NPCIndex = ViewSegment[i][j].NPCIndex[k];
                    character->x = start_x;
                    character->y = start_y;
                    bool startOnSight = isOnSight(*character, NPC[NPCIndex]);
                    character->x = end_x;
                    character->y = end_y;
                    bool endOnSight = isOnSight(*character, NPC[NPCIndex]);
                    if(!startOnSight && endOnSight) {
                        std::string packet = Packet <PACKET_CHARACTER_PARAMS>::construct(NPC[NPCIndex], CHARACTER_NPC, NPCIndex);
                        M.Player[characterIndex].sendPacket(packet);
                    }
                }
            }
        }
    }

    //to do: move character check (appear, dissappear) to this \/ (maybe)
    if(characterSet == CHARACTER_PLAYER && (tile_startX != tile_x || tile_startY != tile_y)) {
        int start_x1 = tile_startX-PLAYER_TILES_VIEW_DISTANCE;
        int start_y1 = tile_startY-PLAYER_TILES_VIEW_DISTANCE;
        int start_x2 = tile_startX+PLAYER_TILES_VIEW_DISTANCE;
        int start_y2 = tile_startY+PLAYER_TILES_VIEW_DISTANCE;
        int end_x1 = tile_x-PLAYER_TILES_VIEW_DISTANCE;
        int end_y1 = tile_y-PLAYER_TILES_VIEW_DISTANCE;
        int end_x2 = tile_x+PLAYER_TILES_VIEW_DISTANCE;
        int end_y2 = tile_y+PLAYER_TILES_VIEW_DISTANCE;
        if(start_x1 >= end_x1 && start_y1 >= end_y1 && start_x1 <= end_x2 && start_y1 <= end_y2) {
            for(int i=end_x2+1; i<=start_x2; ++i) {
                for(int j=start_y1; j<=start_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, true);
                        character->sendPacket(packet);
                    }
                }
            }
            for(int i=start_x1; i<=end_x2; ++i) {
                for(int j=end_y2+1; j<=start_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, true);
                        character->sendPacket(packet);
                    }
                }
            }
            for(int i=end_x1; i<=end_x2; ++i) {
                for(int j=end_y1; j<start_y1; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, false);
                        character->sendPacket(packet);
                    }
                }
            }
            for(int i=end_x1; i<start_x1; ++i) {
                for(int j=start_y1; j<=end_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, false);
                        character->sendPacket(packet);
                    }
                }
            }
        }
        else if(start_x2 >= end_x1 && start_y1 >= end_y1 && start_x2 <= end_x2 && start_y1 <= end_y2) {
            for(int i=start_x1; i<end_x1; ++i) {
                for(int j=start_y1; j<=start_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, true);
                        character->sendPacket(packet);
                    }
                }
            }
            for(int i=end_x1; i<=start_x2; ++i) {
                for(int j=end_y2+1; j<=start_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, true);
                        character->sendPacket(packet);
                    }
                }
            }
            for(int i=end_x1; i<=end_x2; ++i) {
                for(int j=end_y1; j<start_y1; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, false);
                        character->sendPacket(packet);
                    }
                }
            }
            for(int i=start_x2+1; i<=end_x2; ++i) {
                for(int j=start_y1; j<=end_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, false);
                        character->sendPacket(packet);
                    }
                }
            }
        }
        else if(start_x2 >= end_x1 && start_y2 >= end_y1 && start_x2 <= end_x2 && start_y2 <= end_y2) {
            for(int i=start_x1; i<=start_x2; ++i) {
                for(int j=start_y1; j<end_y1; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, true);
                        character->sendPacket(packet);
                    }
                }
            }
            for(int i=start_x1; i<end_x1; ++i) {
                for(int j=end_y1; j<=start_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, true);
                        character->sendPacket(packet);
                    }
                }
            }
            for(int i=start_x2+1; i<=end_x2; ++i) {
                for(int j=end_y1; j<=end_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, false);
                        character->sendPacket(packet);
                    }
                }
            }
            for(int i=end_x1; i<=start_x2; ++i) {
                for(int j=start_y2+1; j<=end_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, false);
                        character->sendPacket(packet);
                    }
                }
            }
        }
        else if(start_x1 >= end_x1 && start_y2 >= end_y1 && start_x1 <= end_x2 && start_y2 <= end_y2) {
            for(int i=start_x1; i<=start_x2; ++i) {
                for(int j=start_y1; j<end_y1; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, true);
                        character->sendPacket(packet);
                    }
                }
            }
            for(int i=end_x2+1; i<=start_x2; ++i) {
                for(int j=end_y1; j<=start_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, true);
                        character->sendPacket(packet);
                    }
                }
            }
            for(int i=end_x1; i<start_x1; ++i) {
                for(int j=end_y1; j<=end_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, false);
                        character->sendPacket(packet);
                    }
                }
            }
            for(int i=start_x1; i<=end_x2; ++i) {
                for(int j=start_y2+1; j<=end_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, false);
                        character->sendPacket(packet);
                    }
                }
            }
        }
        else {
            for(int i=start_x1; i<=start_x2; ++i) {
                for(int j=start_y1; j<=start_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, true);
                        character->sendPacket(packet);
                    }
                }
            }
            for(int i=end_x1; i<=end_x2; ++i) {
                for(int j=end_y1; j<=end_y2; ++j) {
                    if(isOutOfMap(i, j)) continue;
                    if(!Tile[i][j].object.empty()) {
                        std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, false);
                        character->sendPacket(packet);
                    }
                }
            }
        }
    }

    return true;
}

char UtilityModule::projectileMove(ProjectileClass &projectile)
{
    float step_x = 0.f;
    float step_y = 0.f;

    if(projectile.projectileType == PROJECTILE_TYPE_MISSILE) {
        float boost = projectile.distanceTraveled/20.f+15.f;
        step_x = deltaTime*boost;
        step_y = deltaTime*boost;
    }
    else if(projectile.projectileType == PROJECTILE_TYPE_GRENADE_LAUNCHER_GRENADE) {
        step_x = deltaTime*30.f;
        step_y = deltaTime*30.f;
    }
    else if(projectile.projectileType == PROJECTILE_TYPE_GRENADE) {
        if(projectile.distanceTraveled >= projectile.grenadeThrowDistance) {
            if(projectile.distanceTraveled < projectile.grenadeThrowDistance+40.f) {
                projectile.grenadeFlySpeed = 8.f;
            }
            else if(projectile.distanceTraveled < projectile.grenadeThrowDistance+60.f) {
                projectile.grenadeFlySpeed = 3.f;
            }
            else if(projectile.distanceTraveled < projectile.grenadeThrowDistance+70.f) {
                projectile.grenadeFlySpeed = 1.f;
            }
            else projectile.grenadeFlySpeed = 0.f;
        }
        step_x = deltaTime*projectile.grenadeFlySpeed;
        step_y = deltaTime*projectile.grenadeFlySpeed;
    }
    else {
        step_x = deltaTime*60.f;
        step_y = deltaTime*60.f;
    }

    const float smallStep_x = 5.f;
    const float smallStep_y = 5.f;

    while(step_x > 0.001f || step_y > 0.001f) {
        float currentStep_x, currentStep_y;
        if(step_x > smallStep_x) currentStep_x = smallStep_x;
        else currentStep_x = step_x;
        if(step_y > smallStep_y) currentStep_y = smallStep_y;
        else currentStep_y = step_y;

        float dir = projectile.dir;
        if(projectile.projectileType == PROJECTILE_TYPE_GRENADE_LAUNCHER_GRENADE) {
            dir = atan2(projectile.target_y-projectile.y, projectile.target_x-projectile.x);
        }

        float move_x = currentStep_x*cos(dir);
        float move_y = currentStep_y*sin(dir);
        projectile.x += move_x;
        projectile.y += move_y;
        projectile.distanceTraveled += sqrt(move_x*move_x+move_y*move_y);
        if(projectile.projectileType == PROJECTILE_TYPE_GRENADE_LAUNCHER_GRENADE &&
           fabs(projectile.x-projectile.target_x) < 5.f &&
           fabs(projectile.y-projectile.target_y) < 5.f) {
            makeExplosion(projectile, projectile.x, projectile.y);
            return HIT_EXPLOSION;
        }

        int tile_x = int(projectile.x/TILE_SIZE);
        int tile_y = int(projectile.y/TILE_SIZE);
        for(int i=tile_x-1; i<=tile_x+1; ++i) {
            for(int j=tile_y-1; j<=tile_y+1; ++j) {
                if(isOutOfMap(i, j)) continue;

                for(size_t k=0; k<Tile[i][j].playerIndex.size(); ++k) {
                    int playerIndex=Tile[i][j].playerIndex[k];
                    if(projectile.ownerCharacterType == CHARACTER_PLAYER && projectile.ownerIndex == playerIndex) continue;
                    if(getDistance((int)Player[playerIndex].x, (int)Player[playerIndex].y, (int)projectile.x, (int)projectile.y) <= CHARACTER_RADIUS) {
                        if(projectile.projectileType == PROJECTILE_TYPE_MISSILE || projectile.projectileType == PROJECTILE_TYPE_GRENADE_LAUNCHER_GRENADE) {
                            makeExplosion(projectile, projectile.x, projectile.y);
                            return HIT_EXPLOSION;
                        }
                        else if(projectile.projectileType == PROJECTILE_TYPE_GRENADE) {
                            projectile.grenadeFlySpeed = 0.f;
                            projectile.x -= move_x;
                            projectile.y -= move_y;
                            return HIT_GRENADE_HIT_OBSTACLE;
                        }
                        else {
                            characterHitByProjectile(CHARACTER_PLAYER, playerIndex, projectile);
                            return HIT_BLOOD;
                        }
                    }
                }
                for(size_t k=0; k<Tile[i][j].NPCIndex.size(); ++k) {
                    int NPCIndex = Tile[i][j].NPCIndex[k];
                    if(projectile.ownerCharacterType == CHARACTER_NPC && projectile.ownerIndex == NPCIndex) continue;
                    if(getDistance((int)NPC[NPCIndex].x, (int)NPC[NPCIndex].y, (int)projectile.x, (int)projectile.y) <= CHARACTER_RADIUS) {
                        if(projectile.projectileType == PROJECTILE_TYPE_MISSILE || projectile.projectileType==PROJECTILE_TYPE_GRENADE_LAUNCHER_GRENADE) {
                            makeExplosion(projectile, projectile.x, projectile.y);
                            return HIT_EXPLOSION;
                        }
                        else if(projectile.projectileType == PROJECTILE_TYPE_GRENADE) {
                            projectile.grenadeFlySpeed = 0.f;
                            projectile.x -= move_x;
                            projectile.y -= move_y;
                            return HIT_GRENADE_HIT_OBSTACLE;
                        }
                        else {
                            characterHitByProjectile(CHARACTER_NPC, NPCIndex, projectile);
                            return HIT_BLOOD;
                        }
                    }
                }
            }
        }

        int newTile_x = int(projectile.x/TILE_SIZE);
        int newTile_y = int(projectile.y/TILE_SIZE);
        if(isOutOfMap(newTile_x, newTile_y) || !isShootThroughAble(newTile_x, newTile_y)) {
            if(projectile.projectileType == PROJECTILE_TYPE_MISSILE || projectile.projectileType == PROJECTILE_TYPE_GRENADE_LAUNCHER_GRENADE) {
                makeExplosion(projectile, projectile.x, projectile.y);
                return HIT_EXPLOSION;
            }
            else if(projectile.projectileType == PROJECTILE_TYPE_GRENADE) {
                projectile.grenadeFlySpeed = 0.f;
                projectile.x -= move_x;
                projectile.y -= move_y;
                return HIT_GRENADE_HIT_OBSTACLE;
            }
            else {
                return HIT_NORMAL;
            }
        }

        step_x -= smallStep_x;
        step_y -= smallStep_y;
        if(step_x < 0.f) step_x = 0.f;
        if(step_y < 0.f) step_y = 0.f;
    }
    return 0;
}

void UtilityModule::makeExplosion(const ProjectileClass &projectile, float x, float y)
{
    int tile_x = int(x/TILE_SIZE);
    int tile_y = int(y/TILE_SIZE);
    std::vector <std::pair <int, float> > NPCMoveByExplosion;

    for(int i=tile_x-3; i<=tile_x+3; ++i) {
        for(int j=tile_y-3; j<=tile_y+3; ++j) {
            if(isOutOfMap(i, j)) continue;
            for(size_t k=0; k<Tile[i][j].playerIndex.size(); ++k) {
                int playerIndex = Tile[i][j].playerIndex[k];
                float distance = getDistance(Player[playerIndex].x, Player[playerIndex].y, x, y);
                if(distance <= 2*TILE_SIZE) {
                    characterHitByProjectile(CHARACTER_PLAYER, playerIndex, projectile);
                }
            }
            for(size_t k=0; k<Tile[i][j].NPCIndex.size(); ++k) {
                int NPCIndex = Tile[i][j].NPCIndex[k];
                float distance = getDistance(NPC[NPCIndex].x, NPC[NPCIndex].y, x, y);
                if(distance <= 2*TILE_SIZE) {
                    characterHitByProjectile(CHARACTER_NPC, NPCIndex, projectile);
                    float dir = atan2(y-sin(projectile.dir)*10.f-NPC[NPCIndex].y, x-cos(projectile.dir)*10.f-NPC[NPCIndex].x);
                    NPCMoveByExplosion.push_back(std::pair <int, float> (NPCIndex,dir+M_PI));
                }
            }
        }
    }
    for(size_t i=0; i<NPCMoveByExplosion.size(); ++i) {
        NPCMoveConstantDistance(NPCMoveByExplosion[i].first, NPCMoveByExplosion[i].second, 50.f);
    }
}

void UtilityModule::characterHitByProjectile(char characterSet, int characterIndex, const ProjectileClass &projectile)
{
    _assert_return(isValidCharacterSet(characterSet), NULL, 0, "Invalid characterSet in characterHitByProjectile.");
    CharacterClass *character;
    if(characterSet == CHARACTER_PLAYER) {
        _assert_return(characterIndex >= 0 && characterIndex < (int)Player.size(), NULL, 0, "Player index out of bounds in characterHitByProjectile.");
        character = &Player[characterIndex];
    }
    else {
        _assert_return(characterIndex >= 0 && characterIndex < (int)NPC.size(), NULL, 0, "NPC index out of bounds in characterHitByProjectile.");
        character = &NPC[characterIndex];
    }
    if(projectile.team != character->team || (projectile.pvp && characterSet == CHARACTER_PLAYER)) {
        int damageResist = 0;
        for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
            /*
            to do:
            damageResist+=character->objectOnSlot[i].damageResist?
            */
        }
        int finalDamage = projectile.damage-damageResist;
        if(finalDamage > character->param[CHARACTER_PARAM_HEALTH]) finalDamage = character->param[CHARACTER_PARAM_HEALTH];
        if(finalDamage < 0) finalDamage = 0;

        int health_before_hit = character->param[CHARACTER_PARAM_HEALTH];
        changeCharacterParamBy(*character, characterSet, characterIndex, CHARACTER_PARAM_HEALTH, -finalDamage, true);

        if(isDead(*character) && health_before_hit>0) {
            character->timeout_respawn = globalTime+5000;
            if(characterSet == CHARACTER_NPC) {
                if(character->NPCType >= 0) {
                    _assert_return(character->NPCType < (int)NPCType.size(), NULL, 0,
                                   "NPC type out of bounds in characterHitByProjectile.");
                    int tile_x = int(character->x/TILE_SIZE);
                    int tile_y = int(character->y/TILE_SIZE);

                    NPCTypeClass *deadNPCType = &NPCType[character->NPCType];
                    if(!isOutOfMap(tile_x, tile_y)) {
                        for(size_t i=0; i<deadNPCType->lootObject.size(); ++i) {
                            if(util::rand(1,100) <= deadNPCType->lootObject[i].chance) {
                                int quantity = util::rand(deadNPCType->lootObject[i].quantityFrom,
                                                          deadNPCType->lootObject[i].quantityTo);
                                _assert_return(deadNPCType->lootObject[i].objectType >= 0 &&
                                               deadNPCType->lootObject[i].objectType < (int)ObjectType.size(),
                                               NULL, 0, "Loot object type out of bounds in characterHitByProjectile.");
                                if(isStackable(deadNPCType->lootObject[i].objectType)) {
                                    Tile[tile_x][tile_y].object.push_back(ObjectClass(deadNPCType->lootObject[i].objectType));
                                    Tile[tile_x][tile_y].object.back().param[OBJECT_PARAM_QUANTITY] = quantity;
                                }
                                else {
                                    for(int j=0; j<quantity; ++j) {
                                        Tile[tile_x][tile_y].object.push_back(ObjectClass(deadNPCType->lootObject[i].objectType));
                                    }
                                }
                            }
                        }
                        updateTileForPlayers(tile_x, tile_y);
                    }
                }
            }
            else {
                //player dies
            }
        }
    }
}

void UtilityModule::updateTileForPlayers(int tile_x, int tile_y)
{
    _assert_return(!isOutOfMap(tile_x, tile_y), NULL, 0, "Position out of bounds in updateTileForPlayers.");
    std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(tile_x, tile_y, false);
    float tile_middleX = tile_x*TILE_SIZE-TILE_SIZE/2.f;
    float tile_middleY = tile_y*TILE_SIZE-TILE_SIZE/2.f;
    sendToAllPlayersInView(packet.c_str(), 1, tile_middleX, tile_middleY, -1);
}

bool UtilityModule::NPCMove(int NPCIndex, float dir, float speedMultiplier)
{
    _assert_return_value(NPCIndex >=0 && NPCIndex < (int)NPC.size(), NULL, 0,
                         "NPCIndex out of bounds in NPCMove.", false);

    float step_x = deltaTime*7.f*speedMultiplier;
    float step_y = deltaTime*7.f*speedMultiplier;
    const float smallStep_x = 5.f;
    const float smallStep_y = 5.f;

    float start_x = NPC[NPCIndex].x;
    float start_y = NPC[NPCIndex].y;

    bool collided = false;
    while(step_x > 0.001f || step_y > 0.001f) {
        float currentStep_x, currentStep_y;
        if(step_x > smallStep_x) currentStep_x = smallStep_x;
        else currentStep_x = step_x;
        if(step_y > smallStep_y) currentStep_y = smallStep_y;
        else currentStep_y = step_y;

        float last_x = NPC[NPCIndex].x;
        NPC[NPCIndex].x += currentStep_x*cos(dir);
        if(NPCCollides(NPCIndex)) {
            NPC[NPCIndex].x = last_x;
            collided = true;
        }
        float last_y = NPC[NPCIndex].y;
        NPC[NPCIndex].y += currentStep_y*sin(dir);
        if(NPCCollides(NPCIndex)) {
            NPC[NPCIndex].y = last_y;
            collided = true;
        }

        step_x -= smallStep_x;
        step_y -= smallStep_y;
        if(step_x < 0.f) step_x = 0.f;
        if(step_y < 0.f) step_y = 0.f;
    }

    float end_x = NPC[NPCIndex].x;
    float end_y = NPC[NPCIndex].y;
    NPC[NPCIndex].x = start_x;
    NPC[NPCIndex].y = start_y;

    changeCharacterPosition(CHARACTER_NPC, NPCIndex, end_x, end_y, false);

    return !collided;
}

bool UtilityModule::NPCMoveConstantDistance(int NPCIndex, float dir, float distance)
{
    _assert_return_value(NPCIndex>=0 && NPCIndex < (int)NPC.size(), NULL, 0,
                         "NPCIndex out of bounds in NPCMoveConstantDistance.", false);

    float step_x = distance;
    float step_y = distance;
    const float smallStep_x = 5.f;
    const float smallStep_y = 5.f;

    float start_x = NPC[NPCIndex].x;
    float start_y = NPC[NPCIndex].y;

    bool collided = false;
    while(step_x > 0.001f || step_y > 0.001f) {
        float currentStep_x, currentStep_y;
        if(step_x > smallStep_x) currentStep_x = smallStep_x;
        else currentStep_x = step_x;
        if(step_y > smallStep_y) currentStep_y = smallStep_y;
        else currentStep_y = step_y;

        float last_x = NPC[NPCIndex].x;
        NPC[NPCIndex].x += currentStep_x*cos(dir);
        if(NPCCollides(NPCIndex)) {
            NPC[NPCIndex].x = last_x;
            collided = true;
        }

        float last_y = NPC[NPCIndex].y;
        NPC[NPCIndex].y += currentStep_y*sin(dir);
        if(NPCCollides(NPCIndex)) {
            NPC[NPCIndex].y = last_y;
            collided = true;
        }

        step_x -= smallStep_x;
        step_y -= smallStep_y;
        if(step_x < 0.f) step_x = 0.f;
        if(step_y < 0.f) step_y = 0.f;
    }

    float end_x = NPC[NPCIndex].x;
    float end_y = NPC[NPCIndex].y;
    NPC[NPCIndex].x = start_x;
    NPC[NPCIndex].y = start_y;

    changeCharacterPosition(CHARACTER_NPC, NPCIndex, end_x, end_y, false);

    return !collided;
}

void UtilityModule::removePlayerIndexFromTile(int tile_x, int tile_y, int playerIndex)
{
    _assert_return(!isOutOfMap(tile_x, tile_y), Player[playerIndex].name.c_str(), playerIndex, "Position out of bounds in removePlayerIndexFromTile.")

    for(size_t i=0; i<Tile[tile_x][tile_y].playerIndex.size(); ++i) {
        if(Tile[tile_x][tile_y].playerIndex[i] == playerIndex) {
            if(i != Tile[tile_x][tile_y].playerIndex.size()-1)
                std::swap(Tile[tile_x][tile_y].playerIndex[i], Tile[tile_x][tile_y].playerIndex.back());
            Tile[tile_x][tile_y].playerIndex.pop_back();
            return;
        }
    }
}

void UtilityModule::removeNPCIndexFromTile(int tile_x, int tile_y, int NPCIndex)
{
    _assert_return(!isOutOfMap(tile_x, tile_y), NULL, 0, "Position out of bounds in removeNPCIndexFromTile.");

    for(size_t i=0; i<Tile[tile_x][tile_y].NPCIndex.size(); ++i) {
        if(Tile[tile_x][tile_y].NPCIndex[i] == NPCIndex) {
            if(i != Tile[tile_x][tile_y].NPCIndex.size()-1)
                std::swap(Tile[tile_x][tile_y].NPCIndex[i], Tile[tile_x][tile_y].NPCIndex.back());
            Tile[tile_x][tile_y].NPCIndex.pop_back();
            return;
        }
    }
}

void UtilityModule::removePlayerIndexFromViewSegment(int viewSegment_x, int viewSegment_y, int playerIndex)
{
    _assert_return(!isViewSegmentOutOfBounds(viewSegment_x, viewSegment_y), NULL, 0,
                    "View segment out of bounds in removePlayerIndexFromViewSegment.");

    for(size_t i=0; i<ViewSegment[viewSegment_x][viewSegment_y].playerIndex.size(); ++i) {
        if(ViewSegment[viewSegment_x][viewSegment_y].playerIndex[i] == playerIndex) {
            if(i != ViewSegment[viewSegment_x][viewSegment_y].playerIndex.size()-1)
                std::swap(ViewSegment[viewSegment_x][viewSegment_y].playerIndex[i], ViewSegment[viewSegment_x][viewSegment_y].playerIndex.back());
            ViewSegment[viewSegment_x][viewSegment_y].playerIndex.pop_back();
            return;
        }
    }
}

void UtilityModule::removeNPCIndexFromViewSegment(int viewSegment_x, int viewSegment_y, int NPCIndex)
{
    _assert_return(!isViewSegmentOutOfBounds(viewSegment_x, viewSegment_y), NULL, 0,
                    "View segment out of bounds in removePlayerIndexFromViewSegment.");

    for(size_t i=0; i<ViewSegment[viewSegment_x][viewSegment_y].NPCIndex.size(); ++i) {
        if(ViewSegment[viewSegment_x][viewSegment_y].NPCIndex[i] == NPCIndex) {
            if(i != ViewSegment[viewSegment_x][viewSegment_y].NPCIndex.size()-1)
                std::swap(ViewSegment[viewSegment_x][viewSegment_y].NPCIndex[i], ViewSegment[viewSegment_x][viewSegment_y].NPCIndex.back());
            ViewSegment[viewSegment_x][viewSegment_y].NPCIndex.pop_back();
            return;
        }
    }
}

void UtilityModule::endNPCInteraction(CharacterClass &player)
{
    if(player.NPCInteraction.type == NPC_INTERACTION_TYPE_TALK) {
        player.NPCInteraction.type = NPC_INTERACTION_TYPE_NONE;
        std::string packet = Packet <PACKET_CURRENT_DIALOGUE_BLOCK>::construct(player);
        player.sendPacket(packet);
    }
    else if(player.NPCInteraction.type == NPC_INTERACTION_TYPE_TRADE) {
        player.NPCInteraction.type = NPC_INTERACTION_TYPE_NONE;
        std::string packet = Packet <PACKET_TRADE_WITH_NPC_OBJECTS_LIST>::construct(player);
        player.sendPacket(packet);
    }
    else {
        player.NPCInteraction.type = NPC_INTERACTION_TYPE_NONE;
    }
}

void UtilityModule::getNextMoveTile(TilePositionClass &tilePosition, float from_x, float from_y, float to_x, float to_y)
{
    int tileFrom_x = int(from_x/TILE_SIZE);
    int tileFrom_y = int(from_y/TILE_SIZE);
    int tileTo_x = int(to_x/TILE_SIZE);
    int tileTo_y = int(to_y/TILE_SIZE);

    if(isOutOfMap(tileFrom_x, tileFrom_y) || isOutOfMap(tileTo_x, tileTo_y)) {
        tilePosition.x = -1;
        tilePosition.y = -1;
        return;
    }

    if(fabs(from_x-(tileFrom_x*TILE_SIZE+TILE_SIZE/2.f)) < 5.f && fabs(from_y-(tileFrom_y*TILE_SIZE+TILE_SIZE/2.f)) < 5.f) {
        int pathFinding_x1 = tileFrom_x-PLAYER_TILES_VIEW_DISTANCE;
        int pathFinding_y1 = tileFrom_y-PLAYER_TILES_VIEW_DISTANCE;
        int pathFinding_x2 = tileFrom_x+PLAYER_TILES_VIEW_DISTANCE;
        int pathFinding_y2 = tileFrom_y+PLAYER_TILES_VIEW_DISTANCE;

        Tile[tileTo_x][tileTo_y].BFS_fromTile.x = -1;
        Tile[tileTo_x][tileTo_y].BFS_fromTile.y = -1;
        Tile[tileTo_x][tileTo_y].BFS_visited = false;
        for(int i=pathFinding_x1; i<=pathFinding_x2; ++i) {
            for(int j=pathFinding_y1; j<=pathFinding_y2; ++j) {
                if(!isOutOfMap(i, j)) {
                    Tile[i][j].BFS_fromTile.x = -1;
                    Tile[i][j].BFS_fromTile.y = -1;
                    Tile[i][j].BFS_visited = false;
                }
            }
        }

        std::queue <TilePositionClass> BFS_tiles;
        BFS_tiles.push(TilePositionClass(tileFrom_x, tileFrom_y));
        Tile[tileFrom_x][tileFrom_y].BFS_visited = true;
        while(!BFS_tiles.empty()) {
            if(BFS_tiles.front().x == tileTo_x && BFS_tiles.front().y == tileTo_y) break;

            if(BFS_tiles.front().x > pathFinding_x1 && !isOutOfMap(BFS_tiles.front().x-1, BFS_tiles.front().y)) {
                if(isPassable(BFS_tiles.front().x-1, BFS_tiles.front().y) &&
                   !Tile[BFS_tiles.front().x-1][BFS_tiles.front().y].BFS_visited) {
                    Tile[BFS_tiles.front().x-1][BFS_tiles.front().y].BFS_fromTile.x = BFS_tiles.front().x;
                    Tile[BFS_tiles.front().x-1][BFS_tiles.front().y].BFS_fromTile.y = BFS_tiles.front().y;
                    Tile[BFS_tiles.front().x-1][BFS_tiles.front().y].BFS_visited = true;
                    BFS_tiles.push(TilePositionClass(BFS_tiles.front().x-1, BFS_tiles.front().y));
                }
            }
            if(BFS_tiles.front().x < pathFinding_x2 && !isOutOfMap(BFS_tiles.front().x+1, BFS_tiles.front().y)) {
                if(isPassable(BFS_tiles.front().x+1, BFS_tiles.front().y) &&
                   !Tile[BFS_tiles.front().x+1][BFS_tiles.front().y].BFS_visited) {
                    Tile[BFS_tiles.front().x+1][BFS_tiles.front().y].BFS_fromTile.x = BFS_tiles.front().x;
                    Tile[BFS_tiles.front().x+1][BFS_tiles.front().y].BFS_fromTile.y = BFS_tiles.front().y;
                    Tile[BFS_tiles.front().x+1][BFS_tiles.front().y].BFS_visited = true;
                    BFS_tiles.push(TilePositionClass(BFS_tiles.front().x+1, BFS_tiles.front().y));
                }
            }
            if(BFS_tiles.front().y > pathFinding_y1 && !isOutOfMap(BFS_tiles.front().x, BFS_tiles.front().y-1)) {
                if(isPassable(BFS_tiles.front().x, BFS_tiles.front().y-1) &&
                   !Tile[BFS_tiles.front().x][BFS_tiles.front().y-1].BFS_visited) {
                    Tile[BFS_tiles.front().x][BFS_tiles.front().y-1].BFS_fromTile.x = BFS_tiles.front().x;
                    Tile[BFS_tiles.front().x][BFS_tiles.front().y-1].BFS_fromTile.y = BFS_tiles.front().y;
                    Tile[BFS_tiles.front().x][BFS_tiles.front().y-1].BFS_visited = true;
                    BFS_tiles.push(TilePositionClass(BFS_tiles.front().x, BFS_tiles.front().y-1));
                }
            }
            if(BFS_tiles.front().y < pathFinding_y2 && !isOutOfMap(BFS_tiles.front().x, BFS_tiles.front().y+1)) {
                if(isPassable(BFS_tiles.front().x, BFS_tiles.front().y+1) &&
                   !Tile[BFS_tiles.front().x][BFS_tiles.front().y+1].BFS_visited) {
                    Tile[BFS_tiles.front().x][BFS_tiles.front().y+1].BFS_fromTile.x = BFS_tiles.front().x;
                    Tile[BFS_tiles.front().x][BFS_tiles.front().y+1].BFS_fromTile.y = BFS_tiles.front().y;
                    Tile[BFS_tiles.front().x][BFS_tiles.front().y+1].BFS_visited = true;
                    BFS_tiles.push(TilePositionClass(BFS_tiles.front().x, BFS_tiles.front().y+1));
                }
            }
            BFS_tiles.pop();
        }
        if(Tile[tileTo_x][tileTo_y].BFS_visited) {
            int currentTile_x = tileTo_x;
            int currentTile_y = tileTo_y;
            while(1) {
                if(currentTile_x < 0 || currentTile_y < 0) {
                    tilePosition.x = -1;
                    tilePosition.y = -1;
                    return;
                }
                if(Tile[currentTile_x][currentTile_y].BFS_fromTile.x == tileFrom_x &&
                   Tile[currentTile_x][currentTile_y].BFS_fromTile.y == tileFrom_y) {
                    break;
                }
                else {
                    int tmp_x = currentTile_x;
                    int tmp_y = currentTile_y;
                    currentTile_x = Tile[tmp_x][tmp_y].BFS_fromTile.x;
                    currentTile_y = Tile[tmp_x][tmp_y].BFS_fromTile.y;
                }
            }
            tilePosition.x = currentTile_x;
            tilePosition.y = currentTile_y;
        }
        else {
            tilePosition.x = -1;
            tilePosition.y = -1;
        }
    }
    else {
        tilePosition.x = tileFrom_x;
        tilePosition.y = tileFrom_y;
    }
}

bool UtilityModule::addObjectToPlayerInventory(CharacterClass &player, const ObjectClass &object)
{
    if(player.objectInInventory.empty()) return false;
    for(size_t i=0; i<player.objectInInventory[0].size(); ++i) {
        for(size_t j=0; j<player.objectInInventory.size(); ++j) {
            if(player.objectInInventory[j][i].type < 0) {
                player.objectInInventory[j][i] = object;
                std::string packet = Packet <PACKET_OBJECT_CHANGE_IN_INVENTORY>::construct(j, i, player.objectInInventory[j][i]);
                player.sendPacket(packet);
                return true;
            }
        }
    }
    return false;
}

std::string UtilityModule::getPlayerRichName(CharacterClass &player, int playerIndex)
{
    std::string richName = "`0`r"+player.name;
    if(player.param[CHARACTER_PARAM_RANK] == CHARACTER_RANK_PLAYER);
    else if(player.param[CHARACTER_PARAM_RANK] == CHARACTER_RANK_GM) richName += " `1[GM]";
    else richName += " `1[undefined]";

    if(player.param[CHARACTER_PARAM_FACTION] >= 0) {
        if(player.param[CHARACTER_PARAM_FACTION] >= (int)Faction.size()) {
            changeCharacterParamTo(player, CHARACTER_PLAYER, playerIndex, CHARACTER_PARAM_FACTION, -1, true);
            _assert_return_value(0, player.name.c_str(), playerIndex,
                                 "Player faction index out of bounds in getPlayerRichName.", "error");
        }
        richName += " `2["+Faction[player.param[CHARACTER_PARAM_FACTION]].shortName+" `b";
        if(player.param[CHARACTER_PARAM_FACTION_RANK] == CHARACTER_FACTION_RANK_RECRUIT) richName += "R";
        else if(player.param[CHARACTER_PARAM_FACTION_RANK] == CHARACTER_FACTION_RANK_MEMBER) richName += "M";
        else if(player.param[CHARACTER_PARAM_FACTION_RANK] == CHARACTER_FACTION_RANK_COMMANDER) richName += "C";
        else if(player.param[CHARACTER_PARAM_FACTION_RANK] == CHARACTER_FACTION_RANK_LEADER) richName += "L";
        else richName += "undefined";
        richName += "`r]";
    }

    richName += "`0";

    return richName;
}

float UtilityModule::getDistance(float x1, float y1, float x2, float y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

float UtilityModule::getDistance(const CharacterClass &ch1, const CharacterClass &ch2)
{
    return getDistance(ch1.x, ch1.y, ch2.x, ch2.y);
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

void UtilityModule::logOutPlayer(int playerIndex)
{
    _assert_return(playerIndex >= 0 && playerIndex < (int)Player.size(), NULL, 0,
                   "Player index out of bounds in logOutPlayer.");
    if(Player[playerIndex].isOnline) {
        Player[playerIndex].isOnline = false;
        Player[playerIndex].NPCInteraction.type = NPC_INTERACTION_TYPE_NONE;

        int tile_x = int(Player[playerIndex].x/TILE_SIZE);
        int tile_y = int(Player[playerIndex].y/TILE_SIZE);
        int viewSegment_x = int(Player[playerIndex].x/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));
        int viewSegment_y = int(Player[playerIndex].y/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));

        _assert_return(!isOutOfMap(tile_x, tile_y), Player[playerIndex].name.c_str(), playerIndex,
                       "Position out of bounds in logOutPlayer.");
        _assert_return(!isViewSegmentOutOfBounds(viewSegment_x, viewSegment_y), Player[playerIndex].name.c_str(), playerIndex,
                       "View segment out of bounds in logOutPlayer.");

        removePlayerIndexFromTile(tile_x, tile_y, playerIndex);
        removePlayerIndexFromViewSegment(viewSegment_x, viewSegment_y, playerIndex);

        std::string packet = Packet <PACKET_CHARACTER_LOST_SIGHT>::construct(CHARACTER_PLAYER, playerIndex);
        sendToAllPlayersInView(packet.c_str(), 1, Player[playerIndex].x, Player[playerIndex].y, playerIndex);

        printf("Player %s (id %d) logged out.\n", Player[playerIndex].name.c_str(), playerIndex);
    }
    if(Player[playerIndex].peer != NULL) {
        Player[playerIndex].peer->data = (void*)-1;
        Player[playerIndex].peer = NULL;
    }
}

void UtilityModule::forceDisconnect(ENetPeer *peer)
{
    _assert_return(peer != NULL, NULL, 0, "Peer is NULL in forceDisconnect.");
    enet_peer_disconnect_now(peer, 0);
    if((int)peer->data >= 0 && (int)peer->data < (int)Player.size()) {
        logOutPlayer((int)peer->data);
    }
    else {
        printf("Client %d disconnected (force disconnect).\n", (int)peer->data);
    }
    peer->data = (void*)-1;
}

void UtilityModule::sendToAllPlayersInView(const char *packet, int viewSegmentsDistance, float x, float y, int playerIndexException)
{
    int view_segment_x = int(x/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));
    int view_segment_y = int(y/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));
    int tile_x1 = int(x/TILE_SIZE);
    int tile_y1 = int(y/TILE_SIZE);

    for(int i=view_segment_x-viewSegmentsDistance; i<=view_segment_x+viewSegmentsDistance; ++i) {
        for(int j=view_segment_y-viewSegmentsDistance; j<=view_segment_y+viewSegmentsDistance; ++j) {
            if(isViewSegmentOutOfBounds(i, j)) continue;

            for(size_t k=0; k<ViewSegment[i][j].playerIndex.size(); ++k) {
                int playerIndex = ViewSegment[i][j].playerIndex[k];
                if(playerIndex == playerIndexException) continue;
                int tile_x2 = int(Player[playerIndex].x/TILE_SIZE);
                int tile_y2 = int(Player[playerIndex].y/TILE_SIZE);
                if(abs(tile_x1-tile_x2) <= viewSegmentsDistance*PLAYER_TILES_VIEW_DISTANCE &&
                   abs(tile_y1-tile_y2) <= viewSegmentsDistance*PLAYER_TILES_VIEW_DISTANCE) {
                    Player[playerIndex].sendPacket(packet);
                }
            }
        }
    }
}
