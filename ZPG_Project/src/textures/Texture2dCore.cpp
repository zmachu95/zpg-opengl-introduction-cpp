// Texture2dCore.cpp - Contains definition of Texture2dCore class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#include "Texture2dCore.h"

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include "ImageData.h"
#include "TextureOptionsTranslator.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <textures/ITexture.h>
#include <utility>

using namespace std::string_literals;

Texture2dCore::Texture2dCore(
        GLuint textureId)
    : m_textureId{textureId} {
    std::cout << "Created 2D texture with ID " << textureId << ".\n ";
}

Texture2dCore::Texture2dCore(
        Texture2dCore&& other) noexcept
    : m_textureId{std::exchange(other.m_textureId, 0)} {}

Texture2dCore::~Texture2dCore() { this->deleteTexture(); }

Texture2dCore& Texture2dCore::operator=(
        Texture2dCore&& other) noexcept {
    if (this != &other) {
        this->deleteTexture();

        this->m_textureId = std::exchange(other.m_textureId, 0);
    }

    return *this;
}

Texture2dCore Texture2dCore::fromFile(
        const std::string& textureFile, TextureWrapping horizontalWrapping,
        TextureWrapping verticalWrapping,
        TextureMinifyFiltering minifyFiltering,
        TextureMagnifyFiltering magnifyFiltering) {
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // set the texture wrapping / filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            TextureOptionsTranslator::translateTextureWrapping(
                    horizontalWrapping));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
            TextureOptionsTranslator::translateTextureWrapping(
                    verticalWrapping));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            TextureOptionsTranslator::translateMinifyFiltering(
                    minifyFiltering));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            TextureOptionsTranslator::translateMagnifyFiltering(
                    magnifyFiltering));

    // load and generate the texture
    ImageData imageData = ImageData::fromFile(textureFile, true);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageData.getWidth(),
            imageData.getHeight(), 0,
            translateChannelsCount(imageData.getChannelsCount()),
            GL_UNSIGNED_BYTE, imageData.getData());
    glGenerateMipmap(GL_TEXTURE_2D);

    /* following line is needed to prevent texture leaks into GL_TEXTURE0 */
    glBindTexture(GL_TEXTURE_2D, 0);
    return Texture2dCore{textureId};
}

GLuint Texture2dCore::getId() const { return this->m_textureId; }

GLenum Texture2dCore::getTextureTarget() const { return GL_TEXTURE_2D; }

void Texture2dCore::deleteTexture() {
    if (this->m_textureId != 0) {
        std::cout << "Deleting 2D texture with ID " << this->m_textureId
                  << ".\n";
        glDeleteTextures(1, &this->m_textureId);
        this->m_textureId = 0;
    }
}

GLint Texture2dCore::translateChannelsCount(
        int channelsCount) {
    switch (channelsCount) {
        case 3:
            return GL_RGB;
        case 4:
            return GL_RGBA;
        default:
            throw std::invalid_argument("Option "s
                                        + std::to_string((int)channelsCount)
                                        + " is not implemented!");
    }
}
