#include <bits/stdc++.h>
#include <unordered_map> 
#include <ctime>
#include<chrono>

using namespace std;

int **costMatrix;
unordered_map<char, int> charIndex; 
int dashCost;
void printList(vector<vector<int> > s){
	for(int i=0; i<s.size(); i++){
		for(int j=0; j<s[i].size();j++)
			cout<<s[i][j]<<" ";
		cout<<endl;
	}
	return;
}

vector<vector<int> > readFile(int &k, int &dashCost, string file){
	int Tmax;		//max Time of Run
	int charCount = 0;
	int s_len;
	// int k = 0; //max length of any string
	
	ifstream inFile;
	inFile.open(file.c_str());

	if (!inFile.is_open()) 
	{
		cout<<"file doesn't open"<<endl;
		vector<vector<int> > v = {{0}};
		return v ;
	}

	inFile >> Tmax;
	cout << Tmax <<endl;
	inFile >> charCount;
	cout << charCount <<endl;
	int word;
	int index = 1;
	char c;
	char comma;
	charIndex['_'] = 0;
	for(int i=0; i<charCount; i++){
		inFile >> c;
		cout << c <<", ";
		if(i!= charCount-1) inFile >> comma;
		charIndex[c] = i+1;
	}

	cout<< endl;
	inFile >> s_len;
	// inFile >> s_len;
	cout<<"s_len "<<s_len<<endl;
	vector<string> s(s_len);
	k = 0;
	for(int i=0; i<s_len; i++){
		inFile >> s[i];
		if(k<s[i].size()) k = s[i].size();
		cout << s[i] <<endl;
	}

	inFile >> dashCost;

	costMatrix = (int**)malloc(sizeof(int*)*(charCount+1));

	for(int i=0 ;i<(charCount+1); i++){
		costMatrix[i] = (int*)malloc(sizeof(int)*(charCount+1));
	}

	for(int i=0 ;i<(charCount+1); i++){
		for(int j=0; j<(charCount+1); j++){
			inFile >> costMatrix[i][j];
			cout << costMatrix[i][j]<<" ";
		}
		cout<<endl;
	}

	inFile.close();
	
	vector<vector<int> > vect(s_len);
	int val=0;
	for(int i=0; i<s_len; i++){
		for(int j=0; j<s[i].size(); j++){
			val = (charIndex[s[i][j]]);
			vect[i].push_back(val);
		}
	}
	cout<<endl;
	cout<<"Converted string input is:" <<endl;
	// printList(vect);
	return vect ;
}

// int costNode(vector<vector<int> > arr){
// 	int costN = 0;
// 	int pnt=0;
// 	int r,c;
// 	while(pnt<arr[0].size()){
// 		for(int i=0; i<arr.size(); i++){
// 			if(arr[i][pnt]==0) 
// 			cost = cost + dashCost;
// 			for(int j=i+1; j<arr.size(); j++){
// 				r= arr[i][pnt]; c=arr[j][pnt];
// 				costN = costN + cost[0][0];
// 				cout<<cost[0][0]<<endl;
// 				cout<<"i: "<<i<<" j: "<<j<<endl;
// 			}
// 		}	
// 		pnt++;
// 	}
// 	cout<<"done \n";
// 	return costN;
// }

int costNode(vector<vector<int> > arr, int lastMin){  //lastmin to abort cost calculation the moment it exceeds the currrent minCost 
	int costN = 0;
	vector<int> list = {};

	for(int counter=0;counter<arr[0].size();counter++){
		list.clear();

		for(int i=0;i<arr.size();i++){
			list.push_back(arr[i][counter]);
		}

		for(int j=0;j<list.size()-1;j++){
			if(list[j]==0) 
 				costN = costN + dashCost;
			if(costN > lastMin)
				break;
			for(int k=j+1;k<list.size();k++){
				costN = costN + costMatrix[list[j]][list[k]];
				if(costN > lastMin)
 					break;
				// cout<<cost[list[j]][list[k]]<<endl;
				// cout<<"j: "<<j<<" k: "<<k<<endl;
			}
		}
	}

	return costN;
}


