#include <iostream>
#include <string>
#include "8-puzzle.h"

using namespace std;

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

	state state1;
	cin >> state1;
	cout << state1;
    //int pos0, pos1, pos2, pos4, pos5, pos6, pos7, pos8;
	//cin >> pos0 >> pos1 >> pos2 >> pos4 >> pos5 >> pos6 >> pos9 >> pos8;


	return 0;
}