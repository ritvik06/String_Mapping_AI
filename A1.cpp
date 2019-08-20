#include <bits/stdc++.h>
using namespace std;

int dashMatch = 1;
int dash_cost = 3;
int misMatch = 2;
int *pnt;

int pathCost(vector<int> taken, vector<string> str){

	int l = str.size();
	int pcost = 0;
	for(int i=0; i<l; i++){
		for(int j=i+1; j<l; j++){
			if(taken[i]==0){
				if(taken[j]!=0)
					pcost = pcost + dashMatch;
			}
			else {
				if(taken[j]==0) pcost = pcost + dashMatch;
				else if(str[i][pnt[i]].compare(str[j][pnt[j]])!=0)
					pcost = pcost + misMatch;
				
			}
		}
	}

	for(int i=0 ; i<taken.size(); i++){
		if(taken[i]==0)
			pcost = pcost + dash_cost;
	}
	return pcost;
}

int main(){
	vector<int> taken(3);
	vector<string> str;
	str.push_back("ACTGTGA");
	str.push_back("TACTGC");
	str.push_back("ACTGA");

	for

	
}

