#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>

using namespace std;

//This is Question 3


/* Running Time of this algorithm is O(N^3) in the arrangement function. The space complexity is O(n^2) 
	for storing the game pieces in the array*/

int stringToNumber(string s) {
	int num=0;
	stringstream converter(s);
	converter>>num;
	
	return num;
}

vector<int> conversion(string line) {
	vector<int> final;
	string theword="";
	for(int i=0;i<line.size();i++) {
		if(line[i]==' ') {
			if(theword=="Row"|| theword=="Col") {}
			else {
				final.push_back(stringToNumber(theword));
			}
			theword="";
		}

		else {
			theword+=line[i];
		}
	}
	final.push_back(stringToNumber(theword));

	return final;
}

int indexMax(vector<int> col) {
	int max=0;
	for(int i=1;i<col.size();i++) {
		if(col[i]>col[max]) {
			max=i;
		}
	}

	return max;
}

vector<vector<int>> arrangement(vector<vector<int>> a, vector<int>& row, vector<int>& col) {
	vector<vector<int>> array=a;
	for(int i=0;i<row.size();i++) {
		while(row[i]!=0) {
			int index=indexMax(col);
			array[i][index]=1;
			col[index]--;
			row[i]--;
		}
	}

	return array;
}

void finalAnswer(vector<vector<int>> arr, vector<int> row, vector<int> col) {
	if(accumulate(row.begin(),row.end(),0)!=accumulate(col.begin(),col.end(),0)) {
		cout<<"Not Possible"<<endl;
	}

	else {
		for(int i=0;i<arr.size();i++) {
			for(int j=0;j<arr[i].size();j++) {
				if(arr[i][j]==1) {
					cout<<"("<<i+1<<","<<j+1<<") ";
				}
			}

			cout<<endl;
		}
	}
}

int main() {
	string filename;
	cout<<"Enter Filename: ";
	cin>>filename;
	cout<<endl;

	ifstream file;
	file.open(filename.c_str());
	vector<int> row;
	vector<int> col;
	vector<vector<int>> array;
	bool possible=1;

	string line;
	getline(file,line);

	int i=0;
	while(getline(file,line)) {
		if(i==0) row=conversion(line);
		else col=conversion(line);
		i++;
	}
	
	//Initializing the array
	for(int i=0;i<row.size();i++) {
		vector<int> a;
		for(int j=0;j<col.size();j++) {
			a.push_back(0);
		}
		array.push_back(a);
	} 

	
	vector<vector<int>> newArray=arrangement(array, row, col);

	finalAnswer(newArray,row,col);

	return 0;
}
