#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <vector>


using namespace std;

//Data structure used vectors of vectors(ajdacency list)
//Implemented BFS with time complexity O(V+E), where V is number of nodes and E is number of edges
//Space complexity is O(n^2) as the maximum space is taken by vector<vector<string>> in the main function.

//Problem:
//		This implementation does not work on the input C(number>9)

vector<string> decisionMaker(bool decision, vector<char> color) {
	vector<string> answer;
	string a="";
	string b="";
	if(decision) {
		vector<int> red;
		vector<int> blue;
		answer.push_back("Yes");
		for(int i=0;i<color.size();i++) {
			if(color[i]=='R') {
				red.push_back(i);
			}

			else blue.push_back(i);
		}

		if(red.size()>1) {
			for(int i=0;i<red.size()-1;i++) {
				a=a+'C'+(char)(red[i]+48)+ ", "; 

			}
		}

		a=a+'C'+(char)(red[red.size()-1]+48);

		if(blue.size()>1) {
			for(int i=0;i<blue.size()-1;i++) {
				b=b+'C'+(char)(blue[i]+48)+ ", "; 

			}
		}

		b=b+'C'+(char)(blue[blue.size()-1]+48);

		answer.push_back(a);
		answer.push_back(b);

		return answer;


	}

	else {
		answer.push_back("No");
		//Some of the code is left
		return answer;
	}
}


vector<vector<string>> conversion(vector<string> test) {

	vector<vector<string>> total;
	for(int i=0;i<test.size();i++) {
		vector<string> nodes;
		for (int j=0;j<test[i].length();j++) {
			if(test[i][j]=='C') {
				nodes.push_back(test[i].substr(j+1,1));
			}
		}

		total.push_back(nodes);
	}
	return total;	
}

vector<int> noder(vector<vector<string>> a) {
	vector<int> hello;
	for(int i=0;i<a.size();i++) {
		int b=(int)(a[i][0][0])-48;
		hello.push_back(b);

	}

	return hello;
}

vector<vector<int>> neighbours(vector<int> a, vector<vector<string>> b) {
	vector<vector<int>> final;
	for(int i=0;i<a.size();i++) {
		vector<int> tt;
		for(int j=1;j<b[i].size();j++) {
			int temp=(int)(b[i][j][0])-48;
			tt.push_back(temp);
		}

		final.push_back(tt);
	}

	return final;
}

vector<string> colorChecker(vector<int> indinode,vector<vector<int>> neinode) {
	vector<string> answer;
	bool decision=true;
	bool alert=false;
	vector<bool> visited;
	for(int i=0;i<indinode.size();i++) {
		visited.push_back(0);
	}

	vector<char> color;

	for(int i=0;i<indinode.size();i++) {
		color.push_back('O');
	}

	queue<int> thequeue;

	thequeue.push(indinode[0]);
	color[indinode[0]]='R';
	visited[indinode[0]]=1;

	while(!thequeue.empty()) {
		int temp=thequeue.front();
		if(!neinode[temp].empty()) {
			for(int i=0;i<neinode[temp].size();i++) {
				if(visited[neinode[temp][i]]==0 and color[neinode[temp][i]]=='O') {
					thequeue.push(neinode[temp][i]);
					visited[neinode[temp][i]]=1;
					color[neinode[temp][i]]= (color[temp]=='R') ? 'B':'R';
				}

				else if(visited[neinode[temp][i]]==1) {
					if(color[temp]==color[neinode[temp][i]]) {
						alert=true;
						decision=false;
						break;
					}
				}
			}

		}

		if (alert) break;

		thequeue.pop();

	}

	cout<<endl;

	answer=decisionMaker(decision,color);
	return answer;

}









int main() {
	string filename;
	cout<<"Enter filename: ";
	cin>>filename;
	ifstream file;
	file.open(filename.c_str());
	string s;
	vector<string> test;
	vector<int> individualNodes;
	vector<vector<int>> neighbourNodes;
	vector<string> answer;
	
	vector<vector<string>> total;
 	while(getline(file,s)) {
		break;
	}

	while(getline(file,s)) {
		test.push_back(s);
	}

	vector<vector<string>> thenodes;

	thenodes=conversion(test);
	individualNodes=noder(thenodes);
	neighbourNodes=neighbours(individualNodes,thenodes);


	answer=colorChecker(individualNodes,neighbourNodes);  

	for(int i=0;i<answer.size();i++) {
		cout<<answer[i]<<endl;
	}
	





		
	return 0;	
}
 