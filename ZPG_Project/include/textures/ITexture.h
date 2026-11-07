// ITexture.h - Contains declaration of ITexture interface and related enum
// classes.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

/**
 * @brief Groups texture wrapping options.
 */
enum class TextureWrapping {
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_TO_EDGE,
    // CLAMP_TO_BORDER
};

/**
 * @brief Groups texture magnifying options.
 */
enum class TextureMagnifyFiltering { NEAREST, LINEAR };

/**
 * @brief Groups texture minifying options.
 */
enum class TextureMinifyFiltering {
    NEAREST,
    LINEAR,
    NEAREST_WITH_MIPMAP_NEAREST,
    LINEAR_WITH_MIPMAP_NEAREST,
    NEAREST_WITH_MIPMAP_LINEAR,
    LINEAR_WITH_MIPMAP_LINEAR,
};

/**
 * @brief Groups available texturing units.
 */
enum class TexturingUnit {
    UNIT0,
    UNIT1,
    UNIT2,
    UNIT3,
    UNIT4,
    UNIT5,
    UNIT6,
    UNIT7,
    UNIT8,
    UNIT9,
    UNIT10,
    UNIT11,
    UNIT12,
    UNIT13,
    UNIT14,
    UNIT15
};

using GLuint = unsigned int;
using GLenum = unsigned int;

/**
 * @brief Represents texture and its common properties.
 */
class ITexture {
  public:
    virtual ~ITexture() = default;

    /**
     * @brief Gets the texture's ID.
     * @return Texture's ID.
     */
    virtual GLuint getId() const = 0;

    /**
     * @brief Gets OpenGL constant representing the bound texturing unit.
     * @return GLenum OpenGL constant representing the texturing unit.
     */
    virtual GLenum getTexturingUnit() const = 0;

    /**
     * @brief Gets the index of bound texturing unit.
     * @return Non-negative index of the bound texturing unit.
     */
    virtual GLuint getTexturingUnitId() const = 0;

    /**
     * @brief Gets OpenGL constant representing texture target used in
     * glBindTexture call.
     * @return OpenGL GLenum constant with texture target.
     */
    virtual GLenum getTextureTarget() const = 0;
};
