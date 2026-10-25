// Translation.h - Contains declaration of Translation class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "ITransformationChangeListenable.h"
#include "TransformationChangePublisher.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <transformations/ITranslation.h>

/**
 * @brief A translation transformation matrix.
 */
class Translation : public ITranslation,
                    public ITransformationChangeListenable {
  public:
    /**
     * @brief Standard Translation constructor.
     */
    Translation();

    virtual ~Translation() = default;

    /*
     *
     */

    /**
     * @brief Gets the transformation matrix.
     * @return The transformation matrix.
     */
    virtual const glm::mat4& getMatrix();

    /*
     *
     */

    /**
     * @brief Registers listener for transformation change event.
     * @param listener Listener to register.
     */
    virtual void registerTransformationChangeListener(
            const TransformationChangeListenerPtr& listener);

    /**
     * @brief Moves relative to current position.
     * @param dx X component of relative movement.
     * @param dy Y component of relative movement.
     * @param dz Z component of relative movement.
     */
    virtual void move(const float dx, const float dy, const float dz);

    /**
     * @brief Performs translation to supplied coordinates.
     * @param x Target x coordinate.
     * @param y Target y coordinate.
     * @param z Target z coordinate.
     */
    virtual void translateTo(const float x, const float y, const float z);

  private:
    float m_x;
    float m_y;
    float m_z;
    glm::mat4 m_matrix;
    TransformationChangePublisher m_publisher;

    /**
     * @brief Calculates and stores new translation matrix based on current
     * configuration.
     */
    void calculateTranslationMatrix();

    /**
     * @brief Notifies all listeners that the translation matrix changed.
     */
    void notifyListeners();
};
