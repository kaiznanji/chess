#include "piece.h"
#include "box.h"
#include "board.h"
#include <cmath>
#include <iostream>
using namespace std;


Piece::Piece(bool black, char name) : black(black), name(name) {}
                
bool Piece::isBlack() {
	return black;
}      

char Piece::getName() {
	return name;
}

bool Piece::firstMove() {
    return moved;
}

bool Piece::inCheck(Board *board, Box *kingBox) {
	// Check for checkmate by seeing if opponent pieces can attack where you move
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece *attacking_piece = board->getBox(i,j)->getPiece();
			if (attacking_piece && this->isBlack() != attacking_piece->isBlack()) {
				// Check edge case for pawn since it only canMove if the King is actually already moved
				if (attacking_piece->getName() == 'P') {
					int xcoord = i - kingBox->getX();
					int ycoord = j - kingBox->getY();
					if (xcoord == 1 || xcoord == -1) {
						if (attacking_piece->isBlack() && ycoord == 1) {
							return true;
						} else if (!attacking_piece->isBlack() && ycoord == -1) {
							return true;
						} 
					}
				} else if (attacking_piece->getName() == 'K') {
					int x = abs(kingBox->getX() - i);
					int y = abs(kingBox->getY() - j);
					if (x <= 1 && y <= 1) {
						return true;
					}	
				} else if (attacking_piece->canMove(board, board->getBox(i,j), kingBox)) {
					// cout << i << j << "  " << kingBox->getX() << kingBox->getY() << endl;
					// cout << attacking_piece->getName() << "  " << (attacking_piece->isBlack() ? "Black" : "White") << endl;
					return true;
				}
			}
		}
	}
	return false;
}

void Piece::setMoved(bool moved) {
	this->moved = moved;
}

Piece::~Piece() {}


// Pawn
Pawn::Pawn(bool black) : Piece(black, 'P') {}

bool Pawn::canMove(Board *board, Box *start, Box *end) {
	// Check to see if move is to a piece with the same colour
	if (end->getPiece() && end->getPiece()->isBlack() == this->isBlack()) {
        return false;
    }

	int x = start->getX() - end->getX();
    int y = start->getY() - end->getY();

	// Check for if they are starting position or moving(x == 0) or attacking(x != 0)
	if (x != 0) {
		if (this->firstMove()) {
			this->setMoved(false);
		}
		if (end->getPiece() && end->getPiece()->isBlack() != this->isBlack() && (x == 1 || x == -1)) {
            if (this->isBlack() && y == 1) {
				return true;
			} else if (!this->isBlack() && y == -1) {
				return true;
			} 
		}
	} else {
		// Check if where you are moving has a piece
		if (end->getPiece()) {
			return false;
		}

		if (this->isBlack()) {
			if (this->firstMove()) {
				this->setMoved(false);
				if (y == 2 && !board->getBox(start->getX(), start->getY()-1)->getPiece()) {
					return true;
				}
			}
			if (y == 1) {
				return true;
			}
		} else {
			if (this->firstMove()) {
				this->setMoved(false);
				if (y == -2 && !board->getBox(start->getX(), start->getY()+1)->getPiece()) {
					return true;
				} 
			}
			if (y == -1) {
				return true;
			}
		} 
	}
	return false;
	
	// TODO: Check for EnPassant			
}

Pawn::~Pawn() {}


// King
King::King(bool black) : Piece(black, 'K') {}

bool King::canMove(Board *board, Box *start, Box *end) {
	// Check to see if move is to a piece with the same colour
	if (end->getPiece() && end->getPiece()->isBlack() == this->isBlack()) {
		return false;
	}

	if (this->inCheck(board, end)) {
		return false;
	}
	int x = abs(end->getX() - start->getX());
	int y = abs(end->getY() - start->getY());
	if (x <= 1 && y <= 1) {
		return true;
	} else {
		return false;
	}	
	// TODO: Check for Castling
}

King::~King() {}


// Queen
Queen::Queen(bool black) : Piece(black, 'Q') {}

