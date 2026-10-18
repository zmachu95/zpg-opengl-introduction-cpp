// ShaderManager.cpp - Contains definition of ShaderManager class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <shaders/FragmentShader.h>
#include <shaders/ShaderManager.h>
#include <shaders/VertexShader.h>
#include <string>
#include <utility>

ShaderManager ShaderManager::s_instance = ShaderManager{};

const char SHADERS_FOLDER[] = "resources\\shaders\\";

static std::string buildFullShaderFilePath(
        const char* shaderFileName) {
    return std::string{SHADERS_FOLDER} + shaderFileName;
}

ShaderManager::ShaderManager()
    : m_fragmentShadersCache{}, m_vertexShadersCache{} {}

void ShaderManager::destroy() {
    s_instance.m_fragmentShadersCache.clear();
    s_instance.m_vertexShadersCache.clear();
}

FragmentShader& ShaderManager::getFragmentShader(
        const char* shaderFileName) {
    std::string shaderFullFileName = buildFullShaderFilePath(shaderFileName);
    if (s_instance.m_fragmentShadersCache.find(shaderFileName)
            == s_instance.m_fragmentShadersCache.end()) {
        s_instance.m_fragmentShadersCache.insert(
                std::pair<std::string, FragmentShader>(
                        shaderFileName, FragmentShader::compileShaderFromFile(
                                                shaderFullFileName.c_str())));
    }

    return s_instance.m_fragmentShadersCache.at(shaderFileName);
}

VertexShader& ShaderManager::getVertexShader(
        const char* shaderFileName) {
    std::string shaderFullFileName = buildFullShaderFilePath(shaderFileName);
    if (s_instance.m_vertexShadersCache.find(shaderFileName)
            == s_instance.m_vertexShadersCache.end()) {
        s_instance.m_vertexShadersCache.insert(
                std::pair<std::string, VertexShader>(
                        shaderFileName, VertexShader::compileShaderFromFile(
                                                shaderFullFileName.c_str())));
    }

    return s_instance.m_vertexShadersCache.at(shaderFileName);
}
