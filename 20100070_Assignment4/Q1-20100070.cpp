#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

//COMPLETED
using namespace std;

/*RECURRENCE RELATION
	JOB(high, low, 0)=0 
	JOB(high, low, n)= max(high[n-1] + JOB(high, low, n-2),
						   low[n-1] + JOB(high, low, n-1))
*/

/*TIME COMPLEXITY
	There are n subproblems and as this code is a memoized
	code, each subproblem takes O(1) time, therefore, total
	time complexity is O(n).
*/


int stringToNumber(string s) {
	int num=0;
	stringstream converter(s);
	converter>>num;
	
	return num;
}

string numberToString(int n) {
	stringstream ss;
	ss << n;
	string str = ss.str();

	return str;
}

int numberOfInputs(string line) {
	size_t b=line.find_last_of(' ');
	return stringToNumber(line.substr(b+1));
}

vector<int> converter(string line) {
	vector<int> Rev;
	string word="";
	for(int i=3;i<line.size();i++) {
		if(line[i]==' ') {
			Rev.push_back(stringToNumber(word));
			word="";
		}

		else word+=line[i];
	}

	Rev.push_back(stringToNumber(word));
	return Rev;

}

int JobsinWeeks(vector<int> &memo, vector<int> high, vector<int> low, int n, vector<pair<char, int>>& jw) {
	if(n<=0) return 0;

	if(memo[n]!=-1000) return memo[n];

	int a= high[n-1] + JobsinWeeks(memo, high, low, n-2, jw);
	int b=low[n-1] + JobsinWeeks(memo, high, low, n-1, jw);
	
	if(a > b) {
		jw.push_back(make_pair('H', a));
		memo[n]=a;
		return memo[n];
	}

	else {
		jw.push_back(make_pair('L', b));
		memo[n]=b;
		return memo[n];
	}
}

vector<pair<char, int>> setThisJob(vector<pair<char,int>> jw, int n) {
	vector<pair<char,int>> js;
	for(int i=jw.size()-1;i>=jw.size()-n+1;i--) {
		js.push_back(make_pair(jw[i].first, jw[i].second-jw[i-1].second));
	}

	js.push_back(make_pair(jw[jw.size()-n].first, jw[jw.size()-n].second));

	return js;
}

vector<string> finalAnswer(vector<pair<char, int>> js) {
	vector<string> answer;

	for(int i=0;i<js.size();i++) {
		if(js[i].first=='L') 
			answer.push_back("Low "+ numberToString(js[i].second));

		else {
			if(i==js.size()-1) 
				answer.push_back("High "+ numberToString(js[i].second));
			
			else {
				answer.push_back("High "+ numberToString(js[i].second + js[i+1].second));
				answer.push_back("Priming");
				i++;
			}
		}
	}

	return answer;
}

int main() {
	string filename;
	cout<<"Enter filename: ";
	cin>>filename;

	ifstream file;
	file.open(filename.c_str());
	string line;
	vector<int> RevenueLow;
	vector<int> RevenueHigh;

	if(file.fail()) cout<<"Error Reading File"<<endl;

	getline(file,line);
	int n=numberOfInputs(line);


	getline(file,line);
	RevenueHigh=converter(line);

	getline(file,line);
	RevenueLow=converter(line);

	vector<pair<char, int>>	 jobweek;
	vector<pair<char, int>> jobsetter;
	vector<string> answer;

	vector<int> memo;
	for(int i=0;i<n+1;i++) {
		memo.push_back(-1000);
	}

	int totalRevenue=JobsinWeeks(memo, RevenueHigh, RevenueLow, n, jobweek);
	jobsetter=setThisJob(jobweek, n);

	answer=finalAnswer(jobsetter);

	reverse(answer.begin(), answer.end());

	for(int i=0;i<answer.size();i++) {
		cout<<"Week "<<i+1<<": "<<answer[i]<<endl;
	}

	cout<<"Total Revenue: "<<totalRevenue<<endl;


	return 0;
}




