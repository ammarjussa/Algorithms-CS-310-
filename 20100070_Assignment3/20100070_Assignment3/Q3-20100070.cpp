#include <iostream>
#include <vector>

using namespace std; 

/* The running time complexity is O(n^2) as we have to add the alphabets in every index. Space is also O(N^2)
	Recurrence relation: 
	T(i,j)=2T(i/2,j/2)+O(1)*/

int alp=0;

vector<vector<char>> initializeTheBoard(int size) {
	vector<vector<char>> board;
	for(int i=0;i<size;i++) {
		vector<char> row;
		for(int j=0;j<size;j++) {
			row.push_back('/');
		}

		board.push_back(row);
	}

	return board;
}



pair<int, int> findthebox(vector<vector<char>> board, int r, int c, int n) {
	for(int i=r;i<=n;i++) {
		for(int j=c; j<=n;j++) {
			if(board[i][j]!='/')
				return make_pair(i,j);

		}
	}

}

void placeTheBoomerang(vector<vector<char>> &board, pair<int, int> coord, int r, int c, int n) {
	char ch=alp+65;
	int mr=n/2-1+r;
	int mc=n/2-1+c;
	

	if(coord.first<=mr && coord.second<=mc) {
		if(board[mr][mc+1]=='/') board[mr][mc+1]=ch;
		if(board[mr+1][mc]=='/') board[mr+1][mc]=ch;
		if(board[mr+1][mc+1]=='/') board[mr+1][mc+1]=ch;

	}
	else if(coord.first<=mr && coord.second>mc) {
		if(board[mr][mc]=='/') board[mr][mc]=ch;
		if(board[mr+1][mc]=='/') board[mr+1][mc]=ch;
		if(board[mr+1][mc+1]=='/') board[mr+1][mc+1]=ch;

	}
	else if(coord.first>mr && coord.second<=mc) {
		if(board[mr][mc]=='/') board[mr][mc]=ch;
		if(board[mr][mc+1]=='/') board[mr][mc+1]=ch;
		if(board[mr+1][mc+1]=='/') board[mr+1][mc+1]=ch;

	}
	else if(coord.first>mr && coord.second>mc) {
		if(board[mr][mc+1]=='/') board[mr][mc+1]=ch;
		if(board[mr+1][mc]=='/') board[mr+1][mc]=ch;
		if(board[mr][mc]=='/') board[mr][mc]=ch;

	}

	else cout<<"Error"<<endl;
	
	alp++;

}

void smallplace(vector<vector<char>> &board, int sr, int sc) {
	char ch=alp+65;
	for(int i=sr;i<sr+2;i++) {
		for(int j=sc;j<sc+2;j++) {
			if(board[i][j]=='/') 
				board[i][j]=ch;
		}
	}
	alp++;
}

void boomerang(vector<vector<char>> &board,int r, int c, int n) {
	if(n==2) {
		smallplace(board, r, c);
	}

	else {

		pair<int,int> coord=findthebox(board, r,c,n);
		placeTheBoomerang(board, coord, r,c,n);



		boomerang(board, r,c,n/2);
		boomerang(board, r, c+(n/2), n/2);
		boomerang(board, r+(n/2), c, n/2);
		boomerang(board, r+(n/2), c+(n/2), n/2);
		

	}
}

int main() {
	int n;
	cout<<"Enter the size of the array: ";
	cin>>n;

	vector<vector<char>> board;
	vector<vector<char>> boomerangedBoard;

	board=initializeTheBoard(n);

	int row,col;
	cout<<"Enter the coordinates of the blank square"<<endl;
	cin>>row>>col;

	board[row][col]='-';

	//just for checking

	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}

	cout<<endl<<endl;

	boomerang(board,0,0,n);
	cout<<endl<<endl;

	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}





	return 0;
}