#include "NewCode.hpp"

Faction::AddPlayerResult::Enum Faction::addPlayer(Character &player)
{
    //if(player.hasFaction()) return AddPlayerResult::PlayerHasFaction;
    //if(isFull()) return AddPlayerResult::FactionIsFull;

    //member.push_back(player);

    return AddPlayerResult::OK;
}

Faction::RemovePlayerResult::Enum Faction::removePlayer(Character &player)
{
    //if(!isPlayerMember(player)) return RemovePlayerResult::PlayerIsNotMember;
    //if(leader.ID == player.ID) return RemovePlayerResult::PlayerIsLeader;

    return RemovePlayerResult::OK;
}

Faction::ChangePlayerRankResult::Enum Faction::changePlayerRank(Character &player, Faction::PlayerRank::Enum newRank)
{
    /*if(!isPlayerMember(player)) return ChangePlayerRankResult::PlayerIsNotMember;
    if(getPlayerRank(player) == ) return ChangePlayerRankResult::
    if(!PlayerRank::isValid(newRank)) return ChangePlayerRankResult::InvalidRank;
    if()*/
}

Faction::Faction(Character &newLeader)
    :   name("undefined"),
        leader(newLeader)
{
    member.push_back(Member(newLeader, PlayerRank::Leader));
}

void test()
{
    CharacterClass a;
    Faction faction(a);

    container <Character> cont;

    cont.push_back(Character());
    cont.push_back(Character());
    cont.push_back(Character());
    cont.push_back(Character());
    cont.push_back(Character());
    cont.push_back(Character());
    cont.push_back(Character());
    cont.push_back(Character());
    cont.push_back(Character());
    cont.push_back(Character());
    cont.push_back(Character());
    cont.push_back(Character());
    cont.push_back(Character());

    for(size_t i=0; i<cont.size(); ++i) faction.addPlayer(cont[i]);

    faction.KUPSKO();

    //printf("%d %d\n", cont[5].param[0], cont[9].param[0]);
}
