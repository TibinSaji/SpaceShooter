#pragma once
#include "Entity.h"

class Debris : public Entity	// the debris class
{
	//int x, y;
	int health, score;
	//char shape;
	float add = 0.0f;
	float speed;
	static int Dno;

public:

	bool move();
	Debris(int, int, int, int, int, char, float);
	int getScore();
	int getHealth();
	void setHealth(int);
	static void newDeb();
	static int getDno();
};

