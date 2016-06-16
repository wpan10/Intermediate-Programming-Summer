#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <utility>

using namespace std;


vector<string> split(string str, char delimiter){

	stringstream ss(str);
	vector<string> v;
	string tok;

	v.push_back("<START>");
	while(getline(ss,tok,delimiter)){
		v.push_back(tok);
	}
	v.push_back("<End>");
	return v;
}


map<string,int> build_model_map(vector<string> v){
	vector<string>::iterator itr;
	string key;int val;
	map<string,int> m;
	map<string,int>::iterator mit;
	for(itr = v.begin(); itr!= v.end()-1; itr++){
		key = *itr + " " + *(itr+1);
		if (m.find(key)!=m.end()){
			mit = m.find(key);
			mit->second++;
		}else{
			val = 1;
			m.insert(pair<string,int>(key,val));
		}
	}
	return m;
}

string read_file(string file_name){
	ifstream f;
	f.open(file_name);
	string str;
	string mystr;
	do{
		getline(f,str);
		//cout <<"string: "<< str;
		mystr += str;	
	}while(getline(f,str));
	f.close();
	return mystr;
}

int compare(pair<string,int> p1, pair<string,int> p2){
	return (p1.second > p2.second);
}

void print(map<string,int> m, string order){
	switch(order[0]){
		case 'a':
		{
			map<string,int>::iterator mit;
			for (mit = m.begin(); mit!= m.end(); mit++){
				cout << mit->first << " " << mit->second << endl;
			}
			break;
		}
		case 'r':
		{
			map<string,int>::reverse_iterator rmit;
			for (rmit = m.rbegin(); rmit!= m.rend(); rmit++){
				cout << rmit->first << " " << rmit->second << endl;
			}
			break;
		}
		case 'c':
		{
			map<string,int>::iterator mit;
			vector<pair<string,int>> v;
			for(mit = m.begin(); mit!= m.end(); mit++){
				v.push_back(make_pair(mit->first, mit->second));
			}
			sort(v.begin(),v.end(),compare);
			for (vector<pair<string,int>>::iterator itr = v.begin();itr!=v.end();++itr){
				cout << itr->first << " " << itr->second << endl;
			}
			break;
		}
		default:
			cout<<"invalid input"<<endl;
			break;
	}
}



int main(int argc, char* argv[]){
	string mystr = read_file(argv[2]);
	vector<string> v = split(mystr,' ');
	vector<string>::iterator itr;
	cout << endl;
	map<string,int> m = build_model_map(v);
	print(m,argv[1]);
}