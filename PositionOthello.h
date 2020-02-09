#ifndef POSITION_OTHELLO_H
#define POSITION_OTHELLO_H

#include <iostream>
#include <vector>
#include "Move.h"

class PositionOthello {

public:
	PositionOthello();
	//~PositionOthello(); //not sure if i need a destructor or not yet maybe to delete Move vectors..

	void printBoard();

	int getNbOfMoveAlreadyPlayed();

	int getCurrentPlayer();

	//utiliser pour jouer le coup que le joueur veut jouer
	//renvoit true si tous est ok pour jouer le coup que le joueur veut jouer
	//renvoit false si coup n'est pas legal
	bool playerPlay(Move& m);

	// when no move is possible for pawn we can skip turn
	void skipTurn();

	//verifies if player is allowed to skip turn
	//returns true if player is allowed to skip turn 
	//and false if not allowed (which mean there is at least one possible move)
	bool checkSkipTurn(Move& m);

	//program must first check all the possible moves Move to make
	//then eval the best one
	//just this would be only depth 1 but then if we can to check for more depth need to use minMax
	void computerPlay();

	//undo a move that a player just played
	void unPlay(); //make it virtual pure ???

	void changeTurn();

	//returns false if game is not over, and true if it is over
	//the game is over when aucun des deux joueurs ne peut plus jouer de coup légal. 
	//usually happens when all 64 pieces are placed
	/*La partie est terminée lorsque aucun des deux joueurs ne peut plus jouer. 
	Cela arrive généralement lorsque les 64 cases sont occupées. 
	Mais il se peut qu’il reste des cases vides où personne ne peut plus jouer : 
	par exemple lorsque tous les pions deviennent d’une même couleur après un retournement.*/
	bool gameOver();

	//Avoir plus de pions de sa couleur que l’adversaire à la fin de la partie pour gagner
	//uses gameOver() and computeScore to return the winner of the game
	int winner();

	//might need to return something not sure yet
	//might compute only one player score or both score
	//compute only if game is over or anytime during game ??
	//On compte les pions pour déterminer le score. Les cases vides sont données au vainqueur.
	int * computeScore(int r[]);

	//must somehow return or make or update a list (which kind ?) 
	//of all possible moves considering the current position of all 
	//pawns and of current player
	//or add a list type data structure to the class that will be modified in this method
	Move* possibleMoves();

	//evaluate current position and returns a double representing the evaluation
	//evaluation can be the number of ennemi pieces turned ?
	double eval();

	//returns the best move to make ? and the evaluation of that move?
	Move minMax(int depth);

	//do I also need alphaBeta type of algo??? 


private:
	//make the attributes pointers???
	int currentPlayer;
	int board[8][8];
	int nbOfMoveAlreadyPlayed;
	std::vector<Move> tabRight;
	std::vector<Move> tabLeft;
	std::vector<Move> tabUp;
	std::vector<Move> tabDown;
	std::vector<Move> tabDiaRightUp;
	std::vector<Move> tabDiaLeftUp;
	std::vector<Move> tabDiaRightDown;
	std::vector<Move> tabDiaLeftDown;
	bool checkRight(Move const& m);
	bool checkLeft(Move const& m);
	bool checkUp(Move const& m);
	bool checkDown(Move const& m);
	bool checkDiagonalRightUp(Move const& m);
	bool checkDiagonalLeftUp(Move const& m);
	bool checkDiagonalRightDown(Move const& m);
	bool checkDiagonalLeftDown(Move const& m);
	void applyMove(Move const& m);
};

#endif