// ITranslation.h - Contains declaration of ITranslation interface.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <transformations/ITransformation.h>

/**
 * @brief Interface for translation transformation matrix.
 */
class ITranslation : public ITransformation {
  public:
    virtual ~ITranslation() = default;

    /**
     * @brief Moves relative to current position.
     * @param dx X component of relative movement.
     * @param dy Y component of relative movement.
     * @param dz Z component of relative movement.
     */
    virtual void move(const float dx, const float dy, const float dz) = 0;

    /**
     * @brief Performs translation to supplied coordinates.
     * @param x Target x coordinate.
     * @param y Target y coordinate.
     * @param z Target z coordinate.
     */
    virtual void translateTo(const float x, const float y, const float z) = 0;
};
