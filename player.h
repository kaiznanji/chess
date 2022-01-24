#ifndef __PLAYER_H__
#define __PLAYER_H__

class Board;

class Player {
	bool black = false;
	bool human = false;

	public:
		Player(bool black, bool human);
		bool isHuman();
		bool isBlack();
		virtual void autoMove(Board *board);
		~Player();
};


class ComputerPlayer: public Player {
	int computerLevel;

	public:
		ComputerPlayer(bool black, int computerLevel);
		void autoMove(Board *board) override;
		~ComputerPlayer();
};

#endif
