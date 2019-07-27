#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <climits>

//COMPLETED
using namespace std;

/*RECURRENCE RELATION 
	CUTTER(cut, 0) = 0
	CUTTER(cut, n) = n + CUTTER(cut[i]) + CUTTER(n-cut[i])
*/

/*TIME COMPLEXITY
	Let n be the length of ruler and m be the number of cuts. 
	Number of subproblems are m!(m factorial). For each subproblem, 
	it takes O(1) complexity. As it is an iterative memoized code, 
	the total time complexity is O(n^2*m).
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

bool searchvector(vector<int> v, int value) {
	for(int i=0;i<v.size();i++) {
		if(v[i]==value) return 1;
	}

	return 0;
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

int optimal(vector<int> cut, int n, vector<int> &fc) {
	int i,j;
	int bind=0;
	int a[n+1][n+1];
	for(int temp=1;temp<=n;temp++){
        for(i=0, j=i+temp;j<=n;j++,i++){
            if(temp==1)
                a[i][j]=0;
            else{
                int minSum = INT_MAX;
                for(int c=0;c<cut.size();c++){
                    if(cut[c]<j && cut[c] >i){
                        int cost=(j-i)+a[i][cut[c]]+a[cut[c]][j];

                        if(cost<minSum) {
                            minSum=cost;
                            fc.push_back(cut[c]);

                        }
                    }
                }
                if(minSum>=INT_MAX)
                a[i][j]=0;
                else {
                    a[i][j]=minSum;
                }
            }
        }
    }


    return a[0][n];
}


int main() {
	string filename;
	cout<<"Enter filename: ";
	cin>>filename;

	ifstream file;
	file.open(filename.c_str());
	string line;
	vector<int> Cuts;
	vector<int> Order;
	vector<vector<int>> par;
	vector<int> FinalCut;
	vector<int> FinalCutOrdering;

	if(file.fail()) cout<<"Error Reading File"<<endl;

	getline(file,line);
	int LengthOfRuler=numberOfInputs(line);

	getline(file,line);
	Cuts=converter(line);

	int final=optimal(Cuts,LengthOfRuler, FinalCut);

	for(int i=FinalCut.size()-1;i>=0;i--) {
		if(searchvector(FinalCutOrdering, FinalCut[i])) {}
		else {
			FinalCutOrdering.push_back(FinalCut[i]);
		}	
	}

	cout<<"Optimal cut ordering: ";
	for(int i=0;i<FinalCutOrdering.size();i++) {
		cout<<FinalCutOrdering[i]<<" ";
	}
	cout<<endl;	

	cout<<"Least Cost: "<<final<<endl;


	return 0;
}