#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 transformation = mat4(1.0f);
uniform mat4 projectionMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);
out vec3 vertexColor;

void main()
{
    if(gl_VertexID>36443) {
        vertexColor = clamp(0.2 + 1 * (abs(color.y)), 0.0, 1.0) * vec3(0.2f, 1.f, 0.f);
    } else {
        vertexColor = clamp(0.5 + 1 * (abs(color.y)), 0.0, 1.0) * vec3(0.7f, 0.3f, 0.2f);
    }

    gl_Position = projectionMatrix * viewMatrix * transformation * vec4(position, 1.0);
}