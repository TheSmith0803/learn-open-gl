#ifndef CHUNK_H
#define CHUNK_H

#include<cstdint>
#include"Mesh.h"

class Chunk
{
private:
	static const int CHUNK_WIDTH = 16;
	static const int CHUNK_HEIGHT = 16;
	static const int CHUNK_DEPTH = 16;
	uint8_t blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];  // 0 = air, 1 = block

	enum BlockFace { FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM }; 

public:
	Mesh* chunkMesh = nullptr;

	Chunk();
	~Chunk();
	bool blockIsSolid(int x, int y, int z);
	void generateMesh(const Vertex* cubeVerts);
	void addFace(std::vector<Vertex>& vertices, std::vector<GLuint>& indices,
		GLuint& vertexIndex, int x, int y, int z, BlockFace face, const Vertex* cubeVerts);
};

#endif
