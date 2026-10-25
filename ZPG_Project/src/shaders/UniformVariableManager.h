// UniformVariableManager.h - Contains declaration of UniformVariableManager
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <cameras/ICameraUpdateListener.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <string>
#include <unordered_map>

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
     */
    void applySupplementalMatrices(
            const std::unordered_map<std::string, glm::mat4>&
                    supplementalMatricesMap);

  private:
    GLuint m_parentShaderProgramId;
    bool m_cameraUpdated;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::vec3 m_cameraPosition;
    std::unordered_map<std::string, GLint> m_uniformVariableLocations;

    /**
     * @brief Gets the location of uniform shader variable.
     * @param variableName The variable name.
     * @return GLint with the variable name.
     */
    GLint getUniformVariableLocation(const std::string& variableName);

    /**
     * @brief Sets new bool value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     */
    void setBoolUniformVar(const std::string& variableName, const bool value);

    /**
     * @brief Sets new int value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     */
    void setIntUniformVar(const std::string& variableName, const int value);

    /**
     * @brief Sets new float value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     */
    void setFloatUniformVar(const std::string& variableName, const float value);

    /**
     * @brief Sets new glm::vec3 value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     */
    void setVec3UniformVar(
            const std::string& variableName, const glm::vec3& value);

    /**
     * @brief Sets new glm::vec4 value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     */
    void setVec4UniformVar(
            const std::string& variableName, const glm::vec4& value);

    /**
     * @brief Sets new glm::mat3 value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     */
    void setMat3UniformVar(
            const std::string& variableName, const glm::mat3& value);

    /**
     * @brief Sets new glm::mat4 value to given uniform variable.
     * @param variableName The name of uniform variable to set.
     * @param value The new value.
     */
    void setMat4UniformVar(
            const std::string& variableName, const glm::mat4& value);

    /*
     *
     */

    /**
     * @brief Handles the camera update.
     * @param projectionMatrix The new camera projection matrix.
     * @param viewMatrix The new camera view matrix.
     * @param cameraPosition The new camera position.
     */
    virtual void handleCameraUpdate(const glm::mat4& projectionMatrix,
            const glm::mat4& viewMatrix, const glm::vec3& cameraPosition);
};
