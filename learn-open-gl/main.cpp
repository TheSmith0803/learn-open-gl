/*
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include"shaderClass.h"
#include"Texture.h"
#include"VBO.h"
#include"EBO.h"
#include"VAO.h"
#include"Camera.h
*/

#include<cstdlib>
#include<random>
#include"Mesh.h"
#include"Model.h"
#include"Chunk.h"

float skyboxVertices[] =
{
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
};

unsigned int skyboxIndices[] = {
	// Right
	1,2,6,
	6,5,1,
	// Left
	0,4,7,
	7,3,0,
	// Front
	0,1,5,
	5,4,0,
	// Back
	6,2,3,
	3,7,6,
	// Top
	4,5,6,
	6,7,4,
	// Bottom
	2,1,0,
	0,3,2,

};

Vertex cubeVertices[] =
{
											// Front face (z = 0.1)
Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
Vertex{glm::vec3( 0.5f, -0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
Vertex{glm::vec3( 0.5f,  0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.3333f)},

                                            // Back face (z = -0.1)
Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(0.0f, 0.0f)},
Vertex{glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(1.0f, 0.0f)},
Vertex{glm::vec3( 0.5f,  0.5f, -0.5f) ,  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(-0.5f,  0.5f,- 0.5f) ,  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(0.0f, 0.3333f)},

                                         // Left face (x = -0.1)									
Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(0.0f, 0.0f)},
Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(1.0f, 0.0f)},
Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(0.0f, 0.3333f)},

											// Right face (x = 0.1)									
Vertex{glm::vec3( 0.5f, -0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(0.0f, 0.0f)},
Vertex{glm::vec3( 0.5f, -0.5f, -0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(1.0f, 0.0f)},
Vertex{glm::vec3( 0.5f,  0.5f, -0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3( 0.5f,  0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(0.0f, 0.3333f)},

											// Top face (y = 0.1)										
Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(0.0f, 0.3333f)},
Vertex{glm::vec3( 0.5f,  0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3( 0.5f,  0.5f, -0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(1.0f, 0.6666f)},
Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(0.0f, 0.6666f)},

											// Bottom face (y = -0.1)									
Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(0.0f, 0.6666f)},
Vertex{glm::vec3( 0.5f, -0.5f, -0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(1.0f, 0.6666f)},
Vertex{glm::vec3( 0.5f, -0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(1.0f, 1.0f)},
Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(0.0f, 1.0f)},
};

GLuint cubeIndices[] =
{
	// Front face
	2, 1, 0,   0, 3, 2,
	// Back face
	4, 5, 6,   6, 7, 4,
	// Left face
	10, 9, 8,  8, 11, 10,
	// Right face
	14, 13, 12, 12, 15, 14,
	// Top face
	18, 17, 16, 16, 19, 18,
	// Bottom face
	22, 21, 20, 20, 23, 22
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

/*for reading text files(aka shaders)
convert to c string using c_str() method after
std::string readTextFile(const std::string& filePath);
*/

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

const double crntTime = glfwGetTime();

int main() {


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPACT, GL_TRUE);
#endif  



	//init the glfw window object
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//register resize function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	// glad: load all OpenGL function pointers
    // ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		return -1;
	}

	Texture blockTexture[]{
		Texture("Atlas.png", "diffuse", 0)
	};


	// SKYBOX CODE: PUT THIS IN TO A CLASS AT SOME POINT
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::string facesCubeMap[6] = {
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg",
	};

	unsigned int cubemapTexture;
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubeMap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load skybox texture: " << facesCubeMap[i] << std::endl;
			stbi_image_free(data);
		}

	}

	// PLEASE PUT THIS IN A CLASS LOL



	Shader blockShader("block.vert", "block.frag");
	Shader skyboxShader("skybox.vert", "skybox.frag");
	
	glm::vec4 blockColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
	glm::vec3 blockPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 blockModel = glm::mat4(1.0f);
	blockModel = glm::translate(blockModel, blockPos);
	
	glm::vec3 dirtPos = glm::vec3(10.0f, 0.0f, 0.0f);
	glm::mat4 dirtModel = glm::mat4(1.0f);
	dirtModel = glm::translate(dirtModel, dirtPos);
	

	blockShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(blockShader.ID, "model"), 0, GL_FALSE, glm::value_ptr(blockModel));
	glUniform4f(glGetUniformLocation(blockShader.ID, "lightColor"), blockColor.x, blockColor.y, blockColor.z, blockColor.w);
	glUniform3f(glGetUniformLocation(blockShader.ID, "lightPos"), blockPos.x, blockPos.y, blockPos.z);

	skyboxShader.Activate();
	glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);
	


	//Figure out how to do a texture atlas lmao

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	//face culling makes sure the backside of rendered
	//objects doesnt render
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.3f, 2.0f));

	//Get a block rendered
	std::vector <Vertex>  cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
	std::vector <GLuint>  cubeInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
	std::vector <Texture> cubeTex(blockTexture, blockTexture + sizeof(blockTexture) / sizeof(Texture));
	Mesh block(cubeVerts, cubeInd, cubeTex);

	double prevTime = 0.0f;
	double crntTime = 0.0f;
	double timeDiff;
	unsigned int counter = 0;

	//init Chunk
	Chunk chunk;

	////////////////////////////
	//START OF THE RENDER LOOP//
	////////////////////////////

	while (!glfwWindowShouldClose(window))
	{
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;
		if (timeDiff >= 1.0 / 60.0)
		{
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string newTitle = "LearnOpenGL - " + FPS + "FPS / " + ms + "ms";
			glfwSetWindowTitle(window, newTitle.c_str());
			prevTime = crntTime;
			counter = 0;
		}

		// input
		processInput(window);
		
		//specify color of background
		glClearColor(0.45f, 0.45f, 0.95f, 1.0f);
		//clear the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.Inputs(window);
		camera.updateMatrix(80.0f, 0.5f, 500.0f);
		
		//trees.Draw(shaderProgram, camera);
		glEnable(GL_CULL_FACE);

		//GEN MINECRAFT CHUNK FOR REAL
		chunk.chunkMesh->Draw(blockShader, camera, glm::mat4(1.0f));

		// skybox stuff
		glDepthFunc(GL_LEQUAL);
		skyboxShader.Activate();

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.5f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glDepthFunc(GL_LESS);

		 /*POLL EVENTS AND STUFF*/
		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//optional: de-allocate all resources once they've outlived their purpose:
	// ----------------------------------------------------------------------
	
	blockShader.Delete();
	skyboxShader.Delete();

	
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
