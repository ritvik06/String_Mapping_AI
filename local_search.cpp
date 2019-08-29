#include<bits/stdc++.h>
#include<chrono>

int max_length=8;
int dash_cost=3;

using namespace std;

vector<vector<int> > random_start(vector<vector<int> > arr){

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

int cost(vector<vector<int> > arr){
	int cost = 0;
	vector<int> list = {};


	for(int counter=0;counter<max_length;counter++){
		list.clear();

		for(int i=0;i<arr.size();i++){
			list.push_back(arr[i][counter]);
		}

		for(int j=0;j<list.size()-1;j++){
			for(int k=j+1;k<list.size();k++){
				if(list[j]!=list[k]){
					if(list[j]!=0 && list[k]!=0)
						cost+=2;
					else
						cost+=1;
				}

			}
		}
	}

	return cost;
}

vector<vector<int> > init_state(vector<vector<int> > str_arr){

	for (int i=0;i<str_arr.size();i++){
		if(str_arr[i].size()>max_length){
			max_length = str_arr[i].size();
		}
	}

	for (int i=0;i<str_arr.size();i++){
		int dif = max_length - str_arr[i].size();
		for (int j=0;j<dif;j++){
			str_arr[i].push_back(0);
		}
	}
	// cout << "size is " << str_arr.size() << " max " << max_length << " ";

	return str_arr;
}


int local_search(vector<vector<int> > arr){
	int counter=0,prev_cost,curr_cost;
	vector<int>::iterator itr;
	prev_cost = cost(arr);

	cout << "Initial Matrix " << endl;
	for(int l=0;l<arr.size();l++){
		for(int m=0;m<max_length;m++){
			cout << arr[l][m] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;


	for(counter=0;counter<max_length;counter++){
		for(int i=0;i<arr.size();i++){
			itr = arr[i].begin();
			if(arr[i][max_length-1]==0){
				arr[i].pop_back();
				arr[i].insert(itr+counter,0);
				curr_cost = cost(arr);
				if(curr_cost<prev_cost){
					prev_cost = curr_cost;
				}
				else{
					arr[i].erase(itr+counter);
					arr[i].push_back(0);
				}
				// cout << arr[i][max_length];
			}
		}
		cout << "Iteration no " << counter+1 << endl;
		for(int l=0;l<arr.size();l++){
			for(int m=0;m<max_length;m++){
				cout << arr[l][m] << " ";
			}
			cout << endl;
		}

		cout << endl << endl;	
	}

	return prev_cost;	

}

vector<int> find(vector<int> vec,int pos){
	vector<int> list;

	for(int i=pos+1;i<vec.size();i++){
		if(vec[i]==0)
			list.push_back(i);
	}

	return list;
}

int local_final(vector<vector<int> > arr){
	int prev_cost = cost(arr),min = max_length,curr_cost=0;
	vector<int> list;

	cout << "Starting Cost " << prev_cost <<endl;

	for(int j=0;j<max_length;j++){
		for(int i=0;i<arr.size();i++){
			list = find(arr[i],j);
			// cout << list.size() << endl;
			// cout << "Done" << endl;
			cout << "Swapable " << arr[i][j];

			cout << "entered into " << list[0] << endl;

			for(int k=0;k<list.size();k++){
				// cout << "Entered" << endl;
				arr[i].erase(arr[i].begin()+j);
				arr[i].insert(arr[i].begin()+list[k],0);
				curr_cost = cost(arr);
				if (prev_cost>curr_cost){
					min = k;
					prev_cost = curr_cost;
				}
				arr[i].erase(arr[i].begin()+list[k]);
				arr[i].insert(arr[i].begin()+j,0);


			}
			if(list.size()!=0){
				arr[i].erase(arr[i].begin()+j);
				arr[i].insert(arr[i].begin()+list[min],0);
			}

		}		

		cout << "Iteration no " << j << endl;
		for(int l=0;l<arr.size();l++){
			for(int m=0;m<max_length;m++){
				cout << arr[l][m] << " " ;
			}
			cout << endl;
		}

	}


	return prev_cost; 
}

int main(){
	int CC;
	// vector<vector<int> > vec {{1,2,1,3,2,1,2,1,3,2,3,1,1,3,2,1},
	// 						  {2,3,3,2,2,3,1,3,2,2,1,2,3,1,2},
	// 						  {3,1,2,1,2,3,2,2,1,1,2,3,2,3,2,1,2,1},
	// 						  {3,1,2,3,2,2,1,2,2,3,1,2,2},
	// 						  {3,1,2,2,1,1,2,3,2},
	// 						  {2,1,1,2,3,1},
	// 						  {2,3,1,3,2,3,2,2,3},
	// 						  {2,3,1,2,3,2,3,2,1,2,2,3},
	// 						  {1,3,2,2,3,1,2,2,3,2,1},
	// 						  {1,3,2,3,2,3,1,2,3,2,1,2,3,2},
	// 						{1,2,1,3,2,1,2,1,3,2,3,1,1,3,2,1},
	// 						  {2,3,3,2,2,3,1,3,2,2,1,2,3,1,2},
	// 						  {3,1,2,1,2,3,2,2,1,1,2,3,2,3,2,1,2,1},
	// 						  {3,1,2,3,2,2,1,2,2,3,1,2,2},
	// 						  {3,1,2,2,1,1,2,3,2},
	// 						  {2,1,1,2,3,1},
	// 						  {2,3,1,3,2,3,2,2,3},
	// 						  {2,3,1,2,3,2,3,2,1,2,2,3},
	// 						  {1,3,2,2,3,1,2,2,3,2,1},
	// 						  {1,3,2,3,2,3,1,2,3,2,1,2,3,2},{1,2,1,3,2,1,2,1,3,2,3,1,1,3,2,1},
	// 						  {2,3,3,2,2,3,1,3,2,2,1,2,3,1,2},
	// 						  {3,1,2,1,2,3,2,2,1,1,2,3,2,3,2,1,2,1},
	// 						  {3,1,2,3,2,2,1,2,2,3,1,2,2},
	// 						  {3,1,2,2,1,1,2,3,2},
	// 						  {2,1,1,2,3,1},
	// 						  {2,3,1,3,2,3,2,2,3},
	// 						  {2,3,1,2,3,2,3,2,1,2,2,3},
	// 						  {1,3,2,2,3,1,2,2,3,2,1},
	// 						  {1,3,2,3,2,3,1,2,3,2,1,2,3,2}};


	vector<vector<int> > vec {{1,2,3,4,3,4,1},
								{3,1,2,3,4,2},
								{1,2,3,4,1}};
							

	vector<vector<int> > rand2;			

	auto start = chrono::high_resolution_clock::now();

	rand2 = random_start(vec);
					
	for(int i=0;i<rand2.size();i++){
		for(int j=0;j<rand2[i].size();j++){
			cout << rand2[i][j] << " ";
		}
		rand2[i].resize(max_length);
		cout << endl;
	}

	// cout << "Done" << endl;

	int final_cost = local_final(rand2);

	cout << " Final Cost is " << final_cost << endl;

	// for(int i=0;i<vec.size();i++){
	// 	CC+=((max_length-vec[i].size())*dash_cost);
	// }

	// vec.clear();
	// cout << "Cost after local search is " << (CC + local_search(vec2)) << endl; 

 //    auto end = chrono::high_resolution_clock::now(); 

 //    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
  
 //    time_taken *= 1e-9; 
  
 //    cout << "Time taken by program is : " << fixed << time_taken << setprecision(9); 
 //    cout << " sec" << endl;

	return 0;
}
