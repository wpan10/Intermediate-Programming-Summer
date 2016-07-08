#include <iostream>
#include <string>
#include "ship.h"
using namespace std;

Ship::Ship (int size, string ship_type){
	msize = size;
	mship_type = ship_type;
	mship = new int[msize]();
}

void Ship::set_location(loc &start){
	mstart = start;
}

loc Ship::get_location(){
	return mstart; 
}

bool Ship::check_hit(int x, int y){
	if (mstart.dir == 'v'){
		//if the ship is placed vertically, we check x first
		if (x != mstart.x){
			return false;
		}else{
			for (int j = mstart.y;j>mstart.y - msize; j--){
				if (j == y){
					mship[mstart.y-j] = 1; //to show this part is hitted
					return true;
				}
			}
			return false;
		}
	}else{
		// if the ship is placed horizontally, we check y first
		if (y!= mstart.y){
			return false;
		}else{
			for (int i = mstart.x; i <mstart.x + msize; i++){
				if (i == x){
					mship[i - mstart.x] = 1;
					return true;
				}
			}
			return false;
		}
	}
}

bool Ship::sink(){
	for (int i =0; i < msize; i++){
		if (mship[i] == 0) return false; //still not fully attacked
	}
	return true;
}

int Ship :: get_size(){
	return msize;
}

string Ship:: get_name(){
	return mship_type;
}

void Ship::print_info(){
	cout << "location:" <<mstart.x << ","<<mstart.y << " size: "<< msize << " ship_type: "<< mship_type << endl;
}

