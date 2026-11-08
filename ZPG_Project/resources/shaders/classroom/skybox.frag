// Template for skybox fragment shader
//
// Coded by Zdenek Machu (MAC0690), November 2026

#version 330 core
out vec4 FragColor;

in vec3 texCoords;

uniform samplerCube texture0;

void main()
{    
    float ambientFactor = 0.7f;
    vec4 baseColor = texture(texture0, texCoords);
    vec3 ambient = ambientFactor * baseColor.xyz;
    FragColor = vec4(ambient, baseColor.w);
}