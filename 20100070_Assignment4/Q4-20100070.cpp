#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

//COMPLETED
using namespace std;

/*RECURRENCE RELATION 
	STRING(S1, S2, 0, 0, S3)=0
	STRING(S1, S2, i, j, S3)=STRING(S1, S2, i, j-1, S3) 		  				if i==0 and S2[j-1]!=S3[size-1]
	STRING(S1, S2, i, j, S3)=STRING(S1, S2, i, j-1, S3) + S2[j-1] 				if i==0 and S2[j-1]==S3[size-1]
	STRING(S1, S2, i, j, S3)=STRING(S1, S2, i-1, j, S3) 						if S1[i-1]!=S3[size-1] and j==0
	STRING(S1, S2, i, j, S3)=STRING(S1, S2, i-1, j, S3) 						if S1[i-1]==S3[size-1] and j==0
	STRING(S1, S2, i, j, S3)=STRING(S1, S2, i, j-1, S3)	+ S2[j-1]				if S1[i]!=S3[size-1] and S2[j-1]==S3[size-1]
	STRING(S1, S2, i, j, S3)=STRING(S1, S2, i-1, j, S3) + S1[i-1]				if S1[i]==S3[size-1] and S2[j-1]!=S3[size-1]
	STRING(S1, S2, i, j, S3)=STRING(S1, S2, i-1, j-1, S3) + S1[i-1] + S2[j-1]	if S1[i]==S3[size-1] and S2[j-1]==S3[size-2]
	STRING(S1, S2, i, j, S3)=STRING(S1, S2, i-1, j-1, S3) 						if S1[i]==S3[size-1] and S2[j-1]!=S3[size-1]

*/

/*TIME COMPLEXITY
	Let n be the size of string S1 and m be the size of string S2.
	There were total n*m subproblems and as it is a memoized code, 
	each subproblem took O(1) time.
	Therefore the total time complexity is O(n*m)
*/


string stringDynamo(vector<vector<string>> &memo, vector<pair<char,int>>& cc, string S1, string S2, int i, int j, string S3) {
	int size=S3.size();
	if(i==0 && j==0) {
		return "";
	}

	if(memo[i][j]!="/") return memo[i][j];

	if(i==0 && S2[j-1]!=S3[size-1]) {
		memo[i][j]=stringDynamo(memo, cc, S1, S2, i, j-1, S3);
	}

	else if(i==0 && S2[j-1]==S3[size-1]) {
		cc.push_back(make_pair(S2[j-1], 2));
		memo[i][j]=stringDynamo(memo, cc, S1, S2, i, j-1, S3.substr(0,size-1))+ S2[j-1];
	}

	else if(S1[i-1]!=S3[size-1] && j==0) {
		memo[i][j]=stringDynamo(memo, cc, S1, S2, i-1, j, S3);
	}

	else if(S1[i-1]==S3[size-1] && j==0) {
		cc.push_back(make_pair(S1[i-1], 1));
		memo[i][j]=stringDynamo(memo, cc, S1, S2, i-1, j, S3.substr(0,size-1))+ S1[i-1];
	}

	else if(S1[i-1]==S3[size-1] && S2[j-1]==S3[size-1]) {
		if(j>i) {
			cc.push_back(make_pair(S2[j-1], 2));
			memo[i][j]=stringDynamo(memo, cc, S1, S2, i, j-1, S3.substr(0,size-1))+ S2[j-1];
		}

		else {
			cc.push_back(make_pair(S1[i-1], 1));
			memo[i][j]=stringDynamo(memo, cc, S1, S2, i-1, j, S3.substr(0,size-1))+ S1[i-1];
		}

	}

	else if(S1[i-1]==S3[size-1] && S2[j-1]!=S3[size-2]) {
		cc.push_back(make_pair(S1[i-1], 1));
		memo[i][j]=stringDynamo(memo, cc, S1, S2, i-1, j, S3.substr(0,size-1)) + S1[i-1];
	}

	else if(S1[i-1]!=S3[size-2] && S2[j-1]==S3[size-1]) {
		cc.push_back(make_pair(S2[j-1], 2));
		memo[i][j]= stringDynamo(memo, cc, S1, S2, i, j-1, S3.substr(0,size-1))+ S2[j-1];
	}

	

	else if(S1[i-1]==S3[size-1] && S2[j-1]==S3[size-2]) {
		cc.push_back(make_pair(S1[i-1], 1));
		cc.push_back(make_pair(S2[j-1], 2));
		memo[i][j]=stringDynamo(memo, cc, S1, S2, i-1, j-1, S3.substr(0,size-2)) + S2[j-1] + S1[i-1];
	}

	else if(S1[i-1]==S3[size-2] && S2[j-1]==S3[size-1]) {
		cc.push_back(make_pair(S2[j-1], 2));
		cc.push_back(make_pair(S1[i-1], 1));
		memo[i][j]=stringDynamo(memo, cc, S1, S2, i-1, j-1, S3.substr(0,size-2)) + S1[i-1] + S2[j-1];
	}

	else if(S1[i-1]!=S3[size-1] || S2[j-1]!=S3[size-1]) {
		memo[i][j]= stringDynamo(memo, cc, S1, S2, i-1, j-1, S3);
	}

	return memo[i][j];
}

vector<string> decorate(vector<pair<char, int>> cc, string &fst) {
	vector<string> d;
	string word="";
	if(!cc.empty()) {
		if(cc[cc.size()-1].second==1) {
		fst="S1";
		word+=cc[cc.size()-1].first;
	}

		else {
			fst="S2";
			word+=cc[cc.size()-1].first;
		}

	}
	
	for(int i=cc.size()-2;i>=0;i--) {
		if(cc[i].second!=cc[i+1].second) {
			d.push_back(word);
			word=cc[i].first;
		}

		else {
			word+=cc[i].first;
		}
	}

	d.push_back(word);

	return d;
}

void finalAnswer(string a, vector<string> dec, string S3, string fst) {
	string snd;
	if(a==S3) {
		cout<<"VALID"<<endl;
		if(fst=="S1") {
			snd="S2";
			for(int i=0;i<dec.size();i++) {
				if(i%2==0) {
					cout<<fst<<": "<<dec[i]<<"  ";
				}

				else {
					cout<<snd<<": "<<dec[i]<<"  ";
				}
			}
		}

		else {
			snd="S1";
			for(int i=0;i<dec.size();i++) {
				if(i%2==1) {
					cout<<fst<<": "<<dec[i]<<"  ";
				}

				else {
					cout<<snd<<": "<<dec[i]<<"  ";
				}
			}
		}
	}

	else {
		cout<<"INVALID"<<endl;
	}
	cout<<endl;	
}

int main() {
	// string filename;
	// cout<<"Enter filename: ";
	// cin>>filename;

	// ifstream file;
	// file.open(filename.c_str());
	// string line;
	// vector<pair<char,int>> Collector;
	// string fst;

	string S1,S2,S3;
	// file>>S1>>S2>>S3;

	S1="situated";
	S2="";
	S3="situated";
	vector<vector<string>> memo;

	for(int i=0;i<S1.size()+1;i++) {
		vector<string> m;
		for(int j=0;j<S2.size()+1;j++) {
			m.push_back("/");
		}
		memo.push_back(m);
	} 

	string actualString=stringDynamo(memo, Collector, S1,S2,S1.size(),S2.size(), S3);
	cout<<actualString<<endl;
	cout<<endl;

	vector<string> dec=decorate(Collector, fst);

	finalAnswer(actualString, dec, S3, fst);

	return 0;
}