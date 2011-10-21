#include <iostream>
#include <string>
#include "8-puzzle.h"
#include <list>
#include <vector>
#include <queue>

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

bool isParent(state& st){
	int ** board = st.getBoard();
	if(board[0][0] != 0)return false;
	if(board[0][1] != 0)return false;
	if(board[0][2] != 0)return false;
	if(board[1][0] != 0)return false;
	if(board[1][1] != 0)return false;
	if(board[1][2] != 0)return false;
	if(board[2][0] != 0)return false;
	if(board[2][1] != 0)return false;
	if(board[2][2] != 0)return false;
	if(st.getG() != -1)return false;
	return true;
}

void printPath(state current_state){
	int moveCount = 1;

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

	state goal = *new state(board);

	while(!(current_state == goal)){
		cout << current_state;
		cout << endl;
		cout << "MOVE" << endl;
		cout << endl;
		moveCount++;
		current_state = *current_state.getParent();
	}
	cout << moveCount << " moves in total.";
	cout << endl << endl;
}

int** getInitalizedBoard(int p1, int p2, int** oldBoard){
	int **newBoard;
	newBoard = new int*[NUM_ROWS_ON_BOARD];
	for(int i = 0 ; i < NUM_ROWS_ON_BOARD; i++)
	{
		newBoard[i] = new int[NUM_COLS_ON_BOARD];
	}

	int oldBoardLinear[9];
	for(int i = 0 ; i < 3 ; i++)
	{
		for(int j = 0 ; j < 3 ; j++)
		{
			oldBoardLinear[(i * 3) + j] = oldBoard[i][j];
		}
	}

	int temp = oldBoardLinear[p1];
	oldBoardLinear[p1] = oldBoardLinear[p2];
	oldBoardLinear[p2] = temp;

	newBoard[0][0] = oldBoardLinear[0];
	newBoard[0][1] = oldBoardLinear[1];
	newBoard[0][2] = oldBoardLinear[2];

	newBoard[1][0] = oldBoardLinear[3];
	newBoard[1][1] = oldBoardLinear[4];
	newBoard[1][2] = oldBoardLinear[5];

	newBoard[2][0] = oldBoardLinear[6];
	newBoard[2][1] = oldBoardLinear[7];
	newBoard[2][2] = oldBoardLinear[8];

	return newBoard;
}

