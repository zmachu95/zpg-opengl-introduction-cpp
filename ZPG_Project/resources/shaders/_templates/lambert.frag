// Template for Lambert shader
//
// Coded by Zdenek Machu (MAC0690), October 2026

#version 330 core

in vec3 vertexNormal;
in vec3 vertexPosition;
in vec3 vertexColor;
in vec2 texCoords;

// add more samplers if needed with names textureX, where X is [0, 15]
uniform bool usesTextures = false;
uniform sampler2D texture0;

uniform vec3 lightPosition = vec3(0.0f);

out vec4 FragColor;

float calculateAttenuation() {
    const float k_c = 1.0;
    const float k_l = 1.0;
    const float k_q = 2.0;
    
    float distanceToLight = length(lightPosition - vertexPosition);
    return 1.0f / (k_c + k_l * distanceToLight + k_q * distanceToLight * distanceToLight);
}

float calculateDiffusionIntensity() {
    vec3 toLightVector = lightPosition - vertexPosition;
    return max(dot(normalize(toLightVector), normalize(vertexNormal)), 0.0f);
}

void main()
{
    float ambientFactor = 0.1f;
    float diffFactor = calculateDiffusionIntensity();
    float attenuation = calculateAttenuation();
    vec4 baseColor = usesTextures ? texture(texture0, texCoords) : vec4(vertexColor, 1.0f);

    vec3 ambient = ambientFactor * baseColor.xyz;
    vec3 diffuse = attenuation * diffFactor * baseColor.xyz;

    FragColor = vec4(ambient + diffuse, baseColor.w);
}