#include "LogicModule.hpp"

#include "Master.hpp"

void LogicModule::logicPlayers()
{
    for(size_t i=0; i<Player.size(); ++i) {
        if(!Player[i].isOnline) {
            Player[i].NPCInteraction.type = NPC_INTERACTION_TYPE_NONE;
            continue;
        }

        if(Player[i].NPCInteraction.type == NPC_INTERACTION_TYPE_TALK) {
            if(Player[i].NPCInteraction.dialogueBlock < 0) {
                _assert(0, NULL, 0, "Player NPC dialogue block is negative in logicPlayers.");
                Player[i].NPCInteraction.type = NPC_INTERACTION_TYPE_NONE;
            }
        }
        if(Player[i].NPCInteraction.type != NPC_INTERACTION_TYPE_NONE) {
            if(Player[i].NPCInteraction.NPCIndex < 0 ||
               Player[i].NPCInteraction.NPCIndex >= (int)NPC.size()) {
                _assert(0, NULL, 0, "NPCInteraction.NPCIndex out of bounds in logicPlayers.");
                Player[i].NPCInteraction.type = NPC_INTERACTION_TYPE_NONE;
            }
            else if(getDistance(Player[i], NPC[Player[i].NPCInteraction.NPCIndex]) > NPC_INTERACTION_MAX_DISTANCE ||
                    isDead(NPC[Player[i].NPCInteraction.NPCIndex])) {
                endNPCInteraction(Player[i]);
            }
        }
    }
}

