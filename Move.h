#ifndef MOVE_H
#define MOVE_H

class Move {
public:
	Move(char coordX, char coordY);
	Move(int coordX, int coordY);
	int getX() const; 
	int getY() const;

private:
	int x;
	int y;
};

#endif