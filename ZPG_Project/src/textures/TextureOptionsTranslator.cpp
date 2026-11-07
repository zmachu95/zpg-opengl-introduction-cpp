// TextureOptionsTranslator.cpp - Contains definition of
// TextureOptionsTranslator class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#include "TextureOptionsTranslator.h"

#include <stdexcept>
#include <string>
#include <textures/ITexture.h>

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

using namespace std::string_literals;

GLint TextureOptionsTranslator::translateTextureWrapping(
        TextureWrapping wrapping) {
    switch (wrapping) {
        case TextureWrapping::REPEAT:
            return GL_REPEAT;
        case TextureWrapping::MIRRORED_REPEAT:
            return GL_MIRRORED_REPEAT;
        case TextureWrapping::CLAMP_TO_EDGE:
            return GL_CLAMP_TO_EDGE;
        default:
            throw std::invalid_argument("Option "s
                                        + std::to_string((int)wrapping)
                                        + " is not implemented!");
    }
}

GLint TextureOptionsTranslator::translateMagnifyFiltering(
        TextureMagnifyFiltering filtering) {
    switch (filtering) {
        case TextureMagnifyFiltering::NEAREST:
            return GL_NEAREST;
        case TextureMagnifyFiltering::LINEAR:
            return GL_LINEAR;
        default:
            throw std::invalid_argument("Option "s
                                        + std::to_string((int)filtering)
                                        + " is not implemented!");
    }
}

GLint TextureOptionsTranslator::translateMinifyFiltering(
        TextureMinifyFiltering filtering) {
    switch (filtering) {
        case TextureMinifyFiltering::NEAREST:
            return GL_NEAREST;
        case TextureMinifyFiltering::LINEAR:
            return GL_LINEAR;
        case TextureMinifyFiltering::NEAREST_WITH_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;
        case TextureMinifyFiltering::LINEAR_WITH_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;
        case TextureMinifyFiltering::NEAREST_WITH_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;
        case TextureMinifyFiltering::LINEAR_WITH_MIPMAP_LINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;
        default:
            throw std::invalid_argument("Option "s
                                        + std::to_string((int)filtering)
                                        + " is not implemented!");
    }
}

GLenum TextureOptionsTranslator::translateTexturingUnit(
        TexturingUnit unit) {
    switch (unit) {
        case TexturingUnit::UNIT0:
            return GL_TEXTURE0;
        case TexturingUnit::UNIT1:
            return GL_TEXTURE1;
        case TexturingUnit::UNIT2:
            return GL_TEXTURE2;
        case TexturingUnit::UNIT3:
            return GL_TEXTURE3;
        case TexturingUnit::UNIT4:
            return GL_TEXTURE4;
        case TexturingUnit::UNIT5:
            return GL_TEXTURE5;
        case TexturingUnit::UNIT6:
            return GL_TEXTURE6;
        case TexturingUnit::UNIT7:
            return GL_TEXTURE7;
        case TexturingUnit::UNIT8:
            return GL_TEXTURE8;
        case TexturingUnit::UNIT9:
            return GL_TEXTURE9;
        case TexturingUnit::UNIT10:
            return GL_TEXTURE10;
        case TexturingUnit::UNIT11:
            return GL_TEXTURE11;
        case TexturingUnit::UNIT12:
            return GL_TEXTURE12;
        case TexturingUnit::UNIT13:
            return GL_TEXTURE13;
        case TexturingUnit::UNIT14:
            return GL_TEXTURE14;
        case TexturingUnit::UNIT15:
            return GL_TEXTURE15;
        default:
            throw std::invalid_argument("Option "s + std::to_string((int)unit)
                                        + " is not implemented!");
    }
}
