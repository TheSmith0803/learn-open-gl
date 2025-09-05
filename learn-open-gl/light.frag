#version 330 core

out vec4 FragColor;;
in vec2 texCoordLight;


uniform vec4 lightColor;
uniform sampler2D diffuse0;

void main()
{
	//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	FragColor = texture(diffuse0, texCoordLight);
}
