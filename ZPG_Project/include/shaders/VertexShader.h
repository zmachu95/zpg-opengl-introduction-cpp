// VertexShader.h - Contains declaration of VertexShader class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <shaders/ShaderBase.h>

using GLuint = unsigned int;

/**
 * @brief Represents a vertex shader.
 */
class VertexShader : public ShaderBase {
  public:
    /**
     * @brief Factory method for creating vertex shaders from text file.
     * @param shaderFile Full path to the text file.
     * @return New vertex shader object.
     * @throw ShaderNotCreatedException - Thrown when OpenGL refuses to create
     * shader.
     * @throw ShaderFileNotFoundException - Thrown when supplied file could not
     * be found.
     * @throw ShaderCompileErrorException - Thrown when shader could not be
     * compiled.
     */
    static VertexShader compileShaderFromFile(const char* shaderFile);

  private:
    /**
     * @brief VertexShader standard constructor.
     * @param id The shader ID.
     */
    VertexShader(const GLuint id);
};
