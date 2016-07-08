#include <iostream>
#include "ship_board.h"
#include "ship.h"
using namespace std;

void Board::print_grid(){
	for (int i =0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			cout << mgrid[i][j] << " ";
		}
		cout << endl;
	}
}


bool SBoard::valid_place(Ship &s){
	/*
		This method will check if the placement of this ship is valid,
		will fisrt check if the place location is valid 
		then will check if the location is unoccupied by other ship
	*/
	loc location = s.get_location();
	if (location.dir == 'h'){
		//check 8 >= y >= 1 and xstart <= 8 -size

		if ( location.y <0 || location.y >=8 || (location.x > 7 - s.get_size()) || location.x < 0){
			return false;
		}else{
			//check if the spot has already been taken
			int cppy;
			cppy = 7 - location.y;
			for (int i = location.x; i < location.x + s.get_size(); i++){
				if (mgrid[cppy][i] == 1)
					return false;
			}
		}
		return true;
	}else{
		// check  0<= x < 8
		if (location.x >= 8 ||location.x < 0 || (location.y < s.get_size()) || location.y >= 8){
			return false;
		}else{
			// check if the spot has been taken 
			int cppy;
			cppy = 7 - location.y;
			for(int j = cppy; j < cppy + s.get_size(); j++){
				//cout << mgrid[j][location.x]<<endl;
				if (mgrid[j][location.x] == 1)
					return false;
			}
		}
		return true;
	}
}


bool SBoard::place_ship(Ship &s){
	/*
		This method will place ship on the board,
		update the board and ship list if placement is successful
	*/
	bool success = valid_place(s);
	if (success){
		ship_list.push_back(s);
		loc location = s.get_location(); // update grid
		int size = s.get_size();
		if (location.dir == 'h'){
			int cppy = 7 - location.y;
			for (int i = location.x; i < location.x + size ; i++){
				mgrid[cppy][i] = 1;
			}
		}else{
			int cppy;
			cppy = 7 - location.y;
			for (int j = cppy; j < cppy + size ; j++){
				mgrid[j][location.x] = 1;
			}
		}
	}else{
		cout<<"invalid location of ships" << endl;
	}
	return success;
}


bool SBoard::hit(int x , int y, const string s1){
	vector<Ship>::iterator s_ite;
	s_ite = ship_list.begin();
	for(;s_ite != ship_list.end(); s_ite++){
		if (s_ite->check_hit(x,y)){
			// hit the ship, check if sink the ship
			cout << "Hit!" << endl;
			if(s_ite->sink()){
				//cout <<"sink the ship:" << s_ite -> get_name() << endl;
				string sink_info = s_ite ->get_name() +  " sunk by " + s1;
				cout << sink_info << endl ;;
				ship_list.erase(s_ite);//delete from the list
			}
			return true;
		}
	}
	cout << "Miss!" << endl;
	return false;
}


int SBoard::check_num_ships(){
	return ship_list.size();
}


bool SBoard::check_lose(){
	if (ship_list.size() == 0){
		return true;
	}else{
		return false;
	}
}

void SBoard :: print(){
	for (int i =0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			cout << mgrid[i][j] << " ";
		}
		cout << endl;
	}
}


void OBoard ::set_hit(int x, int y){
	mgrid[x][y] = 'o';
}


void OBoard:: set_miss(int x ,int y){
	mgrid[x][y] = 'x';
}

void OBoard :: print(){
	for (int i =0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			cout << mgrid[i][j] << " ";
		}
		cout << endl;
	}
}
