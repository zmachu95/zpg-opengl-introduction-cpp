// SkyboxTexture.cpp - Contains definition of SkyboxTexture class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#include "SkyBoxTexture.h"

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include <array>
#include <textures/ITexture.h>

#include "ImageData.h"
#include <iostream>
#include <string>
#include <utility>

SkyboxTexture::SkyboxTexture(
        GLuint textureId)
    : m_textureId{textureId} {
    std::cout << "Created skybox texture with ID " << textureId << ".\n ";
}

SkyboxTexture::SkyboxTexture(
        SkyboxTexture&& other) noexcept
    : m_textureId{std::exchange(other.m_textureId, 0)} {}

SkyboxTexture::~SkyboxTexture() { this->deleteTexture(); }

SkyboxTexture& SkyboxTexture::operator=(
        SkyboxTexture&& other) noexcept {
    if (this != &other) {
        this->deleteTexture();

        this->m_textureId = std::exchange(other.m_textureId, 0);
    }

    return *this;
}

SkyboxTexture SkyboxTexture::fromFiles(
        const std::array<std::string, 6>& textureFiles) {
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    // load sequentially all 6 faces of sky box
    for (unsigned int i = 0; i < textureFiles.size(); i++) {
        ImageData imageData = ImageData::fromFile(textureFiles[i], false);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                imageData.getWidth(), imageData.getHeight(), 0, GL_RGB,
                GL_UNSIGNED_BYTE, imageData.getData());
    }

    // set the texture wrapping / filtering options
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    /* following line is needed to prevent texture leaks into GL_TEXTURE0 */
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    return SkyboxTexture{textureId};
}

GLuint SkyboxTexture::getId() const { return this->m_textureId; }

GLenum SkyboxTexture::getTexturingUnit() const { return GL_TEXTURE0; }

GLuint SkyboxTexture::getTexturingUnitId() const { return 0; }

GLenum SkyboxTexture::getTextureTarget() const { return GL_TEXTURE_CUBE_MAP; }

void SkyboxTexture::deleteTexture() {
    if (this->m_textureId != 0) {
        std::cout << "Deleting skybox texture with ID " << this->m_textureId
                  << ".\n";
        glDeleteTextures(1, &this->m_textureId);
        this->m_textureId = 0;
    }
}
