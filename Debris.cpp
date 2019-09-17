#include "Debris.h"
#include "GlobalAndConstants.h"
#include <algorithm>
#include <vector>
#include <random>
#include <time.h>

int Debris:: Dno = 0;

Debris::Debris(int x, int y, int health, int attack, int score, char shape, float speed)
	: Entity(x, y, attack, shape), health(health), score(score), speed(speed) {}

int Debris::getScore()
{
	return score;
}
int Debris::getHealth() { return health; }

void Debris::
setHealth(int health) { this->health = health; }

bool Debris::move()
{
	add += speed;
	if ((Game::Field[getX() + 1][getY()] == Game::FREE) && (add == floor(add)))
	{
		std::swap(Game::Field[getX() + 1][getY()], Game::Field[getX()][getY()]);
		setX(getX() + 1);
	}
	else if (Game::Field[getX() + 1][getY()] == Ship::shape) {
		Ship::health -= getAttack();
		Game::Field[getX()][getY()] = Game::FREE;
		return false;
	}
	else if (Game::Field[getX() + 1][getY()] == '_') { 
		Game::Field[getX()][getY()] = Game::FREE; 
		return false;
	}

}

#define TD Game::typedeb[td]
void Debris::newDeb()
{
	std::default_random_engine random(time(0));
	std::uniform_int_distribution<int> pos(1, Game::Field[0].size() - 1);
	decltype(pos) type(0, Game::typedeb.size() - 1);
	int _y;
	do
		_y = pos(random);
	while (Game::Field[1][_y] != Game::FREE);
	auto td = type(random);
	Game::deb.emplace_back(1, _y, TD.attack, TD.health, TD.score, TD.shape, TD.speed);
	Dno++;
	if(Dno % 10 == 0)
	{
		do
			_y = pos(random);
		while (Game::Field[1][_y] != Game::FREE);
		auto td = type(random);

		Game::deb.emplace_back(1, _y, TD.attack, TD.health, TD.score, TD.shape, TD.speed);
		Dno++;
	}
}

int Debris::getDno()
{
	return Dno;
}
