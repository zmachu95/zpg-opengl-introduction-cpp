// CameraGeometry.cpp - Contains definition of CameraGeometry class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "CameraGeometry.h"
#include "MovementDirectionEnum.h"
#include <cameras/CameraCommonSettings.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

/**
 * @brief Value which denotes zero for floating point numbers.
 */
constexpr float ZERO_LENGTH_TRESHOLD = 1e-6f;

CameraGeometry::CameraGeometry(
        const std::shared_ptr<CameraCommonSettings>& commonSettings,
        const glm::vec3& cameraPosition, const glm::vec3& viewDirection)
    : m_commonSettings{commonSettings}, m_eye{cameraPosition},
      m_yawAngle_deg{0.0f}, m_pitchAngle_deg{0.0f} {
    this->m_yawAngle_deg = this->convertViewDirectionToYawAngle(viewDirection);
    this->m_pitchAngle_deg =
            this->convertViewDirectionToPitchAngle(viewDirection);
}

const glm::vec3& CameraGeometry::getCameraPosition() const {
    return this->m_eye;
}

glm::mat4 CameraGeometry::calculateViewMatrix() const {
    return glm::lookAt(this->m_eye, this->calculateTarget(),
            this->m_commonSettings->getUpUnitVector());
}

bool CameraGeometry::update(
        MovementDirection movementDirection, int horizontalRotationIncrement,
        int verticalRotationIncrement, float deltaT) {
    bool cameraChanged = this->updateLookingDirection(
            horizontalRotationIncrement, verticalRotationIncrement, deltaT);

    const glm::vec3 currentViewVector = this->calculateTarget() - this->m_eye;
    cameraChanged |=
            this->updatePosition(movementDirection, currentViewVector, deltaT);
    return cameraChanged;
}

glm::vec3 CameraGeometry::getForwardMovementDirection(
        const glm::vec3& currentViewVector) const {
    const glm::vec3& upVector = this->m_commonSettings->getUpUnitVector();
    const glm::vec3 upVectorProjection =
            glm::dot(upVector, currentViewVector) * upVector;

    return currentViewVector - upVectorProjection;
}

glm::vec3 CameraGeometry::getRightMovementDirection(
        const glm::vec3& currentViewVector) const {
    return glm::cross(this->getForwardMovementDirection(currentViewVector),
            this->m_commonSettings->getUpUnitVector());
}

glm::vec3 CameraGeometry::convertMovementDirectionToVector(
        MovementDirection dir, const glm::vec3& currentViewVector) const {
    switch (dir) {
        case MovementDirection::FORWARD:
            return glm::normalize(
                    this->getForwardMovementDirection(currentViewVector));
        case MovementDirection::BACKWARD:
            return glm::normalize(
                    -this->getForwardMovementDirection(currentViewVector));
        case MovementDirection::LEFT:
            return glm::normalize(
                    -this->getRightMovementDirection(currentViewVector));
        case MovementDirection::RIGHT:
            return glm::normalize(
                    this->getRightMovementDirection(currentViewVector));
        case MovementDirection::FORWARD_AND_RIGHT:
            return glm::normalize(
                    this->getForwardMovementDirection(currentViewVector)
                    + this->getRightMovementDirection(currentViewVector));
        case MovementDirection::FORWARD_AND_LEFT:
            return glm::normalize(
                    this->getForwardMovementDirection(currentViewVector)
                    - this->getRightMovementDirection(currentViewVector));
        case MovementDirection::BACKWARD_AND_RIGHT:
            return glm::normalize(
                    -this->getForwardMovementDirection(currentViewVector)
                    + this->getRightMovementDirection(currentViewVector));
        case MovementDirection::BACKWARD_AND_LEFT:
            return glm::normalize(
                    -this->getForwardMovementDirection(currentViewVector)
                    - this->getRightMovementDirection(currentViewVector));
        default:
            return glm::vec3{0.f};
    }
}

