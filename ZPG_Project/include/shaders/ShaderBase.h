// ShaderBase.h - Contains declaration of ShaderBase class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <stdexcept>
#include <string>

using GLenum = unsigned int;
using GLuint = unsigned int;

/**
 * @brief Indicates that shader could not be created in OpenGL.
 */
class ShaderNotCreatedException : public std::runtime_error {
  public:
    ShaderNotCreatedException(
            const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @brief Indicates that shader source file could not be found.
 */
class ShaderFileNotFoundException : public std::runtime_error {
  public:
    ShaderFileNotFoundException(
            const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @brief Indicates that shader could not be compiled.
 */
class ShaderCompileErrorException : public std::runtime_error {
  public:
    ShaderCompileErrorException(
            const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @brief Represents a base class for compiled shaders.
 */
class ShaderBase {
  public:
    /**
     * @brief Shader move constructor. See
     * https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170.
     * @param other The source shader to be moved.
     */
    ShaderBase(ShaderBase&& other) noexcept;

    /**
     * @brief Shader copy constructor. This constructor is intentionally deleted
     * to prevent OpenGL from accidentally discarding the compiled shader.
     */
    ShaderBase(const ShaderBase&) = delete;

    virtual ~ShaderBase();

    /*
     *
     */

    /**
     * @brief Shader move operator. See
     * https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170
     * @param other The source shader to be moved.
     * @return Moved Shader object.
     */
    ShaderBase& operator=(ShaderBase&& other) noexcept;

    /**
     * @brief Copy-by-reference operator. This operator is intentionally deleted
     * to prevent OpenGL from accidentally discarding the compiled shader.
     */
    ShaderBase& operator=(const ShaderBase& other) = delete;

    /*
     *
     */

    /**
     * @brief Gets the ID of compiled shader.
     * @return GLuint with shader ID.
     */
    const GLuint getId() const;

    /**
     * @brief Gets the text representing the shader type.
     * @return String representing the shader type.
     */
    const char* getShaderTypeName() const;

  protected:
    /**
     * @brief ShaderBase standard constructor.
     * @param id The shader ID.
     * @param shaderTypeName The text representation of shader type.
     */
    ShaderBase(const GLuint id, const char* shaderTypeName);

    /*
     *
     */

    /**
     * @brief Method for compiling shaders from text file.
     * @param shaderFile Full path to the text file.
     * @param shaderType The type of shader to create.
     * @param shaderTypeName The name of shader type to create.
     * @return GLuint number with new shader ID.
     * @throw ShaderNotCreatedException - Thrown when OpenGL refuses to create
     * shader.
     * @throw ShaderFileNotFoundException - Thrown when supplied file could not
     * be found.
     * @throw ShaderCompileErrorException - Thrown when shader could not be
     * compiled.
     */
    static GLuint compileShaderFromFile(const char* shaderFile,
            const GLenum shaderType, const char* shaderTypeName);

  private:
    GLuint m_id;
    const char* m_shaderTypeName;
};
