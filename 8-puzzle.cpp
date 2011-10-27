#include "8-puzzle.h"

using namespace std;

/**
CONSTRUCTOR:  state(int**, state*)
DESCRIPTION:  Generate a state with a 3x3 board configuration stored in a 2-dimunsional array bd, and a pointer to its parent state.
PARAMS:
bd - A pointer the board to be instantiated
sate - A pointer to the boards parent state
*/
state::state(int **bd, state* prnt){
	if(bd == NULL){
		this->boardMemoryAllocated = false;
		return;
	}
	
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
	this->boardMemoryAllocated = true;
	
	if(prnt == NULL){
		this->g = 0;
		return;
	}
	
	this->g = prnt->getG() + 1;
	this->parent = prnt;
}

state::state(const state& obj){
	this->g = obj.g;
	this->parent = obj.parent;
	if(obj.boardMemoryAllocated == true){
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
}

state::~state(){
	if(this->boardMemoryAllocated){
		for(int i = 0; i < 3; i++){
			delete[] board[i];
		}
		delete[] board;
	}
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
	//int ** board;
	//board = new int*[NUM_ROWS_ON_BOARD];
	//for(int i = 0 ; i < NUM_ROWS_ON_BOARD; i++)
	//{
	//	board[i] = new int[NUM_COLS_ON_BOARD];
	//}

	//board[0][0] = this->board[0][0];
	//board[0][1] = this->board[0][1];
	//board[0][2] = this->board[0][2];
	//board[1][0] = this->board[1][0];
	//board[1][1] = this->board[1][1];
	//board[1][2] = this->board[1][2];
	//board[2][0] = this->board[2][0];
	//board[2][1] = this->board[2][1];
	//board[2][2] = this->board[2][2];
	//return board;
	if(this->boardMemoryAllocated == false){
		int ** boardX = new int*[NUM_ROWS_ON_BOARD];
		for(int i = 0 ; i < NUM_ROWS_ON_BOARD; i++)
		{
			boardX[i] = new int[NUM_COLS_ON_BOARD];
		}
		boardX[0][0] = 0;
		boardX[0][1] = 0;
		boardX[0][2] = 0;
		boardX[1][0] = 0;
		boardX[1][1] = 0;
		boardX[1][2] = 0;
		boardX[2][0] = 0;
		boardX[2][1] = 0;
		boardX[2][2] = 0;
		return boardX;
	}
	return this->board;
}

/**
FUNCTION: getParent()
DESCRIPTION:  Returns the class var parent
RETURN:  //The state from which the current state is generated with one move.
*/
state* state::getParent() const{
	return this->parent;
}

///**
//FUNCTION: overload < operator
//DESCRIPTION: Overloads the < operator so that it can be used to test wheather or not 'this' state is less than the paramater otherState.
//RETURN bool - True if in fact 'this' state is less then otherState
//*/
//bool state::operator< (const state& otherState) const{
//	return this->g < otherState.g;
//}

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
	if(otherState.boardMemoryAllocated == false) return false;
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
		g = otherState.g;
		parent = otherState.parent;
		if(otherState.boardMemoryAllocated && this->boardMemoryAllocated){
			board = new int*[3];
			for(int i = 0 ; i < 3; i++)
			{
				board[i] = new int[3];
			}
			board[0][0] = otherState.getBoard()[0][0];
			board[0][1] = otherState.getBoard()[0][1];
			board[0][2] = otherState.getBoard()[0][2];
			board[1][0] = otherState.getBoard()[1][0];
			board[1][1] = otherState.getBoard()[1][1];
			board[1][2] = otherState.getBoard()[1][2];
			board[2][0] = otherState.getBoard()[2][0];
			board[2][1] = otherState.getBoard()[2][1];
			board[2][2] = otherState.getBoard()[2][2];
		}
		//state newState = *new state(otherState.getBoard(), otherState.getParent());
		//newState.setG(otherState.getG());
		//*this = newState;
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
	cin >> p1 >> p2 >> p3 >> p4 >> p5 >> p6 >> p7 >> p8 >> p9;
	//p1 = 2;
	//p2 = 8;
	//p3 = 3;
	//p4 = 1;
	//p5 = 6;
	//p6 = 4;
	//p7 = 7;
	//p8 = 5;
	//p9 = 0;

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



	x.board = board;
	x.parent= NULL;
	x.g = -1;
	x.boardMemoryAllocated = true;

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
int h1(const state& st){
	int** board = st.getBoard();
	int nMismatchedTiles = 0;
	if(board[0][0] != 1 && board[0][0] != 0)nMismatchedTiles++;
	if(board[0][1] != 2 && board[0][1] != 0)nMismatchedTiles++;
	if(board[0][2] != 3 && board[0][2] != 0)nMismatchedTiles++;
	if(board[1][0] != 8 && board[1][0] != 0)nMismatchedTiles++;
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
int h2(const state& st){
	int** board = st.getBoard();
	int sum = 0;
	if(board[0][0] != 1){
		if(board[0][1] == 1){
			sum += 0;
		}
		else if(board[0][1] == 1){
			sum += 1;
		}
		else if(board[0][2] == 1){
			sum += 2;
		}
		else if(board[1][0] == 1){
			sum += 1;
		}
		else if(board[1][1] == 1){
			sum += 2;
		}
		else if(board[1][2] == 1){
			sum += 3;
		}
		else if(board[2][0] == 1){
			sum += 2;
		}
		else if(board[2][1] == 1){
			sum += 3;
		}
		else if(board[2][2] == 1){
			sum += 4;
		}
	}
	if(board[0][1] != 2){
		if(board[0][0] == 2){
			sum += 1;
		}
		else if(board[0][1] == 2){
			sum += 0;
		}
		else if(board[0][2] == 2){
			sum += 1;
		}
		else if(board[1][0] == 2){
			sum += 2;
		}
		else if(board[1][1] == 2){
			sum += 1;
		}
		else if(board[1][2] == 2){
			sum += 2;
		}
		else if(board[2][0] == 2){
			sum += 3;
		}
		else if(board[2][1] == 2){
			sum += 2;
		}
		else if(board[2][2] == 2){
			sum += 3;
		}
	}
	if(board[0][2] != 3){
		if(board[0][0] == 3){
			sum += 2;
		}
		else if(board[0][1] == 3){
			sum += 1;
		}
		else if(board[0][2] == 3){
			sum += 0;
		}
		else if(board[1][0] == 3){
			sum += 3;
		}
		else if(board[1][1] == 3){
			sum += 2;
		}
		else if(board[1][2] == 3){
			sum += 1;
		}
		else if(board[2][0] == 3){
			sum += 4;
		}
		else if(board[2][1] == 3){
			sum += 3;
		}
		else if(board[2][2] == 3){
			sum += 2;
		}
	}
	if(board[1][0] != 8){
		if(board[0][0] == 8){
			sum += 1;
		}
		else if(board[0][1] == 8){
			sum += 2;
		}
		else if(board[0][2] == 8){
			sum += 3;
		}
		else if(board[1][0] == 8){
			sum += 0;
		}
		else if(board[1][1] == 8){
			sum += 1;
		}
		else if(board[1][2] == 8){
			sum += 2;
		}
		else if(board[2][0] == 8){
			sum += 1;
		}
		else if(board[2][1] == 8){
			sum += 2;
		}
		else if(board[2][2] == 8){
			sum += 3;
		}
	}
	//if(board[1][1] != 0){
	//	if(board[0][0] == 0){
	//		sum += 2;
	//	}
	//	else if(board[0][1] == 0){
	//		sum += 1;
	//	}
	//	else if(board[0][2] == 0){
	//		sum += 2;
	//	}
	//	else if(board[1][0] == 0){
	//		sum += 1;
	//	}
	//	else if(board[1][1] == 0){
	//		sum += 0;
	//	}
	//	else if(board[1][2] == 0){
	//		sum += 1;
	//	}
	//	else if(board[2][0] == 0){
	//		sum += 2;
	//	}
	//	else if(board[2][1] == 0){
	//		sum += 1;
	//	}
	//	else if(board[2][2] == 0){
	//		sum += 2;
	//	}
	//}
	if(board[1][2] != 4){
		if(board[0][0] == 4){
			sum += 3;
		}
		else if(board[0][1] == 4){
			sum += 2;
		}
		else if(board[0][2] == 4){
			sum += 1;
		}
		else if(board[1][0] == 4){
			sum += 2;
		}
		else if(board[1][1] == 4){
			sum += 1;
		}
		else if(board[1][2] == 4){
			sum += 0;
		}
		else if(board[2][0] == 4){
			sum += 3;
		}
		else if(board[2][1] == 4){
			sum += 2;
		}
		else if(board[2][2] == 4){
			sum += 1;
		}
	}
	if(board[2][0] != 7){
		if(board[0][0] == 7){
			sum += 2;
		}
		else if(board[0][1] == 7){
			sum += 3;
		}
		else if(board[0][2] == 7){
			sum += 4;
		}
		else if(board[1][0] == 7){
			sum += 1;
		}
		else if(board[1][1] == 7){
			sum += 2;
		}
		else if(board[1][2] == 7){
			sum += 3;
		}
		else if(board[2][0] == 7){
			sum += 0;
		}
		else if(board[2][1] == 7){
			sum += 1;
		}
		else if(board[2][2] == 7){
			sum += 2;
		}
	}
	if(board[2][1] != 6){
		if(board[0][0] == 6){
			sum += 3;
		}
		else if(board[0][1] == 6){
			sum += 2;
		}
		else if(board[0][2] == 6){
			sum += 3;
		}
		else if(board[1][0] == 6){
			sum += 2;
		}
		else if(board[1][1] == 6){
			sum += 1;
		}
		else if(board[1][2] == 6){
			sum += 2;
		}
		else if(board[2][0] == 6){
			sum += 1;
		}
		else if(board[2][1] == 6){
			sum += 0;
		}
		else if(board[2][2] == 6){
			sum += 1;
		}
	}
	if(board[2][2] != 5){
		if(board[0][0] == 5){
			sum += 4;
		}
		else if(board[0][1] == 5){
			sum += 3;
		}
		else if(board[0][2] == 5){
			sum += 2;
		}
		else if(board[1][0] == 5){
			sum += 3;
		}
		else if(board[1][1] == 5){
			sum += 2;
		}
		else if(board[1][2] == 5){
			sum += 1;
		}
		else if(board[2][0] == 5){
			sum += 2;
		}
		else if(board[2][1] == 5){
			sum += 1;
		}
		else if(board[2][2] == 5){
			sum += 0;
		}
	}
	return sum;
} 


/**
FUNCTION: h3(state&)
DESCRIPTION:  The heuristic function used when double-move operators are allowed.
PARAMS:
st - The state being evaluated against the goal state.
RETURN:
The h3 value of the state passed in.
*/
int h3(const state& st){
	int h2Value = h2(st);
	if(h2Value %2 == 0)
	{
		return (h2Value + 2) / 2;
	}
	else{
		return (h2Value + 1) / 2;
	}
}

/**
FUNCTION: f(int)
DESCRIPTION:  Value of the function f based on the heuristic type (h1 or h2).
PARAMS:
htype - The state being evaluated against the goal state.
RETURN:
The value of function based on the heuristic type.
*/
int f(int htype, const state* st){
	if(htype == 1){
		return st->getG() + h1(*st);
	}
	else if(htype == 2)
	{
		return st->getG() + h2(*st);
	}
	else if(htype == 3)
	{
		return st->getG() + h3(*st);
	}
	else{
		cerr << endl << "ERROR: Illegal Argument to function f() - First argumnet must have value 1 2, or 3" << endl;
		exit(0);
		return -1;
	}
}


