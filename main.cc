#include <iostream>

#include "player.h"
#include "game.h"
#include "board.h"
#include "addtext.h"

using namespace std;

Player *validPlayer(string player, bool black) {
	if (player == "H") {
		Player *p = new Player(black, true);
		return p;
	} else if (player == "C1") {
		ComputerPlayer *p = new ComputerPlayer(black, 1);
		return p;
	} else if (player == "C2") {
		ComputerPlayer *p = new ComputerPlayer(black, 2);
		return p;
	} else if (player == "C3") {
		ComputerPlayer *p = new ComputerPlayer(black, 3);
		return p;
	} else if (player == "C4") {
		ComputerPlayer *p = new ComputerPlayer(black, 4);
		return p;
	} else {
		throw 500;
	}
}

Piece *validPiece(char piece, bool black) {
	if (piece == 'K') {
		King *p = new King(black);
		return p;
	} else if (piece == 'Q') {
		Queen *p = new Queen(black);
        return p;
	} else if (piece == 'B') {
		Bishop *p = new Bishop(black);
		return p;
	} else if (piece == 'R') {
		Rook *p = new Rook(black);
		return p;
	} else if (piece == 'N') {
		Knight *p = new Knight(black);
        return p;
	} else if (piece == 'P') {
        Pawn *p = new Pawn(black);
		return p;
	} else {
        throw 590;
	}
}

void validCoord(int x, int y) {
	if (x > 7 || x < 0 || y < 0 || y > 7) {
		throw 521;
	} 
}


int main () {
	// Initialize scores
	int blackScore = 0;
	int whiteScore = 0;

	string command;
	
	// Instructions
	cout << "WELCOME TO CHESS!!!" << endl;
	cout << "Instructions: (N)ew game  (D)raw vote  (R)esign  (M)ove piece  (S)etup mode (^D) Quit Game" << endl;

	while (cin >> command) {
		if (command == "N") {
			string white;
			string black;
			cout << "Player Types: (H)uman  (C1) Computer Level 1  (C2) Computer Level 2  (C3) Computer Level 3  (C4) Computer Level 4" << endl;
			cout << "Enter a white's player type: ";
			cin >> white;
			cout << "Enter a black's player type: ";
			cin >> black;

			try {
				// Initialize Players
				Player *white_player = validPlayer(white, false);
				Player *black_player = validPlayer(black, true);
				
				// Initialize Board
				Board *b = new Board();

				// Initialize Game
				Game *g = new Game(white_player, black_player, b);
				
				// Initial display
				display(b);
				cout << "Current Turn: " << (g->getCurrentPlayer()->isBlack() ? "BLACK (lower case)" : "WHITE (upper case)") << endl;

				while (cin >> command) {
					if (command == "D") {
						string decision;
						cout << (g->getCurrentPlayer()->isBlack() ? "White" : "Black") << " do you agree to a draw? (Y)es (N)o: ";
						cin >> decision;
						if (decision == "Y") {
							cout << "Tie!" << endl;
							break;
						} else {
							cout << "The game continues..." << endl;
						}
					} else if (command == "R") {
						if (g->getCurrentPlayer()->isBlack()) {
							whiteScore += 1;
							cout << "White wins!" << endl;
						} else {
							blackScore += 1;
							cout << "Black wins!" << endl;
						}
						break;
					} else if (command == "M") {
						// Check if it is a human player
						if (g->getCurrentPlayer()->isHuman()) {	
							char fromX;
							int fromY;
							char toX;
							int toY;
							cout << "From: ";
							cin >> fromX >> fromY;
							cout << "To: ";
							cin >> toX >> toY;
							
							try {
								// Check valid coordinates given
								validCoord(fromX-97, fromY-1);
								validCoord(toX-97, toY-1);

								// Make Move
								if (!g->makeMove(fromX-97, fromY-1, toX-97, toY-1)) {
									cout << "Please enter a valid move!" << endl;
									continue;
								}
							} catch (int ErrorNumber) {
								cout << "Error Code: " << ErrorNumber << endl;
								cout << "Enter valid coordinates!" << endl;
								continue;
							}
						} else {
							g->getCurrentPlayer()->autoMove(b);
						}
						display(b);

						// Check for if someone won or is in check
						if (g->getStatus() == 'w') {
							whiteScore += 1;
							cout << "White wins!" << endl;
							break;
						} else if (g->getStatus() == 'b') {
							blackScore += 1;
							cout << "Black wins!" << endl;
							break;
						} else if (g->getStatus() == 'c') {
							if (g->getCurrentPlayer()->isBlack()) {
								cout << "Black is in check!" << endl;
							} else {
								cout << "White is in check!" << endl;
							}
						}
					} else if (command == "S") {
						cout << "Setup mode entered!" << endl;
						cout << "Instructions: (+) Add piece  (-) Remove piece  (=) Change player turn  (done) Exit setup mode" << endl;
						string operation;
						while (cin >> operation) {
							if (operation == "+") {
								bool black = false;
								char piece;
								char coordX;
								int coordY;
								cout << "Enter a piece and coordinates (ex. Q b3): ";
								cin >> piece >> coordX >> coordY;
								try {
									if (islower(piece)) {
										piece = piece - 32;
										black = true;
									}
										
									validCoord(coordX-97, coordY-1);

									Piece *piece_added = validPiece(piece, black);
									// Replace piece at given coordinates
									b->getBox(coordX-97, coordY-1)->setPiece(piece_added);
								} catch (int ErrorNumber) {
									cout << "Error Code: " << ErrorNumber << endl;
									continue;
								}
								display(b);
							} else if (operation == "-") {
								char coordX;
                                int coordY;
								cout << "Enter coordinates: ";
								cin >> coordX >> coordY;
								try {
									validCoord(coordX-97, coordY-1);

									// Destroy piece at given coordinates
                                    b->getBox(coordX-97, coordY-1)->setPiece(nullptr);
								} catch (int ErrorNumber) {
									cout << "Error Code: " << ErrorNumber << endl;
									cout << "Enter valid coordinates!" << endl;
									continue;
								}
								display(b);
							} else if (operation == "=") {
								string playerTurn;
								cout << "(B)lack or (W)hite: ";
								cin >> playerTurn;
								if (playerTurn == "B") {
									g->setCurrentPlayer(black_player);
								} else if (playerTurn == "W") {
									g->setCurrentPlayer(white_player);
								} else {
									cout << "Enter a valid colour!" << endl;
									continue;
								}
							} else if (operation == "done") {
								// TODO: Check if there is one king each, no pawns are on the first or last row and checkmate function is false
								cout << "Setup Mode Exited." << endl;
								break;
							}
						}
					} else {
						cout << "Please enter a valid command!" << endl;
					}
					cout << "Current Turn: " << (g->getCurrentPlayer()->isBlack() ? "BLACK (lower case)" : "WHITE (upper case)") << endl;
				}
				delete g;
				delete b;
				delete white_player;
				delete black_player;
				cout << "Current Score:" << endl;
				cout << "White: " << whiteScore << endl;
				cout << "Black: " << blackScore << endl;
			} catch (int ErrorNumber) {
					cout << "Error Code: " << ErrorNumber << endl;
					cout << "Invalid Player!" << endl;
					continue;
			}
		}
	}

	cout << "Final Score:" << endl;
	cout << "White: " << whiteScore << endl;
	cout << "Black: " << blackScore << endl;

}
