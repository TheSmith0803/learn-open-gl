#version 330 core
out vec4 FragColor;

// imports the color from the vertex shader
in vec3 crntPos;
in vec3 color; 
in vec3 Normal;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor;

uniform vec3 lightPos;
uniform vec3 camPos;

uniform float distan;


vec4 pointLight() 
{
    
    vec3 lightVec = lightPos - crntPos;
    float dist = length(lightVec);
    float const1 = 0.05;
    float const2 = 0.01;
    float inten = 1.0f / (const1 * dist * dist + const2 * dist + 1.0f);

    //ambient lighting
    float ambient = 0.05f;

    //diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    //FragColor = vec4(color, 1.0);
    return (texture(diffuse0, texCoord) * lightColor * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;

}

vec4 directionalLight() 
{
    //ambient lighting
    float ambient = 0.05f;

    //diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    //FragColor = vec4(color, 1.0);
    return (texture(diffuse0, texCoord) * lightColor * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
    float outerCone = 0.8f;
    float innerCone = 0.95f;
    
    //ambient lighting
    float ambient = 0.05f;

    //diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 5.0f);
    inten = inten / distan;

    //FragColor = vec4(color, 1.0);
    return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}


void main()
{   
    FragColor = directionalLight();
}