#version 330 core
out vec4 FragColor;

//color came from vertex shader
in vec4 vertexColor;

void main()
{
   FragColor = vertexColor;
}