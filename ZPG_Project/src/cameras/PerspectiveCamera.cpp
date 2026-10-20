// PerspectiveCamera.cpp - Contains definition of PerspectiveCamera class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <cameras/CameraCommonSettings.h>
#include <cameras/MovementDirectionEnum.h>
#include <cameras/PerspectiveCamera.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#include <stdexcept>
#include <string>

/**
 * @brief Default value of field of view angle in [deg].
 */
constexpr float DEFAULT_FOV_DEG = 60.0f;

/**
 * @brief Default and minimal value of near clipping plane distance.
 */
constexpr float MIN_NEAR_CLIP_PLANE_DIST = 0.1f;

/**
 * @brief Default value of far clipping plane distance.
 */
constexpr float FAR_CLIP_PLANE_DIST = 100.0f;

/**
 * @brief Minimal value of field of view angle in [deg].
 */
constexpr float MIN_FOV_DEG = 1.0f;

/**
 * @brief Maximal value of field of view angle in [deg].
 */
constexpr float MAX_FOV_DEG = 170.0f;

PerspectiveCamera::PerspectiveCamera(
        const std::shared_ptr<CameraCommonSettings>& commonSettings,
        float aspectRatio, const glm::vec3& cameraPosition,
        const glm::vec3& viewDirection, float fov_deg,
        float nearClippingPlaneDistance, float farClippingPlaneDistance)
    : m_publisher{},
      m_cameraGeometry{commonSettings, cameraPosition, viewDirection},
      m_fov_deg{fov_deg}, m_aspectRatio{aspectRatio},
      m_nearClippingPlaneDistance{nearClippingPlaneDistance},
      m_farClippingPlaneDistance{farClippingPlaneDistance} {
    if (aspectRatio <= 0) {
        throw std::invalid_argument("Aspect ration cannot be <= 0!");
    } else if (fov_deg < MIN_FOV_DEG || fov_deg > MAX_FOV_DEG) {
        throw std::invalid_argument(
                std::string{"Field of view angle must lie in interval ["}
                + std::to_string(MIN_FOV_DEG) + " to "
                + std::to_string(MAX_FOV_DEG) + "]!");
    } else if (nearClippingPlaneDistance < MIN_NEAR_CLIP_PLANE_DIST) {
        throw std::invalid_argument(
                std::string{"Near clipping plane distance cannot be less than "}
                + std::to_string(MIN_NEAR_CLIP_PLANE_DIST));
    } else if (farClippingPlaneDistance <= nearClippingPlaneDistance) {
        throw std::invalid_argument(
                "Far clipping plane distance must be greater than near "
                "clipping plane distance!");
    }
}

PerspectiveCamera::PerspectiveCamera(
        const std::shared_ptr<CameraCommonSettings>& commonSettings,
        float aspectRatio, const glm::vec3& cameraPosition,
        const glm::vec3& viewDirection)
    : PerspectiveCamera(commonSettings, aspectRatio, cameraPosition,
              viewDirection, DEFAULT_FOV_DEG, MIN_NEAR_CLIP_PLANE_DIST,
              FAR_CLIP_PLANE_DIST) {}

PerspectiveCamera::PerspectiveCamera(
        const std::shared_ptr<CameraCommonSettings>& commonSettings,
        float aspectRatio, const glm::vec3& cameraPosition)
    : PerspectiveCamera(commonSettings, aspectRatio, cameraPosition,
              commonSettings->getZeroRotationRefUnitVector()) {}

PerspectiveCamera::PerspectiveCamera(
        const std::shared_ptr<CameraCommonSettings>& commonSettings,
        float aspectRatio)
    : PerspectiveCamera(commonSettings, aspectRatio, glm::vec3{0.0f}) {}

const glm::vec3& PerspectiveCamera::getCameraPosition() const {
    return this->m_cameraGeometry.getCameraPosition();
}

float PerspectiveCamera::getAspectRatio() const { return this->m_aspectRatio; }

float PerspectiveCamera::getFieldOfViewAngle() const { return this->m_fov_deg; }

