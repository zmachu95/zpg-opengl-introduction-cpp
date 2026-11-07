// Template for skybox vertex shader
//
// Coded by Zdenek Machu (MAC0690), November 2026

#version 330 core
layout (location = 0) in vec3 position;

out vec3 texCoords;

uniform mat4 projectionMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);

void main()
{
    texCoords = position;
    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);
} 