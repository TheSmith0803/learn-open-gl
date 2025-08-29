#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <fstream>
#include <sstream>
//#include <shaders/default.vert>
//#include <shaders/default.frag>

#include"shaderClass.h"
#include"Texture.h"
#include"VBO.h"
#include"EBO.h"
#include"VAO.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

/*for reading text files(aka shaders)
convert to c string using c_str() method after
std::string readTextFile(const std::string& filePath);
*/

const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

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
	
	// Vertices coordinates
	GLfloat vertices[] =
	{//     COORDINATES     /        COLORS      /   TexCoord  //

		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,// Lower left corner
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	 0.0f, 1.0f,// Upper left corner
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,// Upper right corner
		 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,// Lower right corner

	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0,2,1, // upper triangle
		0,3,2 // lower triangle
	};

	Shader shaderProgram("shader.vert", "shader.frag");

	VAO VAO1;
	VAO1.Bind();

	// generates vertex buffer object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// gets id of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture
	Texture Shrek("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Shrek.texUnit(shaderProgram, "tex0", 0);

	//very simple render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		//processInput(window);
		// render
		// clear the color buffer

		//specify color of background
		glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
		//clear the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// tell openGl what shader program we want to use
		shaderProgram.Activate();
		//assigns a value to the uniform; NOTE: must always be done after activating the Shader
		glUniform1f(uniID, 0.5f);
		//binds texture so that it appears in rendering
		Shrek.Bind();
		//bind the VAO so opengl knows how to use it
		VAO1.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//optional: de-allocate all resources once they've outlived their purpose:
	// ----------------------------------------------------------------------
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	Shrek.Delete();
	

	
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

