#include <bits/stdc++.h>
#include<chrono>

using namespace std;



int dashMatch = 1;
int dash_cost = 3;
int misMatch = 2;

struct node{
	vector<string> str;
	int h;
	int g;
	int k_str;  
	int level;
};

struct compareFunc { 
    bool operator()(node const& n1, node const& n2) 
    { 
        // return "true" if "p1" is ordered  
        // before "p2", for example: 
        return -(n1.h+n1.g) < -(n2.h+n2.g); 
    } 
}; 

int hfunc(vector<string> s, int k){
	int cost=0;
	//cost of inserting dashes
	for(int i=0; i<s.size(); i++){
		cost = cost + ((k-s[i].size())*dash_cost);
	}
	// cout << "cost1 "<<cost<<endl;
	//cost of matching with dashes
	for(int i=0; i<s.size(); i++){
		for(int j=i+1; j<s.size(); j++){
			if(s[i].size()-s[j].size()<0)
				cost = cost - ((s[i].size()-s[j].size())*dashMatch);
			else 
				cost = cost + ((s[i].size()-s[j].size())*dashMatch);
		}
	}

	return cost;
}

bool findChar(char c, vector<string> s, int index, int start_pnt, vector<vector<int> > &v){
	for(int i=start_pnt; i<s[index].size();i++){
		if(s[index][i]=='_') break;
		if(s[index][i]==c && v[index][i-start_pnt]==0){
			v[index][i-start_pnt]==1;
			// cout<<"true"<<endl;
			return true;
		}
	}
	return false;
}

int hfunc1(vector<string> s, int k, int start_pnt){
	int cost=0;
	//cost of inserting dashes
	for(int i=0; i<s.size(); i++){
		cost = cost + ((k-s[i].size())*dash_cost);
	}
	// cout<<"hi"<<endl;
	vector<vector<int> > v(s.size(),vector<int>(k-start_pnt));
	for(int i=0; i<v.size(); i++){
		for(int j=0; j<v[0].size(); j++){
			v[i][j] = 0;
		}
	}	
	int c=0;
	// cout<<"hi2"<<endl;
	int pnt = start_pnt;
	while(pnt<k){
		for(int i=0; i<s.size() ; i++){
			for(int j=i+1; j<s.size(); j++){
				// cout<<i<<"  "<<j<<endl;
				if(s[i].size()>pnt){
					if(s[i][pnt] != '_'){
					if(!findChar(s[i][pnt],s,j,start_pnt,v))
						cost = cost + dashMatch;
					}	
				}
			}
		}
		pnt++;
	}
	// cout << "cost1 "<<cost<<endl;
	//cost of matching with dashes
	
	return cost;
}

int gfunc(int pnt, vector<string> &s){
	int cost = 0;

	for(int i=0; i<s.size(); i++){
		if(s[i][pnt]=='_') cost = cost+dash_cost;
		for(int j=i+1; j<s.size(); j++){
			if(s[j].size()<pnt) s[j] = s[j] + "_";
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

int findCost(vector<string> v){
	int n = v.size();
	int l = v[0].size();
	int pnt=0;
	int cost=0;
	while(pnt < l){
		for(int i=0; i<n; i++){
			if(v[i][pnt]=='_') cost = cost + dash_cost;
			for(int j=i+1;j<n; j++){
				if(v[i][pnt] != v[j][pnt]){
					if(v[j][pnt] == '_' || v[i][pnt] == '_')
						cost = cost + dashMatch;
					else cost = cost + misMatch;
				}
			}
		}
	pnt++;	
	}

	return cost;
}


node make_Node(node current, int pnt, int i){
	node n1;
	vector<string> newS = current.str;
	// cout<<"size "<<newS[i].size()<<" pnt "<<pnt<<endl;
	if(pnt>newS[i].size()){
		for(int j=0; j<pnt - newS[i].size(); j++)
		newS[i] = newS[i] + "_";

	}
	
	newS[i] = newS[i].substr(0,pnt) + "_" + newS[i].substr(pnt);
	n1.str = newS;
	if(current.k_str < newS[i].size()) n1.k_str = newS[i].size();
	else n1.k_str = current.k_str;
	n1.h = hfunc1(newS,n1.k_str,pnt+1);
	n1.g = current.g + gfunc(pnt,newS);
	// cout<<newS[i]<<"  ";
	// cout<<"cost: h "<<(n1.h)<<" g "<< n1.g<<endl;
	n1.level = pnt;
	return n1;
}



void neighbourNodes(priority_queue<node, vector<node>, compareFunc> &PQ, vector<string> s, int pnt, int index, node current){
	if(index < s.size()){

		node n_1 = make_Node(current, pnt, index);
		PQ.push(n_1);
		neighbourNodes(PQ, n_1.str, pnt, index+1, current);
		if(s[index].size()>pnt)
			neighbourNodes(PQ, s, pnt, index+1, current);
	}
	return;
}

void printList(vector<string> s){
	for(int i=0; i<s.size(); i++){
		cout<<s[i]<<endl;
	}
	return;
}

// int main(){ 
// 	int s_len;
// 	int k = 0; //max length of any string
// 	cin >> s_len;
// 	vector<string> s(s_len);

// 	for(int i=0; i<s_len; i++){
// 		cin>>s[i];
// 		if(s[i].size()>k) k = s[i].size();
// 	}

// 	vector<vector<int> > v(4, vector<int>(5));
// 	for(int i=0; i<v.size(); i++){
// 		for(int j=0; j<v[0].size(); j++){
// 			v[i][j] = 0;
// 		}
// 	}	

// 	// cout<<findChar('Z',s,0,0, v);
// 	// cout<<"sl"<<s_len<<endl;
// 	cout<<h1func(s, k, 0);

// }

int main(){ 
	int s_len;
	int k = 0; //max length of any string
	cin >> s_len;
	vector<string> s(s_len);

	for(int i=0; i<s_len; i++){
		cin>>s[i];
		if(s[i].size()>k) k = s[i].size();
	}

	priority_queue<node, vector<node>, compareFunc> Q;
	vector<node> neighbour;

	node start;
	start.str = s;
	start.g = 0;
	start.h = hfunc1(s,k,0); 
	start.k_str = k;
	start.level = 0;
	int pnt=0;
	bool reach=false;
	int k_temp;
	node current = start;
	// cout<<current.h+current.g<<" here \n";
	// node temp = start;
	Q.push(start);
	Q.pop();

	auto start_time = chrono::high_resolution_clock::now();

	while(!reach){
		node n1 = current;
		// n1.k_str = current.k_str;
		n1.h = hfunc1(current.str,n1.k_str,pnt+1);
		n1.g = current.g + gfunc(pnt,current.str);
		n1.level = pnt;
		Q.push(n1);
		// cout<<"neighbour \n";
		neighbourNodes(Q, current.str, pnt, 0, current);
		
		current = Q.top();
		Q.pop();

		// cout<<"List: "<<current.str.size()<<endl;
		 printList(current.str);
		 cout<<"chosen: "<<(current.h+current.g)<<endl;
		pnt = current.level+1;
		cout<<"pnt "<<current.level<<endl;
		if(pnt>(current.k_str-1)) reach = true;
	}

	auto end = chrono::high_resolution_clock::now(); 



    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start_time).count(); 
  
    time_taken *= 1e-9; 
  
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(9); 
    cout << " sec" << endl;

	cout<<"Output function:"<<endl;
	for(int i=0; i<current.k_str; i++){
		cout<<current.str[i]<<endl;
	}

	return 0; 

}
