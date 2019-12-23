#include <iostream>
#include <vector>
#include "Move.h"
#include "PositionOthello.h"

using namespace std;

PositionOthello::PositionOthello() {
	//player 2 = white
	//player 1 = black

	currentPlayer = 1;
	nbOfMoveAlreadyPlayed = 0;

	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			board[i][j] = 0;
		}
	}

	board[3][3] = 2;
	board[4][3] = 1;
	board[4][4] = 2;
	board[3][4] = 1;
}

void PositionOthello::printBoard() {

	cout << "    ";
	for(char k = 65; k<73; k++) {
		cout << " " << k << " ";
	}

	cout << endl;

	for(int i=0; i<8; i++) {
		cout << " " << i+1 << ": "; // i = rows
		for(int j=0; j<8; j++) {
			//cout << " " << j << " "; j =colomn
			cout << " " << board[i][j] << " ";
		}
		cout << endl;
		cout << endl;
	}
}

void PositionOthello::applyMove(Move const& m) {
   board[m.getX()][m.getY()] = currentPlayer;
}

int PositionOthello::getNbOfMoveAlreadyPlayed() {
   return nbOfMoveAlreadyPlayed;
}

void PositionOthello::passTurn() {
	if (currentPlayer == 1) {
		//TODO: iterate through board to check if indeed there are no possible moves
		currentPlayer = 2;
	} else {
		currentPlayer = 1;
	}
}

bool PositionOthello::playerPlay(Move& m) {
   //bool apply = false;
   int player;
   if(currentPlayer==1) player = 2;
   else if(currentPlayer==2) player = 1;

   //the move must be in an empty spot (=0)
   if(board[m.getX()][m.getY()] != 0) {
      cout << " != 0 cannot play this move here" << endl;
      return false;
   }
   //if the move has no enemy piece adjacent then it's not valid
   if(board[m.getX()-1][m.getY()] != player 
      && board[m.getX()+1][m.getY()] != player
      && board[m.getX()][m.getY()-1] != player
      && board[m.getX()][m.getY()+1] != player
      && board[m.getX()+1][m.getY()+1] != player
      && board[m.getX()+1][m.getY()-1] != player
      && board[m.getX()-1][m.getY()+1] != player
      && board[m.getX()-1][m.getY()-1] != player) {
      cout << " no ennemy piece adjacent to this move " << endl;
         return false;
      }

   //------ checking all pieces needed to be changed ------
    checkRight(m);
    checkLeft(m);
    checkUp(m);
    checkDown(m);
    checkDiagonalRightUp(m);
    checkDiagonalLeftUp(m);
    checkDiagonalRightDown(m);
    checkDiagonalLeftDown(m);

   //no pieces to return so move is not valid
   if(tabRight.empty() 
      && tabLeft.empty() 
      && tabUp.empty() 
      && tabDown.empty()
      && tabDiaRightUp.empty() 
      && tabDiaRightDown.empty() 
      && tabDiaLeftDown.empty() 
      && tabDiaLeftUp.empty()) {
      cout << "no pieces to return so cannot play move" << endl;
      return false;
   }
   
   //return all pieces that need to be returned
   applyMove(m);
      if(!tabRight.empty()) {
         for(int i=0; i<(int)tabRight.size(); i++) {
            applyMove(tabRight[i]);
            //cout << "tabRight " << endl;
         }
      }
      if(!tabLeft.empty()) {
         for(int i=0; i<(int)tabLeft.size(); i++) {
            applyMove(tabLeft[i]);
            //cout << "tabLeft " << endl;
         }
      }
      if(!tabUp.empty()) {
         for(int i=0; i<(int)tabUp.size(); i++) {
            applyMove(tabUp[i]);
            //cout << " tabUp" << endl;
         }
      }
      if(!tabDown.empty()) {
         for(int i=0; i<(int)tabDown.size(); i++) {
            applyMove(tabDown[i]);
            //cout << " tabDown" << endl;
         }
      }
      if(!tabDiaLeftDown.empty()) {
         for(int i=0; i<(int)tabDiaLeftDown.size(); i++) {
            applyMove(tabDiaLeftDown[i]);
            //cout << "tabDiaLeftDown " << endl;
         }
      }
      if(!tabDiaRightDown.empty()) {
         for(int i=0; i<(int)tabDiaRightDown.size(); i++) {
            applyMove(tabDiaRightDown[i]);
            //cout << " tabDiaRightDown" << endl;
         }
      }
      if(!tabDiaLeftUp.empty()) {
         for(int i=0; i<(int)tabDiaLeftUp.size(); i++) {
            applyMove(tabDiaLeftUp[i]);
           //cout << " tabDiaLeftUp" << endl;
         }
      }
      if(!tabDiaRightUp.empty()) {
         for(int i=0; i<(int)tabDiaRightUp.size(); i++) {
            applyMove(tabDiaRightUp[i]);
            //cout << " tabDiaRightUp" << endl;
         }
      }

   nbOfMoveAlreadyPlayed++;
   //cout << "increased nb of moves" << endl;
   tabRight.clear();
   tabLeft.clear();
   tabUp.clear();
   tabDown.clear();
   tabDiaRightUp.clear();
   tabDiaRightDown.clear();
   tabDiaLeftUp.clear();
   tabDiaLeftDown.clear();
   //cout << "cleared all vectors" << endl;
   return true;
}

