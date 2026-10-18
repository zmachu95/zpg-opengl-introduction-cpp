// PerspectiveCamera.h - Contains declaration of PerspectiveCamera class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <cameras/CameraGeometry.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <list>
#include <memory>
#include <utility>

class ICameraUpdateListener;
class CameraCommonSettings;
enum class MovementDirection;

/**
 * @brief Pointer to ICameraUpdateListener instance.
 */
using CameraUpdateListenerPtr = std::weak_ptr<ICameraUpdateListener>;

/**
 * @brief Camera with perspective projection.
 */
class PerspectiveCamera {
  public:
    /**
     * @brief Full constructor for PerspectiveCamera.
     * @param commonSettings Flyweight object containing the common camera
     * settings.
     * @param aspectRatio The camera's aspect ratio (width / height).
     * @param cameraPosition The initial camera's position.
     * @param viewDirection The initial camera's viewing direction.
     * @param fov_deg The field of view angle in [deg].
     * @param nearClippingPlaneDistance Distance of near clipping plane.
     * @param farClippingPlaneDistance Distance of far clipping plane.
     */
    PerspectiveCamera(
            const std::shared_ptr<CameraCommonSettings>& commonSettings,
            float aspectRatio, const glm::vec3& cameraPosition,
            const glm::vec3& viewDirection, float fov_deg,
            float nearClippingPlaneDistance, float farClippingPlaneDistance);

    /**
     * @brief Constructor for PerspectiveCamera with some default settings set.
     * @param commonSettings Flyweight object containing the common camera
     * settings.
     * @param aspectRatio The camera's aspect ratio (width / height).
     * @param cameraPosition The initial camera's position.
     * @param viewDirection The initial camera's viewing direction.
     */
    PerspectiveCamera(
            const std::shared_ptr<CameraCommonSettings>& commonSettings,
            float aspectRatio, const glm::vec3& cameraPosition,
            const glm::vec3& viewDirection);

    /**
     * @brief Constructor for PerspectiveCamera with some default settings set.
     * @param commonSettings Flyweight object containing the common camera
     * settings.
     * @param aspectRatio The camera's aspect ratio (width / height).
     * @param cameraPosition The initial camera's position.
     */
    PerspectiveCamera(
            const std::shared_ptr<CameraCommonSettings>& commonSettings,
            float aspectRatio, const glm::vec3& cameraPosition);

    /**
     * @brief Constructor for PerspectiveCamera with some most settings set.
     * @param commonSettings Flyweight object containing the common camera
     * settings.
     * @param aspectRatio The camera's aspect ratio (width / height).
     */
    PerspectiveCamera(
            const std::shared_ptr<CameraCommonSettings>& commonSettings,
            float aspectRatio);

    /*
     *
     */

    /**
     * @brief Gets the current camera's position.
     * @return The camera's current position.
     */
    const glm::vec3& getCameraPosition() const;

    /**
     * @brief Gets the current aspect ratio (width / height).
     * @return The current aspect ratio value.
     */
    float getAspectRatio() const;

    /**
     * @brief Gets current field of view angle.
     * @return The current field of view angle in [deg].
     */
    float getFieldOfViewAngle() const;

    /**
     * @brief Gets the distance to near clipping plane.
     * @return Distance to near clipping plane.
     */
    float getNearClippingPlaneDistance() const;

    /**
     * @brief Gets the distance to far clipping plane.
     * @return Distance to far clipping plane.
     */
    float getFarClippingPlaneDistance() const;

    /*
     *
     */

    /**
     * @brief Sets the aspect ratio (width / height).
     * @param width Width.
     * @param height Height.
     * @throw std::invalid_argument - Thrown when width or height <= 0.
     */
    void setAspectRatio(int width, int height);

    /**
     * @brief Sets the field of view value.
     * @param angle_deg New value in [deg]
     * @throw std::invalid_argument - Thrown when angle_deg is outside of
     * permissible values range.
     */
    void setFieldOfViewAngle(float angle_deg);

    /**
     * @brief Sets the near clipping plane distance.
     * @param distance The new distance value.
     * @throw std::invalid_argument - Thrown when distance is less than
     * permissible minimal value OR distance is greater than for far clipping
     * plane.
     */
    void setNearClippingPlaneDistance(float distance);

    /**
     * @brief Sets the far clipping plane distance.
     * @param distance The new distance value.
     * @throw std::invalid_argument - Thrown when distance is less than near
     * clipping plane distance.
     */
    void setFarClippingPlaneDistance(float distance);

    /*
     *
     */

    /**
     * @brief Registers listener for camera update event.
     * @param listener Listener to register.
     * @return ID number which can be used to unregister the listener.
     */
    int registerCameraUpdateListener(const CameraUpdateListenerPtr& listener);

    /**
     * @brief Unregisters listener with supplied ID.
     * @param listenerId The ID of listener to unregister.
     * @return true if the listener was found and unregistered, otherwise
     * returns false.
     */
    bool unregisterCameraUpdateListener(int listenerId);

    /**
     * @brief Updates the camera's configuration.
     * @param movementDirection Direction in which the camera should move.
     * @param horizontalRotationIncrement The change of camera's viewing
     * direction - horizontal component.
     * @param verticalRotationIncrement The change of camera's viewing
     * direction - vertical component.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void update(MovementDirection movementDirection,
            int horizontalRotationIncrement, int verticalRotationIncrement,
            float deltaT);

  private:
    CameraGeometry m_cameraGeometry;
    std::list<std::pair<int, CameraUpdateListenerPtr>> m_cameraUpdateListeners;
    int m_lastListenerId;
    float m_fov_deg;
    float m_aspectRatio;
    float m_nearClippingPlaneDistance;
    float m_farClippingPlaneDistance;

    /*
     *
     */

    /**
     * @brief Calculates the camera's projection matrix.
     * @return The camera's projection matrix.
     */
    glm::mat4 calculateProjectionMatrix() const;

    /*
     *
     */

    /**
     * @brief Raises camera update event if supplied argument is true.
     * @param cameraChanged Supply true to raise camera update event.
     */
    void notifyOnChange(bool cameraChanged);

    /**
     * @brief Notifies all camera update listeners.
     */
    void notifyCameraUpdateListeners();
};
