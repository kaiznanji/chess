#ifndef __BOX_H__
#define __BOX_H__

#include "piece.h"

class Box {
	int x;
	int y;
	Piece *piece;	
	
	public: 
		Box(int x, int y, Piece *p);
		int getX();
		int getY();
		Piece *getPiece();
		void setX(int x);
		void setY(int y);
		void setPiece(Piece *p);
		~Box();
};

#endif
