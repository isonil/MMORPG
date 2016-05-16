#include "CharacterPosition.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_CHARACTER_POSITION>::onReceive(const ENetEvent &event)
{
    char characterSet = 0;
    int ID = 0, x = 0, y = 0, dir = 0;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d %d", &characterSet, &ID, &x, &y, &dir);

    _assert(Master::getInstance().isValidCharacterSet(characterSet), "Invalid character set in processPacket_characterPosition.");
    _assert(ID >= 0,"Character index is negative in processPacket_characterPosition.");

    CharacterClass &character = Master::getInstance().getWorld().getCharacter(characterSet, ID);

    if(ID == playerCharacterID && characterSet == CHARACTER_PLAYER) {
        Master::getInstance().getWorld().getPlayer(ID).setPosition(sf::Vector2f(x, y));
        Master::getInstance().getWorld().getPlayer(ID).setDirection(dir/100.f);
    }
    else if(fabs(character.getPosition().x-x) > 150.f || fabs(character.getPosition().y-y) > 150.f) {
        character.setPosition(sf::Vector2f(x, y));
        character.setDestPosition(sf::Vector2f(x, y));
        character.setDirection(dir/100.f);
        character.setSpeed(7.5f);
    }
    else {
        character.setDestPosition(sf::Vector2f(x, y));
        float distance = Master::getInstance().getDistance(character.getPosition().x, character.getPosition().y, x, y);
        character.setSpeed(distance*0.24f);
    }
    character.setDestDirection(dir/100.f);
}

std::string Packet <PACKET_CHARACTER_POSITION>::construct(float x, float y, float dir)
{
    std::ostringstream oss;
    oss << PACKET_CHARACTER_POSITION << ' ' << (int)x << ' ' << (int)y << ' ' << int(dir*100.f);
    return oss.str();
}
