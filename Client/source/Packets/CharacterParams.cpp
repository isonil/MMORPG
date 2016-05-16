#include "CharacterParams.hpp"

#include "Master.hpp"

void Packet <PACKET_CHARACTER_PARAMS>::onReceive(const ENetEvent &event)
{
    char ch, characterSet = 0;
    int ID = 0, x = 0, y = 0, dir = 0;
    int health = 0, maxHealth=0;
    int level = 1;
    std::string name = "undefined";

    std::istringstream packet((char*)event.packet->data);
    packet >> ch >> characterSet >> ID >> name >> x >> y >> dir >> health >> maxHealth >> level;

    _assert(Master::getInstance().isValidCharacterSet(characterSet), "Invalid character set in processPacket_characterParams.");
    _assert(ID >= 0, "Character index is negative in processPacket_characterParams.");

    CharacterClass &character = Master::getInstance().getWorld().getCharacter(characterSet, ID);

    character.setName(name);
    character.setPosition(sf::Vector2f(x, y));
    character.setDestPosition(sf::Vector2f(x, y));
    character.setDirection(dir/100.f);
    character.setDestDirection(dir/100.f);
    character.setVisibility(true);
    character.setParam(CHARACTER_PARAM_HEALTH, health);
    character.setParam(CHARACTER_PARAM_MAX_HEALTH, maxHealth);
    character.setParam(CHARACTER_PARAM_LEVEL, level);
    for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
        packet >> character.getObjectOnSlot(i).type;
        _assert(character.getObjectOnSlot(i).type < (int)Master::getInstance().ObjectType.size(),
                "Slot object type out of bounds in processPacket_characterParams.");
    }
}
