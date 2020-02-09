#include <iostream>
#include <string>

#include "PositionOthello.h"
#include "Move.h"

using namespace std;

bool checkCoord(string const& s) {
	if(s.length() != 2) return false;
	if(s[1]<65 || s[1]>72 || s[0]<49 || s[0]>56) return false;
	return true;
}

int main() {

	cout << "HOW TO PLAY" << endl;
	cout << "" << endl;

	PositionOthello board = PositionOthello();

	board.printBoard();

	while(!board.gameOver()) {
		cout << endl;
		cout << "Player " << board.getCurrentPlayer() << " your next move is (enter the coordinates : number then letter \n if there is no possible move you can skip your turn by typing skip)" << endl;
		string coord;
		cin >> coord;
		if(cin.fail()) {
          cin.clear(); 
          cin.ignore(std::numeric_limits<int>::max(),'\n'); 
          cout << "mauvaise entree 1" << endl;
      	}
      	if(coord == "skip") {
      		board.skipTurn();
      	}
		while(!checkCoord(coord) && coord != "skip") {
			cout << "Try again, you must enter the coordinates : letter and then number next to each other (no space)" << endl;
			// string coord;
			cin >> coord;
			if(cin.fail()) {
		        cin.clear(); 
		        cin.ignore(std::numeric_limits<int>::max(),'\n'); 
	            cout << "mauvaise entree 2" << endl;
   	        }
		}
		if(checkCoord(coord)) {
			Move m = Move(coord[0], coord[1]);
			//cout << "Move m.x = " << m.getX() << " Move m.y = " << m.getY() << endl;
			if(board.playerPlay(m) == false) {
				cout << "cannot make that move" << endl;
			} else {
				cout << "Ok, let's make that move" << endl;
				board.changeTurn();
				board.printBoard();
				//cout << "nb of turns played = " << board.getNbOfMoveAlreadyPlayed() << endl;
			}
			//cout << "end of if checkCoord true" << endl;

		}
		// while(!checkCoord(coord)) {
		// 	cout << "Try again, you must enter the coordinates : letter and then number next to each other (no space)" << endl;
		// 	string coord;
		// 	cin >> coord;
		// }
	}

	cout << "The game is over and the winner is player " << board.winner() << endl;
	int res[2];
	int *resptr = board.computeScore(res);
	cout << "player 1 has " << resptr[0] << " points and player 2 has " << resptr[1] << " points " << endl;
	

	return 0;
}