bool PositionOthello::checkRight(Move const& m) {
   if(board[m.getX()][m.getY()+1] == currentPlayer) {
   	cout << "1" << endl;
      return true;
   }
   if(m.getY()+1 >= 7 || board[m.getX()][m.getY()+1] == 0) {
      tabRight.clear();
      cout << "CLEAR 1" << endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX(), m.getY()+1);
      tabRight.push_back(nextMove);
      cout << "R1" << endl;
      return checkRight(nextMove);
   }
}

bool PositionOthello::checkLeft(Move const& m) {
   if(board[m.getX()][m.getY()-1] == currentPlayer) {
   	cout << "2" << endl;
      return true;
   }
   if(m.getY()-1 <= 0 || board[m.getX()][m.getY()-1] == 0) {
      tabLeft.clear();
      cout << "CLEAR 2" << endl;
      return false;
   }
   else {
      Move nextMove = Move(m.getX(), m.getY()-1);
      tabLeft.push_back(nextMove);
      cout << "R2" << endl;
      return checkLeft(nextMove);
   }
}

bool PositionOthello::checkUp(Move const& m) {
   if(board[m.getX()-1][m.getY()] == currentPlayer) {
   	cout << "3" << endl;
      return true;
   }
   if(m.getX()-1 <= 0 || board[m.getX()-1][m.getY()] == 0) {
      tabUp.clear();
      cout << "CLEAR 3" << endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX()-1, m.getY());
      tabUp.push_back(nextMove);
      cout << "R3" << endl;
      return checkUp(nextMove);
   }
}

bool PositionOthello::checkDown(Move const& m) {
   if(board[m.getX()+1][m.getY()] == currentPlayer) {
   	cout << "4" << endl;
      return true;
   }
   if(m.getX()+1 >= 7 || board[m.getX()+1][m.getY()] == 0) {
      tabDown.clear();
      cout << "CLEAR 4" << endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX()+1, m.getY());
      tabDown.push_back(nextMove);
      cout << "R4" << endl;
      return checkDown(nextMove);
   }
}

bool PositionOthello::checkDiagonalRightUp(Move const& m) {
   // cout << "sizeof(int) = " << sizeof(int) << endl;
   // cout << "sizeof(board) = " << sizeof(board) << endl;
   // cout << "(sizeof(board)/sizeof(int)) = " << (sizeof(board)/sizeof(int)) << endl;
   if(board[m.getX()-1][m.getY()+1] == currentPlayer) {
   	cout << "5" << endl;
      return true;
   }
   if(m.getY()+1 >= 7 || m.getX()-1 <= 0 || board[m.getX()-1][m.getY()+1] == 0) {
      tabDiaRightUp.clear();
      cout << "CLEAR 5" << endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX()-1, m.getY()+1);
      tabDiaRightUp.push_back(nextMove);
      cout << "R5" << endl;
      return checkDiagonalRightUp(nextMove);
   }
}

