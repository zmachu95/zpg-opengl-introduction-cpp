#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 transformation = mat4(1.0f);
uniform mat4 projectionMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);

out vec3 vertexColor;

void main()
{
    vertexColor = vec3(0.f, 0.35f, 0.f);

    gl_Position = projectionMatrix * viewMatrix * transformation * vec4(position, 1.0);
}