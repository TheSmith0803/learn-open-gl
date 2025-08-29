#version 330 core
layout (location = 0) in vec3 aPos;
//Colors
layout (location = 1) in vec3 aColor;

layout (location = 2) in vec2 aTex;

// outputs the color for the fragment shader
out vec3 color;

out vec2 texCoord;

// controls the scale of the vertices
uniform float scale;

void main()
{
   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
   // assigns the colors from the vertex data to the "color"
   color = aColor;
   texCoord = aTex;
}