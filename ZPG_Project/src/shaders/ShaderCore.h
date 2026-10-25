// ShaderCore.h - Contains declaration of ShaderCore class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <stdexcept>
#include <string>

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
 * @brief Indicates that shader could not be created in OpenGL.
 */
class ShaderNotCreatedException : public std::runtime_error {
  public:
    ShaderNotCreatedException(
            const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @brief Groups available shader types.
 */
enum class ShaderType { VERTEX, FRAGMENT };

using GLuint = unsigned int;
using GLenum = unsigned int;

/**
 * @brief The raw compiled shader.
 */
class ShaderCore {
  public:
    /**
     * @brief ShaderCore move constructor. See
     * https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170.
     * @param other The source shader to be moved.
     */
    ShaderCore(ShaderCore&& other) noexcept;

    /**
     * @brief ShaderCore copy constructor. This constructor is intentionally
     * deleted to prevent OpenGL from accidentally discarding the compiled
     * shader.
     */
    ShaderCore(const ShaderCore&) = delete;

    ~ShaderCore();

    /*
     *
     */

    /**
     * @brief Copy-by-reference operator. This operator is intentionally deleted
     * to prevent OpenGL from accidentally discarding the compiled shader.
     */
    ShaderCore& operator=(const ShaderCore& other) = delete;

    /**
     * @brief ShaderCore move operator. See
     * https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170
     * @param other The source shader to be moved.
     * @return Moved Shader object.
     */
    ShaderCore& operator=(ShaderCore&& other) noexcept;

    /*
     *
     */

    /**
     * @brief Compiles new shader from supplied shader file contents.
     * @param shaderFileContents The file contents.
     * @param shaderType Enum value representing the shader type.
     * @return New ShaderCore object.
     * @throw ShaderNotCreatedException - Thrown if the shader could not be
     * created.
     * @throw ShaderCompileErrorException - Thrown if the shader was not
     * compiled.
     */
    static ShaderCore compile(
            const std::string& shaderFileContents, ShaderType shaderType);

    /*
     *
     */

    /**
     * @brief Gets the ID of compiled shader.
     * @return GLuint with shader ID.
     */
    GLuint getId() const;

    /**
     * @brief Gets the compiled shader type.
     * @return String with shader type.
     */
    const std::string& getType() const;

  private:
    GLuint m_id;
    std::string m_shaderType;

    /**
     * @brief ShaderCore standard constructor.
     * @param id ID of the compiled shader.
     * @param shaderType String representation of shader type.
     */
    ShaderCore(GLuint id, const std::string& shaderType);

    /**
     * @brief Verifies the shader compilation.
     * @param shaderId ID of shader to verify.
     * @throw ShaderCompileErrorException - Thrown if the shader was not
     * compiled.
     */
    static void verifyShaderCompilation(GLuint shaderId);

    /**
     * @brief Converts ShaderType enum value to GLenum number.
     * @param shaderType The enum value.
     * @return GLenum number.
     */
    static GLenum convertShaderTypeToGlenum(ShaderType shaderType);

    /**
     * @brief Converts ShaderType enum value to text.
     * @param shaderType The enum value.
     * @return Text representing the ShaderType value.
     */
    static const char* convertShaderTypeToString(ShaderType shaderType);

    /**
     * @brief Deletes the shader from OpenGL.
     */
    void deleteShader();
};
