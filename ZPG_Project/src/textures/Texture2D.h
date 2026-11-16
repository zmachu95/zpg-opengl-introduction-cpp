// Texture2D.h - Contains declaration of Texture2D class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <memory>
#include <textures/ITexture.h>

using GLuint = unsigned int;
using GLenum = unsigned int;
class Texture2dCore;

using Texture2dPtr = std::shared_ptr<Texture2dCore>;

/**
 * @brief Wraps a 2D texture and binds it to a specific texturing unit.
 */
class Texture2D : public ITexture {
  public:
    /**
     * @brief Texture2D default constructor.
     * @param texture Pointer to a compiled 2D texture to wrap.
     * @param unit The texturing unit.
     */
    Texture2D(const Texture2dPtr& texture, TexturingUnit unit);

    ~Texture2D() override = default;

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
    Texture2dPtr m_texture;
    TexturingUnit m_unit;
};
