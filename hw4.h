#ifndef HW4_H
#define HW4_H
#include <cstdio>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
using namespace std;

class Bigram{

private: 
	vector<string> v;
	map<string, vector<string>> m;
	int compare(pair<string,int> p1, pair<string,int> p2);
	void split(string str, char delimiter);
	void read_file(string file_name);
	string mfile_name;
	string mystr;
	string output;

public:
	void build_model_map();
	Bigram(string file_name);
	void print();
	void sample();

};

#endif