// ShaderFactory.cpp - Contains definition of ShaderFactory class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "ShaderFactory.h"
#include "FragmentShader.h"
#include "ShaderCore.h"
#include "VertexShader.h"
#include <fstream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std::string_literals;

/**
 * @brief Expected file extension for fragment shaders.
 */
const std::string FRAGMENT_SHADER_FILE_EXTENSION{".frag"};

/**
 * @brief Expected file extension for vertex shaders.
 */
const std::string VERTEX_SHADER_FILE_EXTENSION{".vert"};

/**
 * @brief Path to shader files folder.
 */
const std::string SHADERS_FOLDER = "resources\\shaders\\";

ShaderFactory ShaderFactory::s_instance{};

VertexShaderPtr ShaderFactory::createVertexShaderFromFile(
        const std::string& shaderFileName) {
    if (VertexShaderPtr cachedShader =
                    s_instance.m_vertexShadersCache[shaderFileName].lock()) {
        return cachedShader;
    }

    if (shaderFileName.substr(
                shaderFileName.size() - VERTEX_SHADER_FILE_EXTENSION.size())
            != VERTEX_SHADER_FILE_EXTENSION) {
        throw std::invalid_argument(
                "Supplied file "s + shaderFileName
                + " is not a vertex shader by its file extensions!");
    }

    std::string fileContents =
            s_instance.readShaderFileContents(shaderFileName);
    ShaderCore rawShader =
            ShaderCore::compile(fileContents, ShaderType::VERTEX);

    VertexShaderPtr newVertexShader =
            std::make_shared<VertexShader>(std::move(rawShader));
    s_instance.m_vertexShadersCache[shaderFileName] = newVertexShader;
    return newVertexShader;
}
FragmentShaderPtr ShaderFactory::createFragmentShaderFromFile(
        const std::string& shaderFileName) {
    if (FragmentShaderPtr cachedShader =
                    s_instance.m_fragmentShadersCache[shaderFileName].lock()) {
        return cachedShader;
    }

    if (shaderFileName.substr(
                shaderFileName.size() - FRAGMENT_SHADER_FILE_EXTENSION.size())
            != FRAGMENT_SHADER_FILE_EXTENSION) {
        throw std::invalid_argument(
                "Supplied file "s + shaderFileName
                + " is not a fragment shader by its file extensions!");
    }

    std::string fileContents =
            s_instance.readShaderFileContents(shaderFileName);
    ShaderCore rawShader =
            ShaderCore::compile(fileContents, ShaderType::FRAGMENT);

    FragmentShaderPtr newFragmentShader =
            std::make_shared<FragmentShader>(std::move(rawShader));
    s_instance.m_fragmentShadersCache[shaderFileName] = newFragmentShader;
    return newFragmentShader;
}

std::string ShaderFactory::readShaderFileContents(
        const std::string& shaderFileName) {
    std::ifstream file{SHADERS_FOLDER + shaderFileName};
    if (!file.is_open()) {
        throw ShaderFileNotFoundException("Unable to open file "s
                                          + (SHADERS_FOLDER + shaderFileName)
                                          + ".");
    }
    return std::string{std::istreambuf_iterator<char>{file},
            std::istreambuf_iterator<char>{}};
}
