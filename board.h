#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <memory>

#include "box.h"

class Board {
	Box *boxes[8][8];

	public:
		Board();
		Box *kingBox(bool black);
		Box *getBox(int x, int y); 
		~Board();
};

#endif
