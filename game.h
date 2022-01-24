#ifndef __GAME_H__
#define __GAME_H__

class Player;
class Board;

class Game {
	Player *p1;
	Player *p2;
	Board *board;
	Player *currentPlayer;
	char gameStatus = 's';

	public:
		Game(Player *p1, Player *p2, Board *board);
		void setCurrentPlayer(Player *p);
		Player *getCurrentPlayer();
		char getStatus();
		bool makeMove(int startX, int startY, int endX, int endY);
		~Game();
};

#endif