list<state> neighbor_nodes(state s){
	list<state> neighbors = *new list<state>;
	int** board = s.getBoard();
	if(board[0][0] == 0){
		neighbors.push_back(*new state(getInitalizedBoard(0,1, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(0,3, board), s.getParent()));
	}
	else if(board[0][1] == 0){
		neighbors.push_back(*new state(getInitalizedBoard(1,2, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(1,0, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(1,4, board), s.getParent()));
	}
	else if(board[0][2] == 0){
		neighbors.push_back(*new state(getInitalizedBoard(2,5, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(2,1, board), s.getParent()));
	}
	else if(board[1][0] == 0){
		neighbors.push_back(*new state(getInitalizedBoard(3,0, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(3,6, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(3,4, board), s.getParent()));
	}
	else if(board[1][1] == 0){
		neighbors.push_back(*new state(getInitalizedBoard(4,3, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(4,1, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(4,5, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(4,8, board), s.getParent()));
	}
	else if(board[1][2] == 0){
		neighbors.push_back(*new state(getInitalizedBoard(5,8, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(5,2, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(5,4, board), s.getParent()));
	}
	else if(board[2][0] == 0){
		neighbors.push_back(*new state(getInitalizedBoard(6,7, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(6,3, board), s.getParent()));
	}
	else if(board[2][1] == 0){
		neighbors.push_back(*new state(getInitalizedBoard(7,4, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(7,6, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(7,8, board), s.getParent()));
	}
	else if(board[2][2] == 0){
		neighbors.push_back(*new state(getInitalizedBoard(8,7, board), s.getParent()));
		neighbors.push_back(*new state(getInitalizedBoard(8,5, board), s.getParent()));
	}
	else{
		//cerr << endl << "ERROR:  A state had a board that had an illegal state." << endl;
		//exit(-1);
	}
	return neighbors;
}

list<state> OPEN = *new list<state>();
list<state> CLOSED = *new list<state>();

bool astar(state start, state goal, int h_function_to_use)
{
	//1. Put the start state S0 on OPEN.  Let g(S0) = 0 and estimate h(S0).
	OPEN.push_back(start);
	int hOfStart = 0;
	if(h_function_to_use == 1){
		hOfStart = h1(start);
	}
	else{
		hOfStart = h2(start);
	}
	
	//2. If OPEN is empty, exit with failure.
	while(!OPEN.empty()){

		//3. Remove from OPEN and place on CLOSED a state S whose f value is
		//   minimum.  If there are several states with the same minimum
		//   value, arbitrarily remove one; if one is the goal state, then
		//   remove the goal state.
		list<state>::iterator i;
		bool removedGoalState = false;
		state S;
		int counter = 0;
		bool done = false;
		for(i = OPEN.begin(), S = *i ; i != OPEN.end() && done == false; ++i){
				S = *i;
				if(f(h_function_to_use, *i) < f(h_function_to_use, S)){
					S = *i;
				}
				if(*i == goal)
				{
					OPEN.remove(S);
					CLOSED.push_back(S);
					removedGoalState = true;
					done = true;
					continue;
				}
		}
		if(!removedGoalState){
			OPEN.remove(S);
			CLOSED.push_back(S);
		}

		//4. If S is the goal state, exit successfully and print out the
		//entire solution path (step-by-step state transitions)
		if(S == goal || done){
			printPath(S);
			return true;
		}

		//5. Otherwise, generate S's all possible successor states in one
		//valid move and set their parent pointers back to S.  For every
		//successor state T of S:
				// - Estimate h(T) and compute f(T) = g(T) + h(T) = g(S) + 1 + h(T).
				// - If T is not already on OPEN or CLOSED, then put it on OPEN. 
				// - If T is already on OPEN, compare its old and new f values
				//		and choose the minimum, resetting its parent pointer (along
				//		the path yielding the lowest g(T)).
				// - If T is on CLOSED and its new f value is less than the old
				//		one, put T on OPEN and reset its parent pointer.
		else{
			list<state> neighbors = neighbor_nodes(S);
			list<state>::iterator i;

			int childCount = 0;
			for(i = neighbors.begin() ; i != neighbors.end() ; ++i){
				state T = *i;
				state * oldStateOfT;
			
				bool openContainsT = false;
				list<state>::iterator openIterator;
				for(openIterator = OPEN.begin(); openIterator != OPEN.end() ; ++openIterator){
					if(*openIterator == T){
						openContainsT = true;
						oldStateOfT = &(*openIterator);
						break;
					}
				}	

				bool closedContainsT = false;
				list<state>::iterator closedIterator;
				for(closedIterator = CLOSED.begin(); closedIterator != CLOSED.end() ; ++closedIterator){
					if(*closedIterator == T){
						closedContainsT = true;
						oldStateOfT = &(*closedIterator);
						break;
					}
				}

				//int newGValueOfT = 0;
				//int oldGValueOfT = 0;
				//bool newIsMinGValue = false;
				//
				//

				//


				//if(closedContainsT || openContainsT){
				//	newGValueOfT = S.getG() + 1;
				//	oldGValueOfT = T.getG();
				//	
				//	if(newGValueOfT < oldGValueOfT){
				//		newIsMinGValue = true;
				//	}
				//}

				/////////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////

				if(openContainsT == false && closedContainsT == false){
					OPEN.push_back(T);
				}
				else if(openContainsT){
					//T is already on OPEN, compare its old and new f values
					//and choose the minimum, resetting its parent pointer (along
					//the path yielding the lowest g(T)).
					if(S.getG() + 1 < T.getG()){
						T.setG(S.getG() + 1);
						T.setParent(oldStateOfT->getParent());
					}
				}
				else if(closedContainsT){
					//T is on CLOSED and if its new f value is less than the old
					//one, put T on OPEN and reset its parent pointer.
					if(S.getG() + 1 < T.getG()){
						CLOSED.remove(T);
						OPEN.push_back(T);
						T.setG(S.getG() + 1);
						T.setParent(oldStateOfT->getParent());
					}
				}
				else{
					cerr << endl << "ERROR: Illegal State - state T was located in the OPEN set and the CLOSED set at the same time" << endl;
					exit(0);
				}
			}
		}
    //6. Go to step 2. 
	}
	return false;
}

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

	state goal = *new state(board);

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

		state start;
		cin >> start;
		cout << endl << start << endl;

		if(numberOfInversions(start) % 2 == 0)
		{
			cout << "No solution exists!" << endl << endl;
		}
		else
		{
			astar(start, goal, 1);
		}

		cout << "Inital State (input):" << endl;
		cout << ">>";

		if(cin.peek() == 10)cin.get();
	}

	cout << endl << endl;
	return 0;
}