// UniformVariableManager.h - Contains declaration of UniformVariableManager
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <listeners/ICameraUpdateListener.h>
#include <stdexcept>
#include <string>
#include <unordered_map>

/**
 * @brief Indicates that uniform variable could not be found in the shader
 * program.
 */
class UniformVariableNotFoundException : public std::runtime_error {
  public:
    UniformVariableNotFoundException(const std::string& message)
        : std::runtime_error(message) {};
};

using GLuint = unsigned int;
using GLint = int;

/**
 * @brief Allows setting of shader Uniform variables.
 */
class UniformVariableManager : public ICameraUpdateListener {
  public:
    /**
     * @brief UniformVariableManager default constructor.
     * @param parentShaderProgramId The ID of parent shader program.
     */
    UniformVariableManager(GLuint parentShaderProgramId);

    virtual ~UniformVariableManager() = default;

    /*
     *
     */

    /**
     * @brief Checks whether the camera matrices were updated.
     * @return true if new matrices were received, otherwise returns false.
     */
    bool isCameraUpdated() const;

    /*
     *
     */

    /**
     * @brief Applies the transformation matrix in shader program.
     * @param transformationMatrix The transformation matrix.
     */
    void applyTransformation(const glm::mat4& transformationMatrix);

    /**
     * @brief Applies cached camera matrices in shader program.
     *
     */
    void applyCameraMatrices();

    /*
     *
     */

    /**
     * @brief Applies supplied supplementary matrices in the shader.
     * @param supplementalMatricesMap Map of shader matrix variables and their
     * values.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     */
    void applySupplementalMatrices(
            const std::unordered_map<std::string, glm::mat4>&
                    supplementalMatricesMap);

  private:
    GLuint m_parentShaderProgramId;
    bool m_cameraUpdated;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;

    /**
     * @brief Gets the location of uniform shader variable.
     * @param variableName The variable name.
     * @return GLint with the variable name.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     */
    GLint getUniformVariableLocation(const std::string& variableName) const;

    /**
     * @brief Sets new bool value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     */
    void setBoolUniformVar(
            const std::string& variableName, const bool value) const;

    /**
     * @brief Sets new int value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     */
    void setIntUniformVar(
            const std::string& variableName, const int value) const;

    /**
     * @brief Sets new float value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     */
    void setFloatUniformVar(
            const std::string& variableName, const float value) const;

    /**
     * @brief Sets new glm::vec4 value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     */
    void setVec4UniformVar(
            const std::string& variableName, const glm::vec4& value) const;

    /**
     * @brief Sets new glm::mat4 value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     */
    void setMat4UniformVar(
            const std::string& variableName, const glm::mat4& value) const;

    /*
     *
     */

    /**
     * @brief Handles the camera update.
     * @param projectionMatrix The new camera projection matrix.
     * @param viewMatrix The new camera view matrix.
     */
    void handleCameraUpdate(
            const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
};
