#pragma once

class Debris	// the debris class
{
	int x, y;
	int attack, health;
	char shape;
	float add = 0.0f;

public:

	bool move();

	Debris(int, int, int, int, char);

	int getX() { return x; }
	int getY() { return y; }

	int getHealth() { return health; }
	void setHealth(int health) { this->health = health; }
	
	~Debris();
};

