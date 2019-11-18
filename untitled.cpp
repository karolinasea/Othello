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

	cout << "   ";
	for(char k = 65; k<73; k++) {
		cout << " " << k << " ";
	}

	cout << endl;

	for(int i=0; i<8; i++) {
		cout << " " << i+1 << " "; // i = rows
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

bool PositionOthello::playerPlay(Move& m) {
   int player;
   if(currentPlayer==1) player = 2;
   else if(currentPlayer==2) player = 1;
   //first we check that the move is on an empty spot
   //if(board[m.getX()][m.getY()] != 0) return false;

   //we check if the spot is free and adjacent to at least one ennemy player
   if(board[m.getX()][m.getY()] != 0 && (
      board[m.getX()-1][m.getY()] != player 
      || board[m.getX()+1][m.getY()] != player
      || board[m.getX()][m.getY()-1] != player
      || board[m.getX()][m.getY()+1] != player
      || board[m.getX()+1][m.getY()+1] != player
      || board[m.getX()+1][m.getY()-1] != player
      || board[m.getX()-1][m.getY()+1] != player
      || board[m.getX()-1][m.getY()-1] != player)) {
         return false;
      }

   //------ checking all pieces needed to be changed ------

   if(board[m.getX()][m.getY()+1] == player) {
      tabRight.clear();
      Move nextMove = Move(m.getX(), m.getY()+1);
      tabRight.push_back(nextMove);
      checkRight(nextMove);
   }
   if(board[m.getX()][m.getY()-1] == player) {
      tabLeft.clear();
      Move nextMove = Move(m.getX(), m.getY()-1);
      tabLeft.push_back(nextMove);
      checkLeft(nextMove);
   }
   if(board[m.getX()-1][m.getY()] == player) {
      tabUp.clear();
      Move nextMove = Move(m.getX()-1, m.getY());
      tabUp.push_back(nextMove);
      checkUp(nextMove);
   }
   if(board[m.getX()+1][m.getY()] == player) {
      tabDown.clear();
      Move nextMove = Move(m.getX()+1, m.getY());
      tabDown.push_back(nextMove);
      checkDown(nextMove);
   }
   if(board[m.getX()-1][m.getY()+1] == player) {
      tabDiaRightUp.clear();
      Move nextMove = Move(m.getX()-1, m.getY()+1);
      tabDiaRightUp.push_back(nextMove);
      checkDiagonalRightUp(nextMove);
   }
   if(board[m.getX()-1][m.getY()-1] == player) {
      tabDiaLeftUp.clear();
      Move nextMove = Move(m.getX()-1, m.getY()-1);
      tabDiaLeftUp.push_back(nextMove);
      checkDiagonalLeftUp(nextMove);
   }
   if(board[m.getX()+1][m.getY()+1] == player) {
      tabDiaRightDown.clear();
      Move nextMove = Move(m.getX()+1, m.getY()+1);
      tabDiaRightDown.push_back(nextMove);
      checkDiagonalRightDown(nextMove);
   }
   if(board[m.getX()+1][m.getY()-1] == player) {
      tabDiaLeftDown.clear();
      Move nextMove = Move(m.getX()+1, m.getY()-1);
      tabDiaLeftDown.push_back(nextMove);
      checkDiagonalLeftDown(nextMove);
   }

   //------ end ------

   if(tabRight.empty() && tabLeft.empty() && tabUp.empty() && tabDown.empty()
      && tabDiaRightUp.empty() && tabDiaRightDown.empty() && tabDiaLeftDown.empty() 
      && tabDiaLeftUp.empty()) {
      //no pieces to return so move is not valid
      return false;
   }
   else { //return all pieces that need to be returned
      for(int i=0; i<(int)tabRight.size(); i++) {
         applyMove(tabRight[i]);
      }
      for(int i=0; i<(int)tabLeft.size(); i++) {
         applyMove(tabRight[i]);
      }
      for(int i=0; i<(int)tabUp.size(); i++) {
         applyMove(tabRight[i]);
      }
      for(int i=0; i<(int)tabDown.size(); i++) {
         applyMove(tabRight[i]);
      }
      for(int i=0; i<(int)tabDiaLeftDown.size(); i++) {
         applyMove(tabRight[i]);
      }
      for(int i=0; i<(int)tabDiaRightDown.size(); i++) {
         applyMove(tabRight[i]);
      }
      for(int i=0; i<(int)tabDiaLeftUp.size(); i++) {
         applyMove(tabRight[i]);
      }
      for(int i=0; i<(int)tabDiaRightUp.size(); i++) {
         applyMove(tabRight[i]);
      }
   }
   nbOfMoveAlreadyPlayed++;
   return true;
}

   //then we check that the move can return at least one piece
   //need a recursive function for the move the player wants to make
   // if(board[m.getX()-1][m.getY()] == player 
   //    || board[m.getX()+1][m.getY()] == player
   //    || board[m.getX()][m.getY()-1] == player
   //    || board[m.getX()][m.getY()+1] == player
   //    || board[m.getX()+1][m.getY()+1] == player
   //    || board[m.getX()+1][m.getY()-1] == player
   //    || board[m.getX()-1][m.getY()+1] == player
   //    || board[m.getX()-1][m.getY()-1] == player) {
      
   //    board[m.getX()][m.getY()] = currentPlayer;
   //    if(board[m.getX()-1][m.getY()] == player) board[m.getX()-1][m.getY()] = currentPlayer;
   //    if(board[m.getX()+1][m.getY()] == player) board[m.getX()+1][m.getY()] = currentPlayer;
   //    if(board[m.getX()][m.getY()-1] == player) board[m.getX()][m.getY()-1] = currentPlayer;
   //    if(board[m.getX()][m.getY()+1] == player) board[m.getX()][m.getY()+1] = currentPlayer;
   //    if(board[m.getX()+1][m.getY()+1] == player) board[m.getX()+1][m.getY()+1] = currentPlayer;
   //    if(board[m.getX()+1][m.getY()-1] == player) board[m.getX()+1][m.getY()-1] = currentPlayer;
   //    if(board[m.getX()-1][m.getY()+1] == player) board[m.getX()-1][m.getY()+1] = currentPlayer;
   //    if(board[m.getX()-1][m.getY()-1] == player) board[m.getX()-1][m.getY()-1] = currentPlayer;

   //    nbOfMoveAlreadyPlayed++;
   //    return true;
   // }
   // else return false;


bool PositionOthello::checkRight(Move const& m) {
   if(m.getY() == currentPlayer) return true;
   if(m.getY() == sizeof(board)-1 || m.getY() == 0) {
      tabRight.clear();
      return false;
   }
   else {
      tabRight.push_back(m);
      Move nextMove = Move(m.getX(), m.getY()+1);
      return checkRight(nextMove);
   }
}

bool PositionOthello::checkLeft(Move const& m) {
   if(m.getY() == currentPlayer) return true;
   if(m.getY() == sizeof(board)-1 || m.getY() == 0) {
      tabRight.clear();
      return false;
   }
   else {
      tabRight.push_back(m);
      Move nextMove = Move(m.getX(), m.getY()-1);
      return checkRight(nextMove);
   }
}

bool PositionOthello::checkUp(Move const& m) {
   if(m.getY() == currentPlayer) return true;
   if(m.getY() == sizeof(board)-1 || m.getY() == 0) {
      tabRight.clear();
      return false;
   }
   else {
      tabRight.push_back(m);
      Move nextMove = Move(m.getX()-1, m.getY());
      return checkRight(nextMove);
   }
}

bool PositionOthello::checkDown(Move const& m) {
   if(m.getY() == currentPlayer) return true;
   if(m.getY() == sizeof(board)-1 || m.getY() == 0) {
      tabRight.clear();
      return false;
   }
   else {
      tabRight.push_back(m);
      Move nextMove = Move(m.getX()+1, m.getY());
      return checkRight(nextMove);
   }
}

bool PositionOthello::checkDiagonalRightUp(Move const& m) {
   if(m.getY() == currentPlayer) return true;
   if(m.getY() == sizeof(board)-1 || m.getY() == 0) {
      tabRight.clear();
      return false;
   }
   else {
      tabRight.push_back(m);
      Move nextMove = Move(m.getX()-1, m.getY()+1);
      return checkRight(nextMove);
   }
}

bool PositionOthello::checkDiagonalLeftUp(Move const& m) {
   if(m.getY() == currentPlayer) return true;
   if(m.getY() == sizeof(board)-1 || m.getY() == 0) {
      tabRight.clear();
      return false;
   }
   else {
      tabRight.push_back(m);
      Move nextMove = Move(m.getX()-1, m.getY()-1);
      return checkRight(nextMove);
   }
}

bool PositionOthello::checkDiagonalRightDown(Move const& m) {
   if(m.getY() == currentPlayer) return true;
   if(m.getY() == sizeof(board)-1 || m.getY() == 0) {
      tabRight.clear();
      return false;
   }
   else {
      tabRight.push_back(m);
      Move nextMove = Move(m.getX()+1, m.getY()+1);
      return checkRight(nextMove);
   }
}

bool PositionOthello::checkDiagonalLeftDown(Move const& m) {
   if(m.getY() == currentPlayer) return true;
   if(m.getY() == sizeof(board)-1 || m.getY() == 0) {
      tabRight.clear();
      return false;
   }
   else {
      tabRight.push_back(m);
      Move nextMove = Move(m.getX()+1, m.getY()-1);
      return checkRight(nextMove);
   }
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

