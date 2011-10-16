#include <iostream>
#include <string>
#include "8-puzzle.h"

using namespace std;

int numberOfInversions(state& x)
{
	int num = 0;
	int linearBoard[9];
	for(int i = 0 ; i < 3 ; i++)
	{
		for(int j = 0 ; j < 3 ; j++)
		{
			linearBoard[(i * 3) + j] = x.getBoard()[i][j];
		}
	}
	for(int i = 0 ; i < 9 ; i++)
	{
		for(int j = i ; j < 8 ; j++){
			if(linearBoard[i]!= 0 && linearBoard[i] > linearBoard[j+1] && linearBoard[j+1] != 0){
				num++;
			}
		}
	}
	return num;
}



int main(){

	string input;

	cout << endl << "Goal State:" << endl;
	cout << endl;
	cout << "1 2 3" << endl;
	cout << "8   4" << endl;
	cout << "7 6 5" << endl;
	cout << endl;

	cout << "Inital State (input):" << endl;
	cout << ">>";
	char exit = '\0';

	while(cin.get(exit))
	{
		if(exit == 'E')
			return 0;
		else cin.putback(exit);
		
		state state1;
		cin >> state1;
		cout << endl << state1 << endl;

		if(numberOfInversions(state1) % 2 == 0)
		{
			cout << "No solution exists!" << endl << endl;
		}
		else
		{
			cout << "A solution exists" << endl << endl;
		}

		cout << "Inital State (input):" << endl;
		cout << ">>";
		
		if(cin.peek() == 10)cin.get();
	}

	cout << endl << endl;
	return 0;
}