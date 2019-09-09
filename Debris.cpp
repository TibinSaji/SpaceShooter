#include "Debris.h"
#include "GlobalAndConstants.h"
#include <algorithm>
#include <vector>

Debris::Debris(int x, int y, int health, int attack, char shape)
	:x(x), y(y), health(health), shape(shape), attack(attack) {
	Game::Field[x][y] = shape;
}

bool Debris::move()
{
	add += 0.25;
	if (Game::Field[x + 1][y] == Game::FREE && add==floor(add)) { // Swap using inbuilt function \
			 To move the debris to the next pos
		std::swap(Game::Field[x + 1][y], Game::Field[x][y]);
		x++;
	}
	else if (Game::Field[x + 1][y] == '_' || Game::Field[x + 1][y] == Ship::shape)
	{
		Game::Field[x][y] = Game::FREE;
		Ship::health -= attack;
		return false;
	}
	else
		for (auto f = begin(Game::fire); f != end(Game::fire); f++)
			if (x == f->getX() && y == f->getY())
	return true;
}

Debris::~Debris()
{
}
