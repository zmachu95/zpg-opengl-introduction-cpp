// VertexShader.h - Contains declaration of VertexShader class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "ShaderCore.h"

using GLuint = unsigned int;

/**
 * @brief Represents a vertex shader.
 */
class VertexShader {
  public:
    /**
     * @brief VertexShader standard constructor.
     * @param shaderCore The raw OpenGL shader.
     */
    VertexShader(ShaderCore&& shaderCore);

    /**
     * @brief Gets the ID of compiled shader.
     * @return GLuint with shader ID.
     */
    GLuint getId() const;

  private:
    ShaderCore m_shaderCore;
};
