// Scale.h - Contains declaration of Scale class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <transformations/SingleTransformationBase.h>

/**
 * @brief A scale transformation matrix.
 */
class Scale : public SingleTransformationBase {
  public:
    Scale();

    /*
     *
     */

    /**
     * @brief Increments the current scale factors by supplied values.
     * @param dx X component of scale increment.
     * @param dy Y component of scale increment.
     * @param dz Z component of scale increment.
     */
    void increment(const float dx, const float dy, const float dz);

    /**
     * @brief Sets scale to supplied factors.
     * @param x Scale factor in x direction.
     * @param y Scale factor in y direction.
     * @param z Scale factor in z direction.
     */
    void setScaleTo(const float x, const float y, const float z);

  private:
    float m_x;
    float m_y;
    float m_z;
};
