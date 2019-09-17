#include <fstream>
#include <iostream>
#include <vector>
#include "GlobalAndConstants.h"
#include <string>
#include "Debris.h" 
#include <Windows.h>
#include <conio.h>
#include "Login.h"

void hideCursor();

void menu();

bool login();

void setUp();

void display();

void run();

bool move(char);

int main()
{
	menu();
	setUp();
	run();
}

void run()
{	
	for (int i = 0; i < 3; i++)
		Debris::newDeb();

	char input = 'x';
	while (Ship::health > 0) {
		Game::Field[Ship::x][Ship::y] = Ship::shape;
		display();
		Sleep(100);
		if (_kbhit())
			input = tolower(_getch());
		if (input == ' ')
			Game::fire.emplace_back(), input = 'x';
		if (input == 'p')
			_getch(), input = 'x';
		if (input == 'e')
			return;
		for (int i = 0; i < Game::fire.size(); i++)
			if (!Game::fire[i].move()) 
			{
				Game::Field[Game::fire[i].getX()][Game::fire[i].getY()] = Game::FREE;
				Game::fire.erase(begin(Game::fire) + i);
				i--;
			}

		for (int i=0;i<Game::deb.size();i++)

			if (!Game::deb[i].move())
			{
				Game::deb.erase(begin(Game::deb) + i), i--;
				Debris::newDeb();
			}

		move(input);
		
		system("CLS");
	}
	std::cout << "\n\n\n\t\t\tGAME OVER\n\t\t\tSCORE: " << Ship::score<<std::endl;
	Login l;
	std::string uname = " ";
	std::fstream f("login.dat", std::ios::binary | std::ios::beg);
	while (f.read((char*)& l, sizeof(l)))
	{
		if (uname == l.getUN())
		{
			l.setHscore();
			f.seekp(-int(sizeof(l)), std::ios_base::cur);
			f.write((char*)& l, sizeof(l));
		}
	}
}

void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void menu()
{
	std::cout << "\t\tWELCOME TO SPACE SHOOTER \n\n\n\nDEBRIS\t\tATTACK\t\tHEALTH\t\tSCORE\n";
	std::cout << "  |\t\t  50\t\t  50\t\t  5\n";
	std::cout << "  v\t\t  100\t\t  100\t\t  15\n";
	std::cout << "  o\t\t  100\t\t  150\t\t  10\n";
	std::cout << "  8\t\t  200\t\t  500\t\t  50\n\n";
	std::cout << "\n\n\tHow To Play: A(LEFT)\t  D(RIGHT)\tSPACE BAR(SHOOT)\n\npress any key to start game";
	_getch();
}

bool login()
{
	system("CLS");
	std::cout << "LOGIN with\n\t1.Existing account\n\t2.New account\n\t3.Guest account\n";
	int n;
	std::cout << "Enter choice ";
	std::cin >> n;
	system("CLS");
	std::string uname, pword;
	std::cout << "USERNAME: ";
	std::cin >> uname;
	std::cout << "PASSWORD: ";
	std::cin >> pword;
	Login l;
	std::fstream f("play.dat");
	switch (n) {
	case 1:
		while (!f.eof()) {
			
			if (l.getUN() == uname && l.getPW() == pword)
			{
				std::cout<<"WELCOME BACK";
				std::cout << "HIGHSCORE: " << l.getHscore();
				return true;
			}
			else if (l.getUN() == uname && l.getPW() != pword)
			{
				std::cout << "ERROR";
				return false;
			}
		}
		return false;
	case 2:
		l.setUN(uname);
		l.setPW(pword);
		f.write((char*)& l, sizeof(l));
		return true;
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
		std::cout << '\t' << str << '\n';
	std::cout << "\n\tSCORE: " << Ship::score << "\t\tHEALTH: " << Ship::health << "\t\tLEVEL: " << floor (Debris::getDno() / 10) + 1;
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
