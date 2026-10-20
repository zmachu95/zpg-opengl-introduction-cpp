// Vertex shader for wall clock scenes
//
// Coded by Zdenek Machu (MAC0690), October 2026

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

uniform mat4 transformation = mat4(1.0f);
uniform mat4 projectionMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f) ;

uniform mat4 secondsPinTransformation = mat4(1.0f);
uniform mat4 minutesPinTransformation = mat4(1.0f);
uniform mat4 hoursPinTransformation = mat4(1.0f);

out vec3 vertexColor;

// changes input color to something more fancy
vec3 apply_color(vec3 input_color) {
    if(input_color.x == 0 && input_color.y == 0 && input_color.z == 0) {
        // border
        return vec3(0.2f);
    } else if(input_color.x == 1 && input_color.y == 1 && input_color.z == 0) {
        // logo
        return vec3(5.0f / 255, 195.0f / 255, 222.0f / 255); 
    } else if(input_color.x == 0 && input_color.y == 1.0f && input_color.z == 0) {
        // minutes pin
        return vec3(0.0f);
    } else if(input_color.x == 0 && input_color.y == 0 && input_color.z == 1.0f) {
        // hours pin
        return vec3(0.0f);
    } else {
        return input_color;
    }
}

// applies different transformations to various clock parts
vec4 apply_transformations(vec3 input_color) {
    if(input_color.x == 1.0f && input_color.y == 0 && input_color.z == 0) {
        // seconds pin
        return projectionMatrix * viewMatrix * transformation * secondsPinTransformation * vec4(position, 1.0);
    } else if(input_color.x == 0 && input_color.y == 1.0f && input_color.z == 0) {
        // minutes pin
        return projectionMatrix * viewMatrix * transformation * minutesPinTransformation * vec4(position, 1.0);
    } else if(input_color.x == 0 && input_color.y == 0 && input_color.z == 1.0f) {
        // hours pin
        return projectionMatrix * viewMatrix * transformation * hoursPinTransformation * vec4(position, 1.0);
    } else {
        // everything else
        return projectionMatrix * viewMatrix * transformation * vec4(position, 1.0);
    }
}

void main()
{
    vertexColor = apply_color(color);
    gl_Position = apply_transformations(color);
}