// LightingManager.cpp - Contains definition of LightingManager static class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <lighting/LightingManager.h>
#include <shaders/ShaderProgram.h>
#include <stdexcept>
#include <string>

/**
 * @brief Maximal number of point lights set in shader file.
 */
constexpr unsigned int MAX_POINT_LIGHTS_COUNT = 50;

/**
 * @brief Maximal number of directed lights set in shader file.
 */
constexpr unsigned int MAX_DIRECTED_LIGHTS_COUNT = 1;

const std::string DIRECTION_PROPERTY = ".direction";
const std::string COLOR_PROPERTY = ".color";
const std::string SHININESS_EXPONENT_PROPERTY = ".shininessExponent";
const std::string USE_SPECULAR_PROPERTY = ".useSpecular";
const std::string USE_BLINN_PROPERTY = ".useBlinn";
const std::string POSITION_PROPERTY = ".position";
const std::string ATT_CONST_PROPERTY = ".attConstant";
const std::string ATT_LIN_PROPERTY = ".attLinear";
const std::string ATT_QUAD_PROPERTY = ".attQuadratic";
const std::string INNER_COSINE_CUTOFF_PROPERTY = ".innerCosineCutOff";
const std::string OUTER_COSINE_CUTOFF_PROPERTY = ".outerCosineCutOff";

using namespace std::string_literals;

/**
 * @brief Validates given point light index.
 * @param index The index.
 */
static void validatePointLightIndex(
        unsigned int index) {
    if (index >= MAX_POINT_LIGHTS_COUNT) {
        throw std::invalid_argument{
                "Point light index "s + std::to_string(index) + " is invalid!"};
    }
}

/**
 * @brief Validates given directed light index.
 * @param index The index.
 */
static void validateDirectedLightIndex(
        unsigned int index) {
    if (index >= MAX_DIRECTED_LIGHTS_COUNT) {
        throw std::invalid_argument{"Directed light index "s
                                    + std::to_string(index) + " is invalid!"};
    }
}

/**
 * @brief Creates text for accessing specific directed light within shaders.
 * @param index The light index.
 * @return String for accessing specific directed light within shaders.
 */
static std::string getDirectedLightArrayElementText(
        unsigned int index) {
    return "directedLights["s + std::to_string(index) + "]";
}

/**
 * @brief Creates text for accessing specific point light within shaders.
 * @param index The light index.
 * @return String for accessing specific point light within shaders.
 */
static std::string getPointLightArrayElementText(
        unsigned int index) {
    return "pointLights["s + std::to_string(index) + "]";
}

/**
 * @brief Creates text for accessing specific spot light within shaders.
 * @param index The light index.
 * @return String for accessing specific spot light within shaders.
 */
static std::string getSpotLightArrayElementText(
        unsigned int index) {
    return "spotLights["s + std::to_string(index) + "]";
}

void LightingManager::DirectedLights::setLightsCount(
        ShaderProgram& program, unsigned int count) {
    if (count > MAX_DIRECTED_LIGHTS_COUNT) {
        throw std::invalid_argument{"Cannot set more than "s
                                    + std::to_string(MAX_DIRECTED_LIGHTS_COUNT)
                                    + " directed lights!"};
    }

    program.setSupplementalUniformIntValue("directedLightsCount", count);
}

void LightingManager::PointLights::setLightsCount(
        ShaderProgram& program, unsigned int count) {
    if (count > MAX_POINT_LIGHTS_COUNT) {
        throw std::invalid_argument{"Cannot set more than "s
                                    + std::to_string(MAX_POINT_LIGHTS_COUNT)
                                    + " point lights!"};
    }

    program.setSupplementalUniformIntValue("pointLightsCount", count);
}

void LightingManager::CameraSpotLight::enable(
        ShaderProgram& program, bool enable) {
    program.setSupplementalUniformIntValue("spotLightsCount", (int)enable);
}

void LightingManager::setAmbientFactors(
        ShaderProgram& program, const glm::vec3& factors) {
    program.setSupplementalUniformVector("ambientFactors", factors);
}

void LightingManager::DirectedLights::setLightDirection(
        ShaderProgram& program, unsigned int index,
        const glm::vec3& direction) {
    validateDirectedLightIndex(index);

    program.setSupplementalUniformVector(
            getDirectedLightArrayElementText(index) + DIRECTION_PROPERTY,
            direction);
}

void LightingManager::DirectedLights::setLightColor(
        ShaderProgram& program, unsigned int index, const glm::vec3& color) {
    validateDirectedLightIndex(index);

    program.setSupplementalUniformVector(
            getDirectedLightArrayElementText(index) + COLOR_PROPERTY, color);
}

void LightingManager::DirectedLights::setLightShininessExponent(
        ShaderProgram& program, unsigned int index, float exponent) {
    validateDirectedLightIndex(index);

    program.setSupplementalUniformFloatValue(
            getDirectedLightArrayElementText(index)
                    + SHININESS_EXPONENT_PROPERTY,
            exponent);
}

void LightingManager::DirectedLights::setLightSpecularFlag(
        ShaderProgram& program, unsigned int index, bool applySpecular) {
    validateDirectedLightIndex(index);

    program.setSupplementalUniformBoolValue(
            getDirectedLightArrayElementText(index) + USE_SPECULAR_PROPERTY,
            applySpecular);
}

void LightingManager::DirectedLights::setLightBlinnFlag(
        ShaderProgram& program, unsigned int index, bool applyBlinn) {
    validateDirectedLightIndex(index);

    program.setSupplementalUniformBoolValue(
            getDirectedLightArrayElementText(index) + USE_BLINN_PROPERTY,
            applyBlinn);
}

void LightingManager::PointLights::setLightPosition(
        ShaderProgram& program, unsigned int index, const glm::vec3& position) {
    validatePointLightIndex(index);

    program.setSupplementalUniformVector(
            getPointLightArrayElementText(index) + POSITION_PROPERTY, position);
}

void LightingManager::PointLights::setLightAttenuation(
        ShaderProgram& program, unsigned int index, float constantTerm,
        float linearTerm, float quadraticTerm) {
    validatePointLightIndex(index);

    program.setSupplementalUniformFloatValue(
            getPointLightArrayElementText(index) + ATT_CONST_PROPERTY,
            constantTerm);
    program.setSupplementalUniformFloatValue(
            getPointLightArrayElementText(index) + ATT_LIN_PROPERTY,
            linearTerm);
    program.setSupplementalUniformFloatValue(
            getPointLightArrayElementText(index) + ATT_QUAD_PROPERTY,
            quadraticTerm);
}

void LightingManager::PointLights::setLightColor(
        ShaderProgram& program, unsigned int index, const glm::vec3& color) {
    validatePointLightIndex(index);

    program.setSupplementalUniformVector(
            getPointLightArrayElementText(index) + COLOR_PROPERTY, color);
}

void LightingManager::PointLights::setLightShininessExponent(
        ShaderProgram& program, unsigned int index, float exponent) {
    validatePointLightIndex(index);

    program.setSupplementalUniformFloatValue(
            getPointLightArrayElementText(index) + SHININESS_EXPONENT_PROPERTY,
            exponent);
}

void LightingManager::PointLights::setLightSpecularFlag(
        ShaderProgram& program, unsigned int index, bool applySpecular) {
    validatePointLightIndex(index);

    program.setSupplementalUniformBoolValue(
            getPointLightArrayElementText(index) + USE_SPECULAR_PROPERTY,
            applySpecular);
}

void LightingManager::PointLights::setLightBlinnFlag(
        ShaderProgram& program, unsigned int index, bool applyBlinn) {
    validatePointLightIndex(index);

    program.setSupplementalUniformBoolValue(
            getPointLightArrayElementText(index) + USE_BLINN_PROPERTY,
            applyBlinn);
}

void LightingManager::CameraSpotLight::setCutoffAngles(
        ShaderProgram& program, float innerCutoffAngle_deg,
        float outerCutoffAngle_deg) {
    program.setSupplementalUniformFloatValue(
            getSpotLightArrayElementText(0) + INNER_COSINE_CUTOFF_PROPERTY,
            glm::cos(glm::radians(innerCutoffAngle_deg)));
    program.setSupplementalUniformFloatValue(
            getSpotLightArrayElementText(0) + OUTER_COSINE_CUTOFF_PROPERTY,
            glm::cos(glm::radians(outerCutoffAngle_deg)));
}

void LightingManager::CameraSpotLight::setAttenuation(
        ShaderProgram& program, float constantTerm, float linearTerm,
        float quadraticTerm) {
    program.setSupplementalUniformFloatValue(
            getSpotLightArrayElementText(0) + ATT_CONST_PROPERTY, constantTerm);
    program.setSupplementalUniformFloatValue(
            getSpotLightArrayElementText(0) + ATT_LIN_PROPERTY, linearTerm);
    program.setSupplementalUniformFloatValue(
            getSpotLightArrayElementText(0) + ATT_QUAD_PROPERTY, quadraticTerm);
}

void LightingManager::CameraSpotLight::setColor(
        ShaderProgram& program, const glm::vec3& color) {
    program.setSupplementalUniformVector(
            getSpotLightArrayElementText(0) + COLOR_PROPERTY, color);
}

void LightingManager::CameraSpotLight::setShininessExponent(
        ShaderProgram& program, float exponent) {
    program.setSupplementalUniformFloatValue(
            getSpotLightArrayElementText(0) + SHININESS_EXPONENT_PROPERTY,
            exponent);
}

void LightingManager::CameraSpotLight::setSpecularFlag(
        ShaderProgram& program, bool applySpecular) {
    program.setSupplementalUniformBoolValue(
            getSpotLightArrayElementText(0) + USE_SPECULAR_PROPERTY,
            applySpecular);
}

void LightingManager::CameraSpotLight::setBlinnFlag(
        ShaderProgram& program, bool applyBlinn) {
    program.setSupplementalUniformBoolValue(
            getSpotLightArrayElementText(0) + USE_BLINN_PROPERTY, applyBlinn);
}
