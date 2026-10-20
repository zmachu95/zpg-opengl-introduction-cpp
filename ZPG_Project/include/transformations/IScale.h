// IScale.h - Contains declaration of IScale interface.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <transformations/ITransformation.h>

/**
 * @brief Interface for scale transformation matrix.
 */
class IScale : public ITransformation {
  public:
    virtual ~IScale() = default;

    /**
     * @brief Increments the current scale factors by supplied values.
     * @param dx X component of scale increment.
     * @param dy Y component of scale increment.
     * @param dz Z component of scale increment.
     */
    virtual void increment(const float dx, const float dy, const float dz) = 0;

    /**
     * @brief Sets scale to supplied factors.
     * @param x Scale factor in x direction.
     * @param y Scale factor in y direction.
     * @param z Scale factor in z direction.
     */
    virtual void setScaleTo(const float x, const float y, const float z) = 0;
};
