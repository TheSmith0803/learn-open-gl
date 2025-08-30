#version 330 core

out vec4 FragColor;

in vec2 texCoordLight;

uniform sampler2D lightTex;

void main()
{
	//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	FragColor = texture(lightTex, texCoordLight);
}
