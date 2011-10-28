#include "8-puzzle.h"
#include <list>
#include <stack>

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
	
	this->move = "UNKNOWN";
	this->g = prnt->getG() + 1;
	this->parent = prnt;
}


state::state(int **bd, state* prnt, char * move){
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
	
	this->move = move;
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
			this->move = obj.move;
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

char* state::getMove() const{
	return this->move;
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
			move = otherState.getMove();
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
		
		return -1;
	}
}

list<state*> OPEN = *new list<state*>();
list<state*> CLOSED = *new list<state*>();

int abs(int v){
	if(v < 0) return -v;
	else return v;
}

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
		//if(pathStack.top().getBoard()[0][0] == 0)curPosOf0 = 0;
		//else if(pathStack.top().getBoard()[0][1] == 0)curPosOf0 = 1;
		//else if(pathStack.top().getBoard()[0][2] == 0)curPosOf0 = 2;
		//else if(pathStack.top().getBoard()[1][0] == 0)curPosOf0 = 3;
		//else if(pathStack.top().getBoard()[1][1] == 0)curPosOf0 = 4;
		//else if(pathStack.top().getBoard()[1][2] == 0)curPosOf0 = 5;



		//else if(pathStack.top().getBoard()[2][0] == 0)curPosOf0 = 6;
		//else if(pathStack.top().getBoard()[2][1] == 0)curPosOf0 = 7;
		//else if(pathStack.top().getBoard()[2][2] == 0)curPosOf0 = 8;
		//if(curPosOf0 < lastPosOf0){
		//	if(curPosOf0 == lastPosOf0 - 1){
		//		cout << "RIGHT";
		//	}
		//	else if(curPosOf0 == lastPosOf0 - 2 && allowDoubleMoves){
		//		cout << "DBL-RIGHT";
		//	}
		//	else if( abs(curPosOf0 - lastPosOf0) == 6 && allowDoubleMoves){
		//		cout << "DBL-DOWN";
		//	}
		//	else{
		//		cout << "DOWN";
		//	}
		//}
		//else{
		//	if(curPosOf0 == lastPosOf0 + 1){
		//		cout << "LEFT";
		//	}
		//	else if(curPosOf0 == lastPosOf0 + 2 && allowDoubleMoves){
		//		cout << "DBL-LEFT";
		//	}
		//	else if( abs(curPosOf0 - lastPosOf0) == 6 && allowDoubleMoves){
		//		cout << "DBL-UP";
		//	}
		//	else{
		//		cout << "UPPw";
		//	}
		//}
		
		//if(pathStack.top().getBoard()[0][0] == 0)lastPosOf0 = 0;
		//else if(pathStack.top().getBoard()[0][0] == 0)lastPosOf0 = 0;
		//else if(pathStack.top().getBoard()[0][1] == 0)lastPosOf0 = 1;
		//else if(pathStack.top().getBoard()[0][2] == 0)lastPosOf0 = 2;
		//else if(pathStack.top().getBoard()[1][0] == 0)lastPosOf0 = 3;
		//else if(pathStack.top().getBoard()[1][1] == 0)lastPosOf0 = 4;
		//else if(pathStack.top().getBoard()[1][2] == 0)lastPosOf0 = 5;
		//else if(pathStack.top().getBoard()[2][0] == 0)lastPosOf0 = 6;
		//else if(pathStack.top().getBoard()[2][1] == 0)lastPosOf0 = 7;
		//else if(pathStack.top().getBoard()[2][2] == 0)lastPosOf0 = 8;
		//////////////////////////////////////////////////////////////////////////////////////////////
		///END OF MOVE PRINTER
		//////////////////////////////////////////////////////////////////////////////////////////////
		cout << pathStack.top().getMove();
		cout << endl << endl;
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
		neighbors.push_back(&(*new state(getInitalizedBoard(0,1, board), s, "LEFT")));
		neighbors.push_back(&(*new state(getInitalizedBoard(0,3, board), s, "UP")));
		if(allowDoubleMoves){

				newBoard[0][0] = board[0][1];
				newBoard[0][1] = board[0][2];
				newBoard[0][2] = board[0][0];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s, "DBL-LEFT")));

				newBoard[0][0] = board[1][0];
				newBoard[0][1] = board[1][0];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[2][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[2][2];

				newBoard[2][0] = board[0][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s, "DBL-UP")));
		}
	}
	else if(board[0][1] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(1,2, board), s, "LEFT")));
		neighbors.push_back(&(*new state(getInitalizedBoard(1,0, board), s, "RIGHT")));
		neighbors.push_back(&(*new state(getInitalizedBoard(1,4, board), s, "UP")));
		if(allowDoubleMoves){
				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[1][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[2][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[0][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s, "DBL-UP")));
		}
	}
	else if(board[0][2] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(2,5, board), s, "UP")));
		neighbors.push_back(&(*new state(getInitalizedBoard(2,1, board), s, "RIGHT")));
		if(allowDoubleMoves){
				newBoard[0][0] = board[0][2];
				newBoard[0][1] = board[0][0];
				newBoard[0][2] = board[0][1];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s, "DBL-RIGHT")));

				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[1][2];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[2][2];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[0][2];
				neighbors.push_back(&(*new state(newBoard, s, "DBL-UP")));
		}
	}
	else if(board[1][0] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(3,0, board), s, "DOWN")));
		neighbors.push_back(&(*new state(getInitalizedBoard(3,6, board), s, "UP")));
		neighbors.push_back(&(*new state(getInitalizedBoard(3,4, board), s, "LEFT")));
		if(allowDoubleMoves){
				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[1][1];
				newBoard[1][1] = board[1][2];
				newBoard[1][2] = board[1][0];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s, "DBL-LEFT")));
		}
	}
	else if(board[1][1] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(4,3, board), s, "RIGHT")));
		neighbors.push_back(&(*new state(getInitalizedBoard(4,1, board), s, "DOWN")));
		neighbors.push_back(&(*new state(getInitalizedBoard(4,5, board), s, "LEFT")));
		neighbors.push_back(&(*new state(getInitalizedBoard(4,7, board), s, "UP")));
	}
	else if(board[1][2] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(5,8, board), s, "UP")));
		neighbors.push_back(&(*new state(getInitalizedBoard(5,2, board), s, "DOWN")));
		neighbors.push_back(&(*new state(getInitalizedBoard(5,4, board), s, "RIGHT")));
		if(allowDoubleMoves){
				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[1][2];
				newBoard[1][1] = board[1][0];
				newBoard[1][2] = board[1][1];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s, "DBL-RIGHT")));
		}
	}
	else if(board[2][0] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(6,7, board), s, "LEFT")));
		neighbors.push_back(&(*new state(getInitalizedBoard(6,3, board), s, "DOWN")));
		if(allowDoubleMoves){
				newBoard[0][0] = board[2][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[0][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = board[1][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s, "DBL-DOWN")));

				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = board[2][1];
				newBoard[2][1] = board[2][2];
				newBoard[2][2] = board[2][0];
				neighbors.push_back(&(*new state(newBoard, s, "DBL-LEFT")));
		}
	}
	else if(board[2][1] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(7,4, board), s, "DOWN")));
		neighbors.push_back(&(*new state(getInitalizedBoard(7,6, board), s, "RIGHT")));
		neighbors.push_back(&(*new state(getInitalizedBoard(7,8, board), s, "LEFT")));
		if(allowDoubleMoves){
				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[2][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[0][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[1][1];
				newBoard[2][2] = board[2][2];
				neighbors.push_back(&(*new state(newBoard, s, "DBL-DOWN")));
		}
	}
	else if(board[2][2] == 0){
		neighbors.push_back(&(*new state(getInitalizedBoard(8,7, board), s, "RIGHT")));
		neighbors.push_back(&(*new state(getInitalizedBoard(8,5, board), s, "DOWN")));
		if(allowDoubleMoves){
				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[0][2];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[1][2];

				newBoard[2][0] = board[2][2];
				newBoard[2][1] = board[2][0];
				newBoard[2][2] = board[2][1];
				neighbors.push_back(&(*new state(newBoard, s, "DBL-RIGHT")));
								
				newBoard[0][0] = board[0][0];
				newBoard[0][1] = board[0][1];
				newBoard[0][2] = board[2][2];

				newBoard[1][0] = board[1][0];
				newBoard[1][1] = board[1][1];
				newBoard[1][2] = board[0][2];

				newBoard[2][0] = board[2][0];
				newBoard[2][1] = board[2][1];
				newBoard[2][2] = board[1][2];
				neighbors.push_back(&(*new state(newBoard, s, "DBL-DOWN")));
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



