#include "Master.hpp"

Master *Master::instance = NULL;

void Master::mainLoop()
{
    initDebug();
    while(1) {
        updateDelta();
        logicPlayers();
        logicAI();
        logicProjectiles();
        logicWeather();
        manageNetworkEvents();

        globalTime += deltaTime/30.0*1000.0;
    }
}

void Master::init()
{
    if(!logManager.create("log.txt")) {
        error("Could not create log file 'log.txt'.");
        //We're using MessageBoxA because allegro_message
        //works only after OpenLayer initialization.
        MessageBoxA(NULL, "Could not create log file 'log.txt'.", "Error", 0);
    }

    info("Initializing network.");
    network.init();

    info("Loading tiles.");
    loadTileTypes("data/tiles.dat");

    info("Loading sceneries.");
    loadSceneryTypes("data/sceneries.dat");

    info("Loading objects.");
    loadObjectTypes("data/objects.dat");

    info("Loading scripts.");
    loadScripts("data/scripts.dat", "data/scripts/");

    info("Compiling scripts.");
    //compileScripts();

    info("Loading quests.");
    loadQuests("data/quests.dat");

    info("Loading NPC types.");
    loadNPCTypes("data/npc_types.dat", "data/npc_types/");

    info("Loading map.");
    loadMap("data/map.dat");

    info("Loading NPCs.");
    loadNPCs("data/npcs.dat");
    validateNPCMovementCheckpoints(NPC);

    info("Initializing misc variables.");
    if(Tile.size() && Tile[0].size()) {
        ViewSegment.resize(Tile.size()/PLAYER_TILES_VIEW_DISTANCE+1, std::vector <ViewSegmentClass>(Tile[0].size()/PLAYER_TILES_VIEW_DISTANCE+1));
    }
    srand(time(0));
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)crashHandler);

    info("Initializing done.");
}

void Master::initDebug()
{
    Player.push_back(CharacterClass("ison", "abc"));
    Player.push_back(CharacterClass("Hayachi", "123"));
    Player.push_back(CharacterClass("Lemourin", "lem"));

    Tile[524][509].object.push_back(ObjectClass());
    Tile[524][509].object.back().type = 0;
    Tile[524][506].object.push_back(ObjectClass());
    Tile[524][506].object.back().type = 2;
    Tile[524][506].object.back().param[OBJECT_PARAM_ADDON_1] = 0;

    Faction.resize(1);
    Faction.back().name = "Alliance";
    Faction.back().shortName = "Alliance";
    Faction.back().memberPlayerIndex.push_back(0);

    Player[0].param[CHARACTER_PARAM_HEALTH] = 100;
    Player[0].param[CHARACTER_PARAM_MAX_HEALTH] = 100;
    Player[0].param[CHARACTER_PARAM_RANK] = CHARACTER_RANK_GM;
    Player[0].param[CHARACTER_PARAM_FACTION] = 0;
    Player[0].param[CHARACTER_PARAM_FACTION_RANK] = CHARACTER_FACTION_RANK_LEADER;
    Player[0].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].type = 2;
    Player[1].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].type = 2;

    Player[0].x = 2500;
    Player[0].y = 2500;
    Player[1].x = 523*TILE_SIZE;
    Player[1].y = 505*TILE_SIZE;
    Player[2].x = 523*TILE_SIZE;
    Player[2].y = 505*TILE_SIZE;

    /*for(int i=100; i<180; ++i) { //540 534
        for(int j=100; j<180; ++j) { //535 529
            NPC.push_back(CharacterClass("Guard", ""));
            NPC.back().team = 0;
            NPC.back().x = i*TILE_SIZE*4;
            NPC.back().y = j*TILE_SIZE*4*0;
            NPC.back().respawn_x = i*TILE_SIZE*4;
            NPC.back().respawn_y = j*TILE_SIZE*4*0;
            NPC.back().objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].type = 8;
            NPC.back().objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].timeout_shot = globalTime+rand()%3000;
        }
    }
    NPC.push_back(CharacterClass("Guardsdfsdfsdf", ""));
    NPC.back().team = 0;
    NPC.back().x = 523*TILE_SIZE;
    NPC.back().y = 505*TILE_SIZE;
    NPC.back().respawn_x = 523*TILE_SIZE;
    NPC.back().respawn_y = 505*TILE_SIZE;
    NPC.back().objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].type = 8;
    NPC.back().objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].timeout_shot = globalTime+rand()%3000;*/

    Player[0].objectInInventory[4][1].type = 2;
    Player[0].objectInInventory[0][0].type = 3;
    Player[0].objectInInventory[1][1].type = 3;
    Player[0].objectInInventory[1][1].param[OBJECT_PARAM_ADDON_1] = 4;
    Player[0].objectInInventory[1][1].param[OBJECT_PARAM_ADDON_2] = 6;
    Player[0].objectInInventory[1][1].param[OBJECT_PARAM_ADDON_3] = 7;
    Player[0].objectInInventory[0][2].type = 5;
    Player[0].objectInInventory[2][0].type = 4;
    Player[0].objectInInventory[3][0].type = 8;
    Player[0].objectInInventory[4][0].type = 100;
    Player[0].objectInInventory[4][2].type = 101;
    Player[0].objectInInventory[4][3].type = 102;

    /*
    for(int i=0; i<7; ++i) {
        Player[0].objectInInventory[i][2].type=0;
        Player[0].objectInInventory[i][3].type=0;
    }*/

    //for(int i=0; i<10000; ++i) Player.push_back(CharacterClass());
    //for(int i=0; i<1000; ++i) NPC.push_back(CharacterClass());

    for(size_t i=0; i<NPC.size(); ++i) {
        int tile_x = int(NPC[i].x/TILE_SIZE);
        int tile_y = int(NPC[i].y/TILE_SIZE);
        int viewSegment_x = int(NPC[i].x/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));
        int viewSegment_y = int(NPC[i].y/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));
        _assert_exit(!isOutOfMap(tile_x, tile_y), NULL, 0, "NPC position out of bounds in initDebug.")
        _assert_exit(!isViewSegmentOutOfBounds(viewSegment_x, viewSegment_y), NULL, 0, "NPC view segment out of bounds in initDebug.")
        Tile[tile_x][tile_y].NPCIndex.push_back(i);
        ViewSegment[viewSegment_x][viewSegment_y].NPCIndex.push_back(i);
    }
}

void Master::run()
{
    info("Server running.");
    mainLoop();
    info("Application closed normally.");
}
