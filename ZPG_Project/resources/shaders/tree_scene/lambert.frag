// Lambert shader with multiple point lights and camera flashlight
//
// Coded by Zdenek Machu (MAC0690), November 2026

#version 330 core

#define NUMBER_OF_LIGHTS 10

in vec3 vertexNormal;
in vec3 vertexPosition;
in vec3 vertexColor;
in vec2 texCoords;

// add more samplers if needed with names textureX, where X is [0, 15]
uniform bool usesTextures = false;
uniform sampler2D texture0;

uniform vec3 cameraPosition = vec3(0.0f);
uniform vec3 cameraViewDirection = vec3(0.0f);
uniform vec3 lightPositions[NUMBER_OF_LIGHTS];

float flashlightInnerCosineCutoff = 0.9961f; // 5 deg
float flashlightOuterCosineCutoff = 0.9068f; // 25 deg
float flashlightEpsilon = flashlightInnerCosineCutoff - flashlightOuterCosineCutoff;

out vec4 FragColor;

float calculateAttenuation(vec3 lightPosition) {
    const float k_c = 1.0;
    const float k_l = 0.3;
    const float k_q = 0.08;
    
    float distanceToLight = length(lightPosition - vertexPosition);
    return 1.0f / (k_c + k_l * distanceToLight + k_q * distanceToLight * distanceToLight);
}

float calculateDiffusionIntensity(vec3 lightPosition, vec3 normalizedVertexNormal) {
    vec3 toLightVector = lightPosition - vertexPosition;
    return max(dot(normalize(toLightVector), normalizedVertexNormal), 0.0f);
}

float calculateFlashlightDiffusionIntensity(vec3 normalizedVertexNormal) {
    vec3 toLightVector = normalize(cameraPosition - vertexPosition);
    float fragmentCosine = dot(-cameraViewDirection, toLightVector);
    float intensity = clamp((fragmentCosine - flashlightOuterCosineCutoff) / flashlightEpsilon, 0.0f, 1.0f);
    return intensity * max(dot(toLightVector, normalizedVertexNormal), 0.0f);
}

void main()
{
    float ambientFactor = 0.15f;
    vec4 baseColor = usesTextures ? texture(texture0, texCoords) : vec4(vertexColor, 1.0f);
    vec3 ambient = ambientFactor * baseColor.xyz;
    vec3 normalizedVertexNormal = normalize(vertexNormal);

    vec3 finalColor = ambient;
    for(int i = 0; i < NUMBER_OF_LIGHTS; i++) {
        float diffFactor = calculateDiffusionIntensity(lightPositions[i], normalizedVertexNormal);
        float attenuation = calculateAttenuation(lightPositions[i]);
        vec3 diffuse = attenuation * diffFactor * baseColor.xyz;

        finalColor += diffuse;
    }

    finalColor += 0.8f * calculateFlashlightDiffusionIntensity(normalizedVertexNormal) * calculateAttenuation(cameraPosition);
    FragColor = vec4(finalColor, baseColor.w);
}