float PerspectiveCamera::getNearClippingPlaneDistance() const {
    return this->m_nearClippingPlaneDistance;
}

float PerspectiveCamera::getFarClippingPlaneDistance() const {
    return this->m_farClippingPlaneDistance;
}

void PerspectiveCamera::setAspectRatio(
        int width, int height) {
    if (width <= 0) {
        throw std::invalid_argument("Width cannot be <= 0!");
    } else if (height <= 0) {
        throw std::invalid_argument("Height cannot be <= 0!");
    }

    float oldValue = this->m_aspectRatio;
    this->m_aspectRatio = (float)width / height;
    this->notifyOnChange(oldValue != this->m_aspectRatio);
}
void PerspectiveCamera::setFieldOfViewAngle(
        float angle_deg) {
    if (angle_deg < MIN_FOV_DEG || angle_deg > MAX_FOV_DEG) {
        throw std::invalid_argument(
                std::string{"Field of view angle must lie in interval ["}
                + std::to_string(MIN_FOV_DEG) + " to "
                + std::to_string(MAX_FOV_DEG) + "]!");
    }

    float oldValue = this->m_fov_deg;
    this->m_fov_deg = angle_deg;
    this->notifyOnChange(oldValue != this->m_fov_deg);
}

void PerspectiveCamera::setNearClippingPlaneDistance(
        float distance) {
    if (distance >= this->m_farClippingPlaneDistance) {
        throw std::invalid_argument("Near clipping plane distance must be less "
                                    "than far clipping plane distance!");
    } else if (distance < MIN_NEAR_CLIP_PLANE_DIST) {
        throw std::invalid_argument(
                std::string{"Near clipping plane distance cannot be less than "}
                + std::to_string(MIN_NEAR_CLIP_PLANE_DIST) + "!");
    }

    float oldValue = this->m_nearClippingPlaneDistance;
    this->m_nearClippingPlaneDistance = distance;
    this->notifyOnChange(oldValue != this->m_nearClippingPlaneDistance);
}

void PerspectiveCamera::setFarClippingPlaneDistance(
        float distance) {
    if (distance <= this->m_nearClippingPlaneDistance) {
        throw std::invalid_argument(
                "Far clipping plane distance must be greater "
                "than near clipping plane distance!");
    }

    float oldValue = this->m_farClippingPlaneDistance;
    this->m_farClippingPlaneDistance = distance;
    this->notifyOnChange(oldValue != this->m_farClippingPlaneDistance);
}

int PerspectiveCamera::registerCameraUpdateListener(
        const CameraUpdateListenerPtr& listener) {
    return this->m_publisher.registerCameraUpdateListener(listener,
            this->calculateProjectionMatrix(),
            this->m_cameraGeometry.calculateViewMatrix());
}

bool PerspectiveCamera::unregisterCameraUpdateListener(
        int listenerId) {
    return this->m_publisher.unregisterCameraUpdateListener(listenerId);
}

void PerspectiveCamera::update(
        MovementDirection movementDirection, int horizontalRotationIncrement,
        int verticalRotationIncrement, float deltaT) {
    bool cameraChanged = this->m_cameraGeometry.update(movementDirection,
            horizontalRotationIncrement, verticalRotationIncrement, deltaT);

    if (cameraChanged) {
        this->notifyCameraUpdateListeners();
    }
}

void PerspectiveCamera::notifyCameraUpdateListeners() {
    this->m_publisher.notifyListeners(this->calculateProjectionMatrix(),
            this->m_cameraGeometry.calculateViewMatrix());
}

glm::mat4 PerspectiveCamera::calculateProjectionMatrix() const {
    return glm::perspective(glm::radians(this->m_fov_deg), this->m_aspectRatio,
            this->m_nearClippingPlaneDistance,
            this->m_farClippingPlaneDistance);
}

void PerspectiveCamera::notifyOnChange(
        bool cameraChanged) {
    if (cameraChanged) {
        this->notifyCameraUpdateListeners();
    }
}