vector<vector<int> > random_startNew(vector<vector<int> > arr, int max_length){

	vector<vector<int> > vec2(arr.size(),vector<int>(max_length,0));

	// for(int i=0;i<arr.size();i++){
	// 	for(int j=0;j<arr[i].size();j++){
	// 		vec2[i][j]=arr[i][j];
	// 		// cout << vec[i][j] << " ";
	// 	}
	// }

	int dif,random,prev_random;
	vector<int>::iterator itr;
	vector<int> rand_arr;
	srand ( time(NULL));

	for(int i=0;i<arr.size();i++){
		dif = max_length - arr[i].size();
		cout << "Array size" << arr[i].size();
		cout << "DIF" << dif << endl;
		itr = arr[i].begin();

		for(int j=0;j<dif;j++){
			random = rand()%max_length;			
			rand_arr.push_back(random);
		}


		sort(rand_arr.begin(),rand_arr.end());

		for(int j=0;j<dif;j++){
			cout << "Random " << rand_arr[j] << " ";
		}

		cout << endl;

		for(int j=0;j<dif;j++){
			arr[i].insert(arr[i].begin()+rand_arr[j],0);
			prev_random = random;
		}
		for(int k=0;k<max_length;k++){
			cout << arr[i][k] << " ";
		}

		cout << endl;

	}
	return arr;
} 

vector<vector<int> > random_start(vector<vector<int> > vect, int k){
	// srand (time(NULL));
	int zeroes = 0;
	int random = 0;

	for(int i=0; i<vect.size(); i++){
		zeroes = k-vect[i].size();
		for(int j=0; j<zeroes; j++){
			random = rand()%vect[i].size();
			vect[i].insert(vect[i].begin()+random,0);
		}
	}

	return vect;
}

int oneStep(vector<vector<int> > &v, int ind, int prev_cost){  //oneStep returns a new bect vect if its cost is better than
	bool changed = false;								   //already calculated prev_cost
	// srand(time(NULL));
	int minCost = prev_cost;
	vector<vector<int> > bestVect = v;
	vector<vector<int> > sample;
	int temp=0;

	for(int i=0; i<v[ind].size(); i++){
		if(i!=v[ind].size()-1){
			if(v[ind][i]==0 && v[ind][i+1]!=0){
				sample = v;
				temp = sample[ind][i];
				sample[ind][i] = sample[ind][i+1];
				sample[ind][i+1] = temp;
				int c = costNode(sample, minCost);
				if( minCost > c){
					bestVect = sample;
					minCost = c;
				}
			}
		}
		if(i!=0){
			if(v[ind][i]==0 && v[ind][i-1]!=0){
				sample = v;
				temp = sample[ind][i];
				sample[ind][i] = sample[ind][i-1];
				sample[ind][i-1] = temp;
				int c = costNode(sample, minCost);
				if( minCost > c){
					bestVect = sample;
					minCost = c;
				}
			}
		}
	}
	v = bestVect;
	return minCost;

}

// int randomJump(vector<vector<int> > vect, int prev_cost){
// 	srand(time(NULL));
// 	int 
// }


int local_search(vector<vector<int> > vect, int prev_cost){

	int counter=0;
	int curr_cost=prev_cost;

	vector<vector<int> > vect2=vect;  //change
	vector<vector<int> > best = vect;
	for(int i=0; i<vect.size(); i++){
		vect2 = vect;    
		int c = oneStep(vect2, i, curr_cost);
		if(curr_cost > c){
			best = vect2;
			curr_cost = c;
		}
	}
	cout<<"Best till now:"<<curr_cost<<endl;
	// printList(best);
	cout<<endl;
	if(best!=vect){
		curr_cost = local_search(best, curr_cost);
	}	
	// else{
	// 	randomJump(best, curr_cost);
	// }
	return curr_cost;	

}

int main(){

	int k=0;
	string fileName;
	cin>>fileName;

	vector<vector<int> > vect = readFile (k, dashCost, fileName);

	auto start = chrono::high_resolution_clock::now();
	vector<vector<int> > vect_rand;
	srand (time(0));

	int bestCost = INT_MAX;
	for(int i=0; i<100; i++){
		// vect = random_startNew(vect, k);
		// vect_copy = vect;
		vect_rand = random_start(vect, k);
		// cout<<"random start: "<<endl;
		// printList(vect_rand);
		int initial_cost = costNode(vect_rand,INT_MAX);
		cout<<"cost: "<<initial_cost<<endl;
		int localCost = local_search(vect_rand, initial_cost);
		cout << "Cost after local search is " << localCost << endl; 
		cout << "Output matrix:" <<endl;
		printList(vect_rand);
		
		if(bestCost > localCost) bestCost = localCost;
	    auto end = chrono::high_resolution_clock::now(); 

	    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
	  
	    time_taken *= 1e-9; 
	  
	    cout << "Time taken by program is : " << fixed << time_taken << setprecision(9); 
	    cout << " sec" << endl;
	}

	cout<<"BEST Cost: "<<bestCost<<endl;
	return 0;
}