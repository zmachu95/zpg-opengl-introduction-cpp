// CameraCommonSettings.cpp - Contains definition of CameraCommonSettings class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <cameras/CameraCommonSettings.h>
#include <cmath>
#include <glm/detail/func_geometric.inl>
#include <glm/ext/vector_float3.hpp>
#include <stdexcept>

/**
 * @brief Default limit for mouse look pitch angle in [deg].
 */
constexpr float PITCH_ANGLE_DEFAULT_LIMIT = 89.0f;

/**
 * @brief The default up vector.
 */
constexpr glm::vec3 DEFAULT_UP_VECTOR = glm::vec3{0.0f, 1.0f, 0.0f};

/**
 * @brief The default reference vector for 0 mouse look rotation.
 */
constexpr glm::vec3 DEFAULT_ZERO_ROT_REF_VECTOR = glm::vec3{0.0f, 0.0f, -1.0f};

/**
 * @brief The minimal value of mouse look sensitivity factor.
 */
constexpr float MIN_MOUSE_SENSITIVITY = 0.0f;

/**
 * @brief The minimal value of camera movement speed factor.
 */
constexpr float MIN_MOVEMENT_SPEED = 0.0f;

/**
 * @brief Value which denotes zero for floating point numbers.
 */
constexpr float ZERO_LENGTH_TRESHOLD = 1e-6f;

/**
 * @brief The default value of mouse look sensitivity factor.
 */
constexpr float DEFAULT_MOUSE_SENSITIVITY = 3.0f;

/**
 * @brief The default value of camera movement speed factor.
 */
constexpr float DEFAULT_CAMERA_SPEED = 1.0f;

CameraCommonSettings::CameraCommonSettings(
        bool invertVerticalAxis, float mouseLookSensitivity,
        float cameraMovementSpeed, float limitPitchAngle_deg,
        const glm::vec3& upVector, const glm::vec3& zeroRotationRefVector)
    : m_mouseMoveSensitivity{
              fmaxf(mouseLookSensitivity, MIN_MOUSE_SENSITIVITY)},
      m_cameraMovementSpeed{fmaxf(cameraMovementSpeed, MIN_MOVEMENT_SPEED)},
      m_invertVerticalAxis{invertVerticalAxis},
      m_limitPitchAngle{limitPitchAngle_deg}, m_upVector{0.0f},
      m_zeroRotationRefVector{0.0f} {
    if (upVector.length() < ZERO_LENGTH_TRESHOLD) {
        throw std::invalid_argument("Up vector cannot be zero-length vector!");
    } else if (zeroRotationRefVector.length() < ZERO_LENGTH_TRESHOLD) {
        throw std::invalid_argument(
                "Zero-rotation reference vector cannot be zero-length vector!");
    }

    this->m_upVector = glm::normalize(upVector);
    this->m_zeroRotationRefVector =
            glm::normalize(zeroRotationRefVector
                           - glm::dot(zeroRotationRefVector, this->m_upVector)
                                     * this->m_upVector);
}

CameraCommonSettings::CameraCommonSettings(
        bool invertVerticalAxis, float mouseLookSensitivity,
        float cameraMovementSpeed)
    : CameraCommonSettings(invertVerticalAxis, mouseLookSensitivity,
              cameraMovementSpeed, PITCH_ANGLE_DEFAULT_LIMIT, DEFAULT_UP_VECTOR,
              DEFAULT_ZERO_ROT_REF_VECTOR) {}

CameraCommonSettings::CameraCommonSettings(
        bool invertVerticalAxis)
    : CameraCommonSettings(invertVerticalAxis, DEFAULT_MOUSE_SENSITIVITY,
              DEFAULT_CAMERA_SPEED) {}

CameraCommonSettings::CameraCommonSettings() : CameraCommonSettings(false) {}

const glm::vec3& CameraCommonSettings::getUpUnitVector() const {
    return this->m_upVector;
}

const glm::vec3& CameraCommonSettings::getZeroRotationRefUnitVector() const {
    return this->m_zeroRotationRefVector;
}

float CameraCommonSettings::getMouseLookSensitivity() const {
    return this->m_mouseMoveSensitivity;
}

float CameraCommonSettings::getCameraMovementSpeed() const {
    return this->m_cameraMovementSpeed;
}

void CameraCommonSettings::setMouseLookSensitivity(
        float value) {
    this->m_mouseMoveSensitivity = fmaxf(value, MIN_MOUSE_SENSITIVITY);
}

void CameraCommonSettings::setCameraMovementSpeed(
        float value) {
    this->m_cameraMovementSpeed = value;
}

bool CameraCommonSettings::getInvertVerticalAxis() const {
    return this->m_invertVerticalAxis;
}

float CameraCommonSettings::getLimitPitchAngle() const {
    return this->m_limitPitchAngle;
}

void CameraCommonSettings::setInvertVerticalAxis(
        bool value) {
    this->m_invertVerticalAxis = value;
}
