// Fragment shader used for object highlighting.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

uniform vec3 highlightColor = vec3(0.85f, 0.278f, 0.278f);

void main()
{
    FragColor = vec4(highlightColor, 1.0);
}