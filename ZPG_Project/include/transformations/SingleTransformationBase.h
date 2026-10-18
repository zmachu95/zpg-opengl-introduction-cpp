// SingleTransformationBase.h - Contains declaration of SingleTransformationBase
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <transformations/ITransformation.h>

/**
 * @brief A base class for single transformations.
 */
class SingleTransformationBase : public ITransformation {
  public:
    /**
     * @brief Gets the transformation matrix.
     * @return The transformation matrix.
     */
    virtual glm::mat4 getMatrix() const;

  protected:
    /**
     * @brief Default SingleTransformationBase constructor.
     */
    SingleTransformationBase();

    /*
     *
     */

    /**
     * @brief Performs rotation about specific angle by specified angle in
     * [deg].
     * @param angle_deg The rotation angle in [deg].
     * @param axisX X component of axis unit vector.
     * @param axisY Y component of axis unit vector.
     * @param axisZ Z component of axis unit vector.
     */
    void rotateAboutAxis(
            float angle_deg, float axisX, float axisY, float axisZ);

    /**
     * @brief Performs scaling.
     * @param x Scale factor in x direction.
     * @param y Scale factor in y direction.
     * @param z Scale factor in z direction.
     */
    void scale(float x, float y, float z);

    /**
     * @brief Performs translation to supplied coordinates.
     * @param x Target x coordinate.
     * @param y Target y coordinate.
     * @param z Target z coordinate.
     */
    void translateTo(float x, float y, float z);

  private:
    static const glm::mat4 s_identityMatrix;

    glm::mat4 m_matrix;
};
