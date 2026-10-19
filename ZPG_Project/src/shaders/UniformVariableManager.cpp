// UniformVariableManager.cpp - Contains definition of UniformVariableManager
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/type_ptr.inl>
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

using namespace std::string_literals;

UniformVariableManager::UniformVariableManager(
        GLuint parentShaderProgramId)
    : m_parentShaderProgramId{parentShaderProgramId}, m_cameraUpdated{false},
      m_projectionMatrix{glm::mat4{1.0f}}, m_viewMatrix{glm::mat4{1.0f}} {}

GLint UniformVariableManager::getUniformVariableLocation(
        const std::string& variableName) const {
    GLint location = glGetUniformLocation(
            this->m_parentShaderProgramId, variableName.c_str());
    if (location == -1) {
        throw UniformVariableNotFoundException{
                "Unable to find variable named: "s + variableName};
    }

    return location;
}

void UniformVariableManager::setIntUniformVar(
        const std::string& variableName, const int value) const {
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    glUniform1i(variableLocation, (GLint)value);
}

void UniformVariableManager::setBoolUniformVar(
        const std::string& variableName, const bool value) const {
    this->setIntUniformVar(variableName, (int)value);
}

void UniformVariableManager::setFloatUniformVar(
        const std::string& variableName, const float value) const {
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    glUniform1f(variableLocation, (GLfloat)value);
}

void UniformVariableManager::setVec4UniformVar(
        const std::string& variableName, const glm::vec4& value) const {
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    glUniform4fv(variableLocation, 1, glm::value_ptr(value));
}

void UniformVariableManager::setMat4UniformVar(
        const std::string& variableName, const glm::mat4& value) const {
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    glUniformMatrix4fv(variableLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void UniformVariableManager::handleCameraUpdate(
        const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
    this->m_projectionMatrix = projectionMatrix;
    this->m_viewMatrix = viewMatrix;
    this->m_cameraUpdated = true;
}

bool UniformVariableManager::isCameraUpdated() const {
    return this->m_cameraUpdated;
}

void UniformVariableManager::applyTransformation(
        const glm::mat4& transformationMatrix) {
    this->setMat4UniformVar(
            TRANSFORMATION_MATRIX_UNIFORM_VAR, transformationMatrix);
}

void UniformVariableManager::applyCameraMatrices() {
    this->m_cameraUpdated = false;
    this->setMat4UniformVar(
            PROJECTION_MATRIX_UNIFORM_VAR, this->m_projectionMatrix);
    this->setMat4UniformVar(VIEW_MATRIX_UNIFORM_VAR, this->m_viewMatrix);
}
