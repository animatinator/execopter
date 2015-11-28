// Terrain manager (header)


#ifndef TERRAIN_H
#define TERRAIN_H

#include "terrainslice.h"
#include "blocks.h"
#include "constants.h"
#include <list>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "SDL/SDL_draw.h"

using namespace std;

struct SDL_Surface;


class Terrain
{
	public:
		Terrain();
		~Terrain() {};
		
		void Restart();
		void ResetSlices();
		
		void Update(int gametime);
		void Draw(SDL_Surface* screen) const;
		
		TerrainSlice GetSlice(int index) const;
		vector<Block> GetBlocks() const {return blocks;}
		
		void CreateNewSlice();
		void CreateNewBlock();
	
	private:
		list<TerrainSlice> slices;
		vector<Block> blocks;
		
		int xoffset;
		
		int keyframecounter;
		int blockframecounter;
		int curgradient;
		
		int time;
};

#endif
