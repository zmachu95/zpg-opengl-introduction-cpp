// Template for Blinn-Phong shader
//
// Coded by Zdenek Machu (MAC0690), October 2026

#version 330 core

in vec3 vertexNormal;
in vec3 vertexPosition;
in vec3 vertexColor;

uniform vec3 cameraPosition = vec3(0.0f);
uniform vec3 lightPosition = vec3(0.0f);

out vec4 FragColor;

float specularStrength = 16.0f;

float calculateAttenuation() {
    const float k_c = 1.0;
    const float k_l = 2.0;
    const float k_q = 5.0;
    
    float distanceToLight = length(lightPosition - vertexPosition);
    return 1.0f / (k_c + k_l * distanceToLight + k_q * distanceToLight * distanceToLight);
}

float calculateDiffusionIntensity(const vec3 normalizedToLightVector, const vec3 normalizedVertexNormal) {
    return max(dot(normalizedToLightVector, normalizedVertexNormal), 0.0f);
}

float calculateSpecularIntensity(const vec3 normalizedToLightVector, const vec3 normalizedVertexNormal) {
    vec3 toCameraVector = normalize(cameraPosition - vertexPosition);
    vec3 halfwayVector = normalize(normalizedToLightVector + toCameraVector);
    return pow(max(dot(normalizedVertexNormal, halfwayVector), 0.0f), specularStrength);
}

void main()
{
    vec3 normalizedToLightVector = normalize(lightPosition - vertexPosition);
    vec3 normalizedVertexNormal = normalize(vertexNormal);

    float ambientFactor = 0.1f;
    float diffFactor = calculateDiffusionIntensity(normalizedToLightVector, normalizedVertexNormal);
    float specFactor = calculateSpecularIntensity(normalizedToLightVector, normalizedVertexNormal);
    float attenuation = calculateAttenuation();

    FragColor = vec4((ambientFactor + attenuation * diffFactor) * vertexColor + attenuation * specFactor * vec3(1.0f), 1.0f);
}