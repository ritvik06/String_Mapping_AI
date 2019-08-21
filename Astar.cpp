#include <bits/stdc++.h>
using namespace std;


int dashMatch = 1;
int dash_cost = 3;
int misMatch = 2;

struct node
{
	vector<string> str;
	int h;
	int g;
	int k_str;  
};

int hfunc(vector<string> s, int k){
	int cost=0;
	//cost of inserting dashes
	for(int i=0; i<s.size(); i++){
		cost = cost + ((k-s.size())*dash_cost);
	}
	//cost of matching with dashes
	for(int i=0; i<s.size(); i++){
		for(int j=i+1; j<s.size(); j++){
			cost = cost + (abs(s[i].size()-s[j].size())*dashMatch);
		}
	}

	return cost;


}

int gfunc(int pnt, vector<string> s){
	int cost = 0;

	for(int i=0; i<s.size(); i++){
		for(int j=i+1; j<s.size(); j++){
			if(s[i][pnt]!=s[j][pnt]){
				if(s[i][pnt]=='_' || s[j][pnt]=='_' )
					cost = cost + dashMatch;
				else
					cost = cost + misMatch;
			}
		}
	}
	

	return cost;
}


int main(){ 
	int s_len;
	int k = 0; //max length of any string
	cin >> s_len;
	vector<string> s(s_len);

	for(int i=0; i<s_len; i++){
		cin>>s[i];
		if(s[i].size()>k) k = s[i].size();
	}

	vector<node> neighbour;

	node start;
	start.str = s;
	start.g = 0;
	start.h = hfunc(s,k); 
	start.k_str = k;
	int pnt=0;
	bool reach=false;
	int k_temp;
	node current = start;
	node temp = start;
	while(!reach){
		int f=INT_MAX;
		vector<string> newS = current.str;
		for(int i=0; i<s_len; i++){
			node neigh;
			newS[i] = newS[i].substr(0,pnt) + "_" + newS[i].substr(pnt+1);
			neigh.str = newS;
			k_temp = current.k_str ;
			if(k_temp<newS[i].size()) k_temp = newS[i].size();
			neigh.k_str = k_temp;
			neigh.h = hfunc(newS,k_temp);
			neigh.g = current.g + gfunc(pnt,newS);
			if(neigh.g + neigh.h < f){
				f = neigh.g + neigh.h;
				temp = neigh;
			} 
			newS[i] = newS[i].substr(0,pnt) + newS[i].substr(pnt+1);  //restoring the ith string position
		}

		current = temp;
		pnt++;
		if(pnt>(current.k_str-1)) reach = true;
	}

	cout<<"Output function:"<<endl;
	for(int i=0; i<current.k_str; i++){
		cout<<current.str[i]<<endl;
	}

	return 0; 

}