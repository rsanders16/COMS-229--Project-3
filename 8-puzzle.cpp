#include "8-puzzle.h"

using namespace std;

/**
CONSTRUCTOR:  state(int**, state*)
DESCRIPTION:  Generate a state with a 3x3 board configuration stored in a 2-dimunsional array bd, and a pointer to its parent state.
PARAMS:
bd - A pointer the board to be instantiated
sate - A pointer to the boards parent state
*/
state::state(int **bd, state* prnt = 0){
	this->board = bd;
	this->parent = prnt;
}

state::state(){

}

state::~state(){

}

/**
FUNCTION: getG()
DESCRIPTION:  Returns the class var g
RETURN:  The number of moves from the inital state to the current state.
*/
int state::getG(){
	return this->g;
}

/**
FUNCTION: getBoard()
DESCRIPTION:  Returns the class var board
RETURN:  // 3x3 configuration of the board.
*/
int** state::getBoard(){
	return this->board;
}

/**
FUNCTION: getParent()
DESCRIPTION:  Returns the class var parent
RETURN:  //The state from which the current state is generated with one move.
*/
state* state::getParent(){
	return this->parent;
}

/**
FUNCTION: overload < operator
DESCRIPTION: Overloads the < operator so that it can be used to test wheather or not 'this' state is less than the paramater otherState.
RETURN bool - True if in fact 'this' state is less then otherState
*/
//bool operator< (const state& otherState){}

/**
FUNCTION: overload == operator
DESCRIPTION: Overloads the == operator so that it can be used to test wheather or not 'this' state is equal to otherState.
RETURN bool - True if in fact 'this' state is equal to otherState
*/
//bool operator== (const state& otherState){}


/**
FUNCTION: overload operator << 
DESCRIPTION: Follows the spec of project 2 output for a 'state' object
PARAMS:
ostr - The outstream that the state will be printed to
x - The state object
RETRUN: The outstream used during the execution of this function
*/
ostream& operator<< (ostream& ostr, const state& x) { 
	int ** q = x.board;
	cout << q[0] << " " << q[1] << " " << q[2]  << endl;
	cout << q[3] << " " << q[4] << " " << q[5]  << endl;
	cout << q[6] << " " << q[7] << " " << q[8]  << endl;
	return ostr;
} 

/**
FUNCTION: overload operator >> 
DESCRIPTION: Follows the spec of project 3 input.  A single given board state is inputed via standard input.
PARAMS:
istr - The instream that the 'this' state should be parsed from
x - The state to be created
RETRUN: The instream used during the execution of this function
*/
istream& operator>> (istream& istr, state& x){
	int ** board;
	board = new int * [NUM_ROWS_ON_BOARD];
	for(int i = 0 ; i < NUM_ROWS_ON_BOARD ; i++)
		board[i] = new int [NUM_COLS_ON_BOARD];
	for(int i = 0 ; i < NUM_ROWS_ON_BOARD ; i++)
		for(int j = 0 ; j < NUM_COLS_ON_BOARD ; j++)
			cin >> board[i][j];
	x = *new state(board);
	
	exit(1);
	return istr;
} 


/**
FUNCTION: h1(state&)
DESCRIPTION:  The number of mismatched tiles between a state st and the goal state.
PARAMS:
st - The state being evaluated against the goal state.
RETURN:
The number of mismatched tiles.
*/
int h1(state& st){
	return 0;
}

/**
FUNCTION: h2(state&)
DESCRIPTION:  The Manhattan distance between a state st and the goal state.
PARAMS:
st - The state being evaluated against the goal state.
RETURN:
The Manhattan distance.
*/
int h2(state& st){
	return 0;
} 

/**
FUNCTION: f(int)
DESCRIPTION:  Value of the function f based on the heuristic type (h1 or h2).
PARAMS:
htype - The state being evaluated against the goal state.
RETURN:
The value of function based on the heuristic type.
*/
int f(int htype){
	return 0;
}
