#ifndef BLOCK_UVS_CLASS
#define BLOCK_UVS_CLASS

class BlockUVs
{
public:
	struct blocks {
		float uMin, vMin, uMax, vMax;
	};

	static const blocks GRASS_TOP;
	static const blocks GRASS_SIDE;
	static const blocks DIRT;

	static const blocks STONE;
	static const blocks WOOD;
};

#endif
