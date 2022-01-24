#include "board.h"
#include <iostream>
using namespace std;

int WHITE_SQUARE = 0xDB;
int BLACK_SQUARE = 0xFF;

char getLetter(Piece *piece) {
	if (piece == nullptr) {
		return '_';
	}
	bool black = piece->isBlack();
	char letter = piece->getName();
	if (black) {
		return tolower(letter);
	} else {
		return letter;
	}
}

void display(Board *board) {
	for (int i = 7; i >= 0; --i) {
		cout << i+1 << " ";
		for (int j = 0; j < 8; ++j) {
			char letter = getLetter(board->getBox(j, i)->getPiece());
			cout << "|" << letter;
		}
		cout << "|" << endl;
    }

    cout << endl;
    cout << "   ";
    cout << "a b c d e f g h" << endl;
}


