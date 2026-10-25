// Rotation.h - Contains declaration of Rotation class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "TransformationChangePublisher.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <transformations/IRotation.h>

#include "ITransformationChangeListenable.h"

/**
 * @brief A rotation transformation matrix.
 */
class Rotation : public IRotation, public ITransformationChangeListenable {
  public:
    /**
     * @brief Standard Rotation constructor.
     * @param axisX X component of axis unit vector.
     * @param axisY Y component of axis unit vector.
     * @param axisZ Z component of axis unit vector.
     */
    Rotation(const float axisX, const float axisY, const float axisZ);

    virtual ~Rotation() = default;

    /*
     *
     */

    /**
     * @brief Gets the transformation matrix.
     * @return The transformation matrix.
     */
    virtual const glm::mat4& getMatrix();

    /*
     *
     */

    /**
     * @brief Registers listener for transformation change event.
     * @param listener Listener to register.
     */
    virtual void registerTransformationChangeListener(
            const TransformationChangeListenerPtr& listener);

    /**
     * @brief Increments the rotation by specified angle increment in [deg].
     * @param angle_increment_deg Rotation angle increment in [deg].
     */
    virtual void incrementAngle(const float angle_increment_deg);

    /**
     * @brief Sets the rotation to specified angle in [deg].
     * @param angle_deg Rotation angle in [deg].
     */
    virtual void setAngle(const float angle_deg);

  private:
    float m_angle_deg;
    float m_axisX;
    float m_axisY;
    float m_axisZ;
    glm::mat4 m_matrix;
    TransformationChangePublisher m_publisher;

    /**
     * @brief Calculates and stores new rotation matrix based on current
     * configuration.
     */
    void calculateRotationMatrix();

    /**
     * @brief Notifies all listeners that the rotation matrix changed.
     */
    void notifyListeners();
};
