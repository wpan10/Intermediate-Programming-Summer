#include "checker.h"
#include <iostream>
using namespace std;

Checker::Checker(int x ,int y){
	curr_location.x = x;
	curr_location.y = y;
	isKing = false;
}


coord Checker::move_right_forward(){
	coord new_location = {.x = curr_location.x+1, .y = curr_location.y + 1};
	return new_location;
}

coord Checker::move_left_forward(){
	coord new_location = {.x = curr_location.x -1, .y = curr_location.y + 1};
	return new_location;
}

coord Checker::move_left_backword(){
	coord new_location = {.x = curr_location.x -1, .y = curr_location.y - 1};
	return new_location;
}
	
coord Checker::move_right_backword(){
	coord new_location = {.x = curr_location.x + 1, .y = curr_location.y - 1};
	return new_location;
}

void Checker::set_location(int x , int y){
	curr_location.x = x;
	curr_location.y = y;
}

void Checker::set_king(const bool king){
	isKing = king;
}

bool Checker::is_king(){
	return isKing;
}

coord Checker::get_location(){
	return curr_location;
}

void Checker::print_checker(){
	cout << curr_location.x << "," << curr_location.y << endl;
}




