#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

/* For this question, I made a Location table from the Team and its preferences and did the same thing as question 1.
	The time and space complexity is O(n^2)*/
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

string dashchecker(string line) {
	for(int i=0;i<line.size();i++) {
		if(line[i]==':') {
			if(line[i+2]=='-') return "even";
			else return "odd";
			break;
		}	
	}
}

vector<vector<string>> wordDivider(vector<string> word, int n) {
	vector<vector<string>> theword;
 	vector<string> w;
	int temp=0;
 	for(int i=0;i<word.size();i++) {
 		if(temp==n) {
 			theword.push_back(w);
 			w.clear();
 			temp=0;
 			i--;
 		}

 		else {
 			w.push_back(word[i]);
 			temp++;
 		}
	}

	theword.push_back(w);


	return theword;
}

vector<pair<string, vector<string>>> teamMaker(vector<vector<string>> word, vector<string> alldashing) {
	vector<pair<string, vector<string>>> Final;
	for(int i=0;i<word.size();i++) {
		vector<string> vec;
		string t;
		for(int j=0;j<word[i].size();j++) {
			if(word[i][j][0]=='T') {
				t=word[i][j].substr(0, word[i][j].size()-2);
			}

			else {
				if(alldashing[i]=="even") {
					vec.push_back("-");
					vec.push_back(word[i][j]);
				}

				else if(alldashing[i]=="odd") {
					vec.push_back(word[i][j]);
					vec.push_back("-");
				}
			}

			
		}

		Final.push_back(make_pair(t,vec));
	}

	return Final;
}

vector<pair<string, vector<string>>> initializeLocations(int n) {
	vector<pair<string, vector<string>>> locations;
	vector<string> l;
	string t;
	for(int i=1;i<n+1;i++) {
		t='L'+numberToString(i);
		locations.push_back(make_pair(t,l));
	}

	return locations;

}

void setUpLocation(vector<pair<string, vector<string>>>& locations, vector<pair<string, vector<string>>> Teams) {
	for(int i=0;i<locations.size();i++) {
		int n=Teams[0].second.size()-1;
		string line=locations[i].first;
		while(n>=0) {
			for(int j=0;j<Teams.size();j++) {
				if(Teams[j].second[n]==line) {
					locations[i].second.push_back(Teams[j].first);
				}
			}

			n--;
		}
	}
}

int indexOfTeam(string team, vector<pair<string, vector<string>>> Teams) {
	for(int i=0;i<Teams.size();i++) {
		if(Teams[i].first==team) 
			return i;
	}
}

int indexOfLocation(string l, vector<pair<string, vector<string>>> locations) {
	for(int i=0;i<locations.size();i++) {
		if(locations[i].first==l) 
			return i;
	}
}

bool PreferNewOverCurrent(vector<pair<string, vector<string>>> Teams, int index, string loc, string loc2) {
	vector<string> temp=Teams[index].second;
	for(int i=0;i<temp.size();i++) {
		if(temp[i]==loc) {
			return 1;
			break;
		}

		else if(temp[i]==loc2) {
			return 0;
			break;
		}
	}
}

vector<pair<string,string>> FinalPairing(vector<pair<string, vector<string>>>& locations, vector<pair<string, vector<string>>> Teams){

	vector<bool> Locationfree;
	vector<string> teamPaired;
	for(int i=0;i<locations.size();i++) {
		Locationfree.push_back(0);
	}

	for(int i=0;i<Teams.size();i++) {
		teamPaired.push_back(" ");
	}

	int free=Locationfree.size()-1;
	while(free>=0) {
		int pl;
		for(pl=0;pl<Locationfree.size();pl++) {
			if(Locationfree[pl]==0) break;
		}

		string loc=locations[pl].first;
		vector<string> theteams=locations[pl].second;

		for(int i=0;i<theteams.size() && Locationfree[pl]==0;i++) {
			string theT=theteams[i];
			int index=indexOfTeam(theT, Teams);

			if(teamPaired[index]==" ") {
				teamPaired[index]=loc;
				Locationfree[pl]=1;
				free--;
			}

			else {
				string loc2=teamPaired[index];
				if(PreferNewOverCurrent(Teams, index, loc, loc2)==1) {
					teamPaired[index]=loc;
					Locationfree[pl]=1;
					Locationfree[indexOfLocation(loc2,locations)]=0;
				}
				
			}

		}
	}

	vector<pair<string,string>> finalPair;
	for(int i=0;i<teamPaired.size();i++) {
		finalPair.push_back(make_pair(teamPaired[i], Teams[i].first));
	}

	return finalPair;

}




int main() {
	string filename;
	cout<<"Enter Filename: ";
	cin>>filename;

	ifstream file;
	file.open(filename.c_str());

	string line;
	vector<string> word;
	string dashing;
	vector<string> alldashing;

	getline(file, line);
	int n=numberOfInputs(line);

	while(getline(file,line)) {
		size_t prev=0, pos;
		while((pos= line.find_first_of("-,",prev)) != std::string::npos) {
			if(pos > prev) 
				word.push_back(line.substr(prev, pos-prev));
			prev=pos+1;
		}

		if(prev < line.length()) 
			word.push_back(line.substr(prev, std::string::npos));

		dashing=dashchecker(line);
		alldashing.push_back(dashing);
	}



	vector<vector<string>> theword=wordDivider(word, n+1);

	vector<pair<string, vector<string>>> Teams;
	Teams=teamMaker(theword, alldashing);

	vector<pair<string, vector<string>>> Locations;

	Locations=initializeLocations(n);

	setUpLocation(Locations, Teams);

	vector<pair<string,string>> thePair; 
	thePair=FinalPairing(Locations, Teams);

	//Just for checking
	cout<<"Final Destinations: ";
	for(int i=0;i<thePair.size()-1;i++) {
		cout<<thePair[i].first<<" "<<thePair[i].second<<", ";
	}

	cout<<thePair[thePair.size()-1].first<<" "<<thePair[thePair.size()-1].second<<endl;
 


	return 0;
}