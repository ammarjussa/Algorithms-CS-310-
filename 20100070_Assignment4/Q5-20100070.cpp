#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <climits>

//COMPLETED

using namespace std;

/*RECURRENCE RELATION 
	Matrix(sum, n)= max(total + sum[i-size][j] + sum[i][j-size] - sum[i-size][j-size]
	Matrix(sum, n)= 0 otherwise
*/

/*TIME COMPLEXITY
	There are total n^2 subproblems for each size of max sub matrix we want which makes the
	subproblem n^3. For each subproblem, it takes O(1) time.
	Therefore, the total time complexity is O(n^3)
*/

typedef pair<pair<int, int>, pair<int, int>> PairPair;

int stringToNumber(string s) {
	int num=0;
	stringstream converter(s);
	converter>>num;
	
	return num;
}

int numberOfInputs(string line) {
	size_t b=line.find_last_of(' ');
	return stringToNumber(line.substr(b+1));
}

vector<int> processingNumbers(string line, int n) {
	vector<int> final;
	int i=0;
	if(line[0]=='{') i=2;
	string word="";
	for(i;i<line.size();i++) {
		if(line[i]==',') {
			final.push_back(stringToNumber(word));
			i++;
			word="";
		}

		else {
			word+=line[i];
		}
	}

	if(word==" ") {}

	else {
		final.push_back(stringToNumber(word));	
	}

	if(final.size()==n+1) final.pop_back();	

	return final; 
} 

vector<vector<int>> calculateSumMatrix(vector<vector<int>> matrix) {
	vector<vector<int>> sum;
	for(int i=0;i<matrix.size();i++) {
		vector<int> temp;
		for(int j=0;j<matrix.size();j++) {
			temp.push_back(0);
		}
		sum.push_back(temp);
	}

	sum[0][0]=matrix[0][0];
	for(int i=1;i<matrix.size();i++) {
		sum[i][0]=matrix[i][0]+sum[i-1][0];
	}

	for(int j=1;j<matrix.size();j++) {
		sum[0][j]=matrix[0][j]+sum[0][j-1];
	}

	for(int i=1;i<matrix.size();i++) {
		for(int j=1;j<matrix.size();j++) {
			sum[i][j]=matrix[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
		}
	}

	return sum;
}

PairPair maxsumMatrix(vector<vector<int>> matrix, vector<vector<int>> sum, int n) {
	int tot;
	int maxtotal= INT_MIN;
	pair<int, int> coord;
	pair<int, int> sumNsize;

	for(int subsize=n-1;subsize>=1;subsize--) {	
		for(int i=subsize-1;i<n;i++) {
			for(int j=subsize-1;j<n;j++) {
				tot=sum[i][j];

				if(i-subsize > 0) 
					tot=tot-sum[i-subsize][j];
				if(j-subsize > 0) 
					tot=tot-sum[i][j-subsize];
				if(i-subsize > 0 && j-subsize > 0) {
					tot=tot+sum[i-subsize][j-subsize];
				}

				if(tot > maxtotal) {
					maxtotal=tot;
					coord=make_pair(i,j);
					sumNsize=make_pair(tot, subsize);
				}
			}
		}
	}	

	return make_pair(coord, sumNsize);
}

void finalAnswer(PairPair cnss) {
	int w=cnss.second.second;
	cout<<"Width = "<<w<<endl;
	cout<<endl;
	cout<<"Top right = ("<<cnss.first.first-w+1<<","<<cnss.first.second-w+1<<")"<<endl;
	cout<<"Bottom right = ("<<cnss.first.first<<","<<cnss.first.second<<")"<<endl;
	cout<<endl;

	cout<<"Sum is "<<cnss.second.first<<endl;

}

int main() {
	int opt;
	int n;
	cout<<"Choose to either read values from file or randomly populate the array(1/2): ";
	cin>>opt;
	vector<vector<int>> theMatrix;
	vector<vector<int>> sumMatrix;

	if(opt==1) {
		string filename;
		cout<<"Enter filename: ";
		cin>>filename;

		ifstream file;
		file.open(filename.c_str());

		if(file.fail()) cout<<"Error Reading File"<<endl;

		string line;
		getline(file,line);
		n=numberOfInputs(line);

		while(getline(file,line)) {
			vector<int> temp;
			temp=processingNumbers(line, n);
			theMatrix.push_back(temp);
		}

	}

	else if(opt==2) {
		cout<<"Enter the value of n: ";
		cin>>n;
		srand(time(NULL));
		for(int i=0;i<n;i++) {
			vector<int> daalo;
			for(int j=0;j<n;j++) {
				daalo.push_back(rand() % (n*4) + -(n*2));
			}
			theMatrix.push_back(daalo);
		}
	}

	cout<<endl;

	for(int i=0;i<theMatrix.size();i++) {
		for(int j=0;j<theMatrix[i].size();j++) {
			cout<<theMatrix[i][j]<<" ";
		}
		cout<<endl;
	}

	cout<<endl;

	sumMatrix=calculateSumMatrix(theMatrix);

	PairPair coordNsumsize=maxsumMatrix(theMatrix, sumMatrix, n);

	finalAnswer(coordNsumsize);

	return 0;
}