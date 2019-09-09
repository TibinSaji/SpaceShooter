#pragma once
class Fire
{
	int x, y, attack;
	char shape = '.';
public:
	Fire();
	bool move();

	int getX() { return x; }
	int getY() { return y; }

	~Fire();
};