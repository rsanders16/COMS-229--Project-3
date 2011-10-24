#include "8-puzzle.h"

using namespace std;


bool isDigit(int c){
	return c == 0 || c == 1 || c == 2 || c == 3 || c == 4 || c == 5 || c == 6 || c == 7 || c == 8 || c == 9; 
}

/**
CONSTRUCTOR:  state(int**, state*)
DESCRIPTION:  Generate a state with a 3x3 board configuration stored in a 2-dimunsional array bd, and a pointer to its parent state.
PARAMS:
bd - A pointer the board to be instantiated
sate - A pointer to the boards parent state
*/
state::state(int **bd, state* prnt){

	this->board = new int*[NUM_ROWS_ON_BOARD];
	for(int i = 0 ; i < NUM_ROWS_ON_BOARD; i++)
	{
		this->board[i] = new int[NUM_COLS_ON_BOARD];
	}

	this->board[0][0] = bd[0][0];
	this->board[0][1] = bd[0][1];
	this->board[0][2] = bd[0][2];

	this->board[1][0] = bd[1][0];
	this->board[1][1] = bd[1][1];
	this->board[1][2] = bd[1][2];

	this->board[2][0] = bd[2][0];
	this->board[2][1] = bd[2][1];
	this->board[2][2] = bd[2][2];
	this->parent = prnt;
	this->g = prnt->getG() + 1;
}

state::state(int **bd){

	this->board = new int*[NUM_ROWS_ON_BOARD];
	for(int i = 0 ; i < NUM_ROWS_ON_BOARD; i++)
	{
		this->board[i] = new int[NUM_COLS_ON_BOARD];
	}

	this->board[0][0] = bd[0][0];
	this->board[0][1] = bd[0][1];
	this->board[0][2] = bd[0][2];

	this->board[1][0] = bd[1][0];
	this->board[1][1] = bd[1][1];
	this->board[1][2] = bd[1][2];

	this->board[2][0] = bd[2][0];
	this->board[2][1] = bd[2][1];
	this->board[2][2] = bd[2][2];
	this->parent = new state();
	this->g = 0;
}

state::state(){
	int **board;
	board = new int*[NUM_ROWS_ON_BOARD];
	for(int i = 0 ; i < NUM_ROWS_ON_BOARD; i++)
	{
		board[i] = new int[NUM_COLS_ON_BOARD];
	}
	
	board[0][0] = 0;
	board[0][1] = 0;
	board[0][2] = 0;

	board[1][0] = 0;
	board[1][1] = 0;
	board[1][2] = 0;

	board[2][0] = 0;
	board[2][1] = 0;
	board[2][2] = 0;

	this->board = board;
	this->parent = NULL;
	this->g = -1;
}

state::state(const state& obj){
	this->g = obj.g;
	this->parent = obj.parent;

	this->board = new int*[NUM_ROWS_ON_BOARD];
	for(int i = 0 ; i < NUM_ROWS_ON_BOARD; i++)
	{
		this->board[i] = new int[NUM_COLS_ON_BOARD];
	}

	this->board[0][0] = obj.getBoard()[0][0];
	this->board[0][1] = obj.getBoard()[0][1];
	this->board[0][2] = obj.getBoard()[0][2];
	this->board[1][0] = obj.getBoard()[1][0];
	this->board[1][1] = obj.getBoard()[1][1];
	this->board[1][2] = obj.getBoard()[1][2];
	this->board[2][0] = obj.getBoard()[2][0];
	this->board[2][1] = obj.getBoard()[2][1];
	this->board[2][2] = obj.getBoard()[2][2];
}

state::~state(){
	for(int i = 0 ; i < NUM_ROWS_ON_BOARD; i++)
	{
		delete [] board[i];
	}
	delete [] board;
}

void state::setG(int g){
	this->g = g;
}

void state::setParent(state* prnt){
	this->parent = prnt;
}

