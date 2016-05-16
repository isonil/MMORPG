#include "Classes.hpp"

#include "Master.hpp"

void CharacterClass::sendPacket(const std::string &str)
{
    M.getNetwork().sendPacket(peer, str);
}
