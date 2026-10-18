// Rotation.h - Contains declaration of Rotation class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <transformations/SingleTransformationBase.h>

/**
 * @brief A rotation transformation matrix.
 */
class Rotation : public SingleTransformationBase {
  public:
    /**
     * @brief Standard Rotation constructor.
     * @param axisX X component of axis unit vector.
     * @param axisY Y component of axis unit vector.
     * @param axisZ Z component of axis unit vector.
     */
    Rotation(const float axisX, const float axisY, const float axisZ);

    /*
     *
     */

    /**
     * @brief Increments the rotation by specified angle increment in [deg].
     * @param angle_increment_deg Rotation angle increment in [deg].
     */
    void incrementAngle(const float angle_increment_deg);

    /**
     * @brief Sets the rotation to specified angle in [deg].
     * @param angle_deg Rotation angle in [deg].
     */
    void setAngle(const float angle_deg);

  private:
    float m_angle_deg;

    float m_axisX;
    float m_axisY;
    float m_axisZ;
};
