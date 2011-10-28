#include <iostream>
#include "8-puzzle.h"


using namespace std;

bool RUN_H1 = true;
bool RUN_H2 = true;
bool RUN_H3 = true;

int numberOfInversions(state&);
bool astar(state* start, state* goal, int h_function_to_use);

int main(){



	int **board;
	board = new int*[NUM_ROWS_ON_BOARD];
	for(int i = 0 ; i < NUM_ROWS_ON_BOARD; i++)
	{
		board[i] = new int[NUM_COLS_ON_BOARD];
	}
	
	board[0][0] = 1;
	board[0][1] = 2;
	board[0][2] = 3;

	board[1][0] = 8;
	board[1][1] = 0;
	board[1][2] = 4;

	board[2][0] = 7;
	board[2][1] = 6;
	board[2][2] = 5;

	state goal = *new state(board, NULL, "");

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

		state start(NULL, NULL, "");
		cin >> start;
		//cout << endl << start << endl;

		if(numberOfInversions(start) % 2 == 0)
		{
			cout << endl << "No solution exists!" << endl << endl;
		}
		else
		{
			if(start == goal){
				cout <<endl << goal;
				cout << endl << "0 moves in total." << endl << endl;
			}
			else {
				if(RUN_H1){
					cout << endl << "Using h1:" << endl << endl;
					cout << start << endl;
					astar(&start, &goal, 1);
				}
				if(RUN_H2){
					cout << endl << "Using h2:" << endl << endl;
					cout << start << endl;
					astar(&start, &goal, 2);
				}
				if(RUN_H3){
					cout << endl << "Using h3:" << endl << endl;
					cout << start << endl;
					astar(&start, &goal, 3);
				}
			}
		}

		cout << "Inital State (input):" << endl;
		cout << ">>";

		if(cin.peek() == 10)cin.get();
	}

	cout << endl << endl;
	return 0;
}
