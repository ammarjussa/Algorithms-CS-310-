#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stack>
#include <algorithm>
#include <vector>

using namespace std;

//Data structure used vectors of vectors(ajdacency list)
//Implemented DFS with time complexity O(V+E), where V is number of nodes and E is number of edges
//Space complexity is O(n^2) as the maximum space is taken by vector<vector<string>> in the main function.


//Problem:
//		This implementation does not work on the input L(number>9)

vector<vector<string>> conversion(vector<string> test) {

	vector<vector<string>> total;
	for(int i=0;i<test.size();i++) {
		vector<string> nodes;
		for (int j=0;j<test[i].length();j++) {
			if(test[i][j]=='L') {
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

void grudgeCheckerLine(int starter, vector<vector<int>> neinode, vector<bool> &visited, vector<char> &color, bool &cycle, vector<int> &answer) { 
	stack<int> mystack;

	visited[starter]=1;
	mystack.push(starter);
	color[starter]='R';

	while(!mystack.empty()) {
		int temp=mystack.top();
		if(!neinode[temp].empty()) {
			for(int i=0;i<neinode[temp].size();i++) {
				if(!visited[neinode[temp][i]] && color[neinode[temp][i]]=='O') {
					mystack.push(neinode[temp][i]);
					visited[neinode[temp][i]]=1;
					color[neinode[temp][i]]='R';
					break;
				}

				else if(visited[neinode[temp][i]]) {
					if(color[neinode[temp][i]]=='R') {
						cycle=true;
						break;
					}
				}
			}

			if(mystack.top()==temp && cycle==false) {
				mystack.pop();
				color[temp]='B';
				answer.push_back(temp);

			}

			if(cycle) break;	
		}

		else {
			mystack.pop();
			color[temp]='B';
			answer.push_back(temp);
		}

	}

	if(cycle) {
		answer.clear();
		for(int i=0;i<color.size();i++) {
			if(color[i]=='R') {
				answer.push_back(i);
			}
		}

		answer.push_back(answer[0]);

	}
}

void leveler(int &temp, vector<vector<int>> neinode, vector<int> &levels) {
	if(neinode[temp].empty()) {
		return;
	}

	int lo;

	for(int i=0;i<neinode[temp].size();i++) {
		lo=neinode[temp][i];
		if(levels[temp]==levels[lo]) {
			levels[lo]=levels[temp]+1;
			temp=lo;
			break;
		}
	}



	if(temp==lo) {
		leveler(temp,neinode,levels);
	}

	else return;


}

void grudgeCheckerLevel(int starter, vector<vector<int>> neinode, vector<bool> &visited, vector<char> &color, bool &cycle, vector<vector<int>> &answer, vector<int> &levels) {
	stack<int> mystack;

	visited[starter]=1;
	mystack.push(starter);
	color[starter]='R';

	while(!mystack.empty()) {
		int temp=mystack.top();
		if(!neinode[temp].empty()) {
			for(int i=0;i<neinode[temp].size();i++) {
				if(!visited[neinode[temp][i]] && color[neinode[temp][i]]=='O') {
					mystack.push(neinode[temp][i]);
					visited[neinode[temp][i]]=1;
					color[neinode[temp][i]]='R';
					levels[neinode[temp][i]]=levels[temp]+1;
					break;
				}

				else if(visited[neinode[temp][i]]) {
					if(color[neinode[temp][i]]=='R') {
						cycle=true;
						break;
					}

					else if(color[neinode[temp][i]]=='B') {
						if(levels[temp]==levels[neinode[temp][i]]) {
							int a=neinode[temp][i];
							levels[neinode[temp][i]]=levels[temp]+1;
							leveler(a,neinode,levels);

						}
					}
				}
			}



			if(mystack.top()==temp && cycle==false) {
				mystack.pop();
				color[temp]='B';				

			}

			if(cycle) break;	
		}

		else {
			mystack.pop();
			color[temp]='B';
		}

	}

	for(int i=0;i<levels.size();i++) {
		cout<<levels[i]<<" ";
	}

	cout<<endl;

	if(equal(visited.begin()+1,visited.end(),visited.begin())) {

		int max_level=-1;
		for(int i=0;i<levels.size();i++) {
			if(levels[i]>max_level) {
				max_level=levels[i];
			}
		}

		

		for(int i=0;i<max_level+1;i++) {
			vector<int> a;
			answer.insert(answer.begin()+i,a);
		}


		for(int i=0;i<levels.size();i++) {
			vector<int> a;
			if(answer[levels[i]].empty()) {
				a.push_back(i);
				answer.at(levels[i])=a;
			}

			else {
				for(int j=0;j<answer[levels[i]].size();j++) {
					a.push_back(answer[levels[i]][j]);
				}
				a.push_back(i);
				answer.at(levels[i])=a;
			}
		}

	}	



}





vector<string> display(bool cycle, vector<int> answer1,vector<vector<int>> answer2, char part) {
	vector<string> final;
	
	if(part=='a') {

		if(!cycle) {
			final.push_back("Yes");
			string a="";
			for(int i=answer1.size()-1;i>0;i--) {
				a=a+'L'+(char)(answer1[i]+48)+", ";
			}

			a=a+'L'+(char)(answer1[0]+48);

			final.push_back(a);

		}

		else {
			final.push_back("No");
			string a="";
			for(int i=0;i<answer1.size()-1;i++) {
				a=a+'L'+(char)(answer1[i]+48)+"->";
			}

			a=a+'L'+(char)(answer1[answer1.size()-1]+48);

			final.push_back(a);
		}

		return final;
	}

	else {
		if(cycle) {
			final.push_back("No");

		}

		else {
			final.push_back("Yes");
			for(int i=0;i<answer2.size();i++) {
				string a="";
				for(int j=0;j<answer2[i].size()-1;j++) {
					a=a+'L'+(char)(answer2[i][j]+48)+", ";
				}

				a=a+'L'+(char)(answer2[i][answer2[i].size()-1]+48);
				final.push_back(a);

			}
		}

		return final;
	}

}






vector<string> Final(vector<int> indinode, vector<vector<int>> neinode, char part) {
	vector<bool> visited;
	vector<int> answer1;
	vector<vector<int>> answer2;
	vector<string> final;
	bool cycle=false;

	for(int i=0;i<indinode.size();i++) {
		visited.push_back(0);
	}

	vector<char> color;

	for(int i=0;i<visited.size();i++) {
		color.push_back('O');
	}

	vector<int> levels;

	for(int i=0;i<visited.size();i++) {
		levels.push_back(0);
	}

	if(part=='a') {
		for(int i=0;i<visited.size();i++) {
			if(!visited[i] && cycle==false) {
				grudgeCheckerLine(i, neinode, visited,color,cycle,answer1);
			}
		}
	}

	else {
		for(int i=0;i<visited.size();i++) {
			if(!visited[i] && cycle==false) {
				grudgeCheckerLevel(i,neinode,visited,color,cycle,answer2,levels);
			}
		}
	}



	

	final=display(cycle,answer1,answer2,part);

	return final;


}

int main() {
	string filename;
	char which_part;
	cout<<"Enter filename: ";
	cin>>filename;
	cout<<endl;
	cout<<"Which part of Question2: ";
	cin>>which_part;
	cout<<endl;
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
	answer=Final(individualNodes,neighbourNodes,which_part);

	for(int i=0;i<answer.size();i++) {
		cout<<answer[i]<<endl;
	}


	return 0;
}