// GroupedTransformationFactory.cpp - Contains definition of
// GroupedTransformationFactory class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "GroupedTransformation.h"
#include <memory>
#include <transformations/GroupedTransformationFactory.h>
#include <transformations/IGroupedTransformation.h>

GroupedTransformationPtr
GroupedTransformationFactory::createGroupedTransformation() {
    return std::make_shared<GroupedTransformation>();
}