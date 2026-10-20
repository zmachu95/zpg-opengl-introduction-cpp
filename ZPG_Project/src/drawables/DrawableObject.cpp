// DrawableObject.cpp - Contains definition of DrawableObject class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <drawables/DrawableObject.h>
#include <drawables/Model.h>
#include <memory>
#include <shaders/ShaderProgram.h>
#include <transformations/GroupedTransformation.h>

void DrawableObject::draw(
        ShaderProgram& shaderProgram) {
    this->m_model->draw(shaderProgram, this->m_transformation->getMatrix());
}

GroupedTransformationPtr DrawableObject::getTransformation() {
    return this->m_transformation;
}

DrawableObject::DrawableObject(
        const ModelPtr& model)
    : m_transformation{std::make_shared<GroupedTransformation>()},
      m_model{model} {}
