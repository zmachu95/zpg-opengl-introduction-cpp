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
#include <utility>

DrawableObject::DrawableObject(
        const ModelPtr& model, Byte id)
    : m_id{id}, m_model{model},
      m_transformation{
              GroupedTransformationFactory::createGroupedTransformation()},
      m_textures{} {}

DrawableObject::DrawableObject(
        DrawableObject&& other) noexcept
    : m_id{std::exchange(other.m_id, 0)}, m_model{std::move(other.m_model)},
      m_transformation{std::move(other.m_transformation)},
      m_textures{std::move(other.m_textures)} {}

DrawableObject& DrawableObject::addTexture(
        const TexturePtr& texture) {
    this->m_textures.push_back(texture);
    return *this;
}

DrawableObject DrawableObject::cloneWithoutTransformations(
        Byte newId) const {
    DrawableObject clone = DrawableObject{this->m_model, newId};
    clone.m_textures = this->m_textures;
    return clone;
}

void DrawableObject::draw(
        ShaderProgram& shaderProgram) {
    this->m_model->draw(shaderProgram, this->m_transformation->getMatrix(),
            this->m_textures);
}

Byte DrawableObject::getId() const { return this->m_id; }

GroupedTransformationPtr DrawableObject::getTransformation() {
    return this->m_transformation;
}
