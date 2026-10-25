// FragmentShader.h - Contains declaration of FragmentShader class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "ShaderCore.h"

using GLuint = unsigned int;

/**
 * @brief Represents a vertex shader.
 */
class FragmentShader {
  public:
    /**
     * @brief FragmentShader standard constructor.
     * @param shaderCore The raw OpenGL shader.
     */
    FragmentShader(ShaderCore&& shaderCore);

    /**
     * @brief Gets the ID of compiled shader.
     * @return GLuint with shader ID.
     */
    GLuint getId() const;

  private:
    ShaderCore m_shaderCore;
};
