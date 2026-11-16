// ConstantTransformation.h - Contains declaration of ConstantTransformation
// class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <transformations/ITransformation.h>

/**
 * @brief An immutable transformation matrix.
 */
class ConstantTransformation : public ITransformation {
  public:
    /**
     * @brief Standard ConstantTransformation constructor.
     */
    ConstantTransformation(const glm::mat4& matrix);

    virtual ~ConstantTransformation() = default;

    /**
     * @brief Gets the transformation matrix.
     * @return The transformation matrix.
     */
    const glm::mat4& getMatrix() override;

  private:
    glm::mat4 m_matrix;
};
