#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

//This is Question 6



int stringToNumber(string s) {
	int num=0;
	stringstream converter(s);
	converter>>num;
	
	return num;
}

string numberToString(int a) {
	stringstream ss;
	ss << a;
	string str = ss.str();

	return str;
}

bool parenthesis(char c) {
	switch(c) {
		case '(':
		case ')':
			return true;
		default:
			return false;	
	}
}

bool andor(char c) {
	switch(c) {
		case '^':
		case 'v':
		case '\'':
			return true;
		default:
			return false;	
	}
}

string conversion(string line) {
	string thechars="()";
	for(int i=0;i<thechars.size();i++) {
		line.erase(remove_if(line.begin(),line.end(), &parenthesis), line.end());
	}

	return line;
}

string conversion2(string line) {
	string thechars="^v\'";
	for(int i=0;i<thechars.size();i++) {
		line.erase(remove_if(line.begin(),line.end(), &andor), line.end());
	}

	return line;
}

int extracter(string l) {
	string theword="";
	for(int i=2;i<l.size();i++) {
		theword+=l[i];
	}

	return stringToNumber(theword);
}
 
string findthelastWord(string s) {
	string word="";
	for(int i=s.size()-1;i>=0;i--) {
		if(s[i]==' ') {
			if(i==0) {}
			else break;
		}
		else word+=s[i];
	}

	reverse(word.begin(),word.end());

	return word;
}

map<string, int> hornyFormula(vector<string> variables, vector<string> clauses) {
	map<string,int> truthAssignments;
	for(int i=0;i<variables.size();i++) {
		truthAssignments.insert(make_pair(variables[i],1));
	}

	queue<string> RightOfEmptyImp;
	for(int i=0;i<clauses.size();i++) {
		if(clauses[i][0]=='=') {
			RightOfEmptyImp.push(findthelastWord(clauses[i]));
		}
	}
	int count=0;


	while(!RightOfEmptyImp.empty()) {
		string v=RightOfEmptyImp.front();	
		RightOfEmptyImp.pop();
		truthAssignments[v]=0;

		for(int i=0;i<clauses.size();i++) {
			int j=0;
			
			while(clauses[i][j]!='=') {
				if(clauses[i].substr(j,v.size())==v) {
					clauses[i].erase(j,v.size()); 
					clauses[i]=conversion2(clauses[i]);
					int a=0;
					while(clauses[i][a]==' ') a++;
					if(clauses[i][a]=='=') {
						string z=findthelastWord(clauses[i]);
						if(truthAssignments[z]==0) { 
							RightOfEmptyImp.push(z);
						}
					
					}


				}
				j++;

			}
		}

	}

	return truthAssignments;
} 

vector<string> selectClauses(vector<string> clause) {
	vector<string> sclause;
	for(int i=0;i<clause.size();i++) {
		for(int j=0;j<clause[i].size();j++) {
			if(clause[i][j]=='=') {
				sclause.push_back(clause[i]);
				break;
			}
		}
	}

	return sclause;
}

int main() {

	string filename;
	cout<<"Enter filename: ";
	cin>>filename;
	cout<<endl;

	ifstream file;
	file.open(filename.c_str());

	string line;
	string noOfVar;
	vector<string> clauses;
	vector<string> variables;
	map<string, int> TruthValues;

	getline(file,noOfVar);
	while(getline(file, line)) {
		line=conversion(line);
		clauses.push_back(line);

	}

	vector<string> selectiveClauses=selectClauses(clauses);

	int number=extracter(noOfVar);

	for(int i=1;i<number+1;i++) {
		variables.push_back('x'+numberToString(i));
	}


	TruthValues=hornyFormula(variables,selectiveClauses);

	//Just for checking
	map<string,int> ::iterator it;
	for(it=TruthValues.begin();it!=TruthValues.end();it++) {
		cout<<it->first<<" "<<it->second<<endl;
	}
	



	return 0;
}

