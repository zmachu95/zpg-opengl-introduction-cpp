// Texture2dCore.h - Contains declaration of Texture2dCore class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <string>

enum class TextureWrapping;
enum class TextureMinifyFiltering;
enum class TextureMagnifyFiltering;

using GLenum = unsigned int;
using GLuint = unsigned int;
using GLint = int;

/**
 * @brief A 2D texture bound into OpenGL.
 */
class Texture2dCore {
  public:
    /**
     * @brief Texture2dCore copy constructor. Deliberately deleted to prevent
     * OpenGL from accidentally releasing the texture data.
     */
    Texture2dCore(const Texture2dCore& other) = delete;

    /**
     * @brief Texture2dCore move constructor.
     * @param other Source texture to be moved.
     */
    Texture2dCore(Texture2dCore&& other) noexcept;

    ~Texture2dCore();

    /*
     *
     */

    /**
     * @brief Texture2dCore copy-by-reference operator. Deliberately deleted to
     * prevent OpenGL from accidentally releasing the texture data.
     */
    Texture2dCore& operator=(const Texture2dCore& other) = delete;

    /**
     * @brief Texture2dCore move operator.
     * @param other Source texture to be moved.
     * @return The moved texture.
     */
    Texture2dCore& operator=(Texture2dCore&& other) noexcept;

    /*
     *
     */

    /**
     * @brief Creates and binds new texture using data from file.
     * @param textureFileFullPath Full path to file with an image.
     * @param horizontalWrapping Texture wrapping option to use in horizontal
     * direction.
     * @param verticalWrapping Texture wrapping option to use in vertical
     * direction.
     * @param minifyFiltering Texture filtering option to use when minifying.
     * @param magnifyFiltering Texture filtering option to use when magnifying.
     * @return New Texture2dCore object.
     * @throw std::invalid_argument - Thrown when the image file cannot be found
     * or read.
     */
    static Texture2dCore fromFile(const std::string& textureFileFullPath,
            TextureWrapping horizontalWrapping,
            TextureWrapping verticalWrapping,
            TextureMinifyFiltering minifyFiltering,
            TextureMagnifyFiltering magnifyFiltering);

    /*
     *
     */

    /**
     * @brief Gets the texture's ID.
     * @return Texture's ID.
     */
    GLuint getId() const;

    /**
     * @brief Gets OpenGL constant representing texture target used in
     * glBindTexture call.
     * @return OpenGL GLenum constant with texture target.
     */
    GLenum getTextureTarget() const;

  private:
    GLuint m_textureId;

    /**
     * @brief Default Texture2dCore constructor.
     * @param textureId ID of bound texture.
     */
    Texture2dCore(GLuint textureId);

    /**
     * @brief Translates the number of color channels to OpenGL constant.
     * @param channelsCount Number of color channels present.
     * @return OpenGL GLint constant.
     * @throw std::invalid_argument - Thrown when insupported option is
     * supplied.
     */
    static GLint translateChannelsCount(int channelsCount);

    /**
     * @brief Deletes the texture from OpenGL.
     */
    void deleteTexture();
};
