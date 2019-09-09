#include "Fire.h"
#include "GlobalAndConstants.h"
#include <time.h>
#include <random>

Fire::Fire() :x(Ship::x), y(Ship::y), attack(50) {
	Game::Field[x][y] = shape;
}

bool Fire::move()
{
	if (!x) {
		Game::Field[x][y] = Game::FREE;
		return false;
	}
	
	if (Game::Field[x - 1][y] == Game::FREE)
		std::swap(Game::Field[x][y], Game::Field[x - 1][y]), x--;
	else
		for (std::vector<Debris>::iterator debris = begin(Game::deb); debris != end(Game::deb); debris++)
			if (x - 1 == debris->getX() && y == debris->getY()) 
			{
				debris->setHealth(debris->getHealth() - attack);

				if (debris->getHealth() <= 0) {
					std::default_random_engine random(time(0));
					std::uniform_int_distribution<int>pos(2, Game::Field[0].size() - 1);
					Game::Field[x - 1][y] = Game::FREE;
					Game::deb.erase(debris);
					Game::deb.emplace_back(1, pos(random), 100, 150, 'o');
				}
				Game::Field[x][y] = Game::FREE;
				return false;
			}
	return true;
}

Fire::~Fire()
{
}
