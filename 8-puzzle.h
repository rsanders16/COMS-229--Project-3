#ifndef STATE_H_GUARD
#define STATE_H_GUARD
// ----------
// state.h
// ----------

// Project 3 of Com S 229
// Authour: Ryan K Sanders 

//The number of rows on the playing board.
#define NUM_ROWS_ON_BOARD 3

//The number of columns on the playing board.
#define NUM_COLS_ON_BOARD 3

#include <iostream>
using namespace std;

/**
CLASS: state
DESCRIPTION: Reresents the state of a 8-puzzle
*/
class state{
public:

	/**
	CONSTRUCTOR:  state(int**, state*)
	DESCRIPTION:  Generate a state with a 3x3 board configuration stored in a 2-dimunsional array bd, and a pointer to its parent state.
	PARAMS:
	bd - A pointer the board to be instantiated
	sate - A pointer to the boards parent state
	*/
	state(int **bd, state* prnt);
	
	
	state(int **bd, state* prnt, char* move = "");

    //state(int **bd);

	//state();

	state(const state& obj);

	/**
	DECONSTRUCTOR:
	DESCRIPTION: Destructs "this" state object by freeing the memory of board and parent since they are stored with dynamic memory.
	*/
	~state();

	void setParent(state* prnt);

	/**
	FUNCTION: getG()
	DESCRIPTION:  Returns the class var g
	RETURN:  The number of moves from the inital state to the current state.
	*/
	int getG() const;

	//void setG(int g);

	/**
	FUNCTION: getBoard()
	DESCRIPTION:  Returns the class var board
	RETURN:  // 3x3 configuration of the board.
	*/
	int** getBoard() const;

	/**
	FUNCTION: getParent()
	DESCRIPTION:  Returns the class var parent
	RETURN:  //The state from which the current state is generated with one move.
	*/
	state* getParent() const;

	char* getMove() const;

	/**
	FUNCTION: overload < operator
	DESCRIPTION: Overloads the < operator so that it can be used to test wheather or not 'this' state is less than the paramater otherState.
	RETURN bool - True if in fact 'this' state is less then otherState
	*/
	//bool operator< (const state& otherState) const;

	/**
	FUNCTION: overload == operator
	DESCRIPTION: Overloads the == operator so that it can be used to test wheather or not 'this' state is equal to otherState.
	RETURN bool - True if in fact 'this' state is equal to otherState
	*/
	bool operator== (const state& otherState) const;

	state& operator= (const state& otherState);

	/**
	FUNCTION: overload operator << 
	DESCRIPTION: Follows the spec of project 2 output for a 'state' object
	PARAMS:
		ostr - The outstream that the state will be printed to
		x - The state object
	RETRUN: The outstream used during the execution of this function
	*/
	friend ostream& operator<< (ostream& ostr, const state& x);

	/**
	FUNCTION: overload operator >> 
	DESCRIPTION: Follows the spec of project 3 input.  A single given board state is inputed via standard input.
	PARAMS:
		istr - The instream that the 'this' state should be parsed from
		x - The state to be created
	RETRUN: The instream used during the execution of this function
	*/
	friend istream& operator>> (istream& istr, state& x); 

	

private:

	int g; //Number of moves from the inital state to the current state.

	int **board; // 3x3 configuration of the board. Assume that the square rows are number 0, 1, 2; so are the columns. If the square indexed (i, j) is not occupied by a tile, set board[i][j] to 0. 

	state* parent; //The state from which the current state is generated with one move.

	bool boardMemoryAllocated;

	char* move;

};

/**
FUNCTION: h1(state&)
DESCRIPTION:  The number of mismatched tiles between a state st and the goal state.
PARAMS:
st - The state being evaluated against the goal state.
RETURN:
The number of mismatched tiles.
*/
int h1(const state& st);  

/**
FUNCTION: h2(state&)
DESCRIPTION:  The Manhattan distance between a state st and the goal state.
PARAMS:
st - The state being evaluated against the goal state.
RETURN:
The Manhattan distance.
*/
int h2(const state& st); 

/**
FUNCTION: f(int)
DESCRIPTION:  Value of the function f based on the heuristic type (h1 or h2).
PARAMS:
htype - The state being evaluated against the goal state.
RETURN:
The value of function based on the heuristic type.
*/
int f(int htype, const state* st);

#endif
