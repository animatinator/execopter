// Terrain manager

#include "terrain.h"


int MapRandToRange(int rand, int min, int max)
{
	return min + (rand % (max - min));
}

Terrain::Terrain():
	xoffset(0),
	keyframecounter(TERRAINKEYFRAMEDIST),
	blockframecounter(BLOCKSPACING),
	time(0)
{
	Terrain::ResetSlices();
}

void Terrain::Restart()
{
	Terrain::ResetSlices();
	blocks.clear();
	xoffset = 0;
	keyframecounter = TERRAINKEYFRAMEDIST;
	blockframecounter = BLOCKSPACING;
	curgradient = 0;
	time = 0;
}

void Terrain::ResetSlices()
{
	slices.clear();
	
	for (int i = 0; i <= RES; ++i)
	{
		slices.push_back(TerrainSlice(TERRAINBASEOFFSET, TERRAINBASEHEIGHT));
	}
}

void Terrain::Update(int gametime)
{
	time = gametime;
	
	xoffset += HVELOCITY;
	if (xoffset == SLICEWIDTH)
	{
		xoffset = 0;
		Terrain::CreateNewSlice();
	}
	
	int newx;
	int deleteblock = -1;
	int i = 0;
	
	for (vector<Block>::iterator iter = blocks.begin(); iter != blocks.end(); ++iter, ++i)
	{
		newx = iter->GetX() - HVELOCITY;
		iter->SetX(newx);
		
		if (newx < (-BLOCKWIDTH)) deleteblock = i;
	}
	
	if (deleteblock != -1)
	{
		blocks.erase(blocks.begin() + deleteblock);
	}
}

void Terrain::Draw(SDL_Surface* screen) const
{
	int curslicepos = -xoffset;
	list<TerrainSlice>::const_iterator curslice = slices.begin();
	
	int offset, height;
	
	for (; curslice != slices.end(); ++curslice, curslicepos += SLICEWIDTH)
	{
		offset = curslice->GetOffset();
		height = curslice->GetHeight();
		
		Uint32 colour = SDL_MapRGB(screen->format, 108, 102, 26);
		Draw_FillRect(screen, curslicepos, 0, SLICEWIDTH, offset, colour);
		Draw_FillRect(screen, curslicepos, offset + height, SLICEWIDTH, SCREEN_HEIGHT - (offset + height), colour);
	}
	
	for (vector<Block>::const_iterator iter = blocks.begin(); iter != blocks.end(); ++iter) iter->Draw(screen);
}

TerrainSlice Terrain::GetSlice(int index) const
{
	list<TerrainSlice>::const_iterator iter = slices.begin();
	advance(iter, index);
	
	return *iter;
}

void Terrain::CreateNewSlice()
{
	// Get the newest terrain slice
	list<TerrainSlice>::const_iterator iter = slices.end();
	iter--;
	int curoffset = iter->GetOffset();
	int curheight = iter->GetHeight();
	
	if (keyframecounter == TERRAINKEYFRAMEDIST)
	{
		keyframecounter = -1;  // As it's about to be incremented
		srand(rand());
		
		int nextoffset = MapRandToRange(rand(), (int)((float)(-curoffset) / TERRAINSMOOTHNESS), (int)((float)(SCREEN_HEIGHT - (curheight + curoffset)) / TERRAINSMOOTHNESS));
		curgradient = (int)((float)nextoffset / (float)TERRAINKEYFRAMEDIST);
		
		if (blockframecounter == BLOCKSPACING)
		{
			Terrain::CreateNewBlock();
			blockframecounter = -1;
		}
		
		++blockframecounter;
	}
	
	float scaling = pow((float)TERRAINDECAYSPEED, -((float)time / (TERRAINHEIGHTPERSISTENCE)));
	int newheight = (int)((float)TERRAINBASEHEIGHT * scaling);
	
	slices.push_back(TerrainSlice(curoffset + curgradient, newheight));
	slices.pop_front();
	
	++keyframecounter;
}

void Terrain::CreateNewBlock()
{
	list<TerrainSlice>::iterator iter = slices.end();
	advance(iter, -1);
	TerrainSlice curslice = *iter;
	
	srand(rand());
	int offset = MapRandToRange(rand(), curslice.GetOffset(), (curslice.GetOffset() + curslice.GetHeight()) - BLOCKHEIGHT);
	
	// Add 'for slice covered, shift block out way'
	
	blocks.push_back(Block(offset));
}
