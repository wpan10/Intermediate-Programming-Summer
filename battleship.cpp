#include <iostream>
#include "ship.h"
#include "ship_board.h"
#include <string>
using namespace std;

struct player{
	Ship ac; Ship bs; Ship cru; Ship sub; Ship des;
	SBoard board1;
	OBoard board2;
};

void set_placement(Ship &ship, SBoard &board, string prompt){
	while (true){ 
		cout << prompt << endl;
		string input; 
		cin >> input;
		if (input.size()!= 3){
			if (input[0] == 'q')
				break;
			cout << "invalid input" << endl;
			continue;
		}else{
			if (input[2]!= 'v' && input[2]!= 'h'){
				cout <<input[2] << endl;
				cout << "invalid input of direction " <<endl;
				continue;
			}
		}
		loc location = {.x = int(input[0] - '0'),.y = int(input[1] - '0'),.dir = input[2]};
		ship.set_location(location);
		//ship.print_info();
		if (!board.valid_place(ship)){
			cout << "accross the board, invalid placement" << endl;
		}else{
			board.place_ship(ship);break;
		}
	}
}

void placement(player &p,int player_num){
	string s;
	if (player_num == 1){
		s = "player1";
	}
	else{
		s = "player 2";
	}
	string prompt =  s + " place aircraft carrier(5)";
	set_placement(p.ac,p.board1,prompt);
	//p.board1.print();
	prompt = s + " place battle ship(4)";
	set_placement(p.bs,p.board1,prompt);
	//p.board1.print();
	prompt = s + " place crusier(3)";
	set_placement(p.cru,p.board1,prompt);
	//p.board1.print();
	prompt = s + " place submarine (3)";
	set_placement(p.sub,p.board1,prompt);
	//p.board1.print();
	prompt = s + " place destroyer (2)";
	set_placement(p.des,p.board1,prompt);
	p.board1.print();
}


void battleGame(player p1, player p2){
	cout << "Begin Game!" << endl;
	int turn = 1;
	int x, y;
	string move1,move2;
	while(true){
		/********************** start ******************/
		cout << "Player 1" << " turn " << turn << endl;
		cin >> move1;
		if (move1[0] =='q')
			break;
		if (move1.size() != 2){
			cout << "invalid input" <<endl;
			continue;
		}else if((!isdigit(move1[0])) ||(!isdigit(move1[1]))){
			cout << "invalid input" <<endl;
			continue;
		}else{ 
			x = move1[0] - '0';y = move1[1] - '0';
			bool hit = p1.board1.hit(x,y,"Player 1");
			if (hit){
				p1.board2.set_hit(x,y);
			}else{
				p1.board2.set_miss(x,y);
			}
			if (p1.board1.check_lose()){
				// if all ships sunk
				break;
			}
		}
		/********************************************/
		cout << "Player 2" << " turn " << turn << endl;
		cin >> move2;
		if (move2[0] == 'q')
			break;
		if (move2.size() != 2){
			cout << "invalid input" <<endl;
			continue;
		}else if((!isdigit(move2[0])) ||(!isdigit(move2[1]))){
			cout << "invalid input" <<endl;
			continue;
		}else{ 
			x = move2[0] - '0';y = move2[1] - '0';
			bool hit = p2.board1.hit(x,y,"Player 1");
			if (hit){
				p2.board2.set_hit(x,y);
			}else{
				p2.board2.set_miss(x,y);
			}
			if (p2.board1.check_lose()){
				break;
			}
		}
		turn ++;
	}
}


int main(){

	Ship ac(5,"aircraft carrier");
	Ship bs(4,"battle ship");
	Ship cru(3, "cruiser");
	Ship sub(3, "submarine");
	Ship des(2, "destroyer");
	SBoard board1; 
	OBoard board2;
	player p1 = {.ac = ac, .bs = bs,.cru = cru, .sub = sub,.des = des, .board1 = board1};
	player p2 = {.ac = ac, .bs = bs,.cru = cru, .sub = sub,.des = des, .board2 = board2};
	// set placement:
	cout << "BattleShip!" << endl;
	placement(p1,1);
	placement(p2,2);
	battleGame(p1,p2);

}