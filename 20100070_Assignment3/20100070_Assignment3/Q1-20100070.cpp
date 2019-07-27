#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/*For this question, there are two tables, one of planes and one of airport. So I traversed each plane in the table,
  and applied the gale shapley and made pairs until every plane has an airport. It takes O(n^2) time and space complexity.*/

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

pair<int,int> parser(string line) {
	int i=0;
	pair<int,int> thepair;
	size_t b=line.find_last_of(' ');
	thepair.first=stringToNumber(line.substr(1,b));
	thepair.second=stringToNumber(line.substr(b+2));

	return thepair;
}

vector<int> breaker(string line) {
	vector<int> temp;
	int i=0;
	while(line[i]!=':') i++;
	i=i+2;
	int a=i;
	for(int j=i;j<line.size();j++) {
		if(line[j]==',') {
			temp.push_back(stringToNumber(line.substr(a+1,j-a)));
			a=j+2;
		}
	}

	temp.push_back(stringToNumber(line.substr(a+1,line.size()-a)));
	return temp;
}

vector<pair<int,int>> Pairer(string line) {
	vector<pair<int,int>> pairs;
	int i=3;
	int a=i;

	for(int j=i;j<line.size();j++) {
		if(line[j]==',') {
			pair<int,int> thepair=parser(line.substr(a,j-a));
			pairs.push_back(thepair);
			a=j+2;
		}
	}

	pair<int,int> thepair=parser(line.substr(a,line.size()));
	pairs.push_back(thepair);

	return pairs;
}

bool PreferNewOverCurrent(vector<vector<int>> Airports, int theairport, int neww, int previous) {
	for(int i=0;i<Airports.size();i++) {
		if(Airports[theairport][i]==neww) { return 1; break; }
		else if(Airports[theairport][i]==previous) { return 0; break;}
	}
}

bool NoPairConflict(vector<pair<int,int>> EPair, int airport, int plane) {
	for(int i=0;i<EPair.size();i++) {
		if(EPair[i].first==plane && EPair[i].second==airport) 
			return 0;
		
	}

	return 1;
}

vector<int> finalPairing(vector<vector<int>> Planes, vector<vector<int>> Airports, vector<pair<int,int>> ExcludedPair) {
	vector<bool> PlanesFree;
	for(int i=0;i<Planes.size();i++) {
		PlanesFree.push_back(0);
	}

	PlanesFree[0]=1;

	vector<int> AirportPair;
	for(int i=0;i<Airports.size();i++) {
		AirportPair.push_back(-1);
	}

	AirportPair[0]=-100000;

	int NoOfFreePlanes=Planes.size()-1;

	while(NoOfFreePlanes>0) {
		int pl;
		for(pl=1;pl<PlanesFree.size();pl++) {
			if(PlanesFree[pl]==0) 
				break;
		}

		for(int i=0;i<Planes.size() && PlanesFree[pl]==0;i++) {
			int air=Planes[pl][i];

			if(AirportPair[air]==-1) {
				AirportPair[air]=pl;
				PlanesFree[pl]=1;
				NoOfFreePlanes--;
			}

			else {
				int pl2=AirportPair[air];
				if(PreferNewOverCurrent(Airports, air, pl,pl2)==1) {
					if(NoPairConflict(ExcludedPair,air, pl)) {
						AirportPair[air]=pl;
						PlanesFree[pl]=1;
						PlanesFree[pl2]=0;
						
					}
					
				}
			}
		}
 	}

 	return AirportPair;
}

void PrintThePairsOut(vector<int> Airpair) {
	for(int i=1;i<Airpair.size()-1;i++) {
		cout<<'A'+numberToString(i)<<" "<<'P'+numberToString(Airpair[i])<<", ";
	}
	cout<<'A'+numberToString(Airpair.size()-1)<<" "<<'P'+numberToString(Airpair[Airpair.size()-1])<<endl;
}

int main() {
	string filename;
	cout<<"Enter Filename: ";
	cin>>filename;
	ifstream file;
	file.open(filename.c_str());

	string line;

	getline(file,line);
	int n=numberOfInputs(line);

	vector<vector<int>> Planes;
	vector<vector<int>> Airports;
	vector<pair<int,int>> ExcludedPair;

	vector<int> tempo;
	tempo.push_back(-1111);
	Planes.push_back(tempo);
	Airports.push_back(tempo);

	for(int i=0;i<n;i++) {
		getline(file,line);
		vector<int> dup=breaker(line);
		Planes.push_back(dup);
	}

	for(int i=0;i<n;i++) {
		getline(file,line);
		vector<int> dup=breaker(line);
		Airports.push_back(dup);
	}

	getline(file,line);
	ExcludedPair=Pairer(line);

	vector<int> finalPair=finalPairing(Planes, Airports, ExcludedPair);

	PrintThePairsOut(finalPair);


	
	//Handle the pair conflict, rest of it is working. 
	


	// //Just for checking
	// for(int i=1;i<Planes.size();i++) {
	// 	for(int j=0;j<Planes[i].size();j++) {
	// 		cout<<Planes[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }

	// cout<<endl;	

	// for(int i=1;i<Airports.size();i++) {
	// 	for(int j=0;j<Airports[i].size();j++) {
	// 		cout<<Airports[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }

	// cout<<endl;

	// for(int i=0;i<ExcludedPair.size();i++) {
	// 	cout<<ExcludedPair[i].first<<" "<<ExcludedPair[i].second<<endl;
	// }
	


	return 0;
}