bool Queen::canMove(Board *board, Box *start, Box *end) {
	// Check to see if move is to a piece with the same colour
	if (end->getPiece() && end->getPiece()->isBlack() == this->isBlack()) {
		return false;
	}
	int startX = start->getX();
	int startY = start->getY();
	int endX = end->getX();
	int endY = end->getY();
	
	int dirX = -1;
	int dirY = -1;
	if (startX < endX) {
		dirX = 1;
	}
	if (startY < endY) {
		dirY = 1;
	}

	// Check if end point is not a valid move
	if (abs(start->getX() - end->getX()) == abs(start->getY() - end->getY())) {
		// Check for obstacles in diagonal path
		for (int i = 1; i < abs(endX-startX); ++i) {
			if (board->getBox(startX+i*dirX,startY+i*dirY)->getPiece()) {
				return false;
   			}
  		}
		return true;
	} else if (start->getX() == end->getX()) {
		// Check for obstacles in vertical path	
		for (int i = 1; i < abs(endY-startY); ++i) {
			if (board->getBox(startX,startY+i*dirY)->getPiece()) {
				return false;
			}
		}
		
		return true;
	} else if (start->getY() == end->getY()) {
		// Check for obstacles in horizontal path
		for (int i = 1; i < abs(endX-startX); ++i) {
			if (board->getBox(startX+i*dirX,startY)->getPiece()) {
				return false;
			}
		}
		
		return true;
	} else {
		return false;
	}
		
}

Queen::~Queen() {}


// Bishop
Bishop::Bishop(bool black) : Piece(black, 'B') {}

bool Bishop::canMove(Board *board, Box *start, Box *end) {
	// Check to see if move is to a piece with the same colour
	if (end->getPiece() && end->getPiece()->isBlack() == this->isBlack()) {
		return false;
	}

	int startX = start->getX();
	int startY = start->getY();
	int endX = end->getX();
	int endY = end->getY();

	int dirX = -1;
	int dirY = -1;
	if (startX < endX) {
		dirX = 1;
	}
	if (startY < endY) {
		dirY = 1;
	}

	if (abs(start->getX() - end->getX()) == abs(start->getY() - end->getY())) {
		// Check for obstacles in diagonal path
		for (int i = 1; i < abs(endX-startX); ++i) {
			if (board->getBox(startX+i*dirX,startY+i*dirY)->getPiece()) {
				return false;
			}
		}
		return true;
	} else {
		return false;
	}
}

Bishop::~Bishop() {}


// Rook
Rook::Rook(bool black) : Piece(black, 'R') {}

bool Rook::canMove(Board *board, Box *start, Box *end) {
	// Check to see if move is to a piece with the same colour
	if (end->getPiece() && end->getPiece()->isBlack() == this->isBlack()) {
		return false;
	}

	int startX = start->getX();	
	int startY = start->getY();
	int endX = end->getX();
	int endY = end->getY();

	int dirX = -1;
	int dirY = -1;
	if (startX < endX) {
		dirX = 1;
	}
	if (startY < endY) {
		dirY = 1;
	}

	// Check if end point is not a valid move
	if (start->getX() == end->getX()) {
		// Check for obstacles in vertical path
		for (int i = 1; i < abs(endY-startY); ++i) {
			if (board->getBox(startX,startY+i*dirY)->getPiece()) {
				return false;
			}
		}
	} else if (start->getY() == end->getY()) {
		// Check for obstacles in horizontal path
		for (int i = 1; i < abs(endX-startX); ++i) {
			if (board->getBox(startX+i*dirX,startY)->getPiece()) {
				return false;
			}
		}
	} else {
			return false;
	}
	return true;
}

Rook::~Rook() {}


// Knight
Knight::Knight(bool black) : Piece(black, 'N') {}

bool Knight::canMove(Board *board, Box *start, Box *end) {
	// Check to see if move is to a piece with the same colour
	if (end->getPiece() && end->getPiece()->isBlack() == this->isBlack()) {
		return false;
	}

	int x = abs(end->getX() - start->getX());
	int y = abs(end->getY() - start->getY());
	if ((x == 1 && y == 2) || (x == 2 && y == 1)) {
		return true;
	} else {
		return false;
	}
}

Knight::~Knight() {}

