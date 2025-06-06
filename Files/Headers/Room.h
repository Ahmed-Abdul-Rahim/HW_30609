#ifndef ROOM_H
#define ROOM_H

#include "Enemy.h"
#include <memory>
#include <string>
using namespace std;

class Enemy;

class Room {
public:
    string description, sound, smell;
    shared_ptr<Enemy> enemy;
    shared_ptr<Room> north;
    shared_ptr<Room> south;
    shared_ptr<Room> east;
    shared_ptr<Room> west;
    bool fireTrap, waterChallenge, vineTrap;
    string item;

    Room(const string& desc, const string& snd, const string& sml);
};

#endif
