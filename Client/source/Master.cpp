#include "Master.hpp"

#include <windows.h>
#include <conio.h>
#include "global.hpp"
#include "utility.hpp"
#include "benchmark.hpp"
#include "SpriteDrawQueueClass.hpp"
#include "DataStream.hpp"
#include "Shaders.hpp"
#include "RichText.hpp"

void UserInterface::showError(const std::string &str)
{
    errorStr = str;
    isErrorShown = true;
    Master::getInstance().inGameError = str;
    // BLLS
}

void UserInterface::hideError()
{
    isErrorShown = false;
}

Master *Master::instance = NULL;

void Master::loadResourcesThread()
{
    info("Initializing Audiere sound.");
    audiereAudioDevice = audiere::OpenDevice();
    if(!audiereAudioDevice) {
        error("Could not initialize Audiere sound.");
    }

    info("Initializing network.");
    network.init();

    info("Loading tiles.");
    loadTileTypes("data/tiles.dat");

    info("Loading sceneries.");
    loadSceneryTypes("data/sceneries.dat");

    info("Loading objects.");
    loadObjectSlotDefaultSprites();
    loadObjectTypes("data/objects.dat");

    info("Loading lights.");
    loadLightTypes("data/lights.dat");

    info("Loading static light sources.");
    loadStaticLightSources("data/light_sources.dat");

    info("Loading interface/misc sprites.");
    loadTexture(missingTexture, "gfx/misc/missingTexture.png");
    loadTexture(penumbraTexture, "gfx/misc/penumbra.png");
    loadTexture(mouseTexture, "gfx/interface/mouse.png");
    loadTexture(mouseMoveObjectTexture, "gfx/interface/mouse_move_object.png");
    loadTexture(Interface.chatWindowTexture, "gfx/interface/chat.png");
    loadTexture(Interface.chatEditBoxTexture, "gfx/interface/chat_editbox.png");
    loadTexture(Interface.chatTabTexture, "gfx/interface/chat_tab.png");
    loadTexture(Interface.objectSlotTexture, "gfx/interface/object_slot.png");
    loadTexture(minimapTexture, "gfx/misc/minimap.png");
    loadTexture(missileTexture, "gfx/misc/missile.png");
    loadTexture(grenadeLauncherGrenadeTexture, "gfx/misc/grenade_launcher_grenade.png");
    loadTexture(grenadeTexture, "gfx/misc/grenade.png");
    loadTexture(waterColorMapTexture, "gfx/misc/water[colorMap].png");
    loadTexture(waterNormalMapTexture, "gfx/misc/water[normalMap].png");
    loadTexture(waterNoiseTexture, "gfx/misc/waterNoise.png");
    loadTexture(skyTexture, "gfx/misc/sky.png");

    waterSprite.setTexture(waterColorMapTexture);

    Interface.objectSlotSprite.setTexture(Interface.objectSlotTexture);
    Interface.chatWindowSprite.setTexture(Interface.chatWindowTexture);
    Interface.chatEditBoxSprite.setTexture(Interface.chatEditBoxTexture);
    Interface.chatTabSprite.setTexture(Interface.chatTabTexture);

    for(int i=0; i<PARTICLE_TEXTURES_QUANTITY; ++i) {
        char path[150];
        sprintf(path, "gfx/misc/particle%d.png", i+1);
        loadTexture(particleTexture[i], path);
        particleSprite[i].setTexture(particleTexture[i]);
    }
    for(int i=0; i<RAINDROP_SPLASH_ANIMATION_FRAMES_QUANTITY; ++i) {
        char path[150];
        sprintf(path, "gfx/misc/raindrop%d.png", i+1);
        loadTexture(Weather.rainDropSplashFrameTexture[i], path);
        Weather.rainDropSplashFrameSprite[i].setTexture(Weather.rainDropSplashFrameTexture[i]);
    }

    info("Packing tile textures.");
    tileColorMapTextureAtlas.pack(SUPPORTED_TEXTURE_SIZE_REQUIREMENT);
    tileNormalMapTextureAtlas.pack(SUPPORTED_TEXTURE_SIZE_REQUIREMENT);

    info("NOT Loading fonts.");
    //LoadFont(FontMain, "fonts/arial.ttf", 15, 12, Rgba::WHITE);

    info("Loading nature/misc sounds.");
    /*loadSample(&bulletHitSample, "sfx/misc/bullet_hit.wav");
    loadSample(&bulletBloodHitSample, "sfx/misc/bullet_blood_hit.wav");
    loadSample(&explosionSample, "sfx/misc/explosion.wav");
    loadSample(&grenadeLauncherShotSample, "sfx/misc/grenade_launcher.wav");
    loadSample(&grenadeThrowSample, "sfx/misc/grenade_throw.wav");
    loadSample(&grenadeBounceSample, "sfx/misc/grenade_bounce.wav");
    loadSample(&levelUpSample, "sfx/misc/levelup.wav");
    loadSample(&Weather.lightningSample, "sfx/nature/lightning.wav");*/
    // ALLS

    audiere::OutputStreamPtr dayBackgroundSound(OpenSound(audiereAudioDevice, "sfx/nature/day.ogg", true));
    if(!dayBackgroundSound) {
        error("Could not load 'sfx/nature/day.ogg'.");
    }
    Weather.dayBackgroundSound = dayBackgroundSound;
    Weather.dayBackgroundSound->setVolume(0.f);
    Weather.dayBackgroundSound->setRepeat(true);

    audiere::OutputStreamPtr nightBackgroundSound(OpenSound(audiereAudioDevice, "sfx/nature/night.ogg", true));
    if(!nightBackgroundSound) {
        error("Could not load 'sfx/nature/night.ogg'.");
    }
    Weather.nightBackgroundSound = nightBackgroundSound;
    Weather.nightBackgroundSound->setVolume(0.f);
    Weather.nightBackgroundSound->setRepeat(true);

    audiere::OutputStreamPtr smallRainSound(OpenSound(audiereAudioDevice, "sfx/nature/rain.ogg",true));
    if(!smallRainSound) {
        error("Could not load 'sfx/nature/rain.ogg'.");
    }
    Weather.smallRainSound = smallRainSound;
    Weather.smallRainSound->setVolume(0.f);
    Weather.smallRainSound->setRepeat(true);

    audiere::OutputStreamPtr mediumRainSound(OpenSound(audiereAudioDevice, "sfx/nature/rain.ogg", true));
    if(!mediumRainSound) {
        error("Could not load 'sfx/nature/rain.ogg'.");
    }
    Weather.mediumRainSound = mediumRainSound;
    Weather.mediumRainSound->setVolume(0.f);
    Weather.mediumRainSound->setRepeat(true);

    audiere::OutputStreamPtr heavyRainSound(OpenSound(audiereAudioDevice, "sfx/nature/rain.ogg",true));
    if(!heavyRainSound) {
        error("Could not load 'sfx/nature/rain.ogg'.");
    }
    Weather.heavyRainSound = heavyRainSound;
    Weather.heavyRainSound->setVolume(0.f);
    Weather.heavyRainSound->setRepeat(true);

    info("Loading map.");
    loadMap("data/map.dat");

    info("Loading texts.");
    loadTexts("data/texts.dat");

    info("Loading quests.");
    loadQuests("data/quests.dat", "data/quests/");

    info("Compiling shaders.");
    /*if(!lightShader.loadFromMemory(VERTEX_SHADER_LIGHT, FRAGMENT_SHADER_LIGHT)) {
        error("Could not compile light shader. Please report this bug.");
    }
    lightShader.setParameter("normalMap", normalMapFBO.getTexture());
    lightShader.setParameter("heightMap", heightMapFBO.getTexture());
    lightShader.setParameter("shadowMap", shadowMapFBO.getTexture());*/
    if(!waterShader.loadFromMemory(VERTEX_SHADER_WATER, FRAGMENT_SHADER_WATER)) {
        error("Could not compile water shader. Please report this bug.");
    }
    if(!lightToLightDiffuseMapShader.loadFromMemory(VERTEX_SHADER_LIGHT_TO_LIGHT_DIFFUSE_MAP,
                                                    FRAGMENT_SHADER_LIGHT_TO_LIGHT_DIFFUSE_MAP)) {
        error("Could not compile lightToLightDiffuseMap shader. Please report this bug.");
    }
    lightToLightDiffuseMapShader.setParameter("normalMap", normalMapFBO.getTexture());
    lightToLightDiffuseMapShader.setParameter("heightMap", heightMapFBO.getTexture());
    lightToLightDiffuseMapShader.setParameter("shadowMap", shadowMapFBO.getTexture());
    if(!lightToLightSpecularMapShader.loadFromMemory(VERTEX_SHADER_LIGHT_TO_LIGHT_SPECULAR_MAP,
                                                     FRAGMENT_SHADER_LIGHT_TO_LIGHT_SPECULAR_MAP)) {
        error("Could not compile lightToLightSpecularMap shader. Please report this bug.");
    }
    lightToLightSpecularMapShader.setParameter("normalMap", normalMapFBO.getTexture());
    lightToLightSpecularMapShader.setParameter("heightMap", heightMapFBO.getTexture());
    lightToLightSpecularMapShader.setParameter("shadowMap", shadowMapFBO.getTexture());
    if(!postProcessShader.loadFromMemory(VERTEX_SHADER_POST_PROCESS,
                                         FRAGMENT_SHADER_POST_PROCESS)) {
        error("Could not compile post process shader. Please report this bug.");
    }

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
    playerCharacterID = -1;
    timeout_sendPosition = 0.0;
    timeout_lightningLight = 0.0;
    srand(time(0));
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)crashHandler);
    //for(int i=0; i<1; ++i) LightSource.push_back(LightSourceClass(525*TILE_SIZE, 515*TILE_SIZE, 500));
    //LightSource.push_back(LightSourceClass(535*TILE_SIZE, 545*TILE_SIZE, 1000));
    currentPacketData = NULL;
	addRenderState = sf::RenderStates::Default;
	addRenderState.blendMode = sf::BlendAdd;
	multiplyRenderState = sf::RenderStates::Default;
	multiplyRenderState.blendMode = sf::BlendMultiply;

    loadingDoneMutex.lock();
    loadingDone = true;
    loadingDoneMutex.unlock();
}

