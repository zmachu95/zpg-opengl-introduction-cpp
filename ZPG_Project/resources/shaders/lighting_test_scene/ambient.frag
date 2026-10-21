// Template for ambient shader
//
// Coded by Zdenek Machu (MAC0690), October 2026

#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

void main()
{
    float ambientFactor = 0.1f;
    FragColor = vec4(ambientFactor * vec3(0.385f, 0.647f, 0.812f), 1.0f);
}