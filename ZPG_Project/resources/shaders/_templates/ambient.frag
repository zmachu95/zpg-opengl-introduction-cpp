// Template for ambient shader
//
// Coded by Zdenek Machu (MAC0690), October 2026

#version 330 core

in vec3 vertexColor;
in vec2 texCoords;

// add more samplers if needed with names textureX, where X is [0, 15]
uniform bool usesTextures = false;
uniform sampler2D texture0;

out vec4 FragColor;

void main()
{
    float ambientFactor = 0.9f;
    vec4 baseColor = usesTextures ? texture(texture0, texCoords) : vec4(vertexColor, 1.0f);
    vec3 ambient = ambientFactor * baseColor.xyz;
    FragColor = vec4(ambient, baseColor.w);
}