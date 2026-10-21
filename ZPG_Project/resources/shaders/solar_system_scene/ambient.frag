// Template for ambient shader
//
// Coded by Zdenek Machu (MAC0690), October 2026

#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

void main()
{
    float ambientFactor = 1.0f;
    FragColor = vec4(ambientFactor * vertexColor, 1.0f);
}