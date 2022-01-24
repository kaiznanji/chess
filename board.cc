#include "board.h"
#include "piece.h"
#include "box.h"

using namespace std;


Board::Board() {
	// initialize pawns
	for (int i = 0; i < 8; ++i) {
		boxes[i][1] = new Box(i, 1, new Pawn(false));
		boxes[i][6] = new Box(i, 6, new Pawn(true));
	}

	// initialize other pieces
	boxes[0][0] = new Box(0, 0, new Rook(false));
	boxes[1][0] = new Box(1, 0, new Knight(false));
	boxes[2][0] = new Box(2, 0, new Bishop(false));
	boxes[3][0] = new Box(3, 0, new Queen(false));
	boxes[4][0] = new Box(4, 0, new King(false));
	boxes[5][0] = new Box(5, 0, new Bishop(false));
	boxes[6][0] = new Box(6, 0, new Knight(false));
	boxes[7][0] = new Box(7, 0, new Rook(false));

	boxes[0][7] = new Box(0, 7, new Rook(true));
	boxes[1][7] = new Box(1, 7, new Knight(true));
	boxes[2][7] = new Box(2, 7, new Bishop(true));
	boxes[3][7] = new Box(3, 7, new Queen(true));
	boxes[4][7] = new Box(4, 7, new King(true));
	boxes[5][7] = new Box(5, 7, new Bishop(true));
	boxes[6][7] = new Box(6, 7, new Knight(true));
	boxes[7][7] = new Box(7, 7, new Rook(true));

	// initialize other empty spots
	for (int i = 0; i < 8; i++) {
		for (int j = 2; j < 6; j++) {
			boxes[i][j] = new Box(i, j, nullptr);
		}
	}
}	

Box * Board::getBox(int x, int y) {
	if (x < 0 || x > 7 || y < 0 || y > 7) {
		throw 530;
	}

	return boxes[x][y];
}

Box * Board::kingBox(bool black) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Box *box = boxes[i][j];
			Piece *piece = box->getPiece();
			if (piece && piece->getName() == 'K' && black == piece->isBlack()) {
				return box;
			}
		}
	}
	return nullptr;
}

Board::~Board() {}


