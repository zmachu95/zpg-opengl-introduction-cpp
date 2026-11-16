// SkyboxTexture.h - Contains declaration of SkyboxTexture class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <array>
#include <string>
#include <textures/ITexture.h>

/*
 * @brief Number of textures needed to fully define the skybox.
 */
#define SKYBOX_TEXTURES_COUNT 6

using GLuint = unsigned int;
using GLenum = unsigned int;

class SkyboxFiles;

/**
 * @brief A Skybox texture bound in OpenGL.
 */
class SkyboxTexture : public ITexture {
  public:
    /**
     * @brief SkyboxTexture copy constructor. Deliberately deleted to prevent
     * OpenGL from accidentally releasing the texture data.
     */
    SkyboxTexture(const SkyboxTexture& other) = delete;

    /**
     * @brief SkyboxTexture move constructor.
     * @param other Source texture to be moved.
     */
    SkyboxTexture(SkyboxTexture&& other) noexcept;

    ~SkyboxTexture() override;

    /*
     *
     */

    /**
     * @brief SkyboxTexture copy-by-reference operator. Deliberately deleted to
     * prevent OpenGL from accidentally releasing the texture data.
     */
    SkyboxTexture& operator=(const SkyboxTexture& other) = delete;

    /**
     * @brief SkyboxTexture move operator.
     * @param other Source texture to be moved.
     * @return The moved texture.
     */
    SkyboxTexture& operator=(SkyboxTexture&& other) noexcept;

    /*
     *
     */

    /**
     * @brief Creates and binds new skybox texture using data from supplied
     * files.
     * @param textureFiles Array skybox pictures in following order: positive x,
     * negative x, positive y, negative y, positive z, negative z.
     * @return New SkyboxTexture object.
     * @throw std::invalid_argument - Thrown when the image file cannot be found
     * or read.
     */
    static SkyboxTexture fromFiles(
            const std::array<std::string, SKYBOX_TEXTURES_COUNT>& textureFiles);

    /*
     *
     */

    /**
     * @brief Gets the texture's ID.
     * @return Texture's ID.
     */
    GLuint getId() const override;

    /**
     * @brief Gets OpenGL constant representing the bound texturing unit.
     * @return GLenum OpenGL constant representing the texturing unit.
     */
    GLenum getTexturingUnit() const override;

    /**
     * @brief Gets the index of bound texturing unit.
     * @return Non-negative index of the bound texturing unit.
     */
    GLuint getTexturingUnitId() const override;

    /**
     * @brief Gets OpenGL constant representing texture target used in
     * glBindTexture call.
     * @return OpenGL GLenum constant with texture target.
     */
    GLenum getTextureTarget() const override;

  private:
    GLuint m_textureId;

    /**
     * @brief SkyboxTexture default constructor.
     * @param textureId ID of bound texture.
     */
    SkyboxTexture(GLuint textureId);

    /**
     * @brief Deletes the texture from OpenGL.
     */
    void deleteTexture();
};
