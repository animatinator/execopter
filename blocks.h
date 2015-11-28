// Blocks (header)


#ifndef BLOCK_H
#define BLOCK_H

#include "SDL/SDL_draw.h"
#include "constants.h"

struct SDL_Surface;

class Block
{
	public:
		Block(int ypos, int xpos = SCREEN_WIDTH);
		~Block() {}
		
		void Draw(SDL_Surface* screen) const;
		
		int GetX() const {return x;}
		void SetX(int newx) {x = newx;}
		int GetOffset() const {return offset;}
		void SetOffset(int newo) {offset = newo;}
	
	private:
		int offset;
		int x;
};

#endif
