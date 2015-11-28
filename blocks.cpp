// Blocks


#include "blocks.h"


Block::Block(int ypos, int xpos):
	offset(ypos),
	x(xpos)
{}

void Block::Draw(SDL_Surface* screen) const
{
	Draw_FillRect(screen, x, offset, BLOCKWIDTH, BLOCKHEIGHT, SDL_MapRGB(screen->format, 108, 102, 50));
}
