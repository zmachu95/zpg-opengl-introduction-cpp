// Fragment shader for multiple lighting models
//
// Coded by Zdenek Machu (MAC0690), November 2026

#version 330 core

// defines number of lights in the scene
#define NUMBER_OF_POINT_LIGHTS 50
#define NUMBER_OF_SPOT_LIGHTS 1
#define NUMBER_OF_DIRECTED_LIGHTS 1

struct DirectedLight {
    vec3 direction;
    
    vec3 color;
    float shininessExponent;

    bool useSpecular;
    bool useBlinn;
};

struct PointLight {
    vec3 position;
    
    float attConstant;
    float attLinear;
    float attQuadratic;

    vec3 color;
    float shininessExponent;

    bool useSpecular;
    bool useBlinn;
};

struct SpotLight {
    // uses camera position and direction
    float innerCosineCutOff;
    float outerCosineCutOff;
  
    float attConstant;
    float attLinear;
    float attQuadratic;

    vec3 color;
    float shininessExponent;

    bool useSpecular;
    bool useBlinn;
};

in vec3 vertexNormal;
in vec3 vertexPosition;
in vec3 vertexColor;
in vec2 texCoords;

// add more samplers if needed with names textureX, where X is [0, 15]
uniform bool usesTextures = false;
uniform sampler2D texture0;

uniform vec3 cameraPosition = vec3(0.0f);
uniform vec3 cameraViewDirection = vec3(0.0f);

uniform vec3 ambientFactors = vec3(1.0f);

uniform int directedLightsCount = 0;
uniform int pointLightsCount = 0;
uniform int spotLightsCount = 0;

uniform PointLight pointLights[NUMBER_OF_POINT_LIGHTS];
uniform SpotLight spotLights[NUMBER_OF_SPOT_LIGHTS];
uniform DirectedLight directedLights[NUMBER_OF_DIRECTED_LIGHTS];

out vec4 FragColor;

float calculateAttenuation(
        float distanceToLight, float attConstant, float attLinear, 
        float attQuadratic) {
    
    float linearTerm = attLinear * distanceToLight;
    float quadTerm = attQuadratic * distanceToLight * distanceToLight;
    return 1.0f / (attConstant + linearTerm + quadTerm);
}

float calculateDiffusionIntensity(
        const vec3 normalizedToLightVector, const vec3 normalizedVertexNormal) {
    return max(dot(normalizedToLightVector, normalizedVertexNormal), 0.0f);
}

float calculateSpecularIntensity_phong(
        const vec3 normalizedToLightVector, const vec3 normalizedVertexNormal, 
        const vec3 normalizedToCameraVector) {
    vec3 reflectDirection = reflect(-normalizedToLightVector, normalizedVertexNormal);
    return max(dot(reflectDirection, normalizedToCameraVector), 0.0f);
}

float calculateSpecularIntensity_blinn(
        const vec3 normalizedToLightVector, const vec3 normalizedVertexNormal, 
        const vec3 normalizedToCameraVector) {
    vec3 halfwayVector = normalize(normalizedToLightVector + normalizedToCameraVector);
    return max(dot(normalizedVertexNormal, halfwayVector), 0.0f);
}

float calculateSpotLightOverallIntensity(
        const vec3 normalizedToLightVector, const vec3 normalizedVertexNormal,
        const vec3 normalizedLightDirection, float innerCosineCutOff,
        float outerCosineCutOff) {
    float fragmentCosine = dot(-normalizedLightDirection, normalizedToLightVector);
    return clamp(
        (fragmentCosine - outerCosineCutOff) / (innerCosineCutOff - outerCosineCutOff), 
        0.0f, 1.0f);
}

