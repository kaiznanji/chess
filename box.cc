#include "box.h"


Box::Box(int x, int y, Piece *p) : x(x), y(y), piece(p) {}

int Box::getX() {
	return x;
}

int Box::getY() {
	return y;
}

Piece * Box::getPiece() {
	return piece;
}

void Box::setX(int x) {
       this->x = x;
}

void Box::setY(int y) {
	this->y = y;
}

void Box::setPiece(Piece *p) {
	this->piece = p;
}

Box::~Box() {}
