// Template for Lambert shader
//
// Coded by Zdenek Machu (MAC0690), October 2026

#version 330 core

in vec3 vertexNormal;
in vec3 vertexPosition;
in vec3 vertexColor;

out vec4 FragColor;

uniform vec3 lightPosition = vec3(0.0f);

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
    FragColor = vec4((ambientFactor + attenuation * diffFactor) * vertexColor, 1.0f);
}