#include "hw4.h"
#include <cstdio>
#include <map>
#include <vector>
#include <utility>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>


using namespace std;

void Bigram::read_file(string file_name){
	/*
		reading strings from a file line by line.
	*/
	ifstream f;
	f.open(file_name);
	string str;
	do{
		getline(f,str);
		//cout <<"string: "<< str;
		mystr += str;	
	}while(getline(f,str));
	f.close();
}

Bigram::Bigram(string file_name){
	/*
		initialize mystr by reading from a file
	*/
	mfile_name = file_name;
	read_file(mfile_name);
}


void Bigram::split(string str, char delimiter){
	/*
		split a string into a vector of string 	
	*/
	stringstream ss(str);
	string tok;

	v.push_back("<START>");
	while(getline(ss,tok,delimiter)){
		v.push_back(tok);
	}
	v.push_back("<END>");
}

int Bigram::compare(pair<string,int> p1, pair<string,int> p2){
	/*
		helper function to compare a pair by its count(int value)
	*/
	return (p1.second > p2.second);
}


void Bigram::build_model_map(){
	vector<string>::iterator itr;
	string key; 
	int val;
	map<string,vector<string>>::iterator mitr;
	split(mystr,' ');
	for (itr = v.begin(); itr!= v.end()-1; itr++){
		key = *itr;
		string next_key = *(next(itr));
		if (m.empty()){
			vector<string> v(1,next_key);
			m.insert(pair<string,vector<string>>(key,v));
			continue;
		}
		mitr = m.find(key);
		if (mitr!= m.end()){
			(mitr->second).push_back(next_key);
		}else{		
			//	we insert our new vector<string>
			vector<string> v_(1,next_key);
			m.insert(pair<string,vector<string>>(key,v_));
		}	
	}
}


void Bigram::print(){
	map<string,vector<string>>::iterator mitr;
	for (mitr = m.begin();mitr!= m.end(); mitr++){
		vector<string>::iterator vitr;
		vector<string> v_tmp = mitr->second;
		cout << mitr->first<<" => ";
		for (vitr = v_tmp.begin(); vitr != v_tmp.end(); vitr++){
			cout << (*vitr)<< " ";
		}
		cout<<endl;
	}
}


void Bigram:: sample(){
	//find start
	string key = "<START>";
	map<string,vector<string>>::iterator mitr;
	mitr = m.find(key);
	output = "";
	output += key;
	while(key!= "<END>" ){
		if(mitr == m.end()){
			cout <<"Sth wrong!"<<endl;
			break;
		}
		int count = (mitr->second).size();
		key = (mitr->second)[rand()%count];
		mitr = m.find(key);
		output += " "+ key;
	}
	cout <<output<<endl;
}