float CameraGeometry::convertViewDirectionToYawAngle(
        const glm::vec3& viewDirection) const {
    if (viewDirection.length() < ZERO_LENGTH_TRESHOLD) {
        return 0.0f;
    } else {
        const glm::vec3& xAxisVector =
                this->m_commonSettings->getZeroRotationRefUnitVector();
        const glm::vec3& zAxisVector =
                this->m_commonSettings->getUpUnitVector();
        const glm::vec3 yAxisVector = glm::cross(zAxisVector, xAxisVector);

        float x = glm::dot(viewDirection, xAxisVector);
        float y = glm::dot(viewDirection, yAxisVector);

        float rawYawAngle_deg = glm::degrees(std::atan2f(y, x));

        if (rawYawAngle_deg < 0.0f) {
            return 360.0f + rawYawAngle_deg;
        } else {
            return rawYawAngle_deg;
        }
    }
}

float CameraGeometry::convertViewDirectionToPitchAngle(
        const glm::vec3& viewDirection) const {
    if (viewDirection.length() < ZERO_LENGTH_TRESHOLD) {
        return 0;
    } else {
        const glm::vec3& yAxisVector =
                this->m_commonSettings->getUpUnitVector();
        float y = glm::dot(viewDirection, yAxisVector);
        float x = (viewDirection - y * yAxisVector).length();

        return glm::degrees(std::atan2f(y, x));
    }
}

glm::vec3 CameraGeometry::calculateTarget() const {
    const glm::vec3& localAxisX =
            this->m_commonSettings->getZeroRotationRefUnitVector();
    const glm::vec3& localAxisZ = this->m_commonSettings->getUpUnitVector();
    const glm::vec3 localAxisY = glm::cross(localAxisZ, localAxisX);

    float yawAngle_rad = glm::radians(this->m_yawAngle_deg);
    float pitchAngle_rad = glm::radians(this->m_pitchAngle_deg);

    /* these target coordinates are w.r.t. to eye */
    glm::vec3 targetPoint_local{cos(yawAngle_rad) * cos(pitchAngle_rad),
            sin(yawAngle_rad) * cos(pitchAngle_rad), sin(pitchAngle_rad)};

    glm::mat3 localToGlobalCsTransform{localAxisX, localAxisY, localAxisZ};

    return this->m_eye + localToGlobalCsTransform * targetPoint_local;
}

bool CameraGeometry::updateLookingDirection(
        int horizontalRotationIncrement, int verticalRotationIncrement,
        float deltaT) {
    float newYawAngle_deg = this->m_yawAngle_deg
                            + this->convertRotationIncrementToAngleIncrement(
                                      horizontalRotationIncrement)
                                      * deltaT;

    int pitchAngleDirection =
            (this->m_commonSettings->getInvertVerticalAxis() ? -1 : 1);
    float newPitchAngle_deg =
            this->m_pitchAngle_deg
            + pitchAngleDirection
                      * this->convertRotationIncrementToAngleIncrement(
                              verticalRotationIncrement)
                      * deltaT;

    bool cameraChanged = newYawAngle_deg != this->m_yawAngle_deg
                         || newPitchAngle_deg != this->m_pitchAngle_deg;

    this->m_yawAngle_deg = newYawAngle_deg - 360.0f * (newYawAngle_deg > 360.0f)
                           + 360.0f * (newYawAngle_deg < 0.0f);
    this->m_pitchAngle_deg = glm::clamp(newPitchAngle_deg,
            -this->m_commonSettings->getLimitPitchAngle(),
            this->m_commonSettings->getLimitPitchAngle());

    return cameraChanged;
}

bool CameraGeometry::updatePosition(
        MovementDirection movementDirection, const glm::vec3& currentViewVector,
        float deltaT) {
    glm::vec3 directionVector = this->convertMovementDirectionToVector(
            movementDirection, currentViewVector);

    this->m_eye += this->m_commonSettings->getCameraMovementSpeed() * deltaT
                   * directionVector;

    bool cameraChanged = directionVector.x != 0 || directionVector.y != 0
                         || directionVector.z != 0;
    return cameraChanged;
}

float CameraGeometry::convertRotationIncrementToAngleIncrement(
        int rotationIncrement) const {
    return -this->m_commonSettings->getMouseLookSensitivity()
           * rotationIncrement;
}
