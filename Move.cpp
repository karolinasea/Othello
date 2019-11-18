#include "Move.h"

Move::Move(int coordX, int coordY) {
	if(coordX>-1 && coordX<8 && coordY>-1 && coordY<8) {
		x = coordX;
		y = coordY;
	}
}	

Move::Move(char coordX, char coordY) {	
	switch(coordX) {
		case 49: x=0;
		break;
		case 50: x=1;
		break;
		case 51: x=2;
		break;
		case 52: x=3;
		break;
		case 53: x=4;
		break;
		case 54: x=5;
		break;
		case 55: x=6;
		break;
		case 56: x=7;
		break;
	}
	switch(coordY) {
		case 65: y=0;
		break;
		case 66: y=1;
		break;
		case 67: y=2;
		break;
		case 68: y=3;
		break;
		case 69: y=4;
		break;
		case 70: y=5;
		break;
		case 71: y=6;
		break;
		case 72: y=7;
		break;
	}
}

int Move::getX() const {return x;}

int Move::getY() const {return y;}