#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std; 
//The time complexity of this algorithm is O(nlogn) as I have used a divide and conquer algorithm inside a loop function.
//Space is O(n) to store photos with species.
/* Recurrence Relation: 
		T(n)=T(n/2)+O(1)*/

string numberToString(int n) {
	stringstream ss;
	ss << n;
	string str = ss.str();

	return str;
}

vector<string> initializePhotos(int n) {
	vector<string> photos;
	for(int i=0;i<n;i++) {

		photos.push_back('P'+numberToString(i));
	}

	return photos;
}

vector<char> initializeSpecies(int m) {
	vector<char> species;
	for(int i=0;i<m;i++) {
		char c=i+65;
		species.push_back(c);
	}

	return species;

}

vector<pair<string,char>> assigner(vector<string> photos, vector<char> species) {
	vector<pair<string,char>> p;
	srand(time(NULL));
	for(int i=0;i<photos.size();i++) {
		pair<string,char> thepair;
		thepair.first=photos[i];
		int num=(rand() % species.size())+0;
		thepair.second=species[num];

		p.push_back(thepair);
	}

	return p;
}

char decode(pair<string,char> photo1, pair<string,char> photo2) {
	if(photo1.second==photo2.second) {
		return 'Y';
	}

	else return 'N';
}
	
bool sortBySpe(const pair<string,char> &a, const pair<string, char> &b) {
	return (a.second < b.second);
}


//Divide and Conquer
int binarySearch(vector<pair<string,char>> species, int low, int high, pair<string, char> photo) {
	if(high>=low) {
		int mid=(low+high)/2;

		if((mid==0 || sortBySpe(species[mid-1], photo)) && decode(species[mid], photo)=='Y')
			return mid;
		else if(sortBySpe(species[mid], photo)) 
			return binarySearch(species, mid+1, high, photo);
		else
			return binarySearch(species, low, mid-1, photo);

	}

	return -1;
}

bool isMajority(vector<pair<string,char>> species, pair<string,char> thephoto) {
	int n=species.size();
	int index=binarySearch(species, 0, n-1, thephoto);
	if(index==-1) return false;

	if(((index+n/2)<=(n-1)) && decode(species[index+n/2], thephoto)=='Y') 
		return true;
	else return false;
}

bool isvisited(vector<pair<string, char>> v, pair<string, char> photo) {
	for(int i=0;i<v.size();i++) {
		if(decode(v[i],photo)=='Y') 
			return true;
	}

	return false;
}

string MajorityChecker(vector<pair<string,char>> species) {
	vector<pair<string,char>> visited;
	for(int i=0;i<species.size();i++) {
		if(isvisited(visited,species[i])==0) {
			bool decision=isMajority(species, species[i]);
			visited.push_back(species[i]);
			if(decision==true) return "success";
		}
		
	}

	return "failure";
}

int main() {

	int n,m;
	cout<<"Enter the number of photos: ";
	cin>>n;
	cout<<"Enter number of species: ";
	cin>>m;

	vector<string> photos;
	photos=initializePhotos(n);

	vector<char> species;
	species=initializeSpecies(m);

	vector<pair<string,char>> ActualPhotosWithSpecies;
	ActualPhotosWithSpecies=assigner(photos,species);

	//just for checking


	for(int i=0;i<ActualPhotosWithSpecies.size();i++) {
		cout<<ActualPhotosWithSpecies[i].first<<" "<<ActualPhotosWithSpecies[i].second<<endl;
	}

	cout<<endl<<endl;

	sort(ActualPhotosWithSpecies.begin(), ActualPhotosWithSpecies.end(),sortBySpe);

	string finale=MajorityChecker(ActualPhotosWithSpecies);

	cout<<finale<<endl;





	return 0;
}