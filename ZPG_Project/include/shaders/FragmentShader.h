// FragmentShader.h - Contains declaration of FragmentShader class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <shaders/ShaderBase.h>

using GLuint = unsigned int;

/**
 * @brief Represents a fragment shader.
 */
class FragmentShader : public ShaderBase {
  public:
    /**
     * @brief Factory method for creating fragment shaders from text file.
     * @param shaderFile Full path to the text file.
     * @return New FragmentShader object.
     * @throw ShaderNotCreatedException - Thrown when OpenGL refuses to create
     * shader.
     * @throw ShaderFileNotFoundException - Thrown when supplied file could not
     * be found.
     * @throw ShaderCompileErrorException - Thrown when shader could not be
     * compiled.
     */
    static FragmentShader compileShaderFromFile(const char* shaderFile);

  private:
    /**
     * @brief FragmentShader standard constructor.
     * @param id The shader ID.
     */
    FragmentShader(const GLuint id);
};
