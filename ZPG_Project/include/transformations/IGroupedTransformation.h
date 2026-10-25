// IGroupedTransformation.h - Contains declaration of IGroupedTransformation
// interface.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>
#include <transformations/ITransformation.h>

class IGroupedTransformation;
class IRotation;
class IScale;
class ITranslation;

/**
 * @brief Pointer for IRotation object.
 */
using RotationPtr = std::shared_ptr<IRotation>;

/**
 * @brief Pointer for IScale object.
 */
using ScalePtr = std::shared_ptr<IScale>;

/**
 * @brief Pointer for ITranslation object.
 */
using TranslationPtr = std::shared_ptr<ITranslation>;

/**
 * @brief Pointer for IGroupedTransformation object.
 */
using GroupedTransformationPtr = std::shared_ptr<IGroupedTransformation>;

/**
 * @brief Pointer for ITransformation object.
 */
using TransformationPtr = std::shared_ptr<ITransformation>;

/**
 * @brief Interface for a transformations group.
 */
class IGroupedTransformation : public ITransformation {
  public:
    virtual ~IGroupedTransformation() = default;

    /**
     * @brief Adds new rotation matrix to the group.
     * @param axisX X component of axis unit vector.
     * @param axisY Y component of axis unit vector.
     * @param axisZ Z component of axis unit vector.
     * @return Shared pointer to the new rotation matrix.
     */
    virtual RotationPtr addNewRotation(
            float axisX, float axisY, float axisZ) = 0;

    /**
     * @brief Adds new scale matrix to the group.
     * @return Shared pointer to the new scale matrix.
     */
    virtual ScalePtr addNewScale() = 0;

    /**
     * @brief Adds new translation matrix to the group.
     * @return Shared pointer to the new translation matrix.
     */
    virtual TranslationPtr addNewTranslation() = 0;

    /**
     * @brief Adds new transformations group to the group.
     * @return Shared pointer to the new transformation group.
     */
    virtual GroupedTransformationPtr addNewGroup() = 0;

    /**
     * @brief Adds reference to another transformation matrix to this group.
     * @param transformation Reference to shared pointer of transformation to
     * add.
     */
    virtual void addReferenceToAnother(
            const TransformationPtr& transformation) = 0;
};
