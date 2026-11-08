#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 inTexCoords;

uniform mat4 transformation = mat4(1.0f);
uniform mat4 projectionMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat3 normalMatrix = mat3(1.0f);

out vec3 vertexColor;
out vec3 vertexNormal;
out vec3 vertexPosition;
out vec2 texCoords;

void main()
{
    vertexColor = vec3(0.f, 0.2f, 0.f);
    vertexNormal = normalMatrix * normal;
    vertexPosition = vec3(transformation * vec4(position, 1.0));
    texCoords = inTexCoords;
    gl_Position = projectionMatrix * viewMatrix * transformation * vec4(position, 1.0);
}