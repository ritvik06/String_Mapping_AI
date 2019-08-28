#include<bits/stdc++.h>
#include<chrono>

int max_length=7;
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
	srand ( time(NULL));

	for(int i=0;i<arr.size();i++){
		dif = max_length - arr[i].size();
		cout << "Array size" << arr[i].size();
		cout << "DIF" << dif << endl;
		itr = arr[i].begin();

		for(int j=0;j<dif;j++){
			random = rand()%max_length;
			if(random == prev_random){
				random=(random+1)%(max_length);
			}	
			cout << "Random-" << random << endl;
			arr[i].insert(arr[i].begin()+random,0);
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

vector<vector<int> > next_state(vector<vector<int> > arr){

	for(int i=0;i<max_length;i++){
				
	}


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
		cout << endl;
	}

	for(int i=0;i<vec.size();i++){
		CC+=((max_length-vec[i].size())*dash_cost);
	}

	vec.clear();
	cout << "Cost after local search is " << (CC + local_search(vec2)) << endl; 

    auto end = chrono::high_resolution_clock::now(); 

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
  
    time_taken *= 1e-9; 
  
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(9); 
    cout << " sec" << endl;

	return 0;
}
