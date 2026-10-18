// CameraCommonSettings.h - Contains declaration of CameraCommonSettings class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <glm/ext/vector_float3.hpp>

/**
 * @brief Flyweight class for common camera settings.
 */
class CameraCommonSettings {
  public:
    /**
     * @brief Full constructor of CameraCommonSettings.
     * @param invertVerticalAxis Flag whether vertical axis should be inverted.
     * @param mouseLookSensitivity Factor for mouse look sensitivity.
     * @param cameraMovementSpeed Factor for camera movement speed.
     * @param limitPitchAngle_deg The maximal limit for mouse look pitch angle
     * in [deg].
     * @param upVector The camera up vector.
     * @param zeroRotationRefVector Reference vector for 0 mouse look rotation.
     * @throw std::invalid_argument - Thrown when upVector or
     * zeroRotationRefVector are zero-length vectors.
     */
    CameraCommonSettings(bool invertVerticalAxis, float mouseLookSensitivity,
            float cameraMovementSpeed, float limitPitchAngle_deg,
            const glm::vec3& upVector, const glm::vec3& zeroRotationRefVector);

    /**
     * @brief Constructor for CameraCommonSettings with some default settings
     * set.
     * @param invertVerticalAxis Flag whether vertical axis should be inverted.
     * @param mouseLookSensitivity Factor for mouse look sensitivity.
     * @param cameraMovementSpeed Factor for camera movement speed.
     */
    CameraCommonSettings(bool invertVerticalAxis, float mouseLookSensitivity,
            float cameraMovementSpeed);

    /**
     * @brief Constructor for CameraCommonSettings with most default settings
     * set.
     * @param invertVerticalAxis Flag whether vertical axis should be inverted.
     */
    CameraCommonSettings(bool invertVerticalAxis);

    /**
     * @brief Constructor for CameraCommonSettings with all default settings
     * set.
     */
    CameraCommonSettings();

    /*
     *
     */

    /**
     * @brief Gets the up vector as unit vector.
     * @return The up vector as unit vector.
     */
    const glm::vec3& getUpUnitVector() const;

    /**
     * @brief Gets the reference vector for 0 mouse look rotation as unit
     * vector.
     * @return The reference vector for 0 mouse look rotation as unit vector.
     */
    const glm::vec3& getZeroRotationRefUnitVector() const;

    /**
     * @brief Gets the mouse look sensitivity factor.
     * @return The mouse look sensitivity factor.
     */
    float getMouseLookSensitivity() const;

    /**
     * @brief Gets the camera movement speed factor.
     * @return The camera movement speed factor.
     */
    float getCameraMovementSpeed() const;

    /**
     * @brief Gets whether the vertical axis should be inverted.
     * @return true if the vertical axis should be inverted, otherwise returns
     * false.
     */
    bool getInvertVerticalAxis() const;

    /**
     * @brief Gets the maximal limit for mouse look pitch angle in [deg].
     * @return The maximal limit for mouse look pitch angle in [deg].
     */
    float getLimitPitchAngle() const;

    /*
     *
     */

    /**
     * @brief Sets the mouse look sensitivity factor. Negative values are
     * converted to 0.
     * @param value New value to set.
     */
    void setMouseLookSensitivity(float value);

    /**
     * @brief Sets the camera movement speed factor. Negative values are
     * converted to 0.
     * @param value New value to set.
     */
    void setCameraMovementSpeed(float value);

    /**
     * @brief Sets whether the vertical axis should be inverted.
     * @param value Supply true to invert the axis, false to keep as is.
     */
    void setInvertVerticalAxis(bool value);

  private:
    glm::vec3 m_upVector;
    glm::vec3 m_zeroRotationRefVector;
    float m_mouseMoveSensitivity;
    float m_cameraMovementSpeed;
    bool m_invertVerticalAxis;
    float m_limitPitchAngle;
};
