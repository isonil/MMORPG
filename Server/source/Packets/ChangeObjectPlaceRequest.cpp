#include "ChangeObjectPlaceRequest.hpp"

#include "Master.hpp"

void Packet <PACKET_CHANGE_OBJECT_PLACE_REQUEST>::onReceive(const ENetEvent &event)
{
    int place = OBJECT_PLACE_NONE;
    int place_p1 = -1, place_p2 = -1, place_p3 = -1;
    int destination_place = OBJECT_PLACE_NONE;
    int destination_place_p1 = -1, destination_place_p2 = -1, destination_place_p3 = -1;
    sscanf((char*)event.packet->data, "%*c %d %d %d %d %d %d %d %d",
           &place, &place_p1, &place_p2, &place_p3,
           &destination_place,&destination_place_p1,&destination_place_p2,&destination_place_p3);

    bool acceptedFrom = false;
    bool acceptedTo = false;
    if(place != OBJECT_PLACE_NONE && destination_place != OBJECT_PLACE_NONE) {
        if(place == OBJECT_PLACE_GROUND) {
            if(!Master::getInstance().isOutOfMap(place_p1, place_p2)) {
                if(abs((int)Master::getInstance().Player[(int)event.peer->data].x/TILE_SIZE-place_p1) <= 1 &&
                   abs((int)Master::getInstance().Player[(int)event.peer->data].y/TILE_SIZE-place_p2) <= 1 &&
                   !Master::getInstance().Tile[place_p1][place_p2].object.empty()) {
                        if(Master::getInstance().isPickUpAble(Master::getInstance().Tile[place_p1][place_p2].object.back().type)) {
                            acceptedFrom = true;
                        }
                }
            }
        }
        else if(place == OBJECT_PLACE_INVENTORY) {
            if(place_p1 >= 0 && place_p2 >= 0 &&
               place_p1 < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
               place_p2 < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT) {
                if(Master::getInstance().Player[(int)event.peer->data].objectInInventory[place_p1][place_p2].type >= 0) {
                    acceptedFrom = true;
                }
            }
        }
        else if(place == OBJECT_PLACE_SLOT) {
            if(place_p1 >= 0 && place_p1 < CHARACTER_OBJECT_SLOTS_QUANTITY) {
                if(Master::getInstance().Player[(int)event.peer->data].objectOnSlot[place_p1].type >= 0) {
                    acceptedFrom = true;
                }
            }
        }
        else if(place == OBJECT_PLACE_INVENTORY_WEAPON_ATTACHMENT) {
            if(place_p1 >= 0 && place_p2 >= 0 && place_p3 >=0 &&
               place_p1 < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
               place_p2 < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT &&
               place_p3 < WEAPON_ATTACHMENTS_QUANTITY) {
                if(Master::getInstance().Player[(int)event.peer->data].objectInInventory[place_p1][place_p2].type >= 0 &&
                   Master::getInstance().Player[(int)event.peer->data].objectInInventory[place_p1][place_p2].param[OBJECT_PARAM_ADDON_1+place_p3] >= 0) {
                    acceptedFrom = true;
                }
            }
        }
        else if(place == OBJECT_PLACE_SLOT_WEAPON_ATTACHMENT) {
            if(place_p1 >= 0 && place_p2 >=0 &&
               place_p1 < CHARACTER_OBJECT_SLOTS_QUANTITY &&
               place_p2 < WEAPON_ATTACHMENTS_QUANTITY) {
                if(Master::getInstance().Player[(int)event.peer->data].objectOnSlot[place_p1].type >= 0 &&
                   Master::getInstance().Player[(int)event.peer->data].objectOnSlot[place_p1].param[OBJECT_PARAM_ADDON_1+place_p2] >= 0) {
                    acceptedFrom = true;
                }
            }
        }
        if(destination_place == OBJECT_PLACE_GROUND) {
            if(!Master::getInstance().isOutOfMap(destination_place_p1, destination_place_p2)) {
                if(abs((int)Master::getInstance().Player[(int)event.peer->data].x/TILE_SIZE-destination_place_p1) <= 1 &&
                   abs((int)Master::getInstance().Player[(int)event.peer->data].y/TILE_SIZE-destination_place_p2) <= 1 &&
                   Master::getInstance().Tile[destination_place_p1][destination_place_p2].object.size() < OBJECTS_PER_TILE_LIMIT &&
                   Master::getInstance().isPassable(destination_place_p1, destination_place_p2)) {
                    acceptedTo = true;
                }
            }
        }
        else if(destination_place == OBJECT_PLACE_INVENTORY) {
            if(destination_place_p1 >= 0 && destination_place_p2 >= 0 &&
               destination_place_p1 < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
               destination_place_p2 < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT) {
                if(Master::getInstance().Player[(int)event.peer->data].objectInInventory[destination_place_p1][destination_place_p2].type < 0) {
                    acceptedTo = true;
                }
            }
        }
        else if(destination_place == OBJECT_PLACE_SLOT) {
            if(destination_place_p1 >= 0 &&
               destination_place_p1 < CHARACTER_OBJECT_SLOTS_QUANTITY) {
                if(Master::getInstance().Player[(int)event.peer->data].objectOnSlot[destination_place_p1].type < 0) {
                    acceptedTo = true;
                }
            }
        }
        else if(destination_place == OBJECT_PLACE_INVENTORY_WEAPON_ATTACHMENT) {
            if(destination_place_p1 >= 0 && destination_place_p2 >= 0 && destination_place_p3 >= 0 &&
               destination_place_p1 < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
               destination_place_p2 < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT &&
               destination_place_p3 < WEAPON_ATTACHMENTS_QUANTITY) {
                if(Master::getInstance().Player[(int)event.peer->data].objectInInventory[destination_place_p1][destination_place_p2].type >= 0 &&
                   Master::getInstance().Player[(int)event.peer->data].objectInInventory[destination_place_p1][destination_place_p2].param[OBJECT_PARAM_ADDON_1+destination_place_p3] < 0) {
                    acceptedTo = true;
                }
            }
        }
        else if(destination_place == OBJECT_PLACE_SLOT_WEAPON_ATTACHMENT) {
            if(destination_place_p1 >= 0 && destination_place_p2 >= 0 &&
               destination_place_p1 < CHARACTER_OBJECT_SLOTS_QUANTITY &&
               destination_place_p2 < WEAPON_ATTACHMENTS_QUANTITY) {
                if(Master::getInstance().Player[(int)event.peer->data].objectOnSlot[destination_place_p1].type >= 0 &&
                   Master::getInstance().Player[(int)event.peer->data].objectOnSlot[destination_place_p1].param[OBJECT_PARAM_ADDON_1+destination_place_p2] < 0) {
                    acceptedTo = true;
                }
            }
        }

        ObjectClass *object = NULL;
        if(acceptedFrom && acceptedTo) {
            ObjectClass newObject;
            if(place == OBJECT_PLACE_GROUND)
                object = &Master::getInstance().Tile[place_p1][place_p2].object.back();
            else if(place == OBJECT_PLACE_INVENTORY)
                object = &Master::getInstance().Player[(int)event.peer->data].objectInInventory[place_p1][place_p2];
            else if(place == OBJECT_PLACE_SLOT)
                object = &Master::getInstance().Player[(int)event.peer->data].objectOnSlot[place_p1];
            else if(place == OBJECT_PLACE_INVENTORY_WEAPON_ATTACHMENT) {
                object = &newObject;
                object->type = Master::getInstance().Player[(int)event.peer->data].objectInInventory[place_p1][place_p2].param[OBJECT_PARAM_ADDON_1+place_p3];
            }
            else if(place == OBJECT_PLACE_SLOT_WEAPON_ATTACHMENT) {
                object = &newObject;
                object->type = Master::getInstance().Player[(int)event.peer->data].objectOnSlot[place_p1].param[OBJECT_PARAM_ADDON_1+place_p2];
            }

            _assert_return(object != NULL, Master::getInstance().Player[(int)event.peer->data].name.c_str(), (int)event.peer->data,
                           "Object is NULL in processPacket_changeObjectPlaceRequest.");
            _assert_return(object->type >=0 && object->type < (int)Master::getInstance().ObjectType.size(), Master::getInstance().Player[(int)event.peer->data].name.c_str(), (int)event.peer->data,
                           "Object type out of bounds in processPacket_changeObjectPlaceRequest.");

            if(destination_place == OBJECT_PLACE_SLOT) {
                if(!Master::getInstance().canObjectBePlacedOnSlot(object->type, destination_place_p1))
                    acceptedTo = false;
            }
            else if(destination_place == OBJECT_PLACE_SLOT_WEAPON_ATTACHMENT) {
                if(Master::getInstance().ObjectType[object->type].baseType != OBJECT_BASE_TYPE_ADDON) acceptedTo = false;

                _assert_return(Master::getInstance().Player[(int)event.peer->data].objectOnSlot[destination_place_p1].type < int(Master::getInstance().ObjectType.size()),
                               Master::getInstance().Player[(int)event.peer->data].name.c_str(),
                               (int)event.peer->data,
                               "Destination object type out of bounds in processPacket_changeObjectPlaceRequest.");

                if(Master::getInstance().ObjectType[Master::getInstance().Player[(int)event.peer->data].objectOnSlot[destination_place_p1].type].baseType != OBJECT_BASE_TYPE_WEAPON)
                    acceptedTo = false;
                else if(Master::getInstance().ObjectType[object->type].attachmentType != weaponAttachmentSlot[destination_place_p2].attachmentType)
                    acceptedTo = false;
                else if(Master::getInstance().ObjectType[object->type].weaponType != Master::getInstance().ObjectType[Master::getInstance().Player[(int)event.peer->data].objectOnSlot[destination_place_p1].type].weaponType)
                    acceptedTo = false;
            }
            else if(destination_place == OBJECT_PLACE_INVENTORY_WEAPON_ATTACHMENT) {
                if(Master::getInstance().ObjectType[object->type].baseType != OBJECT_BASE_TYPE_ADDON)
                    acceptedTo = false;

                _assert_return(Master::getInstance().Player[(int)event.peer->data].objectInInventory[destination_place_p1][destination_place_p2].type < (int)Master::getInstance().ObjectType.size(),
                               Master::getInstance().Player[(int)event.peer->data].name.c_str(),
                               (int)event.peer->data,
                               "Destination object type out of bounds in processPacket_changeObjectPlaceRequest.");

                if(Master::getInstance().ObjectType[Master::getInstance().Player[(int)event.peer->data].objectInInventory[destination_place_p1][destination_place_p2].type].baseType != OBJECT_BASE_TYPE_WEAPON)
                    acceptedTo = false;
                else if(Master::getInstance().ObjectType[object->type].attachmentType != weaponAttachmentSlot[destination_place_p3].attachmentType)
                    acceptedTo = false;
                else if(Master::getInstance().ObjectType[object->type].weaponType != Master::getInstance().ObjectType[Master::getInstance().Player[(int)event.peer->data].objectInInventory[destination_place_p1][destination_place_p2].type].weaponType)
                    acceptedTo = false;
            }
        }

        if(acceptedFrom && acceptedTo) {
            if(destination_place == OBJECT_PLACE_GROUND) {
                Master::getInstance().Tile[destination_place_p1][destination_place_p2].object.push_back(*object);
                Master::getInstance().updateTileForPlayers(destination_place_p1, destination_place_p2);
            }
            else if(destination_place == OBJECT_PLACE_INVENTORY) {
                Master::getInstance().Player[(int)event.peer->data].objectInInventory[destination_place_p1][destination_place_p2] = *object;
                std::string packet = Packet <PACKET_OBJECT_CHANGE_IN_INVENTORY>::construct(destination_place_p1, destination_place_p2, *object);
                M.Player[(int)event.peer->data].sendPacket(packet);
            }
            else if(destination_place == OBJECT_PLACE_SLOT) {
                Master::getInstance().Player[(int)event.peer->data].objectOnSlot[destination_place_p1] = *object;

                std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_SLOT>::construct(destination_place_p1, *object);
                M.Player[(int)event.peer->data].sendPacket(packet);

                packet = Packet <PACKET_CHARACTER_SLOT_OBJECT_CHANGE>::construct(CHARACTER_PLAYER, (int)event.peer->data, destination_place_p1, object->type);
                M.sendToAllPlayersInView(packet.c_str(), 1, M.Player[(int)event.peer->data].x, M.Player[(int)event.peer->data].y, (int)event.peer->data);
            }
            else if(destination_place == OBJECT_PLACE_INVENTORY_WEAPON_ATTACHMENT) {
                Master::getInstance().Player[(int)event.peer->data].objectInInventory[destination_place_p1][destination_place_p2].param[OBJECT_PARAM_ADDON_1+destination_place_p3] = object->type;

                std::string packet = Packet <PACKET_OBJECT_CHANGE_IN_INVENTORY>::construct(destination_place_p1, destination_place_p2,
                                                                                           Master::getInstance().Player[(int)event.peer->data].objectInInventory[destination_place_p1][destination_place_p2]);
                M.Player[(int)event.peer->data].sendPacket(packet);
            }
            else if(destination_place == OBJECT_PLACE_SLOT_WEAPON_ATTACHMENT) {
                Master::getInstance().Player[(int)event.peer->data].objectOnSlot[destination_place_p1].param[OBJECT_PARAM_ADDON_1+destination_place_p2] = object->type;

                std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_SLOT>::construct(destination_place_p1,
                                                                                      Master::getInstance().Player[(int)event.peer->data].objectOnSlot[destination_place_p1]);
                M.Player[(int)event.peer->data].sendPacket(packet);
            }

            if(place == OBJECT_PLACE_GROUND) {
                Master::getInstance().Tile[place_p1][place_p2].object.pop_back();
                Master::getInstance().updateTileForPlayers(place_p1, place_p2);
            }
            else if(place == OBJECT_PLACE_INVENTORY) {
                Master::getInstance().Player[(int)event.peer->data].objectInInventory[place_p1][place_p2].type = -1;

                std::string packet = Packet <PACKET_OBJECT_CHANGE_IN_INVENTORY>::construct(place_p1, place_p2, Master::getInstance().Player[(int)event.peer->data].objectInInventory[place_p1][place_p2]);
                M.Player[(int)event.peer->data].sendPacket(packet);
            }
            else if(place == OBJECT_PLACE_SLOT) {
                Master::getInstance().Player[(int)event.peer->data].objectOnSlot[place_p1].type = -1;

                std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_SLOT>::construct(place_p1, Master::getInstance().Player[(int)event.peer->data].objectOnSlot[place_p1]);
                M.Player[(int)event.peer->data].sendPacket(packet);

                packet = Packet <PACKET_CHARACTER_SLOT_OBJECT_CHANGE>::construct(CHARACTER_PLAYER, (int)event.peer->data, place_p1, Master::getInstance().Player[(int)event.peer->data].objectOnSlot[place_p1].type);
                Master::getInstance().sendToAllPlayersInView(packet.c_str(), 1, Master::getInstance().Player[(int)event.peer->data].x, Master::getInstance().Player[(int)event.peer->data].y, (int)event.peer->data);
            }
            else if(place == OBJECT_PLACE_INVENTORY_WEAPON_ATTACHMENT) {
                Master::getInstance().Player[(int)event.peer->data].objectInInventory[place_p1][place_p2].param[OBJECT_PARAM_ADDON_1+place_p3] = -1;

                std::string packet = Packet <PACKET_OBJECT_CHANGE_IN_INVENTORY>::construct(place_p1, place_p2, Master::getInstance().Player[(int)event.peer->data].objectInInventory[place_p1][place_p2]);
                M.Player[(int)event.peer->data].sendPacket(packet);
            }
            else if(place == OBJECT_PLACE_SLOT_WEAPON_ATTACHMENT) {
                Master::getInstance().Player[(int)event.peer->data].objectOnSlot[place_p1].param[OBJECT_PARAM_ADDON_1+place_p2] = -1;

                std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_SLOT>::construct(place_p1, Master::getInstance().Player[(int)event.peer->data].objectOnSlot[place_p1]);
                M.Player[(int)event.peer->data].sendPacket(packet);
            }
        }
    }
}
