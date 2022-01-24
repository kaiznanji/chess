#include "game.h"
#include "player.h"
#include "board.h"
#include <iostream>
#include <vector>

using namespace std;


struct Positions {
	int x;
	int y;
};

Game::Game(Player *p1, Player *p2, Board *board) {
	this->p1 = p1;
	this->p2 = p2;
	this->board = board;
	this->currentPlayer = p1;
}


void Game::setCurrentPlayer(Player *p) {
	this->currentPlayer = p;
}


Player *Game::getCurrentPlayer() {
	return currentPlayer;
}


char Game::getStatus() {
	return gameStatus;
}

bool checkMate(Board *board, Player *currentPlayer, Box *otherKingBox) {
	
	Piece *king = otherKingBox->getPiece();
	int kingX = otherKingBox->getX();
	int kingY = otherKingBox->getY();
	// 1.) Can the king move to the spots around?
	Positions king_moves[8] = {{  1, -1 },{  1, 0 },{  1,  1 }, { 0,  1 },
							{ -1,  1 },{ -1, 0 },{ -1, -1 }, { 0, -1 } };

	for (int i = 0; i < 8; i++) {
		int x = kingX + king_moves[i].x;
		int y = kingY + king_moves[i].y;

		if (x < 0 || x > 7 || y < 0 || y > 7) {
			// This square does not exist
			continue;
		}

		if (board->getBox(x, y)->getPiece() && board->getBox(x, y)->getPiece()->isBlack() == king->isBlack()) {
			// That square is not empty and is same colour
			continue;
		}

		if (king->canMove(board, otherKingBox, board->getBox(x, y)) && !king->inCheck(board, board->getBox(x, y))) {
			// There exists a spot where the king can move without being in check
			return false;
		}
	}
	return true;
	// TODO: 2. Can the attacker be taken or another piece get into the way? 
}


bool Game::makeMove(int startX, int startY, int endX, int endY) {
	if (board->getBox(startX, startY)->getPiece() == nullptr) {
		return false;
	}

	if (board->getBox(startX, startY)->getPiece()->isBlack() != currentPlayer->isBlack()) {
		return false;
    }

	if (!board->getBox(startX, startY)->getPiece()->canMove(board, board->getBox(startX, startY), board->getBox(endX, endY))) {
		return false;
    }

	// Move piece
	board->getBox(endX, endY)->setPiece(board->getBox(startX, startY)->getPiece());
	board->getBox(startX, startY)->setPiece(nullptr);

	// TODO: Make sure the player's move takes them out/doesn't put them in check
	this->gameStatus = 's';
	
	// Check for when player is in check 
	Box *otherKingBox = board->kingBox(!currentPlayer->isBlack());
	if (board->getBox(endX, endY)->getPiece()->canMove(board, board->getBox(endX, endY), otherKingBox)) {
		this->gameStatus = 'c';
		// Check for checkmate
		if (checkMate(board, currentPlayer, otherKingBox)) {
			if (currentPlayer->isBlack()) {
				this->gameStatus = 'w';
			} else {
				this->gameStatus = 'b';
			}
		}
		
	}

	// Set the current turn to the other player
	if (currentPlayer == p1) {
		this->currentPlayer = p2;
	}
	else {
		this->currentPlayer = p1;
	}

	return true;

}

Game::~Game() {}
