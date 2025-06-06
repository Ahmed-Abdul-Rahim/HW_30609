#include "../Headers/Room.h"

Room::Room(const string& desc, const string& snd, const string& sml)
    : description(desc), sound(snd), smell(sml),
      enemy(nullptr), north(nullptr), south(nullptr),
      east(nullptr), west(nullptr),
      fireTrap(false), waterChallenge(false), vineTrap(false),
      item("") {}
