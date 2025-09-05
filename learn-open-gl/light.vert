#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTex;

in vec4 FragColor;

uniform mat4 model;
uniform mat4 camMatrix;
out vec2 texCoordLight;

void main() 
{
	gl_Position = camMatrix * model * vec4(aPos, 1.0);
	texCoordLight = aTex;
}
