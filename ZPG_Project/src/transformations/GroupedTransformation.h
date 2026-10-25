// GroupedTransformation.h - Contains declaration of GroupedTransformation
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "ITransformationChangeListenable.h"
#include "ITransformationChangedListener.h"
#include "TransformationChangePublisher.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#include <transformations/IGroupedTransformation.h>
#include <vector>

/**
 * @brief Groups multiple transformations into a single object.
 */
class GroupedTransformation
    : public std::enable_shared_from_this<GroupedTransformation>,
      public IGroupedTransformation,
      public ITransformationChangedListener,
      public ITransformationChangeListenable {
  public:
    /**
     * @brief Standard GroupedTransformation constructor.
     */
    GroupedTransformation();

    virtual ~GroupedTransformation() = default;

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
     * @brief Adds new rotation matrix to the group.
     * @param axisX X component of axis unit vector.
     * @param axisY Y component of axis unit vector.
     * @param axisZ Z component of axis unit vector.
     * @return Shared pointer to the new rotation matrix.
     */
    virtual RotationPtr addNewRotation(float axisX, float axisY, float axisZ);

    /**
     * @brief Adds new scale matrix to the group.
     * @return Shared pointer to the new scale matrix.
     */
    virtual ScalePtr addNewScale();

    /**
     * @brief Adds new translation matrix to the group.
     * @return Shared pointer to the new translation matrix.
     */
    virtual TranslationPtr addNewTranslation();

    /**
     * @brief Adds new transformations group to the group.
     * @return Shared pointer to the new transformation group.
     */
    virtual GroupedTransformationPtr addNewGroup();

    /**
     * @brief Adds reference to another transformation matrix to this group.
     * @param transformation Reference to shared pointer of transformation to
     * add.
     */
    virtual void addReferenceToAnother(const TransformationPtr& transformation);

    /**
     * @brief Registers listener for transformation change event.
     * @param listener Listener to register.
     */
    virtual void registerTransformationChangeListener(
            const TransformationChangeListenerPtr& listener);

  private:
    bool m_isDirty;
    std::vector<TransformationPtr> m_transformations;
    glm::mat4 m_cachedMatrix;
    TransformationChangePublisher m_publisher;

    /**
     * @brief Calculates and stores new transformation matrix based on current
     * children configuration.
     */
    void calculateTransformationMatrix();

    /**
     * @brief Notifies all listeners that the rotation matrix changed.
     */
    void notifyListeners();

    /**
     * @brief Handles the signal that atleast one underlying transformation
     * matrix has changed.
     */
    virtual void handleTransformationChange();
};
