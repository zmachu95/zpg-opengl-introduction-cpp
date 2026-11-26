// LightingManager.h - Contains declaration of LightingManager static class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <glm/ext/vector_float3.hpp>

class ShaderProgram;

/**
 * @brief Provides methods for setting lighting properties.
 */
namespace LightingManager {
namespace DirectedLights {
/**
 * @brief Sets the number of directed lights in given shader program.
 * @param program The shader program.
 * @param count Number of directed lights.
 */
void setLightsCount(ShaderProgram& program, unsigned int count);

/**
 * @brief Sets the direction of given directed light in given shader
 * program.
 * @param program The shader program.
 * @param index The index of directed light.
 * @param direction The new direction.
 */
void setLightDirection(
        ShaderProgram& program, unsigned int index, const glm::vec3& direction);

/**
 * @brief Sets the color of given directed light in given shader
 * program.
 * @param program The shader program.
 * @param index The index of directed light.
 * @param color The new color.
 */
void setLightColor(
        ShaderProgram& program, unsigned int index, const glm::vec3& color);

/**
 * @brief Sets the shininess exponent of given directed light in given
 * shader program.
 * @param program The shader program.
 * @param index The index of directed light.
 * @param exponent The new shininess exponent.
 */
void setLightShininessExponent(
        ShaderProgram& program, unsigned int index, float exponent);

/**
 * @brief Enables / disables specular effect of given directed light in
 * given shader program.
 * @param program The shader program.
 * @param index The index of directed light.
 * @param applySpecular Flag whether specular effect is to be enabled.
 */
void setLightSpecularFlag(
        ShaderProgram& program, unsigned int index, bool applySpecular);

/**
 * @brief Enables / disables Blinn model of given directed light in
 * given shader program.
 * @param program The shader program.
 * @param index The index of directed light.
 * @param applyBlinn Flag whether Blinn model is to be used.
 */
void setLightBlinnFlag(
        ShaderProgram& program, unsigned int index, bool applyBlinn);
} // namespace DirectedLights

/*
 *
 */

namespace PointLights {
/**
 * @brief Sets the number of point lights in given shader program.
 * @param program The shader program.
 * @param count Number of point lights.
 */
void setLightsCount(ShaderProgram& program, unsigned int count);

/**
 * @brief Sets the position of given point light in given shader
 * program.
 * @param program The shader program.
 * @param index The index of point light.
 * @param position The new position.
 */
void setLightPosition(
        ShaderProgram& program, unsigned int index, const glm::vec3& position);

/**
 * @brief Sets the attenuation factors of given point light in given
 * shader program.
 * @param program The shader program.
 * @param index The index of point light.
 * @param constantTerm Constant attenuation term.
 * @param linearTerm Linear attenuation term.
 * @param quadraticTerm Quadratic attenuation term.
 */
void setLightAttenuation(ShaderProgram& program, unsigned int index,
        float constantTerm, float linearTerm, float quadraticTerm);

/**
 * @brief Sets the color of given point light in given shader
 * program.
 * @param program The shader program.
 * @param index The index of point light.
 * @param color The new color.
 */
void setLightColor(
        ShaderProgram& program, unsigned int index, const glm::vec3& color);

/**
 * @brief Sets the shininess exponent of given point light in given
 * shader program.
 * @param program The shader program.
 * @param index The index of point light.
 * @param exponent The new shininess exponent.
 */
void setLightShininessExponent(
        ShaderProgram& program, unsigned int index, float exponent);

/**
 * @brief Enables / disables specular effect of given point light in
 * given shader program.
 * @param program The shader program.
 * @param index The index of point light.
 * @param applySpecular Flag whether specular effect is to be enabled.
 */
void setLightSpecularFlag(
        ShaderProgram& program, unsigned int index, bool applySpecular);

/**
 * @brief Enables / disables Blinn model of given point light in
 * given shader program.
 * @param program The shader program.
 * @param index The index of point light.
 * @param applyBlinn Flag whether Blinn model is to be used.
 */
void setLightBlinnFlag(
        ShaderProgram& program, unsigned int index, bool applyBlinn);
} // namespace PointLights

/*
 *
 */

namespace CameraSpotLight {
/**
 * @brief Enables / disables the camera spot light in given shader
 * program.
 * @param program The shader program.
 * @param enable Flag to enable / disable the camera spot light.
 */
void enable(ShaderProgram& program, bool enable);

/**
 * @brief Sets the cutoff angles for the camera spot light in given
 * shader program.
 * @param program The shader program.
 * @param innerCutoffAngle_deg The inner cutoff angle in [deg].
 * @param outerCutoffAngle_deg The outer cutoff angle in [deg].
 */
void setCutoffAngles(ShaderProgram& program, float innerCutoffAngle_deg,
        float outerCutoffAngle_deg);

/**
 * @brief Sets the attenuation factors of camera spot light in given
 * shader program.
 * @param program The shader program.
 * @param constantTerm Constant attenuation term.
 * @param linearTerm Linear attenuation term.
 * @param quadraticTerm Quadratic attenuation term.
 */
void setAttenuation(ShaderProgram& program, float constantTerm,
        float linearTerm, float quadraticTerm);

/**
 * @brief Sets the color of camera spot light in given shader
 * program.
 * @param program The shader program.
 * @param color The new color.
 */
void setColor(ShaderProgram& program, const glm::vec3& color);

/**
 * @brief Sets the shininess exponent of camera spot light in given
 * shader program.
 * @param program The shader program.
 * @param exponent The new shininess exponent.
 */
void setShininessExponent(ShaderProgram& program, float exponent);

/**
 * @brief Enables / disables specular effect of camera spot light in
 * given shader program.
 * @param program The shader program.
 * @param applySpecular Flag whether specular effect is to be enabled.
 */
void setSpecularFlag(ShaderProgram& program, bool applySpecular);

/**
 * @brief Enables / disables Blinn model of camera spot light in
 * given shader program.
 * @param program The shader program.
 * @param applyBlinn Flag whether Blinn model is to be used.
 */
void setBlinnFlag(ShaderProgram& program, bool applyBlinn);
} // namespace CameraSpotLight

/**
 * @brief Sets the ambient color factors in given shader program.
 * @param program The shader program.
 * @param factors Factor values.
 */
void setAmbientFactors(ShaderProgram& program, const glm::vec3& factors);
} // namespace LightingManager
