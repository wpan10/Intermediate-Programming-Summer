#include "checker.h"
#include "checker_board.h"
#include <iostream>
#include <string>
#include <map>
#include <utility>

using namespace std;

CBoard::CBoard(){
	coord location;
	int k;
	for (int j=0; j < 3; j++){
		for(int i = (j%2); i < 8; i = i+2){
			location = {.x = i,.y = j};
			Checker c(i, j);
			k = 7-j;
			//m1[location] = c; 
			m1.insert(pair<coord,Checker>(location,c)); mgrid[k][i] = 1;
		}
	}
	for (int j = 7; j > 4; j--){
		for(int i = (j%2); i < 8; i = i+2){
			location = {.x = i,.y = j};
			Checker c(i, j);
			k = 7 - j;
			//m2[location] = c; 
			m2.insert(pair<coord,Checker>(location,c)); mgrid[k][i] = 2;

		}
	}
}

void CBoard::print_map(map<coord, Checker>& m){
	//map<coord, Checker>::iterator mite;
	//for(mite = m.begin(); mite != m.end(); mite++){
	//	cout << "Location:" << ((mite->first).x) <<"," << ((mite->first).y) << "Checker: " << ((mite->second).print_checker())<<endl;
	//}
}


void CBoard::print_grid(){
	for (int i =0; i<8;i++){
		for(int j =0; j <8; j++){
			cout<< mgrid[i][j];
		}
		cout<<endl;
	}
}


void CBoard::piece_become_king(Checker& m, int player ){
	if (player == 1){
		coord loc = m.get_location();
		if (loc.y == 7 )
			m.set_king(true);
	}else{
		coord loc = m.get_location();
		if (loc.y == 0)
			m.set_king(true);
	}
}


bool CBoard::check_jump_over_opponent_right_forward(int x, int y, map<coord,Checker>&  m){
	// if jump successful, clear the mgrid[x,y] = 0 and set mgrid[xnew, ynew]
	// the first jump is at x-2,y+2, remove x-1,y+1 
	coord curr = {.x = x+2, .y= y+2};
	if(m.find(curr) == m.end()){
		return true;
	}else{
		return false;
	}
}
 

void CBoard::jump_over_opponent_right_forward(int* x, int* y, map<coord,Checker>&m){
	// if jump successful, clear the mgrid[x,y] = 0 and set mgrid[xnew, ynew]
	// the first jump is at x+2,y+2, remove x+1,y+1 
	coord curr = {.x = ((*x)+2),.y= ((*y)+2)};
	int val = mgrid[7-*y][*x]; mgrid[7-*y][*x] = 0; mgrid[7-(*y+1)][(*x+1)] = 0; mgrid[7-(*y+2)][(*x+2)] = val; // switch the board checker location
	coord curr_m = {.x= ((*x)+1),.y = ((*y)+1)};
	m.erase(m.find(curr_m));
	(*x) =+2; (*y) =+2;
	cout << "Jumped!" << endl;
}


bool CBoard::check_jump_over_opponent_left_forward(int x, int y, map<coord,Checker>& m){
	// if jump successful, clear the mgrid[x,y] = 0 and set mgrid[xnew, ynew]
	// the first jump is at x-2,y+2, remove x-1,y+1 
	coord curr = {.x = x-2, .y= y+2};
	if(m.find(curr) == m.end()){
		return true;
	}else{
		return false;
	}
}

void CBoard::jump_over_opponent_left_forward(int* x, int* y, map<coord,Checker>& m){		
	int val = mgrid[7-(*y)][(*x)]; mgrid[7-(*y)][*x] = 0; mgrid[(7 - (*y +1))][(*x -1)] = 0;mgrid[(7-(*y+2))][(*x-2)] = val; // switch the board checker location
	coord curr_m = {.x= ((*x)-1),.y = ((*y)+1)};
	m.erase(m.find(curr_m));
	*x =-2;
	*y =+2;
	cout << "Jumped!" << endl;
}

