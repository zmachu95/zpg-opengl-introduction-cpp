// DrawableObject.cpp - Contains definition of DrawableObject class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "Model.h"
#include <drawables/DrawableObject.h>
#include <memory>
#include <shaders/ShaderProgram.h>
#include <textures/ITexture.h>
#include <transformations/GroupedTransformationFactory.h>
#include <transformations/IGroupedTransformation.h>

void DrawableObject::draw(
        ShaderProgram& shaderProgram) {
    this->m_model->draw(shaderProgram, this->m_transformation->getMatrix(),
            this->m_textures);
}

GroupedTransformationPtr DrawableObject::getTransformation() {
    return this->m_transformation;
}

DrawableObject::DrawableObject(
        const ModelPtr& model)
    : m_transformation{
              GroupedTransformationFactory::createGroupedTransformation()},
      m_model{model} {}

DrawableObject& DrawableObject::addTexture(
        const TexturePtr& texture) {
    this->m_textures.push_back(texture);
    return *this;
}
