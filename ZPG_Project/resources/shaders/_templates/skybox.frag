// Skybox fragment shader
//
// Coded by Zdenek Machu (MAC0690), November 2026

#version 330 core
out vec4 FragColor;

in vec3 texCoords;

uniform vec3 ambientFactors = vec3(0.7f);

uniform samplerCube texture0;

void main()
{    
    vec4 baseColor = texture(texture0, texCoords);
    vec3 ambient = ambientFactors * baseColor.xyz;
    FragColor = vec4(ambient, baseColor.w);
}