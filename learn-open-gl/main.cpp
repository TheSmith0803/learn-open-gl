#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
//#include <shaders/default.vert>
//#include <shaders/default.frag>

#include"shaderClass.h"
#include"VBO.h"
#include"EBO.h"
#include"VAO.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

/*for reading text files(aka shaders)
convert to c string using c_str() method after
std::string readTextFile(const std::string& filePath);
*/

const unsigned int SCR_WIDTH = 800;
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
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};

	Shader shaderProgram("shader.vert", "color1.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	//very simple render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);
		// render
		// clear the color buffer
		

		// activate shader
		shaderProgram.Activate();
		glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//making the triangle flash green
		/*
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue * 5.0f) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram1, "ourColor");
		glUseProgram(shaderProgram1);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		*/
		VAO1.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

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

