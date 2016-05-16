#include "CharacterParamChange.hpp"

#include "../Master.hpp"

void Packet <PACKET_CHARACTER_PARAM_CHANGE>::onReceive(const ENetEvent &event)
{
    char characterSet = 0;
    int ID = 0, param = 0, value = 0;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d", &characterSet, &ID, &param, &value);

    _assert(Master::getInstance().isValidCharacterSet(characterSet), "Invalid character set in processPacket_characterParamChange.");
    _assert(ID >= 0, "Character index is negative in processPacket_characterParamChange.");
    _assert(param >= 0 && param < CHARACTER_PARAMS_QUANTITY, "Character param out of bounds in processPacket_characterParamChange.");

    CharacterClass &character = Master::getInstance().getWorld().getCharacter(characterSet, ID);

    if(characterSet == CHARACTER_PLAYER && ID == playerCharacterID) {
        if(param == CHARACTER_PARAM_HEALTH && value < character.getParam(param)) {
            int offsetX = rand()%2+2;
            int offsetY = rand()%2+2;
            Master::getInstance().viewOffsetX = (rand()%2 == 0?(offsetX):(-offsetX));
            Master::getInstance().viewOffsetY = (rand()%2 == 0?(offsetY):(-offsetY));
        }
        if(param == CHARACTER_PARAM_EXPERIENCE) {
            int diff = value-character.getParam(param);
            if(diff > 0) {
                char message[100];
                sprintf(message, "+%d exp", diff);
                Master::getInstance().Interface.statusLogMessage.push_back(StatusLogMessageClass(message, sf::Color(100, 100, 255)));
            }
            else if(diff < 0) {
                char message[100];
                sprintf(message, "%d exp", diff);
                Master::getInstance().Interface.statusLogMessage.push_back(StatusLogMessageClass(message, sf::Color(255, 50, 50)));
            }
        }
        if(param == CHARACTER_PARAM_MONEY) {
            int diff = value-character.getParam(param);
            if(diff > 0) {
                char message[100];
                sprintf(message, "+%d money", diff);
                Master::getInstance().Interface.statusLogMessage.push_back(StatusLogMessageClass(message, sf::Color(255, 255, 50)));
            }
            else if(diff < 0) {
                char message[100];
                sprintf(message, "%d money", diff);
                Master::getInstance().Interface.statusLogMessage.push_back(StatusLogMessageClass(message, sf::Color(255, 50, 50)));
            }
        }
        if(param == CHARACTER_PARAM_LEVEL) {
            int diff = value-character.getParam(param);
            if(diff > 0) {
                Master::getInstance().Interface.statusLogMessage.push_back(StatusLogMessageClass("You advanced in experience level.", sf::Color(50, 255, 50)));
            }
            else if(diff < 0) {
                Master::getInstance().Interface.statusLogMessage.push_back(StatusLogMessageClass("You lost an experience level.", sf::Color(255, 50, 50)));
            }
        }
    }
    if(param == CHARACTER_PARAM_LEVEL) {
        int diff = value-character.getParam(param);
        if(diff > 0) {
            for(int i=0; i<100; ++i) {
                Master::getInstance().Particle.push_back(ParticleClass(character.getPosition().x+rand()%25-12,
                                                 character.getPosition().y+rand()%25-12,
                                                 (rand()%360)/180.f*M_PI,
                                                 0.4f, 4.f,
                                                 (rand()%360)/180.f*M_PI,
                                                 0, sf::Color(20, 20, 150),
                                                 255.f, true));
            }
            //playPositionalSound(levelUpSample, Player[playerCharacterID].x, Player[playerCharacterID].y, character->x, character->y);
            // ALLS
        }
    }
    character.setParam(param, value);
}
