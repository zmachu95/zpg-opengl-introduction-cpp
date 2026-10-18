// Translation.h - Contains declaration of Translation class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <transformations/SingleTransformationBase.h>

/**
 * @brief A translation transformation matrix.
 */
class Translation : public SingleTransformationBase {
  public:
    /**
     * @brief Standard Translation constructor.
     */
    Translation();

    /*
     *
     */

    /**
     * @brief Moves relative to current position.
     * @param dx X component of relative movement.
     * @param dy Y component of relative movement.
     * @param dz Z component of relative movement.
     */
    void move(const float dx, const float dy, const float dz);

    /**
     * @brief Performs translation to supplied coordinates.
     * @param x Target x coordinate.
     * @param y Target y coordinate.
     * @param z Target z coordinate.
     */
    void translateTo(const float x, const float y, const float z);

  private:
    float m_x;
    float m_y;
    float m_z;
};
