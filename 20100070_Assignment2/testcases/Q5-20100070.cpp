#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <queue>

using namespace std;

//This is Question 5

//Only did Q5 part a, MST tree.

/*Time complexity of this algorithm is O(Elog(V)) as I have used prim's algorithm to calculate the minimum spanning tree. 
  The space complexity is O(n^2) */





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


vector<pair<string, int>> conversion(string line) {
	vector<pair<string, int>> final;
	string theword="";
	string thedistance="";
	
	bool baari=0;
	for(int i=0;i<line.size();i++) {
		if(line[i]==' ') {
			baari=0;
			if(theword=="") {}
			else {
				pair<string, int> jodi;
				jodi.first=theword;
				jodi.second=stringToNumber(thedistance);
				final.push_back(jodi);
			}

			theword="";
			thedistance="";

		}

		else {
			if(line[i]==':') theword="";
			else if(line[i]==',') {}
			else if(line[i]==';') baari=1;
			else {
				if(baari) thedistance+=line[i];
				else theword+=line[i];
			}	

		}
	}
	pair<string, int> jodi;
	jodi.first=theword;
	jodi.second=stringToNumber(thedistance);
	final.push_back(jodi);

	return final;


}

//Used prim's algorithm in this case
vector<int> MinSpanningTree(vector<vector<pair<int, int>>> graph) {
	vector<int> keys;
	for(int i=0;i<graph.size();i++) {
		keys.push_back(numeric_limits<int>::max());
	}

	vector<int> parents;
	for(int i=0;i<keys.size();i++) {
		parents.push_back(-1);
	}

	vector<int> MSTkeAndar;
	for(int i=0;i<keys.size();i++) {
		MSTkeAndar.push_back(0);
	}

	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

	int starter=0;
	pq.push(make_pair(0,starter));
	keys[starter]=0;

	while(!pq.empty()) {
		int u=pq.top().second;
		pq.pop();
		MSTkeAndar[u]=1;

		for(int i=0;i<graph[u].size();i++) {
			int vertice=graph[u][i].first;
			int weight=graph[u][i].second;

			if(MSTkeAndar[vertice]==0 && keys[vertice] > weight) {
				keys[vertice]=weight;
				pq.push(make_pair(keys[vertice],vertice));
				parents[vertice]=u;
			}
		}


	}

	return parents;

	
}  

void printingMST(vector<int> parents, vector<vector<pair<int,int>>> graph) {


	for(int i=0;i<parents.size();i++) {
		cout<<parents[i]<<endl;
	}

	cout<<endl;
	for(int i=1;i<parents.size();i++) {
		int val;
		cout<<"Edges:	";
		string v1="C"+ numberToString(parents[i]);
		string v2="C"+numberToString(i);
		cout<<"Vertex 1: "<<v1;
		cout<<" Vertex 2: "<<v2;
		for(int j=0;j<graph[parents[i]].size();j++) {
			if(graph[parents[i]][j].first==i) {
				val=graph[parents[i]][j].second;
				break;
			}
		}
		cout<<" Val: "<<val<<endl;

	}
}

int main() {
	string filename;
	cout<<"Enter Filename: ";
	cin>>filename;
	cout<<endl;

	ifstream file;
	file.open(filename.c_str());
	vector<vector<pair<string, int>>> graph;
	vector<vector<pair<int, int>>> myPerfectGraph;
	vector<int> baap;

	string line;
	getline(file,line);

	while(getline(file,line)) {
		vector<pair<string , int>> neighbors;
		neighbors=conversion(line);
		graph.push_back(neighbors);
	}

	for(int i=0;i<graph.size();i++) {
		vector<pair<int,int>> neighbors2;
		for(int j=0;j<graph[i].size();j++) {
			pair<int,int> pair;
			pair.first=stringToNumber(graph[i][j].first.erase(0,1));
			pair.second=graph[i][j].second;

			neighbors2.push_back(pair);
		}
		myPerfectGraph.push_back(neighbors2);
	}

		
	baap=MinSpanningTree(myPerfectGraph);
	printingMST(baap,myPerfectGraph);

	//Just for checking
	// for(int i=0;i<myPerfectGraph.size();i++) {
	// 	for(int j=0;j<myPerfectGraph[i].size();j++) {
	// 		cout<<myPerfectGraph[i][j].first<<" "<<myPerfectGraph[i][j].second<<endl;
	// 	}
	// 	cout<<endl;
	// }





	return 0;
}

