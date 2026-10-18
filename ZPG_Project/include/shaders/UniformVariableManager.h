// UniformVariableManager.h - Contains declaration of UniformVariableManager
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float4.hpp>
#include <stdexcept>
#include <string>

/**
 * @brief Indicates that uniform variable could not be found in the shader
 * program.
 */
class UniformVariableNotFoundException : public std::runtime_error {
  public:
    UniformVariableNotFoundException(const std::string& message)
        : std::runtime_error(message) {};
};

/**
 * @brief Indicates that shader program is not active, thus the uniform variable
 * cannot be set.
 */
class ShaderProgramNotActiveException : public std::runtime_error {
  public:
    ShaderProgramNotActiveException(const std::string& message)
        : std::runtime_error(message) {};
};

using GLuint = unsigned int;
using GLint = int;

/**
 * @brief Allows setting of shader Uniform variables.
 */
class UniformVariableManager {
  public:
    /**
     * @brief UniformVariableManager default constructor.
     * @param parentShaderProgramId The ID of parent shader program.
     */
    UniformVariableManager(GLuint parentShaderProgramId);

    /*
     *
     */

    /**
     * @brief Sets whether the parent shader program is active.
     * @param value Value to set.
     */
    void setIsParentShaderProgramActive(bool value);

    /*
     *
     */

    /**
     * @brief Sets new bool value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     * @throw ShaderProgramNotActiveException - Thrown if the shader program is
     * not activated in OpenGL.
     */
    void setBoolUniformVar(
            const std::string& variableName, const bool value) const;

    /**
     * @brief Sets new int value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     * @throw ShaderProgramNotActiveException - Thrown if the shader program is
     * not activated in OpenGL.
     */
    void setIntUniformVar(
            const std::string& variableName, const int value) const;

    /**
     * @brief Sets new float value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     * @throw ShaderProgramNotActiveException - Thrown if the shader program is
     * not activated in OpenGL.
     */
    void setFloatUniformVar(
            const std::string& variableName, const float value) const;

    /**
     * @brief Sets new glm::vec4 value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     * @throw ShaderProgramNotActiveException - Thrown if the shader program is
     * not activated in OpenGL.
     */
    void setVec4UniformVar(
            const std::string& variableName, const glm::vec4& value) const;

    /**
     * @brief Sets new glm::mat4 value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     * @throw ShaderProgramNotActiveException - Thrown if the shader program is
     * not activated in OpenGL.
     */
    void setMat4UniformVar(
            const std::string& variableName, const glm::mat4& value) const;

  private:
    GLuint m_parentShaderProgramId;
    bool m_isParentShaderProgramActive;

    /**
     * @brief Gets the location of uniform shader variable.
     * @param variableName The variable name.
     * @return GLint with the variable name.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     */
    GLint getUniformVariableLocation(const std::string& variableName) const;

    /**
     * @brief Helper function which throws ShaderProgramNotActiveException if
     * the shader is not activated in OpenGL.
     * @param variableName The variable name.
     */
    void throwIfNotActive(const std::string& variableName) const;
};
