#include <iostream>
#include <vector>
#include "Move.h"
#include "PositionOthello.h"

PositionOthello::PositionOthello() {

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

	std::cout << "    ";
	for(char k = 65; k<73; k++) {
		std::cout << " " << k << " ";
	}

	std::cout << std::endl;

	for(int i=0; i<8; i++) {
		std::cout << " " << i+1 << ": "; // i = rows
		for(int j=0; j<8; j++) {
			// j =colomn
			std::cout << " " << board[i][j] << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}

void PositionOthello::applyMove(Move const& m) {
   board[m.getX()][m.getY()] = currentPlayer;
}

int PositionOthello::getNbOfMoveAlreadyPlayed() {
   return nbOfMoveAlreadyPlayed;
}

void PositionOthello::skipTurn() {
   for(int i=0; i<8; i++) {
      for(int j=0; j<8; j++) {
         if(board[i][j] == 0) {
            Move m = Move(i, j);
            if(!checkSkipTurn(m)) {
               std::cout << "You cannot skip your turn because there is at least one possible move to make" << std::endl;
               return;
            }
         }
      }
   }
   if (currentPlayer == 1) currentPlayer = 2;
	else currentPlayer = 1;
}

bool PositionOthello::checkSkipTurn(Move& m) {

   //if the move has no enemy piece adjacent then indeed we can't play that move
   if(board[m.getX()-1][m.getY()] == currentPlayer 
      && board[m.getX()+1][m.getY()] == currentPlayer
      && board[m.getX()][m.getY()-1] == currentPlayer
      && board[m.getX()][m.getY()+1] == currentPlayer
      && board[m.getX()+1][m.getY()+1] == currentPlayer
      && board[m.getX()+1][m.getY()-1] == currentPlayer
      && board[m.getX()-1][m.getY()+1] == currentPlayer
      && board[m.getX()-1][m.getY()-1] == currentPlayer) {
      // cout << " no ennemy piece adjacent to this move " << endl;
         return true;
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

   //no pieces to return so move so indeed we can't play that move
   if(tabRight.empty() 
      && tabLeft.empty() 
      && tabUp.empty() 
      && tabDown.empty()
      && tabDiaRightUp.empty() 
      && tabDiaRightDown.empty() 
      && tabDiaLeftDown.empty() 
      && tabDiaLeftUp.empty()) {
      // std::cout << "no pieces to return so cannot play move" << std::endl;
      return true;
   }
   
   tabRight.clear();
   tabLeft.clear();
   tabUp.clear();
   tabDown.clear();
   tabDiaRightUp.clear();
   tabDiaRightDown.clear();
   tabDiaLeftUp.clear();
   tabDiaLeftDown.clear();

   //none of the conditions are true so the move can actually be played!
   return false;
}

bool PositionOthello::playerPlay(Move& m) {
   // int player;
   // if(currentPlayer==1) player = 2;
   // else if(currentPlayer==2) player = 1;

   //the move must be in an empty spot (=0)
   if(board[m.getX()][m.getY()] != 0) {
      std::cout << " != 0 cannot play this move here" << std::endl;
      return false;
   }
   //if the move has no enemy piece adjacent then it's not valid
   if(board[m.getX()-1][m.getY()] == currentPlayer 
      && board[m.getX()+1][m.getY()] == currentPlayer
      && board[m.getX()][m.getY()-1] == currentPlayer
      && board[m.getX()][m.getY()+1] == currentPlayer
      && board[m.getX()+1][m.getY()+1] == currentPlayer
      && board[m.getX()+1][m.getY()-1] == currentPlayer
      && board[m.getX()-1][m.getY()+1] == currentPlayer
      && board[m.getX()-1][m.getY()-1] == currentPlayer) {
      std::cout << " no ennemy piece adjacent to this move " << std::endl;
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
      std::cout << "no pieces to return so cannot play move" << std::endl;
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
   	// std::cout << "1" << std::endl;
      return true;
   }
   if(m.getY()+1 >= 7 || board[m.getX()][m.getY()+1] == 0) {
      tabRight.clear();
      // std::cout << "CLEAR 1" << std::endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX(), m.getY()+1);
      tabRight.push_back(nextMove);
      // std::cout << "R1" << std::endl;
      return checkRight(nextMove);
   }
}

bool PositionOthello::checkLeft(Move const& m) {
   if(board[m.getX()][m.getY()-1] == currentPlayer) {
   	// std::cout << "2" << std::endl;
      return true;
   }
   if(m.getY()-1 <= 0 || board[m.getX()][m.getY()-1] == 0) {
      tabLeft.clear();
      // std::cout << "CLEAR 2" << std::endl;
      return false;
   }
   else {
      Move nextMove = Move(m.getX(), m.getY()-1);
      tabLeft.push_back(nextMove);
      // std::cout << "R2" << std::endl;
      return checkLeft(nextMove);
   }
}

bool PositionOthello::checkUp(Move const& m) {
   if(board[m.getX()-1][m.getY()] == currentPlayer) {
   	// std::cout << "3" << std::endl;
      return true;
   }
   if(m.getX()-1 <= 0 || board[m.getX()-1][m.getY()] == 0) {
      tabUp.clear();
      // std::cout << "CLEAR 3" << std::endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX()-1, m.getY());
      tabUp.push_back(nextMove);
      // std::cout << "R3" << std::endl;
      return checkUp(nextMove);
   }
}

bool PositionOthello::checkDown(Move const& m) {
   if(board[m.getX()+1][m.getY()] == currentPlayer) {
   	// std::cout << "4" << std::endl;
      return true;
   }
   if(m.getX()+1 >= 7 || board[m.getX()+1][m.getY()] == 0) {
      tabDown.clear();
      // std::cout << "CLEAR 4" << std::endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX()+1, m.getY());
      tabDown.push_back(nextMove);
      // std::cout << "R4" << std::endl;
      return checkDown(nextMove);
   }
}

bool PositionOthello::checkDiagonalRightUp(Move const& m) {
   // cout << "sizeof(int) = " << sizeof(int) << endl;
   // cout << "sizeof(board) = " << sizeof(board) << endl;
   // cout << "(sizeof(board)/sizeof(int)) = " << (sizeof(board)/sizeof(int)) << endl;
   if(board[m.getX()-1][m.getY()+1] == currentPlayer) {
   	// std::cout << "5" << std::endl;
      return true;
   }
   if(m.getY()+1 >= 7 || m.getX()-1 <= 0 || board[m.getX()-1][m.getY()+1] == 0) {
      tabDiaRightUp.clear();
      // std::cout << "CLEAR 5" << std::endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX()-1, m.getY()+1);
      tabDiaRightUp.push_back(nextMove);
      // std::cout << "R5" << std::endl;
      return checkDiagonalRightUp(nextMove);
   }
}

bool PositionOthello::checkDiagonalLeftUp(Move const& m) {
   if(board[m.getX()-1][m.getY()-1] == currentPlayer) {
   	// std::cout << "6" << std::endl;
      return true;
   }
   if(m.getY()-1 <= 0 || m.getX()-1 <= 0 || board[m.getX()-1][m.getY()-1] == 0) {
      tabDiaLeftUp.clear();
      // std::cout << "CLEAR 6" << std::endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX()-1, m.getY()-1);
      tabDiaLeftUp.push_back(nextMove);
      // std::cout << "R6" << std::endl;
      return checkDiagonalLeftUp(nextMove);
   }
}

bool PositionOthello::checkDiagonalRightDown(Move const& m) {
   if(board[m.getX()+1][m.getY()+1] == currentPlayer) {
   	// std::cout << "7" << std::endl;
      return true;
   }
   if(m.getX()+1 >= 7 || m.getY()+1 >= 7 || board[m.getX()+1][m.getY()+1] == 0) {
      tabDiaRightDown.clear();
      // std::cout << "CLEAR 7" << std::endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX()+1, m.getY()+1);
      tabDiaRightDown.push_back(nextMove);
      // std::cout << "R7" << std::endl;
      return checkDiagonalRightDown(nextMove);
   }
}

bool PositionOthello::checkDiagonalLeftDown(Move const& m) {
   if(board[m.getX()+1][m.getY()-1] == currentPlayer) {
   	// std::cout << "8" << std::endl;
      return true;
   }
   if(m.getX()+1 >= 7 || m.getY()-1 == 0 || board[m.getX()+1][m.getY()-1] == 0) {
      tabDiaLeftDown.clear();
      // std::cout << "CLEAR 8" << std::endl;
      return false;
   }
   else {
   	Move nextMove = Move(m.getX()+1, m.getY()-1);
      tabDiaLeftDown.push_back(nextMove);
      // std::cout << "R8" << std::endl;
      return checkDiagonalLeftDown(nextMove);
   }
}

int * PositionOthello::computeScore(int r[]) {
	int cpt0 = 0, cpt1 = 0, cpt2 = 0;
	if(gameOver()) {
		for(int i=0; i<8; i++) {
	      for(int j=0; j<8; j++) {
	         if(board[i][j] == 1) {
               cpt1++; 
            }
	         else if(board[i][j] == 2) {
               cpt2++;
	         } else {
               cpt0++;
            }
	      }
	   }
	   if(cpt0>0 && cpt1>cpt2) {
	   	cpt1+=cpt0;
	   	r[0] = cpt1;
         r[1] = cpt2;
	   }
	   if(cpt0>0 && cpt2>cpt1) {
	   	cpt2+=cpt0; 
	   	r[1] = cpt2;
         r[0] = cpt1;
	   }
	   else {
	   	r[0] = cpt1;
	   	r[1] = cpt2;
         // std::cout << "in else of computeScore res[0] = " << r[0] << " res[1] = " << r[1] << std::endl;
	   }
	}
   // std::cout << "computeScore method nb of 1 = " << cpt1 << " number of 2 = " << cpt2 << " nb of 0 = " << cpt0 << std::endl;
	return r;
}

int PositionOthello::winner() {
   int r[2];
	int *res = computeScore(r);
   // std::cout << " winner method res[0] =  " << res[0] << " winner method res[1] =  " << res[1] << std::endl;
	if(res[0]>res[1]) return 1;
	if(res[1]>res[0]) return 2;
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

