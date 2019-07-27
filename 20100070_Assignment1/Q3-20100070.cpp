#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

//Data Structure used is vector instead of priority queue. So the running time is O(n^2)
//Space complexity is O(n^2) as the maximum space is taken by vector<vector<string>> in the main function.

//Problem:
//This implementation does not work on the input L(number>9) and does not work with distances > 9.

int dijkstra(int start,int end, vector<vector<int>> neighnodes, vector<vector<int>> weightnodes) {
	vector<int> pq;
	vector<int> distances;
	vector<int> path;
	for(int i=0;i<neighnodes.size();i++) {
		if(i==start) distances.push_back(0);

		else distances.push_back(100000);
	}

	for(int i=0;i<distances.size();i++) {
		pq.push_back(distances[i]);
	}

	while(!pq.empty()) {
		sort(pq.rbegin(), pq.rend()); 
		int temp=pq[pq.size()-1];
		pq.pop_back();

		int index = find(distances.begin(), distances.end(), temp) - distances.begin();

		for(int i=0;i<neighnodes[index].size();i++) {
			if(distances[index] + weightnodes[index][i] < distances[neighnodes[index][i]]) {
				pq.erase(remove(pq.begin(), pq.end(), distances[neighnodes[index][i]]), pq.end());
				distances[neighnodes[index][i]]=distances[index] + weightnodes[index][i];
				pq.push_back(distances[neighnodes[index][i]]);
				path.push_back(neighnodes[index][i]);
				
			}
		}
	}

	for(int i=0;i<distances.size();i++) {
		cout<<distances[i]<<" ";
	}

	cout<<endl;

	return distances[end];


}

vector<vector<string>> conversion(vector<string> test, int a) {
	int c;
	if(a==1) c=0; 
	else c=1;

	vector<vector<string>> total;
	for(int i=0;i<test.size();i++) {
		vector<string> nodes;
		for (int j=c;j<test[i].length();j++) {
			if(test[i][j]=='C') {
				nodes.push_back(test[i].substr(j+a,1));
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

vector<vector<int>> neighbours(vector<int> a, vector<vector<string>> b, char u) {
	int c;
	if(u=='n') c=1;
	else c=0;
	vector<vector<int>> final;
	for(int i=0;i<a.size();i++) {
		vector<int> tt;
		for(int j=c;j<b[i].size();j++) {
			int temp=(int)(b[i][j][0])-48;
			tt.push_back(temp);
		}

		final.push_back(tt);
	}

	return final;
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
	vector<vector<int>> weightOfNode;
	vector<string> answer;
	
	vector<vector<string>> total;
 	while(getline(file,s)) {
		break;
	}

	while(getline(file,s)) {
		test.push_back(s);
	}

	vector<vector<string>> thenodes;
	vector<vector<string>> weights;



	thenodes=conversion(test,1);
	weights=conversion(test,3);

	individualNodes=noder(thenodes);
	neighbourNodes=neighbours(individualNodes,thenodes,'n');
	weightOfNode=neighbours(individualNodes,weights,'w');

	string h,f,sp;
	cout<<"Enter home city: ";
	cin>>h;
	cout<<endl;
	cout<<"Enter friend's city: ";
	cin>>f;
	cout<<endl;
	cout<<"Enter scenic spot: ";
	cin>>sp;
	cout<<endl;

	int home=(int)h[1]-48;
	int frend=(int)f[1]-48;
	int spot=(int)sp[1]-48;

	int direct=dijkstra(home,frend,neighbourNodes,weightOfNode);
	int indirect1=dijkstra(home,spot,neighbourNodes,weightOfNode);
	int indirect2=dijkstra(spot,frend,neighbourNodes,weightOfNode);

	if((indirect1+indirect2)>(1.2*direct)) {
		cout<<"Yes, the indirect path is more than 20 percent of the shortest distance."<<endl;	
		cout<<"Direct Path distance: "<<direct<<endl;
		cout<<"Indirect Path distance: "<<indirect1+indirect2<<endl;
	}

	else {
		cout<<"No, the indirect path is less than 20 percent of the shortest distance."<<endl;	
		cout<<"Direct Path distance: "<<direct<<endl;
		cout<<"Indirect Path distance: "<<indirect1+indirect2<<endl;
	}








	return 0;
}