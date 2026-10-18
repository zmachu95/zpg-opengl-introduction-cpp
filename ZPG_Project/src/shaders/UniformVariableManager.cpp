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

using namespace std::string_literals;

UniformVariableManager::UniformVariableManager(
        GLuint parentShaderProgramId)
    : m_parentShaderProgramId{parentShaderProgramId},
      m_isParentShaderProgramActive{false} {}

void UniformVariableManager::throwIfNotActive(
        const std::string& variableName) const {
    if (!this->m_isParentShaderProgramActive) {
        throw ShaderProgramNotActiveException(
                "Cannot set uniform variable `"s + variableName
                + "` because the shader program is not active!");
    }
}

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

void UniformVariableManager::setIsParentShaderProgramActive(
        bool value) {
    this->m_isParentShaderProgramActive = value;
}

void UniformVariableManager::setIntUniformVar(
        const std::string& variableName, const int value) const {
    throwIfNotActive(variableName);
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    glUniform1i(variableLocation, (GLint)value);
    // std::cout << "Successfully set uniform variable `" << variableName <<
    // "`.\n";
}

void UniformVariableManager::setBoolUniformVar(
        const std::string& variableName, const bool value) const {
    this->setIntUniformVar(variableName, (int)value);
}

void UniformVariableManager::setFloatUniformVar(
        const std::string& variableName, const float value) const {
    throwIfNotActive(variableName);
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    glUniform1f(variableLocation, (GLfloat)value);
    // std::cout << "Successfully set uniform variable `" << variableName <<
    // "`.\n";
}

void UniformVariableManager::setVec4UniformVar(
        const std::string& variableName, const glm::vec4& value) const {
    throwIfNotActive(variableName);
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    glUniform4fv(variableLocation, 1, glm::value_ptr(value));
    // std::cout << "Successfully set uniform variable `" << variableName <<
    // "`.\n";
}

void UniformVariableManager::setMat4UniformVar(
        const std::string& variableName, const glm::mat4& value) const {
    throwIfNotActive(variableName);
    GLint variableLocation = this->getUniformVariableLocation(variableName);
    glUniformMatrix4fv(variableLocation, 1, GL_FALSE, glm::value_ptr(value));
    // std::cout << "Successfully set uniform variable `" << variableName <<
    // "`.\n";
}
