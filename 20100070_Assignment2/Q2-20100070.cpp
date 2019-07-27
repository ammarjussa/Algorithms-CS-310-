#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>

using namespace std;

//This is Question 2

/* Proving the algorithm using the exchange argument(Done in seperate PDF) */


/*For this algorithm, I used vectors and pairs. The running time complexity of this algorithm is O(n) where 
  n is the number of locations where the vehicle might stop. The space complexity is also O(n) as I have used 
  only one-dimensional vectors. */


int stringToNumber(string s) {
	int num=0;
	stringstream converter(s);
	converter>>num;
	
	return num;
}

pair<string, int> linetopair(string line) {
	pair<string, int> final;
	string theword;
	string fst;
	for(int i=0;i<line.size();i++) {
		if(line[i]==' ') {
			fst=theword;
			theword="";
		}

		else theword+=line[i];
	}

	int snd=0;
	snd=stringToNumber(theword);

	final.first=fst;
	final.second=snd;

	return final;
}

vector<string> findstops(vector<pair<string, int>> locations, int tank, int rate) {
	int temp=tank;
	vector<string> stops;
	for(int i=locations.size()-1;i>0;i--) {
		int litConsumed=(locations[i].second-locations[i-1].second)*rate;
		if(litConsumed>temp) {
			stops.push_back(locations[i].first);
			temp=tank;
			i++;
		}
		else temp=temp-litConsumed;

	}

	reverse(stops.begin(),stops.end());
	return stops;

}

vector<float> findTimeAtStops(vector<pair<string, int>> locations, vector<string> stops, int tank, int rate, int filling) {
	int temp=tank;
	float time;
	int counter=0;
	int breaker=stops.size()-1;
	int carry=0;

	vector<float> timeAtStops;

	
	for(int i=0;i<locations.size()-1;i++) {
		int litConsumed=(locations[i+1].second-locations[i].second)*rate;
		if(locations[i].first==stops[counter]) {
			if(counter==breaker) {
				carry=i;
				break;
			}
			else {
				time=(float(tank)-float(temp))/float(filling);
				timeAtStops.push_back(time);
				temp=tank;
				i--;
				counter++;
			}
		}

		else temp=temp-litConsumed;

	}

	int litneeded=(locations[locations.size()-1].second-locations[carry].second)*rate;
	time=(float(litneeded)-float(temp))/float(filling);
	timeAtStops.push_back(time);

	return timeAtStops;
} 

void finalAnswer(vector<string> stops, vector<float> timeAtStops) {

	float totaltime=0.0;
	for(int i=0;i<timeAtStops.size();i++) {
		totaltime+=timeAtStops[i];
	}

	for(int i=0;i<timeAtStops.size()-1;i++) {
		cout<<stops[i]<<" "<<timeAtStops[i]<<", ";
	}

	cout<<stops[stops.size()-1]<<" "<<timeAtStops[timeAtStops.size()-1]<<endl;
	cout<<"Total Time: "<<totaltime<<endl;
}


int main() {
	string filename;
	cout<<"Enter filename: ";
	cin>>filename;
	cout<<endl;

	ifstream file;
	file.open(filename.c_str());
	vector<pair <string, int> > essentials;
	vector<pair <string, int> > locations;
	pair<string,int> a=make_pair("S",0);
	locations.push_back(a);

	int i=0;
	string line;

	while(i<4) {
		getline(file,line);
		pair<string, int> thepair;
		thepair=linetopair(line);
		essentials.push_back(thepair);
		i++;
	}

	while(getline(file,line)) {
		pair<string,int> thepair;
		thepair=linetopair(line);
		locations.push_back(thepair);
	}

	int tank=essentials[0].second;
	int rate=essentials[1].second;
	int filling=essentials[2].second;
	int n=essentials[3].second;

	
	vector<string> stops;
	vector<float> timeAtStops;

	//Identifying stops to take during the route
	stops=findstops(locations,tank,rate);
	
	//Going through the path and stopping at each stop found above and finding time taken at each stop
	timeAtStops=findTimeAtStops(locations,stops,tank, rate, filling);


	//final answer
	finalAnswer(stops, timeAtStops);
	
	return 0;
}
