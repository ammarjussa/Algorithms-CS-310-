#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

//This is Question 4

/*Time complexity of my algorithm is O(n) as my calculation function works in linear time. The space complexity
   is O(n)*/
template<class T>
T stringToNumber(string s) {
	T num=0;
	stringstream converter(s);
	converter>>num;
	
	return num;
}

template<class T>
vector<T> converter(string line) {
	vector<T> final;
	string theword="";
	for(int i=0;i<line.size();i++) {
		if(line[i]==' ') {
			if(theword=="L"|| theword=="p") {}
			else {
				final.push_back(stringToNumber<T>(theword));
			}
			theword="";
		}

		else {
			if(line[i]!=',') theword+=line[i];
		}
	}
	final.push_back(stringToNumber<T>(theword));

	return final;
}

vector<pair<int,float>> makingPair(vector<int> r, vector<float> p) {
	vector<pair<int,float>> RackProb;
	for(int i=0;i<r.size();i++) {
		pair<int,float> rp=make_pair(r[i],p[i]);
		RackProb.push_back(rp);
	}

	return RackProb;
}

vector<pair<string, int>> NamingRacks(vector<int> racks) {
	vector<pair<string,int>> theRacks;
	string r="rack";
	for(int i=0;i<racks.size();i++) {
		string abc=r+(char)((i+1)+48);
		pair<string,int> pairing=make_pair(abc,racks[i]);
		theRacks.push_back(pairing);
	}

	return theRacks;
}

float calculateTime(vector<pair<int,float>> RackProb) {
	float expectedTime=0;
	int sum=0;
	for(int i=0;i<RackProb.size();i++) {
		sum+=RackProb[i].first;
		expectedTime+=RackProb[i].second*(float)sum;
	}

	return expectedTime;
}

string findName(int r, vector<pair<string, int>> RackNames) {
	for(int i=0;i<RackNames.size();i++) {
		if(RackNames[i].second==r) {
			return RackNames[i].first;
			break;
		}
	}
}

void finalAnswer(float time, vector<pair<int,float>> Racks, vector<pair<string, int>> RackNames) {
	vector<string> namesOfRack;
	for(int i=0;i<Racks.size();i++) {
		namesOfRack.push_back(findName(Racks[i].first,RackNames));
	}

	for(int i=0;i<namesOfRack.size();i++) {
		cout<<namesOfRack[i]<<endl;
	}

	for(int i=0;i<namesOfRack.size()-1;i++) {
		cout<<namesOfRack[i]<<", ";
	}

	cout<<namesOfRack[namesOfRack.size()-1]<<endl;
	cout<<"Expected Time: "<<time<<endl;
}

bool comparer1(pair<int, float>& ele1, pair<int, float>& ele2) {
	return float(ele1.first)/ele1.second < float(ele2.first)/ele2.second;
}



int main() {
	string filename;
	cout<<"Enter Filename: ";
	cin>>filename;
	cout<<endl;

	ifstream file;
	file.open(filename.c_str());
	vector<int> racks;
	vector<float> probabilities;
	vector<pair<string, int>> RackNames; 

	string line;
	getline(file,line);

	int i=0;
	while(getline(file,line)) {
		if(i==0) racks=converter<int>(line);
		else probabilities=converter<float>(line);
		i++;
	}

	vector<pair<int,float>> RackProb= makingPair(racks,probabilities);
	RackNames=NamingRacks(racks);

	sort(RackProb.begin(),RackProb.end(),comparer1);

	float time=calculateTime(RackProb);



	finalAnswer(time,RackProb,RackNames);


	//Just for checking
	

	return 0;
}