bool CBoard::move_right_forward(int x, int y, int player, int turn, map<coord, Checker>&m, map<coord, Checker>& moppo){
	//first check if the position has a checker
	coord loc = {.x = x,.y = y};
	map<coord, Checker>::iterator mite, mite1;
	mite1 = m.find(loc);
	if (mite1 == m.end()){
			// there is no checker at this postion. print out error msg
			cout <<"invalid location for player "<< player << endl;	
			return false;
	}else{
		//find the checker at this postion and now check if this check can move right forward
		//first check the right forward is empty
		if (mgrid[(7-(y+1))][(x+1)] != 0){
			// a check is here ,test if it's player's checker
			coord newloc = {.x = x+1,.y = y+1};
			mite = m.find(newloc);
			if(mite == m.end()){
				// opponent check
				// need to complete later
				bool jump = check_jump_over_opponent_right_forward(x, y, moppo); // first jump is to right
				if (jump){
					jump_over_opponent_right_forward(&x, &y,m);
					bool jump_right = check_jump_over_opponent_right_forward(x,y,moppo);
					bool jump_left = check_jump_over_opponent_left_forward(x,y,moppo); 
					while(jump_right || jump_left){
						string next_jump;
						if (jump_left && jump_right){
							cout << "Player " << player <<"jump" << turn << "(can choose either left right)" <<endl;
							cin >> next_jump;
							if (next_jump[2]!='l'&& next_jump[2]!='r'){
								cout << "invalid input" <<endl;
								continue;
							}else if((next_jump[0] - '0')!= x || (next_jump[1] - '0')!= y){
								cout <<"invalid input" << endl;
								continue;
							}else{
								// correct input
								if (next_jump[2] == 'l'){
									jump_over_opponent_left_forward(&x,&y,moppo);
									cout << "Jumped!" << endl;
								}else{
									jump_over_opponent_right_forward(&x, &y,moppo);
									cout << "Jumped!" << endl;
								}
								jump_right = check_jump_over_opponent_right_forward(x,y,moppo);
								jump_left = check_jump_over_opponent_left_forward(x,y,moppo); 
							}
						}else if(jump_right){
							cout << "Player " << player <<"jump" << turn << "(can only choose to jump right)" <<endl;
							if ((next_jump[0] - '0')!= x ||(next_jump[1] - '0')!= y){
								cout << "invalid input" <<endl;
								continue;
							}else{
								if (next_jump[2] == 'r'){
									jump_over_opponent_right_forward(&x,&y,m);
									cout << "Jumped!" << endl;
									jump_right = check_jump_over_opponent_right_forward(x,y,moppo);
									jump_left = check_jump_over_opponent_left_forward(x,y,moppo); 
								}else{
									cout << "invalid input" << endl;
									continue;
								}
							}
						}else{
							cout << "Player " << player << "jump" << turn <<"(can only choose to jump left)" << endl;
							if ((next_jump[0] - '0')!= x ||(next_jump[1] - '0')!= y){
								cout << "invalid input" <<endl;
								continue;
							}else{
								if (next_jump[2] == 'l'){
									jump_over_opponent_left_forward(&x,&y,moppo);
									cout << "Jumped!" << endl;
									jump_right = check_jump_over_opponent_right_forward(x,y,moppo);
									jump_left = check_jump_over_opponent_left_forward(x,y,moppo); 
								}else{
									cout << "invalid input" << endl;
									continue;
								}
							}
						}	
					}
					coord newloc = {.x =x, .y = y};
					Checker c_tmp = (mite->second);
					c_tmp.set_location(x,y);
					piece_become_king(c_tmp,player);
					m.erase(mite);
					m.insert(pair<coord,Checker>(newloc,c_tmp));
					return true;
				}else{
					// jump over opponent failed 
					cout << "invalid move" <<endl;
					return false;
				}
			}else{
				// my piece can't move
				cout << "invalid move" <<endl;
				return false;
			}
	}else{
			// this spot is empty
		coord newloc = {.x =x+1, .y = y+1};
		Checker c_tmp = (mite1->second);
		c_tmp.set_location(x,y);
		piece_become_king(c_tmp,player);
		m.erase(mite1);
		m.insert(pair<coord,Checker>(newloc,c_tmp));
		int val  = mgrid[7-y][x];
		mgrid[(7-y)][x] = 0; mgrid[(7-(y+1))][x+1] = val;
		return true;
		}	
	}
}



