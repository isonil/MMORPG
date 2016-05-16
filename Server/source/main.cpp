#include "Master.hpp"

/*
    ctrl f z todo na serwerze, bo costam bylo ze sprawdzaniem czy moge wywolac jakas funkcje z enet po wywolaniu innej, ale to chyba juz jest gdzies w tej liscie todo nizej
    if -> cond w skryptach? IF_FUNC COND_FUNC?
    alive/dead character
    player speed check
    timeouty na wszystko
    warny za nieprawidlowe pakiety, za duzy transfer - ForceDisconnect
    poruszanie sie npc - patrol
    taktyka AI - melee
    obsluga amunicji
    skrzynie
    gildie
    zapis/wczytanie swiata
    skilltree
    handel miedzy graczami
    minimapa
    menu
    obsluga przywilejow - GM
    komendy
    zakladanie kont przez http
    plynne przejscie granatow jak uderza w przeszkode
    plynne przejscie gracza jak go cofa
    zatapianie sie rzuconego granatu
    poprawic oswietlenie projectiles
    npc bez broni nie ma atakowac
    liczenie dmg dla projectiles
    automatyczna zmiana pogody
    pvp system
    safe zone
    log out system
    szukanie wolnego miejsca przy logowaniu
    sprawdzanie poprawnosci skryptu, quest index out of bounds itd
    addon -> attachment?
    quest log
    sprzedawanie itemow
    obsluga item quantity w ekwipunku
    loot z graczy
    wywalic parametr stackable z pliku

    podzial na wyspy:
        NORMAL:

        BUILD:
            wiezyczki
            budowanie
            pozyskiwanie surowcow
        QUEST:

    max level w exp, zabezpieczyc sie przed overflowem o ile jeszcze nie jestem

*/

/*
    IMPORTANT
        is packet guaranteed to have \0 at the end? (processing packets!!!)
        in forceDisconnect can I read/write to data after disconnect?
        todos in manageNetworkEvents()
        includy niekoniecznie w plikach .hpp tylko w .cpp
*/

int main()
{
    printf("Game server:\n");
    printf("    Version  -  %s\n", VERSION);
    printf("  Copyright  -  Piotr Walczak\n");
    printf("\n");
    printf("Build information:\n");
    printf("       Date  -  %s\n", __DATE__);
    printf("       Time  -  %s\n", __TIME__);
    printf("     Target  -  ");
    #ifdef DEBUG
    printf("Debug\n");
    #else
    printf("Release\n");
    #endif
    printf("\n");
    printf("Log: \n");

    Master::getInstance().init();
    Master::getInstance().run();
    Master::getInstance().release();

    return 0;
}
