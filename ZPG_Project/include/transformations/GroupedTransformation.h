// GroupedTransformation.h - Contains declaration of GroupedTransformation
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <glm/fwd.hpp>
#include <memory>
#include <transformations/ITransformation.h>
#include <vector>

class GroupedTransformation; // declaration is needed here for correct aliasing
                             // below
class Rotation;
class Scale;
class Translation;

using RotationPtr = std::shared_ptr<Rotation>;
using ScalePtr = std::shared_ptr<Scale>;
using TranslationPtr = std::shared_ptr<Translation>;
using GroupedTransformationPtr = std::shared_ptr<GroupedTransformation>;
using TransformationPtr = std::shared_ptr<ITransformation>;

/**
 * @brief Groups multiple transformations into a single object.
 */
class GroupedTransformation : public ITransformation {
  public:
    /**
     * @brief Standard GroupedTransformation constructor.
     */
    GroupedTransformation();

    /*
     *
     */

    /**
     * @brief Gets the transformation matrix.
     * @return The transformation matrix.
     */
    virtual glm::mat4 getMatrix() const;

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
    RotationPtr addNewRotation(float axisX, float axisY, float axisZ);

    /**
     * @brief Adds new scale matrix to the group.
     * @return Shared pointer to the new scale matrix.
     */
    ScalePtr addNewScale();

    /**
     * @brief Adds new translation matrix to the group.
     * @return Shared pointer to the new translation matrix.
     */
    TranslationPtr addNewTranslation();

    /**
     * @brief Adds new transformations group to the group.
     * @return Shared pointer to the new transformation group.
     */
    GroupedTransformationPtr addNewGroup();

    /**
     * @brief Adds reference to another transformation matrix to this group.
     * @param transformation Reference to shared pointer of transformation to
     * add.
     */
    void addReferenceToAnother(const TransformationPtr& transformation);

  private:
    std::vector<TransformationPtr> m_transformations;
};
