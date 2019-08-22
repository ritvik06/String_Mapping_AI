#include<iostream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;

int main(){

int time,V,t;
string s;
vector<int> seq;
map<char,int> gene;


cin << time << V;

cin << s;

stringstream ss(str);

for(char i;ss >> i){
	seq.push_back(i);
	if(ss.peek()==','){
		ss.ignore();
	}
}




}