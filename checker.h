#ifndef CHECKER_H
#define CHECKER_H


struct coord{
	int x;
	int y;
	bool operator <(const coord& c1) const{
		if (x != c1.x){
			return x < c1.x; 
		}else{
			return y < c1.y;
		}
	}
};

class Checker{

public:
	Checker(int x, int y);
	coord move_right_forward();
	coord move_left_forward();
	coord move_left_backword();
	coord move_right_backword();
	void set_location(int x , int y);
	void set_king(const bool king);
	bool is_king();
	coord get_location();
	void print_checker();
private:
	coord curr_location = {.x = 0,.y = 0};
	bool isKing;
};

#endif