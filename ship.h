#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>
using namespace std;

struct loc{
	int x;
	int y;
	char dir;
};


class Ship{

public: 
	Ship(int size, string ship_type);
	void set_location(loc &start);
	loc get_location(); //print out location info
	bool sink();
	bool check_hit(int x, int y);
	void print_info();
	int get_size();
	string get_name();

private:
	int msize; 
	string mship_type;
	int *mship;
	loc mstart = {.x = 0,. y = 0, .dir = 'h'}; 
};

#endif