/**
FUNCTION: getG()
DESCRIPTION:  Returns the class var g
RETURN:  The number of moves from the inital state to the current state.
*/
int state::getG() const{
	return this->g;
}

/**
FUNCTION: getBoard()
DESCRIPTION:  Returns the class var board
RETURN:  // 3x3 configuration of the board.
*/
int** state::getBoard() const{
	int ** board;
	board = new int*[NUM_ROWS_ON_BOARD];
	for(int i = 0 ; i < NUM_ROWS_ON_BOARD; i++)
	{
		board[i] = new int[NUM_COLS_ON_BOARD];
	}

	board[0][0] = this->board[0][0];
	board[0][1] = this->board[0][1];
	board[0][2] = this->board[0][2];
	board[1][0] = this->board[1][0];
	board[1][1] = this->board[1][1];
	board[1][2] = this->board[1][2];
	board[2][0] = this->board[2][0];
	board[2][1] = this->board[2][1];
	board[2][2] = this->board[2][2];
	return board;
}

/**
FUNCTION: getParent()
DESCRIPTION:  Returns the class var parent
RETURN:  //The state from which the current state is generated with one move.
*/
state* state::getParent() const{
	return this->parent;
}

/**
FUNCTION: overload < operator
DESCRIPTION: Overloads the < operator so that it can be used to test wheather or not 'this' state is less than the paramater otherState.
RETURN bool - True if in fact 'this' state is less then otherState
*/
bool state::operator< (const state& otherState) const{
	return this->g < otherState.g;
}

/**
FUNCTION: overload == operator
DESCRIPTION: Overloads the == operator so that it can be used to test wheather or not 'this' state is equal to otherState.
RETURN bool - True if in fact 'this' state is equal to otherState
*/
bool state::operator== (const state& otherState) const{
	//if(this->getG() != otherState.getG())return false;
	//if(this->getParent() != otherState.getParent())return false;
	//if(otherState.getParent() == NULL) return false;
	//if(this->getG() != otherState.getG()) return false;
	//if(this->getParent() != this->getParent()) return false;

	if(this->getBoard()[0][0] != otherState.getBoard()[0][0])return false;
	if(this->getBoard()[0][1] != otherState.getBoard()[0][1])return false;
	if(this->getBoard()[0][2] != otherState.getBoard()[0][2])return false;
	if(this->getBoard()[1][0] != otherState.getBoard()[1][0])return false;
	if(this->getBoard()[1][1] != otherState.getBoard()[1][1])return false;
	if(this->getBoard()[1][2] != otherState.getBoard()[1][2])return false;
	if(this->getBoard()[2][0] != otherState.getBoard()[2][0])return false;
	if(this->getBoard()[2][1] != otherState.getBoard()[2][1])return false;
	if(this->getBoard()[2][2] != otherState.getBoard()[2][2])return false;
	return true;
}

state& state::operator= (const state& otherState){
	if(this != &otherState)
	{
		this->g = otherState.g;
		this->parent = otherState.parent;
		this->board[0][0] = otherState.getBoard()[0][0];
		this->board[0][1] = otherState.getBoard()[0][1];
		this->board[0][2] = otherState.getBoard()[0][2];
		this->board[1][0] = otherState.getBoard()[1][0];
		this->board[1][1] = otherState.getBoard()[1][1];
		this->board[1][2] = otherState.getBoard()[1][2];
		this->board[2][0] = otherState.getBoard()[2][0];
		this->board[2][1] = otherState.getBoard()[2][1];
		this->board[2][2] = otherState.getBoard()[2][2];
	}
	return *this;
}


