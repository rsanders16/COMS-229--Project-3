#include <iostream>
#include <string>
#include "8-puzzle.h"
#include <list>
#include <vector>

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




//state& reconstructPath(vector<state> came_from, state& current_node){
//     if(came_from[current_node]){
//		 state p;
//         p = reconstructPath(came_from, came_from[current_node]);
//		 //came_from.insert(current_node);
//         //return (p + current_node);
//	 }
//     else{
//         return current_node;
//	 }
//}


//state& lowestFScore(vector<state> set)
//{
//
//}

void remove(vector<state>& set, state& x){

}

bool contains(vector<state>& set, state& x){
	return 0;
}

void replace(vector<state>& set, state& oldX, state& newX){

}



//state& astar(state& start, state& goal){
//
//
//	   /*vector<state> C;
//
//   SS.push_back("The number is 10");
//   SS.push_back("The number is 20");
//   SS.push_back("The number is 30");
//
//   cout << "Loop by index:" << endl;
//
//   int ii;
//   for(ii=0; ii < SS.size(); ii++)
//   {
//      cout << SS[ii] << endl;
//   }*/
//	
//	 state x;
//	 vector<state> CLOSED;    // The set of nodes already evaluated.
//     vector<state> OPEN;    // The set of tentative nodes to be evaluated, initially containing the start node
//	 vector<state> PATH;
//	 int tentative_g_score;
//	 bool tentative_is_better;
//	 int h_score;
//	 int f_score;
//	 
//    
//	 start.g = 0;  // Cost from start along best known path.
//     h_score = h1(start);
//	 f_score = start.getG() + h_score;    // Estimated total cost from start to goal through y.
// 
//	 while(!OPEN.empty()){
//
//         x = lowestFScore(OPEN);
//         if(x == goal){
//			 return reconstructPath(PATH, PATH[PATH.size()-1]);
//		 }
//	
//		 remove(OPEN, x);
//		 CLOSED.push_back(x);
//		 
//		 for(int i = 0 ; i < neighbor_nodes(x).size() ; i++){
//			 state y = neighbor_nodes(x)[i];
//
//             if(contains(CLOSED, y)){
//				 continue;
//			 }
//
//             tentative_g_score = x.getG() + dist_between(x,y);
//			
//             if(contains(OPEN, y)){
//				 OPEN.push_back(y);
//				 tentative_is_better = 1;
//			 }
//             else if (tentative_g_score < y.getG()){
//                 tentative_is_better = 1;
//			 }
//             else{
//                 tentative_is_better = 0;
//			 }
//             if(tentative_is_better == 1){
//				 replace(PATH, y, x); 
//				 y.g = tentative_g_score;
//				 f_score[y] = y.getG() + h1(y);
//			 }
//	 }
//     cerr << endl << "ERROR: Exiting Program" << endl;
//	 exit(1);
// 
//}



int main(){

	

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
		
		state state1;
		cin >> state1;
		cout << endl << state1 << endl;

		if(numberOfInversions(state1) % 2 == 0)
		{
			cout << "No solution exists!" << endl << endl;
		}
		else
		{
			cout << "A solution exists" << endl << endl;
		}

		cout << "Inital State (input):" << endl;
		cout << ">>";
		
		if(cin.peek() == 10)cin.get();
	}

	cout << endl << endl;
	return 0;
}