#include <fstream>
#include <iostream>
#include <vector>
#include "GlobalAndConstants.h"
#include <string>
#include "Debris.h" 
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <random>


void setUp();

void display();

void run();
bool move(char);

int main()
{
	setUp();
	run();
}

void run()
{
	std::default_random_engine random(time(0));
	std::uniform_int_distribution<int> pos(2, Game::Field[0].size() - 1);

	Game::deb.emplace_back(1, pos(random), 100, 150, 'o');
	Game::deb.emplace_back(1, pos(random), 100, 150, 'o');
	Game::deb.emplace_back(1, pos(random), 100, 150, 'o');


	//Debris deb(5, 5, 10, 5, 'o');
	char input = 'p';

	while (true) {
		Game::Field[Ship::x][Ship::y] = Ship::shape;
		display();
		Sleep(300);
		if (_kbhit())
			input = tolower(_getch());
		if (input == ' ')
			Game::fire.emplace_back(), input = 'p';
		for (int i = 0; i < Game::fire.size(); i++)
			if (!Game::fire[i].move())
				Game::fire.erase(begin(Game::fire) + i), i--;

		/*for (auto f = begin(Game::fire); f != end(Game::fire); f++)
			if (!f->move())
				Game::fire.erase(f);*/

		for (int i=0;i<Game::deb.size();i++)
			if (!Game::deb[i].move())
				Game::deb.erase(begin(Game::deb)+i), i--;

		move(input);
		
		system("CLS");
	}
}

void setUp()
{
	std::ifstream fin("PlaySpace.txt");
	std::string temp;
	while (std::getline(fin, temp)) 
		Game::Field.push_back(temp);
}

void display()
{
	for (std::string str : Game::Field)
		std::cout << str << '\n';
}

#define Pos(a) Game::Field[Ship::x][Ship::y + a]

bool move(char dir) {
	if (dir == 'd' && Pos(1) == Game::FREE) {
		std::swap(Pos(0), Pos(1)), Ship::y++;
		return true;
	}
	else if (dir == 'a' && Pos(-1) == Game::FREE) {
		std::swap(Pos(0), Pos(-1)), Ship::y--;
		return true;
	}
	else if (dir == Game::FREE)
		return true;
	return false;
}