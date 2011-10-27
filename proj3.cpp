#include <iostream>
#include <string>
#include "8-puzzle.h"
#include <list>
#include <stack>
#include <math.h>

using namespace std;

list<state*> OPEN = *new list<state*>();
list<state*> CLOSED = *new list<state*>();

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




void printPath(state* current_state, state* goal, bool allowDoubleMoves){

	
	stack<state> pathStack = *new stack<state>();
	int moveCount = 0;
	while(current_state->getG() != -1){
		pathStack.push(*current_state);
		current_state = current_state->getParent();
		moveCount++;
	}
	int lastPosOf0 = 0;
	int curPosOf0 = 0;
	if(current_state->getBoard()[0][0] == 0)lastPosOf0 = 0;
	else if(current_state->getBoard()[0][1] == 0)lastPosOf0 = 1;
	else if(current_state->getBoard()[0][2] == 0)lastPosOf0 = 2;
	else if(current_state->getBoard()[1][0] == 0)lastPosOf0 = 3;
	else if(current_state->getBoard()[1][1] == 0)lastPosOf0 = 4;
	else if(current_state->getBoard()[1][2] == 0)lastPosOf0 = 5;
	else if(current_state->getBoard()[2][0] == 0)lastPosOf0 = 6;
	else if(current_state->getBoard()[2][1] == 0)lastPosOf0 = 7;
	else if(current_state->getBoard()[2][2] == 0)lastPosOf0 = 8;

	for(int i = 0 ; i < moveCount ; i++){
		//////////////////////////////////////////////////////////////////////////////////////////////
		///START OF MOVE PRINTER
		///LEFT, RIGHT, UP, or DOWN, will be printed out depending on what kind of move took place
		//////////////////////////////////////////////////////////////////////////////////////////////
		if(pathStack.top().getBoard()[0][0] == 0)curPosOf0 = 0;
		else if(pathStack.top().getBoard()[0][1] == 0)curPosOf0 = 1;
		else if(pathStack.top().getBoard()[0][2] == 0)curPosOf0 = 2;
		else if(pathStack.top().getBoard()[1][0] == 0)curPosOf0 = 3;
		else if(pathStack.top().getBoard()[1][1] == 0)curPosOf0 = 4;
		else if(pathStack.top().getBoard()[1][2] == 0)curPosOf0 = 5;



		else if(pathStack.top().getBoard()[2][0] == 0)curPosOf0 = 6;
		else if(pathStack.top().getBoard()[2][1] == 0)curPosOf0 = 7;
		else if(pathStack.top().getBoard()[2][2] == 0)curPosOf0 = 8;
		if(curPosOf0 < lastPosOf0){
			if(curPosOf0 == lastPosOf0 - 1){
				cout << "RIGHT";
			}
			else if(curPosOf0 == lastPosOf0 - 2 && allowDoubleMoves){
				cout << "DBL-RIGHT";
			}
			else if( abs(curPosOf0 - lastPosOf0) == 6 && allowDoubleMoves){
				cout << "DBL-DOWN";
			}
			else{
				cout << "DOWN";
			}
		}
		else{
			if(curPosOf0 == lastPosOf0 + 1){
				cout << "LEFT";
			}
			else if(curPosOf0 == lastPosOf0 + 2 && allowDoubleMoves){
				cout << "DBL-LEFT";
			}
			else if( abs(curPosOf0 - lastPosOf0) == 6 && allowDoubleMoves){
				cout << "DBL-UP";
			}
			else{
				cout << "UP";
			}
		}
		cout << endl << endl;
		if(pathStack.top().getBoard()[0][0] == 0)lastPosOf0 = 0;
		else if(pathStack.top().getBoard()[0][0] == 0)lastPosOf0 = 0;
		else if(pathStack.top().getBoard()[0][1] == 0)lastPosOf0 = 1;
		else if(pathStack.top().getBoard()[0][2] == 0)lastPosOf0 = 2;
		else if(pathStack.top().getBoard()[1][0] == 0)lastPosOf0 = 3;
		else if(pathStack.top().getBoard()[1][1] == 0)lastPosOf0 = 4;
		else if(pathStack.top().getBoard()[1][2] == 0)lastPosOf0 = 5;
		else if(pathStack.top().getBoard()[2][0] == 0)lastPosOf0 = 6;
		else if(pathStack.top().getBoard()[2][1] == 0)lastPosOf0 = 7;
		else if(pathStack.top().getBoard()[2][2] == 0)lastPosOf0 = 8;
		//////////////////////////////////////////////////////////////////////////////////////////////
		///END OF MOVE PRINTER
		//////////////////////////////////////////////////////////////////////////////////////////////

		cout << pathStack.top();
		cout << endl;
		pathStack.pop();

	}

	cout << moveCount << " moves in total.";
	cout << endl << endl;

	//DELETION OF CURRENT LIST
	list<state*>::iterator delIter;
	list<state*>::iterator deleteiter;
	deleteiter = OPEN.erase(OPEN.begin(),OPEN.end());
	CLOSED.erase(CLOSED.begin(), CLOSED.end());
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

list<state*> neighbor_nodes(state* s, bool allowDoubleMoves){
	int **newBoard;
	newBoard = new int*[NUM_ROWS_ON_BOARD];
	for(int i = 0 ; i < NUM_ROWS_ON_BOARD; i++)
	{
		newBoard[i] = new int[NUM_COLS_ON_BOARD];
	}

	list<state*> neighbors = *new list<state*>;
	int** board = s->getBoard();
	if(board[0][0] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(0,1, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(0,3, board), s)));
		if(allowDoubleMoves){

				newBoard[0][0] = board[0][1];
				newBoard[0][1] = board[0][2];
				newBoard[0][2] = 0;

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s)));

				newBoard[0][0] = board[1][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[2][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = 0;
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s)));
		}
	}
	else if(board[0][1] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(1,2, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(1,0, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(1,4, board), s)));
		if(allowDoubleMoves){
				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[1][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[2][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = 0;
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s)));
		}
	}
	else if(board[0][2] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(2,5, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(2,1, board), s)));
		if(allowDoubleMoves){
				newBoard[0][0] = 0;
				newBoard[0][1] = board[0][0];
				newBoard[0][2] = board[0][1];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s)));

				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[1][2];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[2][2];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = 0;
				neighbors.push_back(&(*new state(newBoard, s)));
		}
	}
	else if(board[1][0] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(3,0, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(3,6, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(3,4, board), s)));
		if(allowDoubleMoves){
				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[1][1];
				newBoard[1][1] = board[1][2];
				newBoard[1][2] = 0;

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s)));
		}
	}
	else if(board[1][1] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(4,3, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(4,1, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(4,5, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(4,8, board), s)));
	}
	else if(board[1][2] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(5,8, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(5,2, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(5,4, board), s)));
		if(allowDoubleMoves){
				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = 0;
				newBoard[1][1] = board[0][1];
				newBoard[1][2] = board[1][1];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s)));
		}
	}
	else if(board[2][0] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(6,7, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(6,3, board), s)));
		if(allowDoubleMoves){
				newBoard[0][0] = 0;
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[0][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = board[1][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s)));

				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = board[2][1];
				newBoard[2][1] = board[2][2];
				newBoard[2][2] = 0;
				neighbors.push_back(&(*new state(newBoard, s)));
		}
	}
	else if(board[2][1] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(7,4, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(7,6, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(7,8, board), s)));
		if(allowDoubleMoves){
				newBoard[0][0] = board[0][0];
				newBoard[0][1] = 0;
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[0][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[1][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s)));
		}
	}
	else if(board[2][2] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(8,7, board), s)));
		neighbors.push_back(&(*new state(getInitalizedBoard(8,5, board), s)));
		if(allowDoubleMoves){
				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = 0;
				newBoard[2][1] = board[2][0];
				newBoard[2][2] = board[2][1];
				neighbors.push_back(&(*new state(newBoard, s)));
								
				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = 0;

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[0][2];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[1][2];
				neighbors.push_back(&(*new state(newBoard, s)));
		}
	}

	return neighbors;
}




