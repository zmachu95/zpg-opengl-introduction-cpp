// Texture2D.cpp - Contains definition of Texture2D class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#include "Texture2D.h"
#include "Texture2dCore.h"
#include "TextureOptionsTranslator.h"
#include <textures/ITexture.h>

Texture2D::Texture2D(
        const Texture2dPtr& texture, TexturingUnit unit)
    : m_texture{texture}, m_unit{unit} {}

GLuint Texture2D::getId() const { return this->m_texture->getId(); }

GLenum Texture2D::getTexturingUnit() const {
    return TextureOptionsTranslator::translateTexturingUnit(this->m_unit);
}

GLuint Texture2D::getTexturingUnitId() const { return (GLuint)this->m_unit; }

GLenum Texture2D::getTextureTarget() const {
    return this->m_texture->getTextureTarget();
}
