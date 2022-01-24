#ifndef __PIECE_H__
#define __PIECE_H__

class Board;
class Box;

class Piece {
	bool black = false;
	bool moved = true;
	char name;

	public:
		Piece(bool black, char name);
		bool isBlack();
		char getName();
		bool firstMove();
		bool inCheck(Board *board, Box *kingBox);
		void setMoved(bool moved);
		virtual bool canMove(Board *board, Box *start, Box *end) = 0;
		virtual ~Piece();
};

class Pawn: public Piece {
	public:
		Pawn(bool black);
		// TODO: Add EnPassant Function
		virtual bool canMove(Board *board, Box *start, Box *end) override;
		virtual ~Pawn();
};


class King: public Piece {
	public:
		King(bool black);
		// TODO: Add Castling Function
		virtual bool canMove(Board *board, Box *start, Box *end) override;
		virtual ~King();
};


class Queen: public Piece {
	public:
		Queen(bool black);
		virtual bool canMove(Board *board, Box *start, Box *end) override;
		virtual ~Queen();
};


class Bishop: public Piece {
	public:
		Bishop(bool black);
		virtual bool canMove(Board *board, Box *start, Box *end) override;
		virtual ~Bishop();
};


class Rook: public Piece {
	public:
		Rook(bool black);
		virtual bool canMove(Board *board, Box *start, Box *end) override;
		virtual ~Rook();
};


class Knight: public Piece {
	public:
		Knight(bool black);
		virtual bool canMove(Board *board, Box *start, Box *end) override;
		virtual ~Knight();
};


#endif
