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


Vertex lightVertices[] =
{
	// Front face (z = 0.1)
Vertex{glm::vec3(-0.1f, -0.1f,  0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.3333f)},
Vertex{glm::vec3(0.1f, -0.1f,  0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(0.1f,  0.1f,  0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(1.0f, 0.6666f)},
Vertex{glm::vec3(-0.1f,  0.1f,  0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.6666f)},

// Back face (z = -0.1)
Vertex{glm::vec3(-0.1f, -0.1f, -0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(0.0f, 0.3333f)},
Vertex{glm::vec3(0.1f,  -0.1f, -0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(0.1f,  0.1f, -0.1f) ,  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(1.0f, 0.6666f)},
Vertex{glm::vec3(-0.1f, 0.1f, -0.1f) ,  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec2(0.0f, 0.6666f)},

// Left face (x = -0.1)									
Vertex{glm::vec3(-0.1f, -0.1f, -0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(0.0f, 0.3333f)},
Vertex{glm::vec3(-0.1f, -0.1f,  0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(-0.1f,  0.1f,  0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(1.0f, 0.6666f)},
Vertex{glm::vec3(-0.1f,  0.1f, -0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),   glm::vec2(0.0f, 0.6666f)},

// Right face (x = 0.1)									
Vertex{glm::vec3(0.1f, -0.1f,  0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(0.0f, 0.3333f)},
Vertex{glm::vec3(0.1f, -0.1f, -0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(0.1f,  0.1f, -0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(1.0f, 0.6666f)},
Vertex{glm::vec3(0.1f,  0.1f,  0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),      glm::vec2(0.0f, 0.6666f)},

// Top face (y = 0.1)										
Vertex{glm::vec3(-0.1f,  0.1f,  0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(0.0f, 0.0f)},
Vertex{glm::vec3(0.1f,  0.1f,  0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(1.0f, 0.0f)},
Vertex{glm::vec3(0.1f,  0.1f, -0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(1.0f, 0.3333f)},
Vertex{glm::vec3(-0.1f,  0.1f, -0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec2(0.0f, 0.3333f)},

// Bottom face (y = -0.1)									
Vertex{glm::vec3(-0.1f, -0.1f, -0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(0.0f, 0.6666f)},
Vertex{glm::vec3(0.1f, -0.1f, -0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(1.0f, 0.6666f)},
Vertex{glm::vec3(0.1f, -0.1f,  0.1f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(1.0f, 1.0f)},
Vertex{glm::vec3(-0.1f, -0.1f,  0.1f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),     glm::vec2(0.0f, 1.0f)},
};

GLuint lightIndices[] =
{
	// Front face
	0, 1, 2,   2, 3, 0,
	// Back face
	4, 5, 6,   6, 7, 4,
	// Left face
	8, 9, 10,  10, 11, 8,
	// Right face
	12, 13, 14, 14, 15, 12,
	// Top face
	16, 17, 18, 18, 19, 16,
	// Bottom face
	20, 21, 22, 22, 23, 20
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
	
	
	
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 10.0f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	
	glm::vec3 dirtPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 dirtModel = glm::mat4(1.0f);
	dirtModel = glm::translate(dirtModel, dirtPos);
	

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 0, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(lightShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(dirtModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	//Figure out how to do a texture atlas lmao

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.3f, 2.0f));

	std::vector <Vertex>  lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint>  lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	std::vector <Texture> lightTex(blockTexture, blockTexture + sizeof(blockTexture) / sizeof(Texture));
	Mesh block(lightVerts, lightInd, lightTex);
	//Model sword("C:/Repos/learn-open-gl/Models/sword/sword.gltf");
	//Model scroll("C:/Repos/learn-open-gl/Models/scroll/scroll.gltf");
	//Model bunny("C:/Repos/learn-open-gl/Models/bunny/bunny.gltf");
	Model ground("C:/Repos/learn-open-gl/Models/ground/ground.gltf");
	Model trees("C:/Repos/learn-open-gl/Models/trees/scene.gltf");
	//bunny.Translate(0.0f, 10.0f, 0.0f);

	//very simple render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);
		
		//specify color of background
		glClearColor(0.75f, 0.75f, 0.85f, 1.0f);
		//clear the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.Inputs(window);
		camera.updateMatrix(80.0f, 0.1f, 500.0f);
		
		
	
	
		//sword.Draw(shaderProgram, camera);
		//sword.Draw(shaderProgram, camera);
		//scroll.Draw(shaderProgram, camera);
		block.Draw(lightShader, camera);
		blockTexture->Unbind();
		ground.Draw(shaderProgram, camera);
		trees.Draw(shaderProgram, camera);
		//bunny.Draw(shaderProgram, camera);
		 /*POLL EVENTS AND STUFF*/

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

