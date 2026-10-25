// ShaderFactory.h - Contains declaration of ShaderFactory class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <string>

#include <memory>
#include <stdexcept>
#include <unordered_map>

/**
 * @brief Indicates that shader source file could not be found.
 */
class ShaderFileNotFoundException : public std::runtime_error {
  public:
    ShaderFileNotFoundException(
            const std::string& message)
        : std::runtime_error(message) {}
};

class VertexShader;
class FragmentShader;

using GLuint = unsigned int;
using GLenum = unsigned int;
using VertexShaderPtr = std::shared_ptr<VertexShader>;
using FragmentShaderPtr = std::shared_ptr<FragmentShader>;
using VertexShaderWeakPtr = std::weak_ptr<VertexShader>;
using FragmentShaderWeakPtr = std::weak_ptr<FragmentShader>;

/**
 * @brief Creates and caches compiled shaders.
 */
class ShaderFactory {
  public:
    /**
     * @brief Creates vertex shader from supplied file.
     * @param shaderFileName Shader file name relative to resources/shaders
     * folder.
     * @return Pointer to vertex shader.
     * @throw std::invalid_argument - Thrown if the file extension does not
     * resemble vertex shader file.
     * @throw ShaderFileNotFoundException - Thrown when supplied file could not
     * be found.
     * @throw ShaderNotCreatedException - Thrown if the shader could not be
     * created.
     * @throw ShaderCompileErrorException - Thrown if the shader was not
     * compiled.
     */
    static VertexShaderPtr createVertexShaderFromFile(
            const std::string& shaderFileName);

    /**
     * @brief Creates fragment shader from supplied file.
     * @param shaderFileName Shader file name relative to resources/shaders
     * folder.
     * @return Pointer to fragment shader.
     * @throw std::invalid_argument - Thrown if the file extension does not
     * resemble fragment shader file.
     * @throw ShaderFileNotFoundException - Thrown when supplied file could not
     * be found.
     * @throw ShaderNotCreatedException - Thrown if the shader could not be
     * created.
     * @throw ShaderCompileErrorException - Thrown if the shader was not
     * compiled.
     */
    static FragmentShaderPtr createFragmentShaderFromFile(
            const std::string& shaderFileName);

  private:
    static ShaderFactory s_instance;
    std::unordered_map<std::string, VertexShaderWeakPtr> m_vertexShadersCache;
    std::unordered_map<std::string, FragmentShaderWeakPtr>
            m_fragmentShadersCache;

    /**
     * @brief Reads the contents of shader file and stores it into string.
     * @param shaderFileName Relative path to shader file name.
     * @return String with file contents.
     * @throw ShaderFileNotFoundException - Thrown when supplied file could not
     * be found.
     */
    std::string readShaderFileContents(const std::string& shaderFileName);
};
