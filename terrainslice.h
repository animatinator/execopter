// Terrain slice (header)

#ifndef TERRAINSLICE_H
#define TERRAINSLICE_H

class TerrainSlice
{
	public:
		TerrainSlice(int offset, int height);
		~TerrainSlice() {};
		
		int GetOffset() const {return o;}
		int GetHeight() const {return h;}
	
	private:
		int o;
		int h;
};

#endif
