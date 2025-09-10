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
#include"Camera.h"
#include"BlockUVs.h"
*/
#include"Mesh.h"
#include"Model.h"


Vertex cubeVertices[] =
{
	// Front face (z = 0.1)
Vertex{glm::vec3(-0.1f, -0.1f,  0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
Vertex{glm::vec3(0.1f, -0.1f,  0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
Vertex{glm::vec3(0.1f,  0.1f,  0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(-0.1f,  0.1f,  0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.3333f)},

// Back face (z = -0.1)
Vertex{glm::vec3(-0.1f, -0.1f, -0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(0.0f, 0.0f)},
Vertex{glm::vec3(0.1f,  -0.1f, -0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(1.0f, 0.0f)},
Vertex{glm::vec3(0.1f,  0.1f, -0.1f) ,  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(-0.1f, 0.1f, -0.1f) ,  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(0.0f, 0.3333f)},

// Left face (x = -0.1)									
Vertex{glm::vec3(-0.1f, -0.1f, -0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(0.0f, 0.0f)},
Vertex{glm::vec3(-0.1f, -0.1f,  0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(1.0f, 0.0f)},
Vertex{glm::vec3(-0.1f,  0.1f,  0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(-0.1f,  0.1f, -0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(0.0f, 0.3333f)},

// Right face (x = 0.1)									
Vertex{glm::vec3(0.1f, -0.1f,  0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(0.0f, 0.0f)},
Vertex{glm::vec3(0.1f, -0.1f, -0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(1.0f, 0.0f)},
Vertex{glm::vec3(0.1f,  0.1f, -0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(0.1f,  0.1f,  0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(0.0f, 0.3333f)},

// Top face (y = 0.1)										
Vertex{glm::vec3(-0.1f,  0.1f,  0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(0.0f, 0.3333f)},
Vertex{glm::vec3(0.1f,  0.1f,  0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(0.1f,  0.1f, -0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(1.0f, 0.6666f)},
Vertex{glm::vec3(-0.1f,  0.1f, -0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(0.0f, 0.6666f)},

// Bottom face (y = -0.1)									
Vertex{glm::vec3(-0.1f, -0.1f, -0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(0.0f, 0.6666f)},
Vertex{glm::vec3(0.1f, -0.1f, -0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(1.0f, 0.6666f)},
Vertex{glm::vec3(0.1f, -0.1f,  0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(1.0f, 1.0f)},
Vertex{glm::vec3(-0.1f, -0.1f,  0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(0.0f, 1.0f)},
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

	Shader shaderProgram("default.vert", "default.frag");
	//LINK LIGHT SHADERS
	Shader lightShader("light.vert", "light.frag");
	
	
	
	glm::vec4 blockColor = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	glm::vec3 blockPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 blockModel = glm::mat4(1.0f);
	blockModel = glm::translate(blockModel, blockPos);
	
	glm::vec3 dirtPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 dirtModel = glm::mat4(1.0f);
	dirtModel = glm::translate(dirtModel, dirtPos);
	

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 0, GL_FALSE, glm::value_ptr(blockModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), blockColor.x, blockColor.y, blockColor.z, blockColor.w);
	glUniform3f(glGetUniformLocation(lightShader.ID, "lightPos"), blockPos.x, blockPos.y, blockPos.z);

	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(dirtModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), blockColor.x, blockColor.y, blockColor.z, blockColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), blockPos.x, blockPos.y, blockPos.z);


	//Figure out how to do a texture atlas lmao

	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	
	//face culling makes sure the backside of rendered
	//objects doesnt render
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.3f, 2.0f));

	std::vector <Vertex>  cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
	std::vector <GLuint>  cubeInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
	std::vector <Texture> cubeTex(blockTexture, blockTexture + sizeof(blockTexture) / sizeof(Texture));
	Mesh block(cubeVerts, cubeInd, cubeTex);

	//Model sword("C:/Repos/learn-open-gl/Models/sword/sword.gltf");
	//Model scroll("C:/Repos/learn-open-gl/Models/scroll/scroll.gltf");
	//Model bunny("C:/Repos/learn-open-gl/Models/bunny/bunny.gltf");
	Model ground("C:/Repos/learn-open-gl/Models/ground/ground.gltf");
	Model trees("C:/Repos/learn-open-gl/Models/trees/scene.gltf");
	//bunny.Translate(0.0f, 10.0f, 0.0f);

	double prevTime = 0.0f;
	double crntTime = 0.0f;
	double timeDiff;
	unsigned int counter = 0;


	glm::vec3 blockPosArray[] = {
	   glm::vec3(0.0f, 0.0f, 0.0f),    // First cube at origin
	   glm::vec3(0.2f, 0.0f, 0.0f),    // Second cube 0.2 units to the right
	   glm::vec3(0.4f, 0.0f, 0.0f),    // Third cube 0.4 units to the right
	   glm::vec3(0.6f, 0.0f, 0.0f),    // Fourth cube 0.6 units to the right
	   glm::vec3(0.8f, 0.0f, 0.0f),    // Fifth cube 0.8 units to the right
	   glm::vec3(1.0f, 0.0f, 0.0f),    // Sixth cube 1.0 units to the right
	   glm::vec3(1.2f, 0.0f, 0.0f),    // Seventh cube 1.2 units to the right
	   glm::vec3(1.4f, 0.0f, 0.0f),    // Eighth cube 1.4 units to the right
	   glm::vec3(1.6f, 0.0f, 0.0f),    // Ninth cube 1.6 units to the right
	   glm::vec3(1.8f, 0.0f, 0.0f)     // Tenth cube 1.8 units to the right
	};

	//very simple render loop
	while (!glfwWindowShouldClose(window))
	{

		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;
		if (timeDiff >= 1.0 / 30.0)
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
		glClearColor(0.75f, 0.75f, 0.85f, 1.0f);
		//clear the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.Inputs(window);
		camera.updateMatrix(80.0f, 0.1f, 500.0f);
		
		//here, for singular meshes (not imported models)
		//you can pass the translated identity matrix in,
		//or transform that identity matrix over time like here
		
		//the speed at which the cube will rotate
		/*
		float rotSpeed = 0.0f;
		glm::vec3 axis = glm::vec3(0.0f, 0.0f, 0.0f);
		blockModel = glm::rotate(blockModel, glm::radians(rotSpeed), axis);
		*/

		//generate a minecraft chunk!!
		for (float x = 0.0f; x < 100.0f; x += 0.2f)
		{
			blockPos = glm::vec3(x, 0.0f, 0.0f);
			glm::mat4 newBlockModel = glm::translate(blockModel, blockPos);
			block.Draw(lightShader, camera, newBlockModel);
		}

		blockModel = glm::translate(blockModel, glm::vec3(0.0f, 0.0f, 0.0f));

		//block.Draw(lightShader, camera, blockModel);
		//blockTexture->Unbind();

		//as for translating the Models and such... no idea
		//ground.Draw(shaderProgram, camera);
		//trees.Draw(shaderProgram, camera);
		
		 /*POLL EVENTS AND STUFF*/
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//optional: de-allocate all resources once they've outlived their purpose:
	// ----------------------------------------------------------------------
	
	shaderProgram.Delete();
	lightShader.Delete();

	
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
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

