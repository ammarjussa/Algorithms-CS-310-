#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <numeric>

//COMPLETED
using namespace std;

/*RECURRENCE RELATION
	arr[0][0]=True
	arr[1..i][0]=True
	arr[0][1..j]=False
	arr[i][j]=dp[i][j-set[i]] | dp[i-1][j]
*/

/*TIME COMPLEXITY
	Let s be the sum of the set and let n be no. of elements in the set. 
	There are n*s subproblems and each problem takes O(1) time.
	Therefore, the total time complexity is O(n*s).
*/ 


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

vector<int> converter(string line) {
	vector<int> Rev;
	string word="";
	for(int i=2;i<line.size();i++) {
		if(line[i]==' ') {
			Rev.push_back(stringToNumber(word));
			word="";
		}

		else word+=line[i];
	}

	Rev.push_back(stringToNumber(word));
	return Rev;

}

int findtheSum(int sum, int diff) {
	int a,b;
	a=(sum-diff)/2;
	b=sum-a;

	if(a+b==sum && abs(a-b)==diff) {
		return min(a,b);
	}

	else return -1000;
}

void subsetDynamo(vector<int> numbers, int sum, vector<int>& subset, string& decision) {
	bool thearr[numbers.size()+1][sum+1];

	for(int i=0;i<=numbers.size();i++) {
		thearr[i][0]=1;
	}

	for(int i=1;i<=sum;i++) {
		thearr[0][i]=0;
	}

	for(int i=1;i<=numbers.size();i++) {
		for(int j=1;j<=sum;j++) {
			if(j<numbers[i-1]) 
				thearr[i][j]=thearr[i-1][j];

			else if(j>=numbers[i-1]) {
				thearr[i][j]=thearr[i-1][j] || thearr[i-1][j-numbers[i-1]];
			
			}
		}
	}


	if(thearr[numbers.size()][sum]==1) decision="POSSIBLE";
	else decision="NOT POSSIBLE";

	if(decision=="POSSIBLE") {
		int s=sum;
		int ii=numbers.size();
		while(ii>=0) {
			if(s==0) break;
			
			else if(thearr[ii-1][s]==1) {
				ii--;
			}

			else {
				s=s-numbers[ii-1];
				subset.push_back(numbers[ii-1]);
			}
		}
	}	
	return;

}

void finalAnswer(string d, vector<int> subset, int k, vector<int> n, int sum) {
	if(d=="POSSIBLE") {
		vector<int> subset2;
		for(int i=0;i<n.size();i++) {
			bool hai=false;
			for(int j=0;j<subset.size();j++) {
				if(n[i]==subset[j]) { 
					hai=true;
					break; 
				}
			}
			
			if(!hai) subset2.push_back(n[i]);
		}

		cout<<d<<endl;
		cout<<"S1: ";
		for(int i=0;i<subset2.size();i++) {
			cout<<subset2[i]<<" ";
		}
		cout<<" sum = "<<sum+k<<endl;
		cout<<"S2: ";
		for(int i=0;i<subset.size();i++) {
			cout<<subset[i]<<" ";
		}
		cout<<" sum = "<<sum<<endl;
		cout<<"Difference: "<<sum+k<<"-"<<sum<<" = "<<k<<endl;


	}

	else cout<<d<<endl;
} 


int main() {
	string filename;
	cout<<"Enter filename: ";
	cin>>filename;

	ifstream file;
	file.open(filename.c_str());
	string line;
	vector<int> n;
	vector<int> subset;
	string decision;

	if(file.fail()) cout<<"Error Reading File"<<endl;

	getline(file,line);
	int k=numberOfInputs(line);


	getline(file,line);
	n=converter(line);

	int sum=accumulate(n.begin(), n.end(), 0);

	int numforsum=findtheSum(sum, k);

	if (numforsum==-1000) decision="NOT POSSIBLE";

	else {
		subsetDynamo(n,numforsum, subset, decision);
	}

	finalAnswer(decision, subset,k,n, numforsum);

	return 0;
}