void LogicModule::logicAI()
{
    BenchmarkClass Benchmark;
    BenchmarkClass BenchmarkTotal;
    BenchmarkTotal.StartTimer(0);
    for(size_t i=0; i<NPC.size(); ++i) {
        /*bool start_on_sight=false;
        bool end_on_sight=false;
        float start_x=NPC[i].x;
        float start_y=NPC[i].y;
        */
        bool isAlive = !isDead(NPC[i]);

        if(!isAlive) {
            /*
                NPC is dead, logic related to respawning
            */
            NPC[i].AI_targetCharacterSet=0;
            NPC[i].AI_targetIndex=-1;
            NPC[i].AI_targetCanShootTo=false;
            if(globalTime>=NPC[i].timeout_respawn) {
                if(!changeCharacterPosition(CHARACTER_NPC,i,NPC[i].respawn_x,NPC[i].respawn_y,true)) {
                    NPC[i].timeout_respawn=globalTime+200;
                }
                else {
                    changeCharacterParamTo(NPC[i],CHARACTER_NPC,i,CHARACTER_PARAM_HEALTH,NPC[i].param[CHARACTER_PARAM_MAX_HEALTH],true);
                }
            }
        }
        else if(globalTime>=NPC[i].timeout_AI_checkTarget) {
            /*
                NPC is alive, logic related to finding new target
                and walking path, it needs timer because these are
                very expensive functions.
            */
            Benchmark.StartTimer(0);/////////////////////////////////////////////////////
            NPC[i].timeout_AI_checkTarget=globalTime+rand()%100+200;

            NPC[i].AI_targetCharacterSet=0;
            NPC[i].AI_targetIndex=-1;
            NPC[i].AI_targetCanShootTo=false;

            float closest_distance=0.f;
            float target_x=0.f,target_y=0.f;

            /*
                Iterating through all visible characters and
                finding the best target.
            */
            int view_segment_x=int(NPC[i].x/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));
            int view_segment_y=int(NPC[i].y/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));
            for(int j=view_segment_x-1; j<=view_segment_x+1; ++j) {
                for(int k=view_segment_y-1; k<=view_segment_y+1; ++k) {
                    if(j<0 || k<0 || j>int(ViewSegment.size())) continue;
                    if(k>int(ViewSegment[j].size())) continue;
                    for(size_t l=0; l<ViewSegment[j][k].playerIndex.size(); ++l) {
                        int player_index=ViewSegment[j][k].playerIndex[l];
                        if(Player[player_index].isOnline &&
                           isOnSight(NPC[i],Player[player_index]) &&
                           NPC[i].team!=Player[player_index].team &&
                           !isDead(Player[player_index])) {
                            float distance=fabs(NPC[i].x-Player[player_index].x)+fabs(NPC[i].y-Player[player_index].y);
                            bool isTargetBetter=false;
                            if(NPC[i].AI_targetCanShootTo) {
                                if(isShootThroughAbleBetween(NPC[i].x,NPC[i].y,Player[player_index].x,Player[player_index].y)) {
                                    if(distance<closest_distance) isTargetBetter=true;
                                }
                            }
                            else {
                                if(distance<closest_distance) {
                                    isTargetBetter=true;
                                    NPC[i].AI_targetCanShootTo=isShootThroughAbleBetween(NPC[i].x,NPC[i].y,Player[player_index].x,Player[player_index].y);
                                }
                            }
                            if(NPC[i].AI_targetIndex<0 || isTargetBetter) {
                                if(NPC[i].AI_targetIndex<0) NPC[i].AI_targetCanShootTo=isShootThroughAbleBetween(NPC[i].x,NPC[i].y,Player[player_index].x,Player[player_index].y);
                                NPC[i].AI_targetCharacterSet=CHARACTER_PLAYER;
                                NPC[i].AI_targetIndex=player_index;
                                closest_distance=distance;
                                target_x=Player[player_index].x;
                                target_y=Player[player_index].y;
                            }
                        }
                    }
                    for(size_t l=0; l<ViewSegment[j][k].NPCIndex.size(); ++l) {
                        int npc_index=ViewSegment[j][k].NPCIndex[l];
                        if(npc_index==(int)i) continue;
                        if(isOnSight(NPC[i],NPC[npc_index]) &&
                           NPC[i].team!=NPC[npc_index].team &&
                           !isDead(NPC[npc_index])) {
                            float distance=fabs(NPC[i].x-NPC[npc_index].x)+fabs(NPC[i].y-NPC[npc_index].y);
                            bool isTargetBetter=false;
                            if(NPC[i].AI_targetCanShootTo) {
                                if(isShootThroughAbleBetween(NPC[i].x,NPC[i].y,NPC[npc_index].x,NPC[npc_index].y)) {
                                    if(distance<closest_distance) isTargetBetter=true;
                                }
                            }
                            else {
                                if(distance<closest_distance) {
                                    isTargetBetter=true;
                                    NPC[i].AI_targetCanShootTo=isShootThroughAbleBetween(NPC[i].x,NPC[i].y,NPC[npc_index].x,NPC[npc_index].y);
                                }
                            }
                            if(NPC[i].AI_targetIndex<0 || isTargetBetter) {
                                if(NPC[i].AI_targetIndex<0) NPC[i].AI_targetCanShootTo=isShootThroughAbleBetween(NPC[i].x,NPC[i].y,NPC[npc_index].x,NPC[npc_index].y);
                                NPC[i].AI_targetCharacterSet=CHARACTER_NPC;
                                NPC[i].AI_targetIndex=npc_index;
                                closest_distance=distance;
                                target_x=NPC[npc_index].x;
                                target_y=NPC[npc_index].y;
                            }
                        }
                    }
                }
            }
            Benchmark.StartTimer(1);/////////////////////////////////////////////////////
            /*
                Path-finding. Getting next move tile.
            */
            if((NPC[i].AI_nextMoveTile.x<0 || NPC[i].AI_nextMoveTile.y<0) &&
               NPC[i].AI_targetCharacterSet>0 && NPC[i].AI_targetIndex>=0 && !NPC[i].AI_targetCanShootTo) {
                getNextMoveTile(NPC[i].AI_nextMoveTile,NPC[i].x,NPC[i].y,target_x,target_y);
            }
            if((NPC[i].AI_nextMoveTile.x<0 || NPC[i].AI_nextMoveTile.y<0) &&
               (NPC[i].AI_targetCharacterSet<=0 || NPC[i].AI_targetIndex<0) &&
               !(fabs(NPC[i].x-NPC[i].respawn_x)<5.f && fabs(NPC[i].y-NPC[i].respawn_y)<5.f)) {
                 getNextMoveTile(NPC[i].AI_nextMoveTile,NPC[i].x,NPC[i].y,NPC[i].respawn_x,NPC[i].respawn_y);
            }
        }

        /*
            This part is logic which needs to be processed
            every frame.
        */
        Benchmark.StartTimer(2);/////////////////////////////////////////////////////
        if(isAlive && NPC[i].AI_targetCharacterSet>0 && NPC[i].AI_targetIndex>=0) {
            /*
                If NPC is alive and has a target.
            */
            _assert_return(NPC[i].AI_targetCharacterSet==CHARACTER_PLAYER || NPC[i].AI_targetCharacterSet==CHARACTER_NPC,NULL,0,"Unknown AI_targetCharacterSet in LogicCharacters.");
            CharacterClass *Target;
            if(NPC[i].AI_targetCharacterSet==CHARACTER_PLAYER) {
                _assert_return(NPC[i].AI_targetIndex<int(Player.size()),NULL,0,"AI_targetIndex (player) out of bounds in LogicCharacters.");
                Target=&Player[NPC[i].AI_targetIndex];
            }
            else {
                _assert_return(NPC[i].AI_targetIndex<int(NPC.size()),NULL,0,"AI_targetIndex (NPC) out of bounds in LogicCharacters.");
                Target=&NPC[NPC[i].AI_targetIndex];
            }

            if(isDead(*Target) ||
               (NPC[i].AI_targetCharacterSet==CHARACTER_PLAYER && !Target->isOnline)) {
                NPC[i].AI_targetCharacterSet=0;
                NPC[i].AI_targetIndex=-1;
                NPC[i].AI_targetCanShootTo=false;
                NPC[i].AI_nextMoveTile.x=-1;
                NPC[i].AI_nextMoveTile.y=-1;
            }
            else {
                if(NPC[i].AI_targetCanShootTo) {
                    /*
                        NPC has a clear shot.
                    */
                    NPC[i].dir=atan2(Target->y-NPC[i].y,Target->x-NPC[i].x);
                    float distance=getDistance(NPC[i].x,NPC[i].y,Target->x,Target->y);
                    if(distance<300.f) {
                        if(distance<110.f) NPCMove(i, NPC[i].dir+M_PI);
                        else {
                            if(globalTime>=NPC[i].timeout_AI_changeDodgeMoveDir) {
                                NPC[i].timeout_AI_changeDodgeMoveDir=globalTime+rand()%1000+1200;
                                NPC[i].AI_dodgeMoveDir=rand()%4;
                            }
                            if(NPC[i].AI_dodgeMoveDir>=2 && distance>250.f) NPCMove(i,NPC[i].dir,0.1f);
                            if(NPC[i].AI_dodgeMoveDir>=2 && distance<140.f) NPCMove(i,NPC[i].dir+M_PI,0.1f);
                            if(NPC[i].AI_dodgeMoveDir%2) NPCMove(i,NPC[i].dir+M_PI/2,0.18f);
                            else NPCMove(i,NPC[i].dir-M_PI/2,0.18f);
                        }
                    }
                    if(distance>=300.f) {
                        NPCMove(i,NPC[i].dir);
                    }
                    _assert_return(NPC[i].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].type<int(ObjectType.size()),NULL,0,"NPC weapon object type out of bounds in LogicCharacters.");
                    if(NPC[i].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].type>=0) {
                        if(globalTime>=NPC[i].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].timeout_shot) {
                            NPC[i].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].timeout_shot=globalTime+ObjectType[NPC[i].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].type].baseShotDelay;
                            if(!ObjectType[NPC[i].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].type].isAutomatic)
                                NPC[i].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].timeout_shot+=rand()%100;
                            characterShoot(NPC[i],CHARACTER_NPC,i);
                        }
                    }
                    NPC[i].AI_nextMoveTile.x=-1;
                    NPC[i].AI_nextMoveTile.y=-1;
                }
                else if(NPC[i].AI_nextMoveTile.x>=0 && NPC[i].AI_nextMoveTile.y>=0) {
                    /*
                        NPC does not have a clear shot, but has next move tile.
                    */
                    if(fabs(NPC[i].x-(NPC[i].AI_nextMoveTile.x*TILE_SIZE+TILE_SIZE/2.f))<deltaTime*7.f && fabs(NPC[i].y-(NPC[i].AI_nextMoveTile.y*TILE_SIZE+TILE_SIZE/2.f))<deltaTime*7.f) {
                        NPC[i].x=NPC[i].AI_nextMoveTile.x*TILE_SIZE+TILE_SIZE/2.f;
                        NPC[i].y=NPC[i].AI_nextMoveTile.y*TILE_SIZE+TILE_SIZE/2.f;
                        getNextMoveTile(NPC[i].AI_nextMoveTile,NPC[i].x,NPC[i].y,Target->x,Target->y);
                    }
                    else NPCMove(i,atan2(NPC[i].AI_nextMoveTile.y*TILE_SIZE+TILE_SIZE/2.f-NPC[i].y,NPC[i].AI_nextMoveTile.x*TILE_SIZE+TILE_SIZE/2.f-NPC[i].x));
                    NPC[i].dir=atan2(Target->y-NPC[i].y,Target->x-NPC[i].x);
                }
                NPC[i].timeout_AI_wander_turn=globalTime+7000+rand()%20000;
            }
        }
        else {
            /*
                NPC is dead or does not have a target.
            */
            if(!isAlive) {
                NPC[i].AI_nextMoveTile.x=-1;
                NPC[i].AI_nextMoveTile.y=-1;
            }
            else {
                /*
                    Looking for a way to get to the respawn.
                */
                if(fabs(NPC[i].x-NPC[i].respawn_x)<5.f && fabs(NPC[i].y-NPC[i].respawn_y)<5.f) {
                    NPC[i].AI_nextMoveTile.x=-1;
                    NPC[i].AI_nextMoveTile.y=-1;
                    if(NPC[i].AI_staticDirection) {
                        NPC[i].dir=NPC[i].respawn_dir;
                    }
                    else if(globalTime>=NPC[i].timeout_AI_wander_turn) {
                        NPC[i].timeout_AI_wander_turn=globalTime+7000+rand()%20000;
                        NPC[i].dir=(rand()%360)*M_PI/180.f;
                    }
                }
                else if(fabs(NPC[i].x-NPC[i].respawn_x)<30.f && fabs(NPC[i].y-NPC[i].respawn_y)<30.f) {
                    NPCMove(i,atan2(NPC[i].respawn_y-NPC[i].y,NPC[i].respawn_x-NPC[i].x));
                    NPC[i].dir=atan2(NPC[i].respawn_y-NPC[i].y,NPC[i].respawn_x-NPC[i].x);
                }
                else {
                    if(NPC[i].AI_nextMoveTile.x>=0 && NPC[i].AI_nextMoveTile.y>=0) {
                        if(fabs(NPC[i].x-(NPC[i].AI_nextMoveTile.x*TILE_SIZE+TILE_SIZE/2.f))<deltaTime*7.f && fabs(NPC[i].y-(NPC[i].AI_nextMoveTile.y*TILE_SIZE+TILE_SIZE/2.f))<deltaTime*7.f) {
                            NPC[i].x=NPC[i].AI_nextMoveTile.x*TILE_SIZE+TILE_SIZE/2.f;
                            NPC[i].y=NPC[i].AI_nextMoveTile.y*TILE_SIZE+TILE_SIZE/2.f;
                            getNextMoveTile(NPC[i].AI_nextMoveTile,NPC[i].x,NPC[i].y,NPC[i].respawn_x,NPC[i].respawn_y);
                        }
                        else NPCMove(i,atan2(NPC[i].AI_nextMoveTile.y*TILE_SIZE+TILE_SIZE/2.f-NPC[i].y,NPC[i].AI_nextMoveTile.x*TILE_SIZE+TILE_SIZE/2.f-NPC[i].x));
                        NPC[i].dir=atan2(NPC[i].respawn_y-NPC[i].y,NPC[i].respawn_x-NPC[i].x);
                    }
                }
            }
        }

        /*if(Player[0].isOnline) {
            NPCMove(Player,NPC,Tile,tileType,sceneryType,ObjectType,ViewSegment,i,atan2(Player[0].y-NPC[i].y,Player[0].x-NPC[i].x));
            NPC[i].dir=atan2(Player[0].y-NPC[i].y,Player[0].x-NPC[i].x);
        }*/
        /*float end_x=NPC[i].x;
        float end_y=NPC[i].y;
        for(size_t j=0; j<Player.size(); ++j) {
            if(!Player[j].isOnline) continue;

            NPC[i].x=start_x,NPC[i].y=start_y;
            start_on_sight=OnSight(NPC[i],Player[j]);
            NPC[i].x=end_x,NPC[i].y=end_y;
            end_on_sight=OnSight(NPC[i],Player[j]);
            if(end_on_sight) {
                if(!start_on_sight) {
                    char packet[300];
                    GetCharacterParamsPacket(packet,NPC[i],CHARACTER_NPC,i);
                    SendPacket(Player[j].peer,0,packet);
                }
            }
            else if(start_on_sight && !end_on_sight) {
                char packet[60];
                sprintf(packet,"%c %c %d",PACKET_CHARACTER_LOST_SIGHT,CHARACTER_NPC,i);
                SendPacket(Player[j].peer,0,packet);
            }
        }*/
    }
    Benchmark.StartTimer(-1);
    BenchmarkTotal.StartTimer(-1);
    /*printf("Benchmark timer 0: %d\n",Benchmark.timer[0]);
    printf("Benchmark timer 1: %d\n",Benchmark.timer[1]);
    printf("Benchmark timer 2: %d\n",Benchmark.timer[2]);
    printf("                   ____\n");
    printf("                   %d\n",Benchmark.timer[0]+Benchmark.timer[1]+Benchmark.timer[2]);
    printf("Benchmark total: %d\n",BenchmarkTotal.timer[0]);*/
}

void LogicModule::logicProjectiles()
{
    for(std::list <ProjectileClass>::iterator it = Projectile.begin(); it != Projectile.end();) {
        std::list <ProjectileClass>::iterator projectile = it;
        ++it;

        char hit = projectileMove(*projectile);

        bool explode = false;
        if(isProjectileExplosive(projectile->projectileType) && projectile->distanceTraveled >= MAX_PROJECTILE_TRAVEL_DISTANCE)
            explode = true;
        if(projectile->projectileType == PROJECTILE_TYPE_GRENADE && globalTime >= projectile->timeout_grenadeExplode)
            explode = true;

        if(hit == HIT_GRENADE_HIT_OBSTACLE && projectile->grenadeHitObstaclePacketSent) hit = 0;
        if(hit || explode) {
            if(hit == HIT_GRENADE_HIT_OBSTACLE) projectile->grenadeHitObstaclePacketSent = true;

            std::string packet;
            if(explode)
                packet = Packet <PACKET_PROJECTILE_HIT>::construct(HIT_EXPLOSION, (int)projectile->x, (int)projectile->y, projectile->id);
            else
                packet = Packet <PACKET_PROJECTILE_HIT>::construct(hit, (int)projectile->x, (int)projectile->y, projectile->id);

            sendToAllPlayersInView(packet.c_str(), 2, projectile->x, projectile->y, -1);

            if(explode) makeExplosion(*projectile, projectile->x, projectile->y);
            if(hit != HIT_GRENADE_HIT_OBSTACLE) Projectile.erase(projectile);
            continue;
        }
        if(projectile->distanceTraveled >= MAX_PROJECTILE_TRAVEL_DISTANCE) {
            Projectile.erase(projectile);
            continue;
        }
    }
}

void LogicModule::logicWeather()
{
    Weather.dayTimeInMinutes += (1000.0/30.0*deltaTime)/1000.0;
    if(Weather.dayTimeInMinutes > 60.0*24.0) Weather.dayTimeInMinutes -= 60.0*24.0;
}