void Master::mainLoopMenu()
{
    resetWorld();
    /*LightSource.resize(1);
    LightSource[0].x = 1500.f;
    LightSource[0].y = 1000.f;
    LightSource[0].color = sf::Vector3f(1.f, 1.f, 0.7f);
    LightSource[0].textureIndex = 0;*/
    float blackScreenAlpha = 500.f;
    globalClock.restart();
    while(window.isOpen()) {
        mx = sf::Mouse::getPosition(window).x;
        my = sf::Mouse::getPosition(window).y;

        bool mousePressed = false;
        bool mouseReleased = false;
        keyBuff.clear();
        keyBuffHandled = false;
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            else if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    mb = 1;
                    mx = event.mouseButton.x;
                    my = event.mouseButton.y;
                    mousePressed = true;
                }
                else if(event.mouseButton.button == sf::Mouse::Right) {
                    mb = 2;
                    mx = event.mouseButton.x;
                    my = event.mouseButton.y;
                    mousePressed = true;
                }
            }
            else if(event.type == sf::Event::MouseButtonReleased) {
                if(event.mouseButton.button == sf::Mouse::Left && mb == 1) {
                    mouseReleased = true;
                }
                else if(event.mouseButton.button == sf::Mouse::Right && mb == 2) {
                    mouseReleased = true;
                }
            }
            else if(event.type == sf::Event::KeyPressed) {
                keyBuff.push_back(event.key);
            }
        }
        if(!mousePressed && mouseReleased) mb = 0;
        if(mb != 1) LMBEventHandled = false;
        if(mb != 2) RMBEventHandled = false;

        updateDelta();
        logicMenuInterface();
        //logicParticles();
        logicWeather();
        //Weather.dayTimeInMinutes = 0.0;

        if(quit) break;

        /*static float particleCount = 0.f;
        particleCount += deltaTime/1.5f;
        while(particleCount > 1.f) {
            particleCount -= 1.f;
            Particle.push_back(ParticleClass(1900.f+rand()%7-3,
                                             1200.f+rand()%7-3,
                                             (rand()%360)/180.f*M_PI,
                                             1.1f,
                                             5.f+(rand()%80)/100.f,
                                             0.f, 3,
                                             sf::Color(210+rand()%40, 70+rand()%80, 20),
                                             255.f, true, true));
            for(int i=0; i<1; ++i) {
                Particle.push_back(ParticleClass(1900.f+rand()%41-20,
                                                 1200.f+rand()%41-20,
                                                 M_PI+(rand()%85)/180.f*M_PI,
                                                 1.1f,
                                                 0.4f,
                                                 0.f, 3,
                                                 sf::Color(90, 90, 90),
                                                 100.f, false));
            }
        }*/

        if(login[0]) {
            mb = 0;
            if(network.startConnecting()) {
                mainLoopGame();
                network.disconnect();
            }
            resetWorld();
            /*LightSource.resize(1);
            LightSource[0].x = 1500.f;
            LightSource[0].y = 1000.f;
            LightSource[0].color = sf::Vector3f(1.f, 1.f, 0.7f);
            LightSource[0].textureIndex = 0;*/
            login[0] = 0;
            password[0] = 0;
            isConnectedToServer = false;
            playerCharacterID = -1;
            blackScreenAlpha = 255.f;

            Interface.menuGUIControl.editBox["logInLoginEditBox"].reset();
            Interface.menuGUIControl.editBox["logInPasswordEditBox"].reset();

            if(!window.isOpen()) return;
        }

        blackScreenAlpha -= deltaTime*7.f;
        if(blackScreenAlpha < 100.f) blackScreenAlpha -= deltaTime*3.f;
        if(blackScreenAlpha < 0.f) blackScreenAlpha = 0.f;

        if(mouseReleased) mb = 0;

        normalMapFBO.clear(sf::Color(128, 128, 255));
        heightMapFBO.clear(sf::Color(50, 50, 50));

        shadowCaster.clear();
        spriteDrawQueue.clear();
        renderMapLayerOne();
        spriteDrawQueue.sort();
        spriteDrawQueue.draw();
        renderMapLayerTwo();
        renderMapLayerThree(); //message width do wywalenia, text width i height z button do wywalenia
        renderWeather();

        colorMapFBO.display();
        normalMapFBO.display();
        heightMapFBO.display();

        renderLights();

        // DEBUG
        /*if(mb == 1) {
            vPoint pos = getWorldPosition(mx, my, View);
            Tile[int(pos.x/TILE_SIZE)][int(pos.y/TILE_SIZE)].sceneryType = 21;
        }*/
        //

        //vPoint pos = getScreenPosition(1900.f, 1200.f, View);
        /*vPoint pos = vPoint(mx, my);
        lightShader.setParameter("lightPos", pos.x/(float)window.getSize().x, pos.y/(float)window.getSize().y);
        if(globalTime < timeout_lightningLight) {
            lightShader.setParameter("ambientLight", 1.f);
        }
        else lightShader.setParameter("ambientLight", std::min(ambientLight/255.f+0.1f, 1.f));
        lightMapFBO.draw(sf::Sprite(lightMapFBO.getTexture()), &lightShader);
        lightMapFBO.display();*/

		sceneFBO.draw(sf::Sprite(colorMapFBO.getTexture()));
		sceneFBO.draw(sf::Sprite(lightDiffuseMap1FBO.getTexture()), multiplyRenderState);
		//sceneFBO.draw(sf::Sprite(lightSpecularMap1FBO.getTexture()), addRenderState);

        sceneFBO.display();

        renderPostProcess();
        renderMenuInterface();
        if(blackScreenAlpha > 0.01f) {
            sf::RectangleShape blackScreen(sf::Vector2f(window.getSize().x, window.getSize().y));
            blackScreen.setFillColor(sf::Color(0, 0, 0, std::min((int)blackScreenAlpha, 255)));
            window.draw(blackScreen);
        }

        static sf::Time prev = globalClock.getElapsedTime();
        printf("%.2lf %.2f delta: %.2lf\n", Weather.dayTimeInMinutes/60.0, Weather.ambientShadowLength, 1000.0/(globalClock.getElapsedTime().asMilliseconds()-prev.asMilliseconds()));
        prev = globalClock.getElapsedTime();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) Weather.dayTimeInMinutes += 10.0*deltaTime;

        window.display();

        globalTime += deltaTime/30.0*1000.0;

        View.x = 1400.f+((float)mx/(float)window.getSize().x-0.5f)*100.f+viewOffsetX;
        View.y = 920.f+((float)my/(float)window.getSize().y-0.5f)*100.f+viewOffsetY;
    }
}

