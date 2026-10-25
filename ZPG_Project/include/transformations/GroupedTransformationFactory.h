// GroupedTransformationFactory.h - Contains declaration of
// GroupedTransformationFactory class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>

class IGroupedTransformation;

/**
 * @brief Pointer for IGroupedTransformation object.
 */
using GroupedTransformationPtr = std::shared_ptr<IGroupedTransformation>;

/**
 * @brief Creates IGroupedTransformation transformations.
 */
class GroupedTransformationFactory {
  public:
    /**
     * @brief Creates new IGroupedTransformation object.
     * @return New IGroupedTransformation object.
     */
    static GroupedTransformationPtr createGroupedTransformation();

  private:
    /**
     * @brief Standard GroupedTransformationFactory constructor.
     */
    GroupedTransformationFactory() = default;
};