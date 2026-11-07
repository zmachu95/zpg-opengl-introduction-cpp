// TextureOptionsTranslator.h - Contains declaration of TextureOptionsTranslator
// class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <textures/ITexture.h>

using GLint = int;
using GLenum = unsigned int;

/**
 * @brief Translates custom enum values to OpenGL constants.
 */
class TextureOptionsTranslator {
  public:
    /**
     * @brief Translates texture wrapping options.
     * @param wrapping Texture wrapping option.
     * @return OpenGL GLint constant.
     * @throw std::invalid_argument - Thrown when insupported option is
     * supplied.
     */
    static GLint translateTextureWrapping(TextureWrapping wrapping);

    /**
     * @brief Translates texture magnify filtering options.
     * @param filtering Texture magnify filtering option.
     * @return OpenGL GLint constant.
     * @throw std::invalid_argument - Thrown when insupported option is
     * supplied.
     */
    static GLint translateMagnifyFiltering(TextureMagnifyFiltering filtering);

    /**
     * @brief Translates texture minify filtering options.
     * @param filtering Texture minify filtering option.
     * @return OpenGL GLint constant.
     * @throw std::invalid_argument - Thrown when insupported option is
     * supplied.
     */
    static GLint translateMinifyFiltering(TextureMinifyFiltering filtering);

    /**
     * @brief Translates texturing unit options.
     * @param unit Texturing unit option.
     * @return OpenGL GLenum constant.
     * @throw std::invalid_argument - Thrown when insupported option is
     * supplied.
     */
    static GLenum translateTexturingUnit(TexturingUnit unit);

  private:
    /**
     * @brief TextureOptionsTranslator default constructor.
     */
    TextureOptionsTranslator() = default;
};