bool CBoard::move_left_forward(int x, int y, int player, int turn, map<coord, Checker>& m,map<coord, Checker>& moppo){
	//first check if the position has a checker
	coord loc = {.x = x,.y = y};
	map<coord, Checker>::iterator mite, mite1;
	mite1 = m.find(loc);
	if (mite1 == m.end()){
			// there is no checker at this postion. print out error msg
			cout <<"invalid location for player  "<< player << endl;	
			return false;
	}else{
		//find the checker at this postion and now check if this check can move right forward
		//first check the right forward is empty
		if (mgrid[7 -(y+1)][x-1]!= 0){
			// a check is here ,test if it's player's checker
			coord newloc = {.x = x-1,.y = y+1};
			mite = m.find(newloc);
			if(mite == m.end()){
				// opponent check
				bool jump = check_jump_over_opponent_left_forward(x, y, moppo); // first jump is to right
				if (jump){
					jump_over_opponent_right_forward(&x, &y,m);
					bool jump_right = check_jump_over_opponent_right_forward(x,y,moppo);
					bool jump_left = check_jump_over_opponent_left_forward(x,y,moppo); 
					while(jump_right || jump_left){
						string next_jump;
						if (jump_left && jump_right){
							cout << "Player " << player <<"jump" << turn << "(can choose either left right)" <<endl;
							cin >> next_jump;
							if (next_jump[2]!='l'&& next_jump[2]!='r'){
								cout << "invalid input" <<endl;
								continue;
							}else if((next_jump[0] - '0')!= x || (next_jump[1] - '0')!= y){
								cout <<"invalid input" << endl;
								continue;
							}else{
								// correct input
								if (next_jump[2] == 'l'){
									jump_over_opponent_left_forward(&x,&y,moppo);
									cout << "Jumped!" << endl;
								}else{
									jump_over_opponent_right_forward(&x, &y,moppo);
									cout << "Jumped!" << endl;
								}
								jump_right = check_jump_over_opponent_right_forward(x,y,moppo);
								jump_left = check_jump_over_opponent_left_forward(x,y,moppo); 
							}
						}else if(jump_right){
							cout << "Player " << player <<"jump" << turn << "(can only choose to jump right)" <<endl;
							if ((next_jump[0] - '0')!= x ||(next_jump[1] - '0')!= y){
								cout << "invalid input" <<endl;
								continue;
							}else{
								if (next_jump[2] == 'r'){
									jump_over_opponent_right_forward(&x,&y,m);
									cout << "Jumped!" << endl;
									jump_right = check_jump_over_opponent_right_forward(x,y,moppo);
									jump_left = check_jump_over_opponent_left_forward(x,y,moppo); 
								}else{
									cout << "invalid input" << endl;
									continue;
								}
							}
						}else{
							cout << "Player " << player << "jump" << turn <<"(can only choose to jump left)" << endl;
							if ((next_jump[0] - '0')!= x ||(next_jump[1] - '0')!= y){
								cout << "invalid input" <<endl;
								continue;
							}else{
								if (next_jump[2] == 'l'){
									jump_over_opponent_left_forward(&x,&y,moppo);
									cout << "Jumped!" << endl;
									jump_right = check_jump_over_opponent_right_forward(x,y,moppo);
									jump_left = check_jump_over_opponent_left_forward(x,y,moppo); 
								}else{
									cout << "invalid input" << endl;
									continue;
								}
							}
						}	
					}
					coord newloc = {.x =x, .y = y};
					Checker c_tmp = (mite->second);
					c_tmp.set_location(x,y);
					piece_become_king(c_tmp,player);
					m.erase(mite1);
					m.insert(pair<coord,Checker>(newloc,c_tmp));
					return true;
				}else{
					// jump over opponent failed 
					cout << "invalid move" <<endl;
					return false;
				}
			}else{
				// my piece can't move
				cout << "invalid move" <<endl;
				return false;
			}
	}else{
			// this spot is empty
		coord newloc = {.x = x-1, .y = y+1};
		Checker c_tmp = (mite1->second);
		c_tmp.set_location(x-1,y+1);
		piece_become_king(c_tmp,player);
		m.erase(mite1);
		m.insert(pair<coord,Checker>(newloc,c_tmp));
		int val  = mgrid[(7-y)][x];
		mgrid[(7-y)][x] = 0; mgrid[(7-(y+1))][(x-1)] = val;
		return true;
		}	
	}
}

bool CBoard::move_right_backward(int x, int y, int player, int turn, map<coord, Checker>& m){
	coord loc = {.x = x,.y = y};
	map<coord, Checker>::iterator mite1;
	mite1 = m.find(loc);
	if (mite1 == m.end()){
		cout << "invalid location of piece for player" << player << endl;
		return false;
	}else{
		// check if the target spot is empty
		if (mgrid[7-(y-1)][x+1] == 0){
			if ((mite1->second).is_king()){
				coord newloc = {.x =x+1, .y = y-1};
				Checker c_tmp = (mite1->second);
				c_tmp.set_location(x+1,y-1);
				piece_become_king(c_tmp,player);
				m.erase(mite1);
				m.insert(pair<coord,Checker>(newloc,c_tmp));
				int val = mgrid[(7-y)][x];
				mgrid[(7-y)][x] = 0;mgrid[(7-(y-1))][(x+1)] = val;
				return true;
			}else{
				cout <<"Not A King, Invalid move on this piece" << endl;
				return false;
			}
		}else{
			cout << "jump failed, invalid move" << endl;
			return false;
		}
	}
}

bool CBoard::move_left_backward(int x, int y, int player, int turn, map<coord, Checker>& m){
	coord loc = {.x = x,.y = y};
	map<coord, Checker>::iterator mite1;
	mite1 = m.find(loc);
	if (mite1 == m.end()){
		cout << "invalid location of piece for player" << player << endl;
		return false;
	}else{
		// check if the target spot is empty
		if (mgrid[(7-(y-1))][(x-1)] == 0){
			if ((mite1->second).is_king()){
				coord newloc = {.x =x-1, .y = y-1};
				Checker c_tmp = (mite1->second);
				c_tmp.set_location(x-1,y-1);
				piece_become_king(c_tmp,player);
				m.erase(mite1);
				m.insert(pair<coord,Checker>(newloc,c_tmp));
				int val = mgrid[(7-y)][x];
				mgrid[(7-y)][x] = 0;mgrid[(7-(y-1))][(x-1)] = val;
				return true;
			}else{
				cout <<"Not A King, Invalid move on this piece" << endl;
				return false;
			}
		}else{
			cout << "jump failed, invalid move" << endl;
			return false;
		}
	}
}

