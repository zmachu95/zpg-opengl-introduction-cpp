// GroupedTransformation.cpp - Contains definition of GroupedTransformation
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "GroupedTransformation.h"
#include "ITransformationChangeListenable.h"
#include "Rotation.h"
#include "Scale.h"
#include "TransformationChangePublisher.h"
#include "Translation.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#include <transformations/IGroupedTransformation.h>
#include <transformations/ITransformation.h>
#include <utility>

GroupedTransformation::GroupedTransformation()
    : m_isDirty{true}, m_transformations{}, m_cachedMatrix{1.0f},
      m_publisher{} {}

const glm::mat4& GroupedTransformation::getMatrix() {
    if (this->m_isDirty) {
        this->calculateTransformationMatrix();
        this->m_isDirty = false;
    }

    return this->m_cachedMatrix;
}

RotationPtr GroupedTransformation::addNewRotation(
        float axisX, float axisY, float axisZ) {
    std::shared_ptr<Rotation> newRotation =
            std::make_shared<Rotation>(axisX, axisY, axisZ);
    newRotation->registerTransformationChangeListener(this->weak_from_this());
    this->m_transformations.push_back(newRotation);
    return newRotation;
}

ScalePtr GroupedTransformation::addNewScale() {
    std::shared_ptr<Scale> newScale = std::make_shared<Scale>();
    newScale->registerTransformationChangeListener(this->weak_from_this());
    this->m_transformations.push_back(newScale);
    return newScale;
}

TranslationPtr GroupedTransformation::addNewTranslation() {
    std::shared_ptr<Translation> newTranslation =
            std::make_shared<Translation>();
    newTranslation->registerTransformationChangeListener(
            this->weak_from_this());
    this->m_transformations.push_back(newTranslation);
    return newTranslation;
}

GroupedTransformationPtr GroupedTransformation::addNewGroup() {
    std::shared_ptr<GroupedTransformation> newGroup =
            std::make_shared<GroupedTransformation>();
    newGroup->registerTransformationChangeListener(this->weak_from_this());
    this->m_transformations.push_back(newGroup);
    return newGroup;
}

void GroupedTransformation::addReferenceToAnother(
        const TransformationPtr& transformation) {
    std::shared_ptr<ITransformationChangeListenable> transformationPublisher =
            std::dynamic_pointer_cast<ITransformationChangeListenable>(
                    transformation);
    transformationPublisher->registerTransformationChangeListener(
            this->weak_from_this());
    this->m_transformations.push_back(transformation);
}

void GroupedTransformation::registerTransformationChangeListener(
        const TransformationChangeListenerPtr& listener) {
    this->m_publisher.registerTransformationChangeListener(listener);
}

void GroupedTransformation::calculateTransformationMatrix() {
    glm::mat4 result{1.0f};

    for (TransformationPtr& ptr : this->m_transformations) {
        ITransformation& transformation = (*ptr);
        /* multiplication from left -> represents transformation relative to
         * something */
        result *= transformation.getMatrix();
    }

    this->m_cachedMatrix = std::move(result);
}

void GroupedTransformation::notifyListeners() {
    this->m_publisher.notifyListeners();
}

void GroupedTransformation::handleTransformationChange() {
    this->m_isDirty = true;
    this->notifyListeners();
}
