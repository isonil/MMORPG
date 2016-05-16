#include "CharacterLostSight.hpp"

#include "Master.hpp"

void Packet <PACKET_CHARACTER_LOST_SIGHT>::onReceive(const ENetEvent &event)
{
    char characterSet = 0;
    int ID = 0;
    sscanf((char*)event.packet->data, "%*c %c %d", &characterSet, &ID);

    _assert(Master::getInstance().isValidCharacterSet(characterSet), "Invalid character set in processPacket_characterLostSight.");
    _assert(ID >= 0,"Character index is negative in processPacket_characterLostSight.");

    CharacterClass &character = Master::getInstance().getWorld().getCharacter(characterSet, ID);

    character.setVisibility(false);
    character.setPosition(sf::Vector2f(0.f, 0.f));
    character.setDestPosition(sf::Vector2f(0.f, 0.f));
}
