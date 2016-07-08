#ifndef SHIP_BOARD
#define SHIP_BOARD
#include <iostream>
#include <vector>
#include "ship.h"

class Board{	
public:
	void print_grid();

private:
	int mgrid[8][8] = {0};
};

class SBoard: public Board{

public:
	bool place_ship(Ship &s);
	bool hit(int x, int y,const string s1); // hit the board at location (x,y)
	bool valid_place(Ship &s); //check if this placement is valid for this ship
	bool check_lose();
	void print();

private:
	//int mgrid[8][8] = {0};
	vector<Ship> ship_list;
	int remaining_ships;	
	int check_num_ships();
};

class OBoard: public Board{
public:
	void set_hit(int x ,int y);
	void set_miss(int x , int y);
	void print();
private:
	char mgrid[8][8] = {'0'};
};
#endif