// UniformVariableManager.cpp - Contains definition of UniformVariableManager
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include <cstdio>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shaders/UniformVariableManager.h>
#include <string>

/**
 * @brief Name of transformation matrix shader uniform variable.
 */
static constexpr const char* TRANSFORMATION_MATRIX_UNIFORM_VAR =
        "transformation";

/**
 * @brief Name of projection matrix shader uniform variable.
 */
static constexpr const char* PROJECTION_MATRIX_UNIFORM_VAR = "projectionMatrix";

/**
 * @brief Name of view matrix shader uniform variable.
 */
static constexpr const char* VIEW_MATRIX_UNIFORM_VAR = "viewMatrix";

/**
 * @brief Name of camera position shader uniform variable.
 */
static constexpr const char* CAMERA_POSITION_UNIFORM_VAR = "cameraPosition";

/**
 * @brief Name of normal matrix shader uniform variable.
 */
static constexpr const char* NORMAL_MATRIX_UNIFORM_VAR = "normalMatrix";

using namespace std::string_literals;

UniformVariableManager::UniformVariableManager(
        GLuint parentShaderProgramId)
    : m_parentShaderProgramId{parentShaderProgramId}, m_cameraUpdated{false},
      m_projectionMatrix{glm::mat4{1.0f}}, m_viewMatrix{glm::mat4{1.0f}},
      m_cameraPosition{0.0f, 0.0f, -1.0f}, m_uniformVariableLocations{} {}

GLint UniformVariableManager::getUniformVariableLocation(
        const std::string& variableName) {
    auto it = this->m_uniformVariableLocations.find(variableName);
    if (it != this->m_uniformVariableLocations.end()) {
        return it->second;
    }

    GLint location = glGetUniformLocation(
            this->m_parentShaderProgramId, variableName.c_str());
    if (location == -1) {
        printf("WARNING! Unable to find variable named `%s` for shader program "
               "%d!\n",
                variableName.c_str(), this->m_parentShaderProgramId);
    }

    this->m_uniformVariableLocations[variableName] = location;
    return location;
}

void UniformVariableManager::setIntUniformVar(
        const std::string& variableName, const int value) {
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    if (variableLocation != -1) {
        glUniform1i(variableLocation, (GLint)value);
    }
}

void UniformVariableManager::setBoolUniformVar(
        const std::string& variableName, const bool value) {
    this->setIntUniformVar(variableName, (int)value);
}

void UniformVariableManager::setFloatUniformVar(
        const std::string& variableName, const float value) {
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    if (variableLocation != -1) {
        glUniform1f(variableLocation, (GLfloat)value);
    }
}

void UniformVariableManager::setVec3UniformVar(
        const std::string& variableName, const glm::vec3& value) {
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    if (variableLocation != -1) {
        glUniform3fv(variableLocation, 1, glm::value_ptr(value));
    }
}

void UniformVariableManager::setVec4UniformVar(
        const std::string& variableName, const glm::vec4& value) {
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    if (variableLocation != -1) {
        glUniform4fv(variableLocation, 1, glm::value_ptr(value));
    }
}

void UniformVariableManager::setMat3UniformVar(
        const std::string& variableName, const glm::mat3& value) {
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    if (variableLocation != -1) {
        glUniformMatrix3fv(
                variableLocation, 1, GL_FALSE, glm::value_ptr(value));
    }
}

void UniformVariableManager::setMat4UniformVar(
        const std::string& variableName, const glm::mat4& value) {
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    if (variableLocation != -1) {
        glUniformMatrix4fv(
                variableLocation, 1, GL_FALSE, glm::value_ptr(value));
    }
}

void UniformVariableManager::handleCameraUpdate(
        const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix,
        const glm::vec3& cameraPosition) {
    this->m_projectionMatrix = projectionMatrix;
    this->m_viewMatrix = viewMatrix;
    this->m_cameraPosition = cameraPosition;
    this->m_cameraUpdated = true;
}

bool UniformVariableManager::isCameraUpdated() const {
    return this->m_cameraUpdated;
}

void UniformVariableManager::applyTransformation(
        const glm::mat4& transformationMatrix) {
    this->setMat4UniformVar(
            TRANSFORMATION_MATRIX_UNIFORM_VAR, transformationMatrix);
    /* also send normal matrix to the shader */
    this->setMat3UniformVar(NORMAL_MATRIX_UNIFORM_VAR,
            glm::transpose(glm::inverse(glm::mat3(transformationMatrix))));
}

void UniformVariableManager::applyCameraMatrices() {
    this->m_cameraUpdated = false;
    this->setMat4UniformVar(
            PROJECTION_MATRIX_UNIFORM_VAR, this->m_projectionMatrix);
    this->setMat4UniformVar(VIEW_MATRIX_UNIFORM_VAR, this->m_viewMatrix);
    this->setVec3UniformVar(
            CAMERA_POSITION_UNIFORM_VAR, this->m_cameraPosition);
}

void UniformVariableManager::applySupplementalMatrices(
        const std::unordered_map<std::string, glm::mat4>&
                supplementalMatricesMap) {
    for (const auto& kvPair : supplementalMatricesMap) {
        this->setMat4UniformVar(kvPair.first, kvPair.second);
    }
}
