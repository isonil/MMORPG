#include "Client.hpp"

/*
  todo:
    //now
    to czy w npcType item na poprawnym slocie sprawdzane w loadnpctypes a nie w loadnpcs
    object can be placed on slot, moze po prostu basetype i eqtype sprawdzac && ?
    dodawac ambient do kzdego swiatla moze? zamiast robic max
    dla kolorowych swiatel w diffusie tez uwzgledniac kolor?
    zabezpieczyc sie przed ujemnymi indexami w plikach?
    isstackable wywalic parametr?
    sprawdzanie tex czy window.x i y >= supported tex size przy inicjalizacji
    ambientLight do WeatherClass
    ogarnac .display !!! wszedzie
    Shaders.hpp do SDK
    sprawdzic czy pocisk nie moze kolidowac z tym kto go wystrzelil
    jesli klikne na okno to GUI nie dostaje eventow
    inne opcje w menu - Quit, Settings...
    obsluga prawego kliku, nie dziala otwieranie object description window
    updateDelta zmienic na sfmlowe, to samo na serwerze (?) i w SDK
    textureSplattingTexture poprawic w renderMapLayerOne
    scancodeToChar chyba mozna wywalic? tak samo jak allowedChatKeys
    jedna wielka kolejka renderowania?
    uzytek z sunposition moonposition, sprawdzic jak wyznaczam pozycje, czy uzywam, moze wywalic?
    music player? :)
    message box do errorow w SDK, zabezpieczyc sie przed message box przed inicjalizacja OpenLayer (?) w SDK
    ctrl+F //*** lub // ***
    zrobic cos z tym sprawdzaniem poprawnych znakow przy wysylaniu wiadomosci
    LMB_NEW_PRESSED_OUTSIDE do logic windows?
    zamiana spacji na _ przy wysylaniu chat request
    zamiana spacji na _ przy wysylaniu log in packet
    czyszczenie editboxow po zalogowaniu
    czyszczenie wszystkich zmiennych po zalogowaniu
    w mainLoopMenu po powrocie z mainLoopGame ustawic view, jakas stala dla MENU_VIEW, ustawic pogode do menu no i dayTime
    ogarnac teksture penumbry, ostre krawedzie
    bialy ogien

    //later
    uzyc TYLKO sound/music z sfmla + obsluga sound z gameSettings
    obsluga wielu swiatel
    zrobic porzadek w SDK, Weather chyba w ogole niepotrzebne, to samo particle, projectiles itd
    pozbyc sie 'przeskakiwania' przy poruszaniu, raz ze czasem przeskakuje nawet jak wysoki fps, dwa ze ma to byc plynne
    okreslac w parametrach scenerii, obiektu co emituje cien i jaki
    wywalic openlayer, audiere moze tez
    weapon type name zmienic na cos bardziej sensownego niz small gun/big gun
    porzadek z tym gdzie jest konstruowany pakiet, tylko w getNamePacket()
    niektore elementy maja byc przyslaniane przez cien, np postacie albo krzaki
    pozbyc sie wszystkich warningow
    optymalizacja shaderow
    polepszyc okienko czatu, lepsze zakladki, mozliwosc powiekszenia, zaznaczanie tekstu, itd
    nazwy bitmap pozmieniac na nowy styl nazewnictwa
    ctrl+F wszystkie todo we wszystkich plikach
    polskie znaki na czacie?
    porzadek w inicjalizacji i w glownych petlach gry, to samo na serwerze i w SDK
    sposob na zamkniecie serwera poprawnie, a nie krzyzykiem konsoli, moze wprowadzic komendy wysylane przez Deva typu saveWorld, closeServer, etc.
    cienie lekko sie buguja tuz przy krawedziach scian, pewnie przez to ze heightMap jest rowny 50
    powywalac niepotrzebne includy w .hpp te ktore moga byc w .cpp
    przywileje administratora w launcherze
    SDK edycja parametrow
    SDK pasek do przewijania obiektow
    SDK dodawanie NPC, osobne parametry dla kazdego NPC
    SDK odbierac eventy zamiast real-time
    info o disconnect serwera, zrobic jakis safe-disconnect na serwerze zeby wszystkich wylogowalo
    limity na serwerze MAX_PACKET_SIZE, uwzgledniac moze ilosc przesylanych rzeczy jakos? tam gdzie wysylam obiekty na ziemi np.

    //not important
    zrobic porzadek z tymi wszystkimi 'zewnetrznymi' klasami typu ButtonClass - zrobic getFoo(), itd.
    porzadek z wyswietlanym aktualnie object description, ten po najechaniu jak i okienko, tzn porzadek ze stwierdzeniem ktory obiekt wyswietlic
    addon -> attachment wszedzie
    Client/Server/SDK zmienic na Master?
    powywalac komentarze doxygenowe z SDK?
*/

/**
* @mainpage
*
* @b Description
* This is a documentation of official <name> client.
*
* Code is divided on several @ref MODULES_GROUP and one master class - Client -
* wich combines them together.\n
* All defines, global functions and variables are stored in global.hpp file
* which can be accessed from any other file.\n
* All classes except for Client and @ref MODULES_GROUP are stored in Classes.hpp file.\n
* Besides @ref MODULES_GROUP, Client class file, global.hpp and Classes.hpp there can be
* also other files included in any file.\n
*
* @b Rendering
* When drawing scene sprites (affected by light, view position, etc.) one can use
* draw queue.\n
* Changing current FBO is expensive so it's a better idea to
* push all color, normal and height maps to the draw queue and then invoke it.\n
* Interface can be drawn directly into window.
*
* @b Non-character @b Entities
* There are 3 main types of non-character entities.
*   - tiles - Static entities (they can't be changed during gameplay). Loaded by client from map file.
*   - sceneries - Static entities (they can't be changed during gameplay). Loaded by client from map file.
*   - objects - These entities are sent from server when seen by player. They can change their position, appear, disappear, etc.
* Each in-game tile holds tile type, scenery type and container of objects.
*
* @b Character @b Entities
* Character entities are divided into 2 groups.
* - players
* - NPC (non-player characters)
*
* @b Name @b Conventions
* - All classes except for Client and @ref MODULES_GROUP have Class suffix.\n
* - All class names begin with capital letter.\n
* - All variable/method names begin with small letter. If name consists
*   of more than 1 word, further words should begin with capital letter.\n
*   For example:
*   @code
*     thisIsExampleVariable
*   @endcode
*   If variable name can be divided into 2 groups a '_' can be used.\n
*   For example:
*   @code
*     groupName_variableName
*     timeout_something
*     timeout_somethingElse
*   @endcode
* - All defines must be written with capital letters.\n
*
* @see Client
* @see MODULES_GROUP
* @see global.hpp
* @see Classes.hpp
*/

/**
* @defgroup MODULES_GROUP Modules
*
* Client inherits from all modules.
*/

int main(int argc, char **argv)
{
    printf("Game client %s.\n", VERSION);
    printf("Build: %s %s\n", __DATE__, __TIME__);
    printf("Copyright 2011 Piotr Walczak\n");
    #ifdef _GLIBCXX_DEBUG
    printf("--DEBUG MODE--\n");
    #endif
    printf("\n");

    /*
    if(argc < 2 || strcmp(argv[1], "-launcher")) {
        MessageBoxA(NULL, "Please start game using launcher.", "Error", MB_OK);
        return 0;
    }
    */

    Client::getInstance().init();
    Client::getInstance().run();

    return 0;
}
END_OF_MAIN()
