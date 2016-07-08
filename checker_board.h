#ifndef CHECKER_BOARD_H
#define CHECKER_BOARD_H
#include <iostream>
#include <map>
#include <utility>
#include "checker.h"

using namespace std;

class CBoard{

public:
	CBoard();
	void print_grid(); //print out the grid

	bool check_jump_over_opponent_right_forward(int x, int y, map<coord,Checker>&m);
	bool check_jump_over_opponent_left_forward(int x, int y, map<coord,Checker>&m);
	void jump_over_opponent_right_forward(int* x, int* y, map<coord,Checker>& m);
	void jump_over_opponent_left_forward(int* x, int* y, map<coord,Checker>&m);

	bool move_right_forward(int x, int y, int player, int turn, map<coord, Checker>& m, map<coord, Checker>& moppo);
	bool move_left_forward(int x, int y, int player, int turn, map<coord, Checker>& m,map<coord, Checker>& moppo);
	bool move_right_backward(int x, int y, int player, int turn, map<coord, Checker>& m);
	bool move_left_backward(int x, int y, int player, int turn, map<coord, Checker>& m);
	void print_map(map<coord, Checker>& m);
	void piece_become_king(Checker& m, int player );


private:
	int mgrid[8][8] = {0};
	
	map<coord, Checker> m1;
	map<coord, Checker> m2;

};
#endif