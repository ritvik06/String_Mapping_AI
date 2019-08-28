#include <bits/stdc++.h>
#include <unordered_map> 
using namespace std;

int **cost;
unordered_map<char, int> charIndex; 

void printList(vector<vector<int> > s){
	for(int i=0; i<s.size(); i++){
		for(int j=0; j<s[i].size();j++)
			cout<<s[i][j]<<" ";
		cout<<endl;
	}
	return;
}

vector<vector<int> > readFile(int &k, string file)
{
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

	int n=0;
	inFile >> n;

	cost = (int**)malloc(sizeof(int*)*n);

	for(int i=0 ;i<n; i++){
		cost[i] = (int*)malloc(sizeof(int)*n);
	}

	for(int i=0 ;i<n-1; i++){
		for(int j=0; j<n-1; j++){
			inFile >> cost[i][j];
			cout << cost[i][j]<<" ";
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
	printList(vect);
	return vect ;
}


int main(){

	int k=0;
	string fileName;
	cin>>fileName;

	readFile (k, fileName);
	return 0;
}