bool PositionOthello::checkDiagonalLeftUp(Move const& m) {
   if(board[m.getX()-1][m.getY()-1] == currentPlayer) {
   	cout << "6" << endl;
      return true;
   }
   if(m.getY()-1 <= 0 || m.getX()-1 <= 0 || board[m.getX()-1][m.getY()-1] == 0) {
      tabDiaLeftUp.clear();
      cout << "CLEAR 6" << endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX()-1, m.getY()-1);
      tabDiaLeftUp.push_back(nextMove);
      cout << "R6" << endl;
      return checkDiagonalLeftUp(nextMove);
   }
}

bool PositionOthello::checkDiagonalRightDown(Move const& m) {
   if(board[m.getX()+1][m.getY()+1] == currentPlayer) {
   	cout << "7" << endl;
      return true;
   }
   if(m.getX()+1 >= 7 || m.getY()+1 >= 7 || board[m.getX()+1][m.getY()+1] == 0) {
      tabDiaRightDown.clear();
      cout << "CLEAR 7" << endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX()+1, m.getY()+1);
      tabDiaRightDown.push_back(nextMove);
      cout << "R7" << endl;
      return checkDiagonalRightDown(nextMove);
   }
}

bool PositionOthello::checkDiagonalLeftDown(Move const& m) {
   if(board[m.getX()+1][m.getY()-1] == currentPlayer) {
   	cout << "8" << endl;
      return true;
   }
   if(m.getX()+1 >= 7 || m.getY()-1 == 0 || board[m.getX()+1][m.getY()-1] == 0) {
      tabDiaLeftDown.clear();
      cout << "CLEAR 8" << endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX()+1, m.getY()-1);
      tabDiaLeftDown.push_back(nextMove);
      cout << "R8" << endl;
      return checkDiagonalLeftDown(nextMove);
   }
}

int * PositionOthello::computeScore(int * res) {
	int cpt0 = 0, cpt1 = 0, cpt2 = 0;
	if(gameOver()) {
		for(int i=0; i<8; i++) {
	      for(int j=0; j<8; j++) {
	         if(board[i][j] == 1) cpt1++; 
	         if(board[i][j] == 2) cpt2++;
	         else cpt0++;
	      }
	   }
	   if(cpt0>0 && cpt1>cpt2) {
	   	cpt1+=cpt0;
	   	res[0] = cpt1;
	   }
	   if(cpt0>0 && cpt2>cpt1) {
	   	cpt2+=cpt0; 
	   	res[1] = cpt2;
	   }
	   else {
	   	res[0] = cpt1;
	   	res[1] = cpt2;
	   }
	}
	return res;
}

int PositionOthello::winner() {
	int res[2];
	int *resptr = computeScore(res);
	if(resptr[0]>resptr[1]) return 1;
	if(resptr[1]>resptr[0]) return 2;
	else return 0; //draw
}

void PositionOthello::computerPlay() {
   //program must first check all the possible moves Move to make
   //iterate board and check and construct all the possible moves that could be made
   //store possible moves in a vector?
   //then eval all the moves and check which one is the best
   //here I could use threads to eval several moves in parallel
   //just this would be only depth 1 but then if we can to check for more depth so need to use minMax
}

int PositionOthello::getCurrentPlayer() {
   return currentPlayer;
}

void PositionOthello::changeTurn() {
	if(currentPlayer == 1) currentPlayer = 2;
	else currentPlayer = 1;
}

bool PositionOthello::gameOver() {
   for(int i=0; i<8; i++) {
      for(int j=0; j<8; j++) {
         if(board[i][j] == 0) {
            return false;
         }
      }
   }
	return true;
}

Move PositionOthello::minMax(int depth) {

   if (gameOver()==true or depth == 0) {
      //return winning score or eval();
   }
    
   //int bestScore;
   Move bestMove(0,0);

   // if (nœud == MAX) { //=Programme
   //    bestScore = -INFINITY;
   //    for (each possible move m) {
   //       make move m;
   //       int score = minimax (depth - 1)
   //       unmake move m;
   //       if (score > bestScore) {
   //          bestScore = score;
   //          bestMove = m ;
   //       }
   //    }
   // }
   // else { //type MIN = adversaire
   //    bestScore = +INFINITY;
   //    for (each possible move m) {
   //       make move m;
   //       int score = minimax (depth - 1)
   //       unmake move m;
   //       if (score < bestScore) {
   //          bestScore = score;
   //          bestMove = m ;
   //       }
   //    }
   // }
   //on othello website they return bestScore but should we return best move??
   //return bestScore;

   return bestMove;
}