/**
* @brief Method containing in-game loop.
*
* Calls methods from LogicModule, RenderModule and NetworkModule.
*/
void Master::mainLoopGame()
{
    /*DataStreamClass dataStream("test.dat");
    sf::Texture texTEST;
    //texTEST.loadFromFile("test.png");
    dataStream.loadTexture("test/test2/test3/test4.png", texTEST);
    sf::Sprite sprTEST;
    sprTEST.setTexture(texTEST);
    sprTEST.setPosition(0, 0);*/

    BenchmarkClass benchmark;
    BenchmarkClass benchmark2;
    while(window.isOpen()) {
        benchmark.clearTimers();
        benchmark2.clearTimers();

        benchmark.startTimer(0);

        mx = sf::Mouse::getPosition(window).x;
        my = sf::Mouse::getPosition(window).y;

        bool mousePressed = false;
        bool mouseReleased = false;
        keyBuff.clear();
        keyBuffHandled = false;
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            else if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    mb = 1;
                    mx = event.mouseButton.x;
                    my = event.mouseButton.y;
                    mousePressed = true;
                }
                else if(event.mouseButton.button == sf::Mouse::Right) {
                    mb = 2;
                    mx = event.mouseButton.x;
                    my = event.mouseButton.y;
                    mousePressed = true;
                }
            }
            else if(event.type == sf::Event::MouseButtonReleased) {
                if(event.mouseButton.button == sf::Mouse::Left && mb == 1) {
                    mouseReleased = true;
                }
                else if(event.mouseButton.button == sf::Mouse::Right && mb == 2) {
                    mouseReleased = true;
                }
            }
            else if(event.type == sf::Event::KeyPressed) {
                keyBuff.push_back(event.key);
            }
        }
        if(!mousePressed && mouseReleased) mb = 0;
        if(mb != 1) LMBEventHandled = false;
        if(mb != 2) RMBEventHandled = false;

        updateDelta();
        benchmark.startTimer(1);
        network.manageNetworkEvents();
        if(!inGameError.empty()) {
            return;
        }
        benchmark.startTimer(2);
        logicWeather();
        if(playerCharacterID >= 0) {
            logicInterface();
            logicCharacters();
            logicProjectiles();
            logicParticles();
            logicPlayerInput();
            logicSendPosition();
            logicView();
        }
        benchmark.startTimer(3);

        if(mouseReleased) mb = 0;

        benchmark.startTimer(4);

        normalMapFBO.clear(sf::Color(128, 128, 255));
        heightMapFBO.clear(sf::Color(50, 50, 50));
        benchmark.startTimer(5);

        benchmark2.startTimer(0);
        shadowCaster.clear();
        benchmark2.startTimer(1);
        spriteDrawQueue.clear();
        renderMapLayerOne();
        benchmark2.startTimer(2);
        renderAllCharacters();
        spriteDrawQueue.sort();
        spriteDrawQueue.draw();
        benchmark2.startTimer(3);
        renderProjectiles();
        benchmark2.startTimer(4);
        spriteDrawQueue.clear();
        renderMapLayerTwo();
        benchmark2.startTimer(5);
        renderMapLayerThree(); //todo: drzewka rysowac w dobrej pozycji, podawac xy lewego gornego rogu, message width do wywalenia, text width i height z button do wywalenia
        spriteDrawQueue.sort();
        spriteDrawQueue.draw();
        benchmark2.startTimer(6);
        renderParticles();
        benchmark2.startTimer(7);
        renderWeather(); //todo: 1 wywolanie scene.draw
        benchmark2.startTimer(8);
        benchmark2.startTimer(9);

        colorMapFBO.display();
        normalMapFBO.display();
        heightMapFBO.display();

        renderLights();

        benchmark2.startTimer(-1);

        benchmark.startTimer(6);

        benchmark.startTimer(7);
		sceneFBO.draw(sf::Sprite(colorMapFBO.getTexture()));
        benchmark.startTimer(8);
		sceneFBO.draw(sf::Sprite(lightDiffuseMap1FBO.getTexture()), multiplyRenderState);
		//sceneFBO.draw(sf::Sprite(lightSpecularMap1FBO.getTexture()), addRenderState);

        renderPostProcess();
        benchmark.startTimer(9);
		if(playerCharacterID >= 0) {
		    renderInterface();
		}
		else {
            sf::Text text;
            text.setCharacterSize(11);
            text.setString("Connecting to game server.");
            text.setPosition((window.getSize().x-getTextWidth("Connecting to game server.", 11))/2,
                             window.getSize().y/2-20);
            text.setColor(sf::Color(220, 220, 220));
            window.draw(text);
		}
        window.display();

        /*
        if(key[KEY_8]) {
            std::ofstream out("map.dat");
            out << Tile.size() << " " << Tile[0].size() << "\n";
            for(size_t i=0; i<Tile[0].size(); ++i) {
                for(size_t j=0; j<Tile.size(); ++j) {
                    out << Tile[j][i].TileType << " " << Tile[j][i].SceneryType << " ";
                }
                out << "\n";
            }
            while(key[KEY_8]);
        }
        if(key[KEY_7]) {
            for(int i=0; i<1000; ++i) for(int j=0; j<1000; ++j) if(Tile[i][j].TileType<0 && Tile[i][j].SceneryType<0 && rand()%65==0) Tile[i][j].SceneryType=22+rand()%3;
            for(int i=1; i<999; ++i) for(int j=1; j<999; ++j) if(Tile[i][j].TileType<=7 && Tile[i][j].TileType>=0 && Tile[i][j].SceneryType<0 && rand()%10==0) {
                if(Tile[i][j-1].TileType>=0 && Tile[i][j-1].TileType<=7 &&
                   Tile[i][j+1].TileType>=0 && Tile[i][j+1].TileType<=7 &&
                   Tile[i-1][j].TileType>=0 && Tile[i-1][j].TileType<=7 &&
                   Tile[i+1][j].TileType>=0 && Tile[i+1][j].TileType<=7 &&
                   Tile[i-2][j-2].TileType>=0 && Tile[i-2][j-2].TileType<=7 &&
                   Tile[i-1][j-1].TileType>=0 && Tile[i-1][j-1].TileType<=7) {
                    Tile[i][j].SceneryType=25+rand()%2;
                }
            }
            //vPoint pos=GetAbsolutePosition(mx,my,View);
            //Tile[int(pos.x/TILE_SIZE)][int(pos.y/TILE_SIZE)].SceneryType=25+rand()%2;
            while(key[KEY_7]);
        }*/

        /*if(key[KEY_1]) Weather.RainType=1;
        if(key[KEY_2]) Weather.RainType=2;
        if(key[KEY_3]) {Weather.RainType=0;Weather.StormType=3;}*/

        //glFlush();
        //glFinish();
        //if(FindWindow(NULL,"project1")==NULL) exit(0);
        //SwapBuffers(GetDC(FindWindow(NULL,"project1")));

        globalTime += deltaTime/30.0*1000.0;

        benchmark.startTimer(-1);
        /*printf("benchmark: 0) %.3lf ms\n", benchmark.timer[0]);
        printf("           1) %.3lf ms\n", benchmark.timer[1]);
        printf("           2) %.3lf ms\n", benchmark.timer[2]);
        printf("           3) %.3lf ms\n", benchmark.timer[3]);
        printf("           4) %.3lf ms\n", benchmark.timer[4]);
        printf("           5) %.3lf ms\n", benchmark.timer[5]);
        printf("           6) %.3lf ms\n", benchmark.timer[6]);
        printf("           7) %.3lf ms\n", benchmark.timer[7]);
        printf("           8) %.3lf ms\n", benchmark.timer[8]);
        printf("           9) %.3lf ms\n", benchmark.timer[9]);
        printf("benchmark2 0) %.3lf ms\n", benchmark2.timer[0]);
        printf("           1) %.3lf ms\n", benchmark2.timer[1]);
        printf("           2) %.3lf ms\n", benchmark2.timer[2]);
        printf("           3) %.3lf ms\n", benchmark2.timer[3]);
        printf("           4) %.3lf ms\n", benchmark2.timer[4]);
        printf("           5) %.3lf ms\n", benchmark2.timer[5]);
        printf("           6) %.3lf ms\n", benchmark2.timer[6]);
        printf("           7) %.3lf ms\n", benchmark2.timer[7]);
        printf("           8) %.3lf ms\n", benchmark2.timer[8]);
        printf("           9) %.3lf ms\n", benchmark2.timer[9]);*/
    }
}

