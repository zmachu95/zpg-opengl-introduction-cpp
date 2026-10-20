// IRotation.h - Contains declaration of IRotation interface.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <transformations/ITransformation.h>

/**
 * @brief Interface for rotation transformation matrix.
 */
class IRotation : public ITransformation {
  public:
    virtual ~IRotation() = default;

    /**
     * @brief Increments the rotation by specified angle increment in [deg].
     * @param angle_increment_deg Rotation angle increment in [deg].
     */
    virtual void incrementAngle(const float angle_increment_deg) = 0;

    /**
     * @brief Sets the rotation to specified angle in [deg].
     * @param angle_deg Rotation angle in [deg].
     */
    virtual void setAngle(const float angle_deg) = 0;
};
