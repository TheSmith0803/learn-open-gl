#include"Chunk.h"

Vertex faceVertices[] =
{
	// Front face (z = 0.1)
Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
Vertex{glm::vec3(0.5f, -0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
Vertex{glm::vec3(0.5f,  0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.3333f)},

// Back face (z = -0.1)
Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(0.0f, 0.3333f)},
Vertex{glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3( 0.5f, -0.5f, -0.5f) ,  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(1.0f, 0.0f)},
Vertex{glm::vec3(-0.5f, -0.5f, -0.5f) ,  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(0.0f, 0.0f)},

// Left face (x = -0.1)									
Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(0.0f, 0.0f)},
Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(1.0f, 0.0f)},
Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(0.0f, 0.3333f)},

// Right face (x = 0.1)									
Vertex{glm::vec3(0.5f, -0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(0.0f, 0.0f)},
Vertex{glm::vec3(0.5f, -0.5f, -0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(1.0f, 0.0f)},
Vertex{glm::vec3(0.5f,  0.5f, -0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(0.5f,  0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(0.0f, 0.3333f)},

// Top face (y = 0.1)										
Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(0.0f, 0.3333f)},
Vertex{glm::vec3(0.5f,  0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(0.5f,  0.5f, -0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(1.0f, 0.6666f)},
Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(0.0f, 0.6666f)},

// Bottom face (y = -0.1)									
Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(0.0f, 0.6666f)},
Vertex{glm::vec3(0.5f, -0.5f, -0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(1.0f, 0.6666f)},
Vertex{glm::vec3(0.5f, -0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(1.0f, 1.0f)},
Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(0.0f, 1.0f)},
};
/*
static const GLuint faceIndices[] =
{
	// Front face
	2, 1, 0,   0, 3, 2,
	// Back face
	6, 5, 4,   4, 7, 6,
	// Left face
	10, 9, 8,  8, 11, 10,
	// Right face
	14, 13, 12, 12, 15, 14,
	// Top face
	18, 17, 16, 16, 19, 18,
	// Bottom face
	22, 21, 20, 20, 23, 22
};
*/
Chunk::Chunk()
{
	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < CHUNK_DEPTH; z++)
			{
				blocks[x][y][z] = (y < 8) ? 1 : 0; //solid bottom hald(?)
			}
		}
	}
	this->generateMesh(faceVertices);
}

Chunk::~Chunk()
{
	delete chunkMesh;
}

bool Chunk::blockIsSolid(int x, int y, int z)
{
	if ((x < 0 || x >= CHUNK_WIDTH) ||
		(y < 0 || y >= CHUNK_HEIGHT) ||
		(z < 0 || z >= CHUNK_DEPTH))
		return false;
	return blocks[x][y][z] != 0;
}

void Chunk::generateMesh(const Vertex* cubeVerts)
{
	std::vector<Vertex> meshVerts;
	std::vector<GLuint> meshInds;
	GLuint vertexIndex = 0;

	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < CHUNK_DEPTH; z++)
			{
				if (!blockIsSolid(x, y, z)) continue;
				
				if (!blockIsSolid(x, y, z + 1))
				{
					addFace(meshVerts, meshInds, vertexIndex, x, y, z, FRONT, cubeVerts);
				}

				if (!blockIsSolid(x, y, z - 1))
				{
					addFace(meshVerts, meshInds, vertexIndex, x, y, z, BACK, cubeVerts);
				}

				if (!blockIsSolid(x + 1, y, z))
				{
					addFace(meshVerts, meshInds, vertexIndex, x, y, z, RIGHT, cubeVerts);
				}

				if (!blockIsSolid(x - 1, y, z))
				{
					addFace(meshVerts, meshInds, vertexIndex, x, y, z, LEFT, cubeVerts);
				}

				if (!blockIsSolid(x, y + 1, z))
				{
					addFace(meshVerts, meshInds, vertexIndex, x, y, z, TOP, cubeVerts);
				}

				if (!blockIsSolid(x, y - 1, z))
				{
					addFace(meshVerts, meshInds, vertexIndex, x, y, z, BOTTOM, cubeVerts);
				}
			}
		}
	}

	std::vector<Texture> textures = { Texture("Atlas.png", "diffuse", 0) };
	chunkMesh = new Mesh(meshVerts, meshInds, textures);
}

void Chunk::addFace(std::vector<Vertex>& vertices, std::vector<GLuint>& indices,
	GLuint& vertexIndex, int x, int y, int z, BlockFace face, const Vertex* cubeVerts)
{
	glm::vec3 offset(x, y, z);
	int startIndex = face * 4;

	// Use the global faceVertices array
	for (int i = 0; i < 4; i++)
	{
		Vertex v = cubeVerts[startIndex + i];  // Fixed: use faceVertices and i
		v.position += offset;
		vertices.push_back(v);  // Fixed: push to vertices vector
	}

	// Add indices for 2 triangles
	indices.push_back(vertexIndex + 0);
	indices.push_back(vertexIndex + 2);
	indices.push_back(vertexIndex + 1);
	indices.push_back(vertexIndex + 3);
	indices.push_back(vertexIndex + 2);
	indices.push_back(vertexIndex + 0);

	vertexIndex += 4;
}