void Master::init()
{
    if(!logManager.create("log.txt")) {
        error("Could not create log file 'log.txt'.");
    }
    sf::err().rdbuf((std::streambuf*)&logManager);

    info("Loading game settings.");
    loadGameSettings("settings.ini");

    if(!sf::Shader::isAvailable()) {
        error("Detected graphics card does not support shaders.");
    }

    if(sf::Texture::getMaximumSize() < SUPPORTED_TEXTURE_SIZE_REQUIREMENT) {
        error("Detected graphics card does not support required %dp textures.", SUPPORTED_TEXTURE_SIZE_REQUIREMENT);
    }
    info("Detected graphics card support %dp textures.", sf::Texture::getMaximumSize());

    if(GameSettings.screenWidth < MINIMUM_SCREEN_WIDTH || GameSettings.screenHeight < MINIMUM_SCREEN_HEIGHT ||
       GameSettings.screenWidth > sf::Texture::getMaximumSize() || GameSettings.screenHeight > sf::Texture::getMaximumSize() ||
       !sf::VideoMode(GameSettings.screenWidth, GameSettings.screenHeight, 32).isValid()) {

        if(GameSettings.loaded) {
            inGameError = "Screen resolution from 'settings.ini' not supported.";
            info("Screen resolution from 'settings.ini' not supported.");
        }

        std::vector <sf::VideoMode> videoMode = sf::VideoMode::getFullscreenModes();
        int found = -1;
        for(size_t i=0; i<videoMode.size(); ++i) {
            if(videoMode[i].bitsPerPixel == 32 &&
               videoMode[i].width >= MINIMUM_SCREEN_WIDTH &&
               videoMode[i].height >= MINIMUM_SCREEN_HEIGHT &&
               videoMode[i].width <= sf::Texture::getMaximumSize() &&
               videoMode[i].height <= sf::Texture::getMaximumSize() &&
               (found < 0 || videoMode[found].width > videoMode[i].width)) {
                found = i;
            }
        }
        if(found >= 0) {
            info("Found valid screen resolution: %u x %u 32bpp.",
                 videoMode[found].width, videoMode[found].height);
            GameSettings.screenWidth = videoMode[found].width;
            GameSettings.screenHeight = videoMode[found].height;
            saveSettings();
        }
        else {
            if(videoMode.empty()) error("Could not find any valid screen resolution.");
            else error("Could not find any valid screen resolution.\nThe best found is: %u x %u %ubpp.\nGame requires at least %d x %d 32bpp.",
                       videoMode[0].width, videoMode[0].height, videoMode[0].bitsPerPixel, MINIMUM_SCREEN_WIDTH, MINIMUM_SCREEN_HEIGHT);
        }
    }

    info("Setting up screen (%d x %d %s).",
         GameSettings.screenWidth,
         GameSettings.screenHeight,
         GameSettings.fullscreen ? "Fullscreen mode" : "Window mode");

    sf::ContextSettings settings;
    settings.antialiasingLevel = 2;
    if(GameSettings.fullscreen) {
        window.create(sf::VideoMode(GameSettings.screenWidth, GameSettings.screenHeight, 32), "Client", sf::Style::Fullscreen, settings);
    }
    else {
        window.create(sf::VideoMode(GameSettings.screenWidth, GameSettings.screenHeight, 32), "Client", sf::Style::Default, settings);
    }

    window.setVerticalSyncEnabled(true);
    info("Video initialized (VSync enabled).");

    info("Used antialiasing level: %u.", window.getSettings().antialiasingLevel);
    info("OpenGL version: %u.%u.", window.getSettings().majorVersion, window.getSettings().minorVersion);

    info("Creating frame buffer objects.");
    colorMapFBO.create(window.getSize().x, window.getSize().y);
    normalMapFBO.create(window.getSize().x, window.getSize().y);
    heightMapFBO.create(window.getSize().x, window.getSize().y);
    shadowMapFBO.create(window.getSize().x, window.getSize().y);
    ambientShadowMapFBO.create(window.getSize().x, window.getSize().y);
    lightDiffuseMap1FBO.create(window.getSize().x, window.getSize().y);
    lightDiffuseMap2FBO.create(window.getSize().x, window.getSize().y);
    lightSpecularMap1FBO.create(window.getSize().x, window.getSize().y);
    lightSpecularMap2FBO.create(window.getSize().x, window.getSize().y);
    sceneFBO.create(window.getSize().x, window.getSize().y);

    info("Starting resources loading thread.");
    sf::Thread thread(&Master::loadResourcesThread, this);
    thread.launch();

    float arc = 0.f;
    sf::Text text;
    text.setCharacterSize(14);
    text.setString("Loading");
    text.setPosition(sf::Vector2f(15.f, window.getSize().y-text.getLocalBounds().height-15.f));
    globalClock.restart();
    while(1) {
        updateDelta();
        arc += deltaTime/20.f;

        float color = (sin(arc)+1.f)/2.f*200.f+55.f;
        text.setColor(sf::Color(255, 255, 255, color));
        window.clear(sf::Color(0, 0, 0, 0));
        window.draw(text);
        window.display();

        sf::sleep(sf::milliseconds(30));

        loadingDoneMutex.lock();
        if(loadingDone) break;
        loadingDoneMutex.unlock();
    }

    info("Generating tile transitions (creating FBO, compiling shader).");
    sf::RenderTexture tileTransitionFBO;
    if(!tileTransitionFBO.create(TILE_SIZE, TILE_SIZE)) {
        error("Could not create tile transition FBO.");
    }
    sf::Shader tileTransitionShader;
    if(!tileTransitionShader.loadFromMemory(VERTEX_SHADER_TILE_TRANSITION,
                                            FRAGMENT_SHADER_TILE_TRANSITION)) {
        error("Could not compile tileTransition shader. Please report this bug.");
    }

    //CTextureAtlas atl;
    for(int i=0; i<256; ++i) {
        int j = i;
        if(j%2) tileTransitionShader.setParameter("texUpLeft", 1.f);
        else tileTransitionShader.setParameter("texUpLeft", 0.f);
        j /= 2;
        if(j%2) tileTransitionShader.setParameter("texUp", 1.f);
        else tileTransitionShader.setParameter("texUp", 0.f);
        j /= 2;
        if(j%2) tileTransitionShader.setParameter("texUpRight", 1.f);
        else tileTransitionShader.setParameter("texUpRight", 0.f);
        j /= 2;
        if(j%2) tileTransitionShader.setParameter("texRight", 1.f);
        else tileTransitionShader.setParameter("texRight", 0.f);
        j /= 2;
        if(j%2) tileTransitionShader.setParameter("texDownRight", 1.f);
        else tileTransitionShader.setParameter("texDownRight", 0.f);
        j /= 2;
        if(j%2) tileTransitionShader.setParameter("texDown", 1.f);
        else tileTransitionShader.setParameter("texDown", 0.f);
        j /= 2;
        if(j%2) tileTransitionShader.setParameter("texDownLeft", 1.f);
        else tileTransitionShader.setParameter("texDownLeft", 0.f);
        j /= 2;
        if(j%2) tileTransitionShader.setParameter("texLeft", 1.f);
        else tileTransitionShader.setParameter("texLeft", 0.f);

        tileTransitionFBO.draw(sf::Sprite(tileTransitionTexture[0][0]), &tileTransitionShader);
        tileTransitionFBO.display();
        sf::Image img = tileTransitionFBO.getTexture().copyToImage();
        //atl.add(tileTransitionTexture[i/16][i%16], *(new sf::Sprite), img, sf::IntRect(0, 0, 50, 50));
        if(!tileTransitionTexture[i/16][i%16].loadFromImage(img)) {
            error("Could not load tile transition texture from image.");
        }
    }
    //atl.pack(900);

    info("Creating interface.");
    Interface.window.push_back(WindowClass("Character Inventory", 200, 200, 380, 425));
    Interface.window.back().setLogicCallback(&Master::callback_logicCharacterInventoryWindow);
    Interface.window.back().setRenderCallback(&Master::callback_renderCharacterInventoryWindow);
    Interface.window.back().visible = false;
    Interface.window.push_back(WindowClass("Object Description", 300, 300, 250, 300));
    Interface.window.back().setLogicCallback(&Master::callback_logicObjectDescriptionWindow);
    Interface.window.back().setRenderCallback(&Master::callback_renderObjectDescriptionWindow);
    Interface.window.back().visible = false;
    Interface.window.push_back(WindowClass("Trade with NPC", 200, 200, 500, 400));
    Interface.window.back().setLogicCallback(&Master::callback_logicTradeWithNPCWindow);
    Interface.window.back().setRenderCallback(&Master::callback_renderTradeWithNPCWindow);
    Interface.window.back().visible = false;
    Interface.window.push_back(WindowClass("Character Stats", 200, 200, 380, 425));
    Interface.window.back().setLogicCallback(NULL);
    Interface.window.back().setRenderCallback(&Master::callback_renderCharacterStatsWindow);
    Interface.window.back().visible = false;
    Interface.window.push_back(WindowClass("Quest Log", 200, 200, 380, 425));
    Interface.window.back().setLogicCallback(NULL);
    Interface.window.back().setRenderCallback(NULL);
    Interface.window.back().visible = false;
    Interface.window.push_back(WindowClass("Skill Tree", 200, 200, 380, 425));
    Interface.window.back().setLogicCallback(NULL);
    Interface.window.back().setRenderCallback(NULL);
    Interface.window.back().visible = false;

    Interface.chatY = window.getSize().y-(Interface.chatTabTexture.getSize().y-3)-Interface.chatWindowTexture.getSize().y-Interface.chatEditBoxTexture.getSize().y;

    EditBoxClass chatEditBox(7,
                             Interface.chatY+(Interface.chatTabTexture.getSize().y-3)+Interface.chatWindowTexture.getSize().y+6,
                             Interface.chatEditBoxTexture.getSize().x-14,
                             15,
                             "",
                             GUIControlClass::Transparent);
    chatEditBox.lengthLimit = CHAT_MESSAGE_LENGTH_LIMIT;
    Interface.GUIControl.editBox["chatEditBox"] = chatEditBox;
    Interface.chatTab.push_back(CHAT_TAB_LOCAL);
    Interface.chatTab.push_back(CHAT_TAB_GLOBAL);
    addMessageToChat(Interface.localChat, "Connecting to the game server.", CHAT_TAB_LOCAL);
    addMessageToChat(Interface.globalChat, "Welcome to Global Chat.", CHAT_TAB_GLOBAL);

    ButtonClass toggleChatButton(3, window.getSize().y+1, 50, 50, "T");
    Interface.GUIControl.button["toggleChatButton"] = toggleChatButton;
    //Interface.toggleChatButton.y=window.getSize().y-(Interface.ChatTabImage.Height()-3)-Interface.ChatWindowImage.Height()-Interface.ChatEditBoxImage.Height()-Interface.toggleChatButtonTexture.Height();

    /*ButtonClass logInButton(50, 100, 60, 20, "Log In", -260.f, GUIControlClass::Menu);
    Interface.menuGUIControl.button["logInButton"] = logInButton;
    ButtonClass settingsButton(50, 122, 70, 20, "Settings", -280.f, GUIControlClass::Menu);
    Interface.menuGUIControl.button["settingsButton"] = settingsButton;
    ButtonClass aboutButton(50, 144, 55, 20, "About", -300.f, GUIControlClass::Menu);
    Interface.menuGUIControl.button["aboutButton"] = aboutButton;
    ButtonClass quitButton(50, 166, 50, 20, "Quit", -320.f, GUIControlClass::Menu);
    Interface.menuGUIControl.button["quitButton"] = quitButton;*/

    EditBoxClass logInLoginEditBox(((int)window.getSize().x-120)/2, (int)window.getSize().y/2-50, 120, 15);
    logInLoginEditBox.helpText = "login";
    logInLoginEditBox.lengthLimit = LOGIN_LENGTH_LIMIT;
    Interface.menuGUIControl.editBox["logInLoginEditBox"] = logInLoginEditBox;
    EditBoxClass logInPasswordEditBox(((int)window.getSize().x-120)/2, (int)window.getSize().y/2-30, 120, 15);
    logInPasswordEditBox.helpText = "password";
    logInPasswordEditBox.passwordMode = true;
    logInPasswordEditBox.lengthLimit = PASSWORD_LENGTH_LIMIT;
    Interface.menuGUIControl.editBox["logInPasswordEditBox"] = logInPasswordEditBox;
    ButtonClass logInButton(((int)window.getSize().x-getTextWidth("Log In", 14))/2, (int)window.getSize().y/2-10, 60, 20, "Log In", -260.f, GUIControlClass::Menu);
    Interface.menuGUIControl.button["logInButton"] = logInButton;
    ButtonClass settingsButton(((int)window.getSize().x-getTextWidth("Settings", 14))/2, window.getSize().y/2+10, 70, 20, "Settings", -280.f, GUIControlClass::Menu);
    Interface.menuGUIControl.button["settingsButton"] = settingsButton;
    ButtonClass aboutButton(((int)window.getSize().x-getTextWidth("About", 14))/2, window.getSize().y/2+30, 55, 20, "About", -300.f, GUIControlClass::Menu);
    Interface.menuGUIControl.button["aboutButton"] = aboutButton;
    ButtonClass quitButton(((int)window.getSize().x-getTextWidth("Quit", 14))/2, window.getSize().y/2+50, 50, 20, "Quit", -320.f, GUIControlClass::Menu);
    Interface.menuGUIControl.button["quitButton"] = quitButton;

    ButtonClass OKButton(((int)window.getSize().x-getTextWidth("OK", 14))/2, window.getSize().y/2, 60, 20, "OK", 255.f, GUIControlClass::Menu);
    Interface.menuErrorGUIControl.button["OKButton"] = OKButton;

    info("Initializing done.");
}

void Master::run()
{
    info("Client running.");
    mainLoopMenu();
    info("Application closed normally.");
}
