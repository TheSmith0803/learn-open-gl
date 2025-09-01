#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>


#include"shaderClass.h"
#include"Texture.h"
#include"VBO.h"
#include"EBO.h"
#include"VAO.h"
#include"Camera.h"
#include"BlockUVs.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

/*for reading text files(aka shaders)
convert to c string using c_str() method after
std::string readTextFile(const std::string& filePath);
*/

const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

// Vertices coordinates
GLfloat vertices[] =
{//     COORDINATES     /        COLORS             /   TexCoord  //

	-0.5f, 0.0f,  0.5f,     0.2f,  0.70f, 0.44f,	  0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	  5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     1.0f,  0.0f,  0.0f,	      0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	  5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.0f,  0.2f,  0.0f,	      2.5f, 5.0,

};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4,
};

GLfloat lightVertices[] = 
{
	// Front face (z = 0.1)
	-0.1f, -0.1f,  0.1f,       0.0f, 0.0f,// bottom-left
	 0.1f, -0.1f,  0.1f,      1.0f, 0.0f
	 0.1f,  0.1f,  0.1f,     1.0f, 1.0f,
	-0.1f,  0.1f,  0.1f,     0.0f, 1.0f,

	// Back face (z = -0.1)
	-0.1f, -0.1f, -0.1f,     0.0f, 0.0f,
	-0.1f,  0.1f, -0.1f,     1.0f, 0.0f,
	 0.1f,  0.1f, -0.1f,     1.0f, 1.0f,
	 0.1f, -0.1f, -0.1f,    0.0f, 1.0f,

	 // Left face (x = -0.1)
	 -0.1f, -0.1f, -0.1f,    0.0f, 0.0f,
	 -0.1f, -0.1f,  0.1f,    1.0f, 0.0f,
	 -0.1f,  0.1f,  0.1f,    1.0f, 1.0f,
	 -0.1f,  0.1f, -0.1f,    0.0f, 1.0f,

	 // Right face (x = 0.1)
	  0.1f, -0.1f,  0.1f,    0.0f, 0.0f,
	  0.1f, -0.1f, -0.1f,    1.0f, 0.0f,
	  0.1f,  0.1f, -0.1f,    1.0f, 1.0f,
	  0.1f,  0.1f,  0.1f,    0.0f, 1.0f,

	  // Top face (y = 0.1)
	  -0.1f,  0.1f,  0.1f,    0.0f, 0.0f,
	   0.1f,  0.1f,  0.1f,    1.0f, 0.0f,
	   0.1f,  0.1f, -0.1f,    1.0f, 1.0f,
	  -0.1f,  0.1f, -0.1f,    0.0f, 1.0f,

	  // Bottom face (y = -0.1)
	  -0.1f, -0.1f, -0.1f,    0.0f, 0.0f,
	   0.1f, -0.1f, -0.1f,    1.0f, 0.0f,
	   0.1f, -0.1f,  0.1f,    1.0f, 1.0f,
	  -0.1f, -0.1f,  0.1f,    0.0f, 1.0f,
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




	// define shaders
	Shader pyramidShader("shader.vert", "shader.frag");

	VAO VAO1;
	VAO1.Bind();

	// generates vertex buffer object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	//for the vertices
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);

	//for a stagnant color
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	//VAO to link the brick texture
	//VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	//LINK LIGHT SHADERS
	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	//for the vertices and shape
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);

	//for shrek texture linking and displaying
	lightVAO.LinkAttrib(lightVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();






	glm::vec4 lighColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.9f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));

	pyramidShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(pyramidShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));

	// Texture
	Texture Shrek("shrek.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Shrek.texUnit(lightShader, "lightTex", 0);
	
	Texture Brick("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	Brick.texUnit(pyramidShader, "tex0", 0);

	//Figure out how to do a texture atlas lmao
	Texture Atlas("Atlas.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	Atlas.texUnit(lightShader, "lightTex", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.3f, 2.0f));

	//very simple render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);
		//specify color of background
		glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
		//clear the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// tell openGl what shader program we want to use
		pyramidShader.Activate();
		camera.Matrix(pyramidShader, "camMatrix");
		//binds texture so that it appears in rendering
		//Brick.Bind();
		//bind the VAO so opengl knows how to use it
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		//Atlas.Bind();
		Shrek.Bind();
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//optional: de-allocate all resources once they've outlived their purpose:
	// ----------------------------------------------------------------------
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	pyramidShader.Delete();
	lightShader.Delete();
	Atlas.Delete();
	Brick.Delete();

	
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

