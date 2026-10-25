// DrawableObject.cpp - Contains definition of DrawableObject class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "Model.h"
#include <drawables/DrawableObject.h>
#include <memory>
#include <shaders/ShaderProgram.h>
#include <transformations/GroupedTransformationFactory.h>
#include <transformations/IGroupedTransformation.h>

void DrawableObject::draw(
        ShaderProgram& shaderProgram) {
    this->m_model->draw(shaderProgram, this->m_transformation->getMatrix());
}

GroupedTransformationPtr DrawableObject::getTransformation() {
    return this->m_transformation;
}

DrawableObject::DrawableObject(
        const ModelPtr& model)
    : m_transformation{
              GroupedTransformationFactory::createGroupedTransformation()},
      m_model{model} {}