bool astar(state* start, state* goal, int h_function_to_use){
	
	bool allowDoubleMoves = false;
	if(h_function_to_use == 3){
				allowDoubleMoves = true;
	}

	OPEN.push_back(&*start);

	while(!OPEN.empty()){
		list<state*>::iterator i = OPEN.begin();
		
		state* S = *i;
		//const state* SPtr = &S;

		for(i = OPEN.begin() ; i != OPEN.end(); ++i){
			if(f(h_function_to_use, *i) < f(h_function_to_use, S)){
				S = *i;
			}
		}
		
		
		CLOSED.push_back(S);
		OPEN.remove(S);
		
		if(*S == *goal){
			
			
			printPath(S, goal, allowDoubleMoves);
			return true;	
		}
		else{
			list<state*> neighbors = neighbor_nodes(S,allowDoubleMoves);
			list<state*>::iterator neighbor_iter;

			//cout << "PARENT: " <<endl << *S << endl << endl;
			for(neighbor_iter = neighbors.begin() ; neighbor_iter != neighbors.end() ; ++neighbor_iter){
				//cout << "CHILD: " <<endl << **neighbor_iter << endl << endl;
				
				state* old_value = *neighbor_iter;
				state* current_neighbor = *neighbor_iter;
				
				list<state*>::iterator open_list_iter;
				bool current_neighbor_is_in_open_list = false;
				for(open_list_iter = OPEN.begin() ; open_list_iter != OPEN.end() ; ++open_list_iter){
					if(**open_list_iter == *current_neighbor){
						current_neighbor_is_in_open_list = true;
						old_value = *open_list_iter;
					}
				}

				list<state*>::iterator closed_list_iter;
				bool current_neighbor_is_in_closed_list = false;
				for(closed_list_iter = CLOSED.begin() ; closed_list_iter != CLOSED.end() ; ++closed_list_iter){
					if(**closed_list_iter == *current_neighbor){
						current_neighbor_is_in_closed_list = true;
						old_value = *closed_list_iter;
					}
				}

				if(current_neighbor_is_in_open_list == false && current_neighbor_is_in_closed_list == false ){
					OPEN.push_back(current_neighbor);
				}
				else if(current_neighbor_is_in_open_list){
					if(f(h_function_to_use, current_neighbor) < f(h_function_to_use, old_value)){
						(*old_value).setParent(S);
					}
				}
				else if(current_neighbor_is_in_closed_list){
					if(f(h_function_to_use, current_neighbor) < f(h_function_to_use, old_value)){
						(*old_value).setParent(S);
						CLOSED.remove(current_neighbor);
						OPEN.push_back(current_neighbor);
					}
				}
			}
		}
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

	state goal = *new state(board, NULL);

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

		state start(NULL, NULL);
		cin >> start;
		cout << endl << start << endl;

		if(numberOfInversions(start) % 2 == 0)
		{
			cout << "No solution exists!" << endl << endl;
		}
		else
		{
			if(start == goal){
				cout << "0 moves in total." << endl << endl;
			}
			else {
				//cout << "Using h1:" << endl << endl;
				astar(&start, &goal, 1);
				cout << "Using h2:" << endl << endl;
				cout << start << endl;
				astar(&start, &goal, 2);
				cout << "Using h3:" << endl << endl;
				cout << start << endl;
				astar(&start, &goal, 3);
			}

		}

		cout << "Inital State (input):" << endl;
		cout << ">>";

		if(cin.peek() == 10)cin.get();
	}

	cout << endl << endl;
	return 0;
}