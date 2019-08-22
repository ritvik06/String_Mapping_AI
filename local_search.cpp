#include<iostream>
#include<vector>
#include<string>

int max_length=4;

using namespace std;

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
	vector<int> column;
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

int main(){
	vector<vector<int> > vec {{1,2,1,3},
							  {2,3},
							  {3,1,2}};

	vector<vector<int> > vec2(vec.size(),vector<int>(max_length,0));

	// vec2 = init_state(vec);

	for(int i=0;i<vec.size();i++){
		for(int j=0;j<vec[i].size();j++){
			vec2[i][j]=vec[i][j];
			// cout << vec[i][j] << " ";
		}
	}
	cout << "Cost after local search is " << local_search(vec2) << endl; 


	return 0;
}
