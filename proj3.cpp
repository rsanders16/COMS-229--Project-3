// Project 3 of Com S 229
// Authour: Ryan K Sanders 

#include <iostream>
#include "8-puzzle.h"

using namespace std;

/*
Set one, two, or all of these booleans to false if you do not wish its corisponding h function to be run during execution of main().
*/
bool RUN_H1 = true;
bool RUN_H2 = true;
bool RUN_H3 = true;

/*
PROTOTYPE numberOfInversions used in main()
*/
int numberOfInversions(state&);

/*
PROTOTYPE astar used in main()
*/
bool astar(state* start, state* goal, int h_function_to_use);

/*
This is where the program begins
*/
int main(){

	//Create a board to hold the goal state.
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

	//Show the user the goal state
	string input;

	cout << endl << "Goal State:" << endl;
	cout << endl;
	cout << "1 2 3" << endl;
	cout << "8   4" << endl;
	cout << "7 6 5" << endl;
	cout << endl;

	//Ask the user for an inital state until they enter 'E'
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

		if(numberOfInversions(start) % 2 == 0)
		{
			//No solution exists so dont try to solve the puzzle.
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
					//solve the program using h1
					cout << endl << "Using h1:" << endl << endl;
					cout << start << endl;
					astar(&start, &goal, 1);
				}
				if(RUN_H2){
					//solve the program using h2
					cout << endl << "Using h2:" << endl << endl;
					cout << start << endl;
					astar(&start, &goal, 2);
				}
				if(RUN_H3){
					//solve the program using h3
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
	//end the program successfully.
	return 0;
}
