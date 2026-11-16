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

    ~GroupedTransformation() override = default;

    /*
     *
     */

    /**
     * @brief Gets the transformation matrix.
     * @return The transformation matrix.
     */
    const glm::mat4& getMatrix() override;

    /*
     *
     */

    /**
     * @brief Adds constant transformation matrix to the group.
     * @param matrix Matrix representing the constant transformation.
     */
    void addConstant(const glm::mat4& matrix) override;

    /**
     * @brief Adds new rotation matrix to the group.
     * @param axisX X component of axis unit vector.
     * @param axisY Y component of axis unit vector.
     * @param axisZ Z component of axis unit vector.
     * @return Shared pointer to the new rotation matrix.
     */
    RotationPtr addNewRotation(float axisX, float axisY, float axisZ) override;

    /**
     * @brief Adds new scale matrix to the group.
     * @return Shared pointer to the new scale matrix.
     */
    ScalePtr addNewScale() override;

    /**
     * @brief Adds new translation matrix to the group.
     * @return Shared pointer to the new translation matrix.
     */
    TranslationPtr addNewTranslation() override;

    /**
     * @brief Adds new transformations group to the group.
     * @return Shared pointer to the new transformation group.
     */
    GroupedTransformationPtr addNewGroup() override;

    /**
     * @brief Adds reference to another transformation matrix to this group.
     * @param transformation Reference to shared pointer of transformation to
     * add.
     */
    void addReferenceToAnother(
            const TransformationPtr& transformation) override;

    /**
     * @brief Registers listener for transformation change event.
     * @param listener Listener to register.
     */
    void registerTransformationChangeListener(
            const TransformationChangeListenerPtr& listener) override;

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
    void handleTransformationChange() override;
};
