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
    virtual ~ITransformation() {};

    /*
     *
     */

    /**
     * @brief Gets the transformation matrix.
     * @return The transformation matrix.
     */
    virtual glm::mat4 getMatrix() const = 0;
};
