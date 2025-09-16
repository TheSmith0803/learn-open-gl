#version 330 core
layout (location = 0) in vec3 aPos;
//Colors
layout (location = 1) in vec3 aColor;

layout (location = 2) in vec3 aNormal;

layout (location = 3) in vec2 aTex;

out vec3 crntPos;
// outputs the color for the fragment shader
out vec3 color;

out vec3 Normal;
// outputs the texture coordinates to the fragment shader
out vec2 texCoord;




uniform mat4 camMatrix;
uniform mat4 model;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
	/*TODO: I am imagining the problem is the way the model class
	is communicating with THIS vertex shader*/
	crntPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));
	// assigns the colors from the vertex data to the "color"
	color = aColor;
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	Normal = aNormal;

	gl_Position = camMatrix * vec4(aPos, 1.0);
	
	/*
	vec4 worldPos = model * vec4(aPos, 1.0f);
	crntPos = vec3(worldPos);

	gl_Position = camMatrix * worldPos;

	color = aColor;
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	Normal = aNormal;
	*/
}