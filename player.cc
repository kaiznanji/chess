#include "player.h"
#include "board.h"

Player::Player(bool black, bool human) : black(black), human(human) {}               

bool Player::isHuman() {
	return human;
}                

void Player::autoMove(Board *board) { }

bool Player::isBlack() {
	return black;
}

Player::~Player() {}

ComputerPlayer::ComputerPlayer(bool black, int computerLevel) : Player(black, false), computerLevel(computerLevel)  {}  

void ComputerPlayer::autoMove(Board *board) {
	if (computerLevel == 1) {
		// TODO: execute algorithmn1
	} else if (computerLevel == 2) {
		// TODO: execute algorithmn2
	} else if (computerLevel == 3) {
		// TODO: execute algorithmn3
	} else if (computerLevel == 4) {
		// TODO: execute algorithmn4
	} 
}

ComputerPlayer::~ComputerPlayer() {}


