#pragma once
#include <vector>
#include <string>
#include "Debris.h"
#include "Fire.h"

namespace Game
{
	extern std::vector <std::string> Field;
	const char FREE = ' ';
	extern std::vector <Debris> deb;
	extern std::vector <Fire> fire;
};

namespace Ship
{
	extern int x, y;
	const char shape = '^';
	extern int health;
}