void main()
{
    vec3 toCameraVector = cameraPosition - vertexPosition;
    float toCameraDistance = length(toCameraVector);
    vec3 normalizedVertexNormal = normalize(vertexNormal);
    vec3 normalizedToCameraVector = toCameraVector / toCameraDistance;
    vec3 normalizedCameraViewDirection = normalize(cameraViewDirection);

    vec4 baseColor = usesTextures 
                        ? texture(texture0, texCoords) 
                        : vec4(vertexColor, 1.0f);
    vec3 finalColor = ambientFactors * baseColor.xyz;
    

    // point lights
    for (int i = 0; i < pointLightsCount; i++) {
        vec3 toLightVector = pointLights[i].position - vertexPosition;
        float toLightDistance = length(toLightVector);
        vec3 normalizedToLightVector = toLightVector / toLightDistance;

        float attenuation = calculateAttenuation(toLightDistance, 
                pointLights[i].attConstant, pointLights[i].attLinear, 
                pointLights[i].attQuadratic);
        float diffuseFactor = calculateDiffusionIntensity(
                normalizedToLightVector, normalizedVertexNormal);
        float specularFactor = !pointLights[i].useSpecular || dot(normalizedToLightVector, normalizedVertexNormal) <= 0 
                                    ? 0.0f 
                                    : (pointLights[i].useBlinn 
                                        ? calculateSpecularIntensity_blinn(
                                                normalizedToLightVector, 
                                                normalizedVertexNormal, 
                                                normalizedToCameraVector)
                                        : calculateSpecularIntensity_phong(
                                                normalizedToLightVector, 
                                                normalizedVertexNormal,
                                                normalizedToCameraVector));
        
        vec3 diffuseComponent = attenuation
                * diffuseFactor * pointLights[i].color * baseColor.xyz;
        vec3 specularComponent = attenuation
                * pow(specularFactor, pointLights[i].shininessExponent) * pointLights[i].color;

        finalColor += diffuseComponent + specularComponent;
    }

    // directed lights
    for (int i = 0; i < directedLightsCount; i++) {
        vec3 normalizedToLightVector = -normalize(directedLights[i].direction);

        float diffuseFactor = calculateDiffusionIntensity(
                normalizedToLightVector, normalizedVertexNormal);
        float specularFactor = !directedLights[i].useSpecular || dot(normalizedToLightVector, normalizedVertexNormal) <= 0 
                                    ? 0.0f 
                                    : (directedLights[i].useBlinn 
                                        ? calculateSpecularIntensity_blinn(
                                                normalizedToLightVector, 
                                                normalizedVertexNormal,
                                                normalizedToCameraVector)
                                        : calculateSpecularIntensity_phong(
                                                normalizedToLightVector, 
                                                normalizedVertexNormal,
                                                normalizedToCameraVector));
        
        vec3 diffuseComponent = 
            diffuseFactor * directedLights[i].color * baseColor.xyz;
        vec3 specularComponent = 
            pow(specularFactor, directedLights[i].shininessExponent) * directedLights[i].color;

        finalColor += diffuseComponent + specularComponent;
    }
    

    // spot lights
    for (int i = 0; i < spotLightsCount; i++) {
        float toLightDistance = length(toCameraDistance);

        float attenuation = calculateAttenuation(toLightDistance, 
                spotLights[i].attConstant, spotLights[i].attLinear, 
                spotLights[i].attQuadratic);
        float overallIntensity = calculateSpotLightOverallIntensity(
                normalizedToCameraVector, normalizedVertexNormal, 
                normalizedCameraViewDirection, spotLights[i].innerCosineCutOff,
                spotLights[i].outerCosineCutOff);
        float diffuseFactor = calculateDiffusionIntensity(
                normalizedToCameraVector, normalizedVertexNormal);
        float specularFactor = !spotLights[i].useSpecular || dot(normalizedToCameraVector, normalizedVertexNormal) <= 0 
                                    ? 0.0f 
                                    : (spotLights[i].useBlinn 
                                        ? calculateSpecularIntensity_blinn(
                                                normalizedToCameraVector, 
                                                normalizedVertexNormal,
                                                normalizedToCameraVector)
                                        : calculateSpecularIntensity_phong(
                                                normalizedToCameraVector, 
                                                normalizedVertexNormal,
                                                normalizedToCameraVector));
        
        vec3 diffuseComponent = overallIntensity * attenuation
                * diffuseFactor * spotLights[i].color * baseColor.xyz;
        vec3 specularComponent = overallIntensity * attenuation
                * pow(specularFactor, spotLights[i].shininessExponent) * spotLights[i].color;

        finalColor += diffuseComponent + specularComponent;
    }

    FragColor = vec4(finalColor, baseColor.w);
}