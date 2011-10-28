#include "8-puzzle.h"
#include <list>
#include <stack>

using namespace std;

/**
CONSTRUCTOR:  state(int**, state*)
DESCRIPTION:  Generate a state with a 3x3 board configuration stored in a 2-dimunsional array bd, and a pointer to its parent state.
PARAMS:
bd - A pointer the board to be instantiated
prnt - A pointer to the boards parent state
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

	/**
	CONSTRUCTOR:  state(int**, state*)
	DESCRIPTION:  Generate a state with a 3x3 board configuration stored in a 2-dimunsional array bd, and a pointer to its parent state.
	PARAMS:
	bd - A pointer the board to be instantiated
	prnt - A pointer to the boards parent state
	move - A sting value of the move this new state took to get form its parent state.
	*/
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

	/**
	COPY CONSTRUCTOR:  state(const state& obj)
	DESCRIPTION:  Deep copyes obj to this object
	PARAMS:
	obj - The obj that this object is about to become.
	*/
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

	/**
	DECONSTRUCTOR:
	DESCRIPTION: Destructs "this" state object by freeing the memory of board and parent since they are stored with dynamic memory.
	*/
state::~state(){
	if(this->boardMemoryAllocated){
		for(int i = 0; i < 3; i++){
			delete[] board[i];
		}
		delete[] board;
	}
}

	/**
	FUNCTION: setParent()
	DESCRIPTION:  Sets this parent to prnt.  Important and used in the astar function.
	RETURN:  The number of moves from the inital state to the current state.
	*/
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
	FUNCTION: getMove()
	DESCRIPTION:  Returns the move this state took from its parent state
	RETURN:  //The sting value of the move this state took from its parent state
	*/
char* state::getMove() const{
	return this->move;
}

