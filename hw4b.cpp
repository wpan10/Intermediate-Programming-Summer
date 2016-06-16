#include <cstdio>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <iostream>
#include <string>
#include "hw4.h"

using namespace std;

int main(int argc, char* argv[]){
	//int num_samples = (int) argv[1];
	string file_name = argv[2];
	Bigram b(file_name);
	b.build_model_map();
	//b.print();
	int num_samples = stoi(argv[1]);
	cout << "samples: " <<num_samples <<endl;
	while (num_samples >0){
		b.sample();
		num_samples--;
	}
}
