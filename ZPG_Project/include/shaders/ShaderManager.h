// ShaderManager.h - Contains declaration of ShaderManager class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <shaders/FragmentShader.h>
#include <shaders/VertexShader.h>
#include <string>
#include <unordered_map>

/**
 * @brief Enlists the available fragment shaders.
 */
class AvailableFragmentShaders {
  public:
    static constexpr const char* BASIC = "basic.frag";
    static constexpr const char* TEST = "test.frag";
    static constexpr const char* LOGIN = "login.frag";
};

/**
 * @brief Enlists the available vertex shaders.
 */
class AvailableVertexShaders {
  public:
    static constexpr const char* BASIC = "basic.vert";
    static constexpr const char* TEST = "test.vert";
};

/**
 * @brief Lazily creates and caches shader objects.
 */
class ShaderManager {
  public:
    /**
     * @brief Gets fragment shader from the cache. If the shader does not exist,
     * it is also created.
     * @param shaderFileName The name of shader file from
     * AvailableFragmentShaders.
     * @return Reference to FragmentShader object.
     */
    static FragmentShader& getFragmentShader(const char* shaderFileName);

    /**
     * @brief Gets vertex shader from the cache. If the shader does not exist,
     * it is also created.
     * @param shaderFileName The name of shader file from
     * AvailableVertexShaders.
     * @return Reference to VertexShader object.
     */
    static VertexShader& getVertexShader(const char* shaderFileName);

    /*
     *
     */

    /**
     * @brief Destroys the shader manager and its cached contents. To be used
     * upon application closing.
     */
    static void destroy();

  private:
    static ShaderManager s_instance;

    std::unordered_map<std::string, FragmentShader> m_fragmentShadersCache;
    std::unordered_map<std::string, VertexShader> m_vertexShadersCache;

    ShaderManager();
};
