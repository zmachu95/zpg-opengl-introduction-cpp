// GroupedTransformation.cpp - Contains definition of GroupedTransformation
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#include <transformations/GroupedTransformation.h>
#include <transformations/ITransformation.h>
#include <transformations/Rotation.h>
#include <transformations/Scale.h>
#include <transformations/Translation.h>
#include <utility>

GroupedTransformation::GroupedTransformation()
    : ITransformation{}, m_transformations{} {}

glm::mat4 GroupedTransformation::getMatrix() const {
    glm::mat4 result{1.0f};

    for (const TransformationPtr& ptr : this->m_transformations) {
        const ITransformation& transformation = (*ptr);
        /* multiplication from left -> represents transformation relative to
         * something */
        result *= transformation.getMatrix();
    }

    return result;
}

RotationPtr GroupedTransformation::addNewRotation(
        float axisX, float axisY, float axisZ) {
    this->m_transformations.push_back(
            std::make_shared<Rotation>(axisX, axisY, axisZ));
    return std::static_pointer_cast<Rotation>(this->m_transformations.back());
}

ScalePtr GroupedTransformation::addNewScale() {
    this->m_transformations.push_back(std::make_shared<Scale>());
    return std::static_pointer_cast<Scale>(this->m_transformations.back());
}

TranslationPtr GroupedTransformation::addNewTranslation() {
    this->m_transformations.push_back(std::make_shared<Translation>());
    return std::static_pointer_cast<Translation>(
            this->m_transformations.back());
}

GroupedTransformationPtr GroupedTransformation::addNewGroup() {
    this->m_transformations.push_back(
            std::make_shared<GroupedTransformation>());
    return std::static_pointer_cast<GroupedTransformation>(
            this->m_transformations.back());
}

void GroupedTransformation::addReferenceToAnother(
        const TransformationPtr& transformation) {
    this->m_transformations.push_back(TransformationPtr{transformation});
}