/**
FUNCTION: overload operator << 
DESCRIPTION: Follows the spec of project 2 output for a 'state' object
PARAMS:
ostr - The outstream that the state will be printed to
x - The state object
RETRUN: The outstream used during the execution of this function
*/
ostream& operator<< (ostream& ostr, const state& x) { 
	if(x.board[0][0] == 0) cout << " "; else cout << x.board[0][0];
	cout << " ";
	if(x.board[0][1] == 0) cout << " "; else cout << x.board[0][1];
	cout << " ";
	if(x.board[0][2] == 0) cout << " "; else cout << x.board[0][2];
	cout << " ";
	cout << endl;

	if(x.board[1][0] == 0) cout << " "; else cout << x.board[1][0];
	cout << " ";
	if(x.board[1][1] == 0) cout << " "; else cout << x.board[1][1];
	cout << " ";
	if(x.board[1][2] == 0) cout << " "; else cout << x.board[1][2];
	cout << " ";
	cout << endl;

	if(x.board[2][0] == 0) cout << " "; else cout << x.board[2][0];
	cout << " ";
	if(x.board[2][1] == 0) cout << " "; else cout << x.board[2][1];
	cout << " ";
	if(x.board[2][2] == 0) cout << " "; else cout << x.board[2][2];
	cout << " ";
	cout << endl;

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
	int p1, p2, p3, p4, p5, p6, p7, p8, p9;
	//cin >> p1 >> p2 >> p3 >> p4 >> p5 >> p6 >> p7 >> p8 >> p9;
	p1 = 0;
	p2 = 2;
	p3 = 3;
	p4 = 1;
	p5 = 8;
	p6 = 4;
	p7 = 7;
	p8 = 6;
	p9 = 5;

	if(!isDigit(p1) || !isDigit(p2) ||!isDigit(p3) ||!isDigit(p4) ||!isDigit(p5) ||!isDigit(p6) ||!isDigit(p7) ||!isDigit(p8) ||!isDigit(p9)){
		cerr << "ERROR: Input Was Not Valid - Program will now exit..." << endl;
		exit(1);
	}

	int **board;
	board = new int*[NUM_ROWS_ON_BOARD];
	for(int i = 0 ; i < NUM_ROWS_ON_BOARD; i++)
	{
		board[i] = new int[NUM_COLS_ON_BOARD];
	}
	
	board[0][0] = p1;
	board[0][1] = p2;
	board[0][2] = p3;

	board[1][0] = p4;
	board[1][1] = p5;
	board[1][2] = p6;

	board[2][0] = p7;
	board[2][1] = p8;
	board[2][2] = p9;



	x = *new state(board);
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
	int** board = st.getBoard();
	int nMismatchedTiles = 0;
	if(board[0][0] != 1 && board[0][0] != 0)nMismatchedTiles++;
	if(board[0][1] != 2 && board[0][1] != 0)nMismatchedTiles++;
	if(board[0][2] != 3 && board[0][2] != 0)nMismatchedTiles++;
	if(board[1][0] != 8 && board[1][0] != 0)nMismatchedTiles++;
	//else if(board[1][1] != 1 && board[1][1] != 0)nMismatchedTiles++;
	if(board[1][2] != 4 && board[1][2] != 0)nMismatchedTiles++;
	if(board[2][0] != 7 && board[2][0] != 0)nMismatchedTiles++;
	if(board[2][1] != 6 && board[2][1] != 0)nMismatchedTiles++;
	if(board[2][2] != 5 && board[2][2] != 0)nMismatchedTiles++;
	return nMismatchedTiles;
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
		cerr << endl << "ERROR:  Function h2() has not been implemented yet." << endl;
		exit(-1);
} 

/**
FUNCTION: f(int)
DESCRIPTION:  Value of the function f based on the heuristic type (h1 or h2).
PARAMS:
htype - The state being evaluated against the goal state.
RETURN:
The value of function based on the heuristic type.
*/
int f(int htype, state& st){
	//if(st.getG() == NULL){
		//cerr << endl << "ERROR: Null Pointer Argumnet" << endl;
		//exit(0);
		//return 0;
	//}
	if(htype == 1){
		return st.getG() + h1(st);
	}
	else if(htype == 2)
	{
		return st.getG() + h2(st);
	}
	else{
		cerr << endl << "ERROR: Illegal Argument to function f() - First argumnet must have value 1 or 2" << endl;
		exit(0);
		return -1;
	}
}



