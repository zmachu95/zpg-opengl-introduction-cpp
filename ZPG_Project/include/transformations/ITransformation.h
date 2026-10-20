// ITransformation.h - Contains declaration of ITransformation interface.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <glm/fwd.hpp>

/**
 * @brief A wrapper for transformation matrices.
 */
class ITransformation {
  public:
    virtual ~ITransformation() = default;

    /**
     * @brief Gets the transformation matrix.
     * @return The transformation matrix.
     */
    virtual const glm::mat4& getMatrix() = 0;
};
