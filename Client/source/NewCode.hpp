#ifndef NEW_CODE_HPP
#define NEW_CODE_HPP

#include "container.hpp"
#include "Classes.hpp"
#include "ReferenceContainer.hpp"
#include "Packets.hpp"
#include "Network.hpp"

typedef CharacterClass Character;

class Faction
{
    public:
        struct PlayerRank
        {
            enum Enum
            {
                Recruit = 0,
                Member,
                Commander,
                Leader
            };

            bool isValid(Enum val)
            {
                return val >= 0 && val < 4;
            }
        };

        struct AddPlayerResult
        {
            enum Enum
            {
                OK = 0,
                PlayerHasFaction,
                FactionIsFull
            };
        };

        struct RemovePlayerResult
        {
            enum Enum
            {
                OK = 0,
                PlayerIsLeader,
                PlayerIsNotMember
            };
        };

        struct ChangePlayerRankResult
        {
            enum Enum
            {
                OK = 0,
                InvalidRank,
                CantDowngradeLeader,
                CantPromoteToLeader,
                PlayerIsNotMember
            };
        };

        class Member
        {
            public:
                Character &player;
                PlayerRank::Enum rank;

                Member(Character &newPlayer, PlayerRank::Enum newPlayerRank)
                    :   player(newPlayer),
                        rank(newPlayerRank) {
                }
        };

    private:
        std::string name;
        container <Member> member;
        Character &leader;

    public:
        inline const std::string &getName() {return name;}
        inline Character &getLeader() {return leader;}
        inline container <Member> &getMembers() {return member;}

        AddPlayerResult::Enum addPlayer(Character &player);
        RemovePlayerResult::Enum removePlayer(Character &player);
        ChangePlayerRankResult::Enum changePlayerRank(Character &player, PlayerRank::Enum newRank);
        void setNewLeader();
        void removeFaction() {}

        void KUPSKO()
        {
            //printf("%d %d %d\n", leader.param[0], member[5].param[0], member[9].param[0]);
            //member[5].param[0] = 1;
            //member[9].param[0] = 2;
        }

        Faction(Character &newLeader);
};

void test();

#endif

/*

        struct AddPlayerResult
        {
            enum Enum
            {
                OK = 0,
                PlayerHasFaction,
                FactionIsFull
            };
        };

        struct RemovePlayerResult
        {
            enum Enum
            {
                OK = 0,
                PlayerIsLeader,
                PlayerIsNotMember
            };
        };

        struct ChangePlayerRankResult
        {
            enum Enum
            {
                OK = 0,
                InvalidRank,
                CantDowngradeLeader,
                CantPromoteToLeader,
                PlayerIsNotMember
            };
        };
*/