/**
FUNCTION: getBoard()
DESCRIPTION:  Returns the class var board
RETURN:  // 3x3 configuration of the board.
*/
int** state::getBoard() const{
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

/**
FUNCTION: overload == operator
DESCRIPTION: Overloads the == operator so that it can be used to test wheather or not 'this' state is equal to otherState.
RETURN bool - True if in fact 'this' state is equal to otherState
*/
bool state::operator== (const state& otherState) const{
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

	/**
	FUNCTION: overload = operator
	DESCRIPTION: Overloads the = operator so that it can be used assign otherState to this state.
	RETURN state reference - The new state
	*/
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
	return st->getG() + h2(*st);
}

/**
The OPEN list used by the AStar Program.  Notice pointers to states where used rather then just states to help speed up the program and reduce memory usage.
*/
list<state*> OPEN = *new list<state*>();

/**
The CLOSED list used by the AStar Program.  Notice pointers to states where used rather then just states to help speed up the program and reduce memory usage.
*/
list<state*> CLOSED = *new list<state*>();

/**
FUNCTION: abs(int)
DESCRIPTION:  Determines the absolute value of an integer.
PARAMS:
v - The number to be calculated againt
RETURN:
The absolute value of v.
*/
int abs(int v){
	if(v < 0) return -v;
	else return v;
}

/**
FUNCTION: numberOfInversions(state&)
DESCRIPTION:  Calculates the number of inversions a given state has.  Follows guidlines from spec of project 3
PARAMS:
x - The state being evaluated for inversions.
RETURN:
A number greater then 0 that represents the number of inversions a puzzle state has.
*/
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

/**
FUNCTION: printPath()
DESCRIPTION:  Given a current state, this function prints out the path from the inital state to the goal state.  Places linked list on stack to reverse order before printing it out.  This part of the program also clean up the memory.
PARAMS:
current_state - Will be the goal state, which will have a pointer to its parent which will have a pointer to its parent and so on unitl the intail state.
*/
void printPath(state* current_state, state* goal, bool allowDoubleMoves){

	stack<state> pathStack = *new stack<state>();
	int moveCount = 0;
	while(current_state->getG() != -1){
		pathStack.push(*current_state);
		current_state = current_state->getParent();
		moveCount++;
	}
	for(int i = 0 ; i < moveCount ; i++){
		cout << pathStack.top().getMove();
		cout << endl << endl;
		cout << pathStack.top();
		cout << endl;
		pathStack.pop();

	}
	cout << moveCount << " moves in total.";
	cout << endl << endl;

	//NOTICE: This is where memory clean up happens.
	//DELETION OF CURRENT LIST
	list<state*>::iterator delIter;
	list<state*>::iterator deleteiter;
	deleteiter = OPEN.erase(OPEN.begin(),OPEN.end());
	CLOSED.erase(CLOSED.begin(), CLOSED.end());
}

/**
FUNCTION: getInitalizedBoard()
DESCRIPTION:  Allocates a new board and swaps two values (makes a move)
PARAMS:
	p1 - place in oldBoard is swaped with place in oldBoard of index p2
	p2 - place in oldBoard is swaped with place in oldBoard of index p1
*/
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

/**
FUNCTION: neighbor_nodes()
DESCRIPTION:  Determines all neighbors of a given state, including double move neighbors if allowDoubleMoves is set to true.
PARAMS:
state - The parent state
allowDobuleMoves - If set to true, then double move neighbors are added to the list that is returned to the caller.
RETURN:  A list of leagal neighboard of the parent
*/
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



/**
FUNCTION: astar()
DESCRIPTION:
	The A* algorithm maintains two lists, OPEN and CLOSED, of 8-Puzzle states.  The
	states in the CLOSED list have been expanded; that is, they have been examined
	and their successor states have been generated.  The states in the OPEN list
	have yet to be expanded.
PARAMS:
state - The parent state
allowDobuleMoves - If set to true, then double move neighbors are added to the list that is returned to the caller.
RETURN:  A list of leagal neighboard of the parent
*/
bool astar(state* start, state* goal, int h_function_to_use){

	bool allowDoubleMoves = false;
	if(h_function_to_use == 3){
		allowDoubleMoves = true;
	}

	//1. Put the start state S0 on OPEN.  Let g(S0) = 0 and estimate
    //h(S0).
	OPEN.push_back(&*start);

	while(!OPEN.empty()){
		list<state*>::iterator i = OPEN.begin();
		state* S = *i;
		for(i = OPEN.begin() ; i != OPEN.end(); ++i){
			if(f(h_function_to_use, *i) < f(h_function_to_use, S)){
				S = *i;
			}
		}

	    //3. Remove from OPEN and place on CLOSED a state S whose f value is
        //minimum.  If there are several states with the same minimum
        //value, arbitrarily remove one; if one is the goal state, then
        //remove the goal state.
		CLOSED.push_back(S);
		OPEN.remove(S);


		//4. If S is the goal state, exit successfully and print out the
        //entire solution path (step-by-step state transitions)
		if(*S == *goal){
			printPath(S, goal, allowDoubleMoves);
			return true;	
		}
		
	    //5. Otherwise, generate S's all possible successor states in one
        //valid move and set their parent pointers back to S.  For every
        //successor state T of S:
		else{
			list<state*> neighbors = neighbor_nodes(S,allowDoubleMoves);
			list<state*>::iterator neighbor_iter;

			for(neighbor_iter = neighbors.begin() ; neighbor_iter != neighbors.end() ; ++neighbor_iter){

				state* old_value = *neighbor_iter;
				state* current_neighbor = *neighbor_iter;

				//Determine if current_neighbor is in open list.
				list<state*>::iterator open_list_iter;
				bool current_neighbor_is_in_open_list = false;
				for(open_list_iter = OPEN.begin() ; open_list_iter != OPEN.end() ; ++open_list_iter){
					if(**open_list_iter == *current_neighbor){
						current_neighbor_is_in_open_list = true;
						old_value = *open_list_iter;
					}
				}

				//Determine if current_neighbor is in closed list.
				list<state*>::iterator closed_list_iter;
				bool current_neighbor_is_in_closed_list = false;
				for(closed_list_iter = CLOSED.begin() ; closed_list_iter != CLOSED.end() ; ++closed_list_iter){
					if(**closed_list_iter == *current_neighbor){
						current_neighbor_is_in_closed_list = true;
						old_value = *closed_list_iter;
					}
				}

				//If T is not already on OPEN or CLOSED, then put it on OPEN. 
				if(current_neighbor_is_in_open_list == false && current_neighbor_is_in_closed_list == false ){
					OPEN.push_back(current_neighbor);
				}

				//If T is already on OPEN, compare its old and new f values
     			//and choose the minimum, resetting its parent pointer (along
     			//the path yielding the lowest g(T)).
				else if(current_neighbor_is_in_open_list){
					if(f(h_function_to_use, current_neighbor) < f(h_function_to_use, old_value)){
						(*old_value).setParent(S);
					}
				}

				//If T is on CLOSED and its new f value is less than the old
   			    //one, remove T from CLOSED, put it on OPEN and reset its parent
   		        //pointer.
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
	//2. If OPEN is empty, exit with failure.
	return false;
}



