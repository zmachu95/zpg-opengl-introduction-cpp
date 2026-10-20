// Scale.h - Contains declaration of Scale class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <transformations/IScale.h>
#include <transformations/ITransformationChangeListenable.h>
#include <transformations/TransformationChangePublisher.h>

/**
 * @brief A scale transformation matrix.
 */
class Scale : public IScale, public ITransformationChangeListenable {
  public:
    /**
     * @brief Standard Scale constructor.
     */
    Scale();

    virtual ~Scale() = default;

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
     * @brief Increments the current scale factors by supplied values.
     * @param dx X component of scale increment.
     * @param dy Y component of scale increment.
     * @param dz Z component of scale increment.
     */
    virtual void increment(const float dx, const float dy, const float dz);

    /**
     * @brief Sets scale to supplied factors.
     * @param x Scale factor in x direction.
     * @param y Scale factor in y direction.
     * @param z Scale factor in z direction.
     */
    virtual void setScaleTo(const float x, const float y, const float z);

  private:
    float m_x;
    float m_y;
    float m_z;
    glm::mat4 m_matrix;
    TransformationChangePublisher m_publisher;

    /**
     * @brief Calculates and stores new scale matrix based on current
     * configuration.
     */
    void calculateScaleMatrix();

    /**
     * @brief Notifies all listeners that the scale matrix changed.
     */
    void notifyListeners();
};
