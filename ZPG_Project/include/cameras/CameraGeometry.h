// CameraGeometry.h - Contains declaration of CameraGeometry class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <memory>

enum class MovementDirection;
class CameraCommonSettings;

/**
 * @brief Provides implementation for camera movement and look.
 */
class CameraGeometry {
  public:
    /**
     * @brief Default constructor for CameraGeometry.
     * @param commonSettings Flyweight object containing the common camera
     * settings.
     * @param cameraPosition Initial camera position.
     * @param viewDirection Initial camera viewing direction.
     */
    CameraGeometry(const std::shared_ptr<CameraCommonSettings>& commonSettings,
            const glm::vec3& cameraPosition, const glm::vec3& viewDirection);

    /*
     *
     */

    /**
     * @brief Gets the current camera's position.
     * @return The camera's current position.
     */
    const glm::vec3& getCameraPosition() const;

    /**
     * @brief Calculates the camera's view matrix.
     * @return The camera's view matrix.
     */
    glm::mat4 calculateViewMatrix() const;

    /*
     *
     */

    /**
     * @brief Updates the camera's configuration and reports back whether any
     * changes were made.
     * @param movementDirection Direction in which the camera should move.
     * @param horizontalRotationIncrement The change of camera's viewing
     * direction - horizontal component.
     * @param verticalRotationIncrement The change of camera's viewing
     * direction - vertical component.
     * @param deltaT Time elapsed since the last drawn frame.
     * @return true if any changes were made to the configuration, otherwise
     * returns false.
     */
    bool update(MovementDirection movementDirection,
            int horizontalRotationIncrement, int verticalRotationIncrement,
            float deltaT);

  private:
    std::shared_ptr<CameraCommonSettings> m_commonSettings;
    glm::vec3 m_eye;
    float m_yawAngle_deg;
    float m_pitchAngle_deg;

    /*
     *
     */

    /**
     * @brief Gets the actual direction for forward movement.
     * @param currentViewVector The current viewing direction.
     * @return Non-normalized vector with forward movement direction.
     */
    glm::vec3 getForwardMovementDirection(
            const glm::vec3& currentViewVector) const;

    /**
     * @brief Gets the actual direction for sideways movement to the
     * right.
     * @param currentViewVector The current viewing direction.
     * @return Non-normalized vector with direction of sideways movement
     * to the right.
     */
    glm::vec3 getRightMovementDirection(
            const glm::vec3& currentViewVector) const;

    /**
     * @brief Converts MovementDirection enum value to a normalized movement
     * direction vector.
     * @param dir MovementDirection enum value.
     * @param currentViewVector The current viewing direction.
     * @return Normalized movement direction vector.
     */
    glm::vec3 convertMovementDirectionToVector(
            MovementDirection dir, const glm::vec3& currentViewVector) const;

    /**
     * @brief Converts raw rotation increment value to angle increment.
     * @param rotationIncrement Raw rotation increment.
     * @return Angle increment in [deg].
     */
    float convertRotationIncrementToAngleIncrement(int rotationIncrement) const;

    /**
     * @brief Converts current viewing direction vector to yaw angle.
     * @param viewDirection The current viewing direction vector.
     * @return Yaw angle in [deg]. Values are clamped between [0, 360] deg.
     */
    float convertViewDirectionToYawAngle(const glm::vec3& viewDirection) const;

    /**
     * @brief Converts current viewing direction vector to pitch angle.
     * @param viewDirection The current viewing direction vector.
     * @return Pitch angle in [deg]. Values are clamped between [-90, 90] deg.
     */
    float convertViewDirectionToPitchAngle(
            const glm::vec3& viewDirection) const;

    /**
     * @brief Calculates target point using current camera configuration.
     * @return The target point coordinates.
     */
    glm::vec3 calculateTarget() const;

    /*
     *
     */

    /**
     * @brief Updates the current camera looking direction.
     * @param horizontalRotationIncrement The change of camera's viewing
     * direction - horizontal component.
     * @param verticalRotationIncrement The change of camera's viewing
     * direction - vertical component.
     * @param deltaT Time elapsed since the last drawn frame.
     * @return true if the looking direction changed, otherwise returns
     * false.
     */
    bool updateLookingDirection(int horizontalRotationIncrement,
            int verticalRotationIncrement, float deltaT);

    /**
     * @brief Updates the camera's position.
     * @param movementDirection Direction in which the camera should move.
     * @param currentViewVector The current viewing direction.
     * @param deltaT Time elapsed since the last drawn frame.
     * @return true if camera's position changed, otherwise returns false.
     */
    bool updatePosition(MovementDirection movementDirection,
            const glm::vec3& currentViewVector, float deltaT);
};
