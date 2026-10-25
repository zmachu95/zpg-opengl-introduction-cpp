// ShaderCore.cpp - Contains definition of ShaderCore class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "ShaderCore.h"

#include <iostream>

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include <stdexcept>
#include <string>
#include <utility>

using namespace std::string_literals;

ShaderCore::ShaderCore(
        GLuint id, const std::string& shaderType)
    : m_id{id}, m_shaderType{shaderType} {
    std::cout << "Created " << shaderType << " with ID " << id << ".\n";
}

ShaderCore::ShaderCore(
        ShaderCore&& other) noexcept
    : m_id{std::exchange(other.m_id, 0)},
      m_shaderType{std::move(other.m_shaderType)} {}

ShaderCore::~ShaderCore() { this->deleteShader(); }

ShaderCore& ShaderCore::operator=(
        ShaderCore&& other) noexcept {
    if (this != &other) {
        this->deleteShader();

        this->m_id = std::exchange(other.m_id, 0);
        this->m_shaderType = std::move(other.m_shaderType);
    }

    return *this;
}

GLuint ShaderCore::getId() const { return this->m_id; }

const std::string& ShaderCore::getType() const { return this->m_shaderType; }

void ShaderCore::verifyShaderCompilation(
        GLuint shaderId) {
    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shaderId, sizeof(infoLog), nullptr, infoLog);
        glDeleteShader(shaderId);
        throw ShaderCompileErrorException(
                "Shader compilation failed:\n"s + infoLog);
    }
}

ShaderCore ShaderCore::compile(
        const std::string& shaderFileContents, ShaderType shaderType) {
    GLuint shaderId =
            glCreateShader(ShaderCore::convertShaderTypeToGlenum(shaderType));
    if (shaderId == 0) {
        throw ShaderNotCreatedException(
                "Unable to create "s
                + ShaderCore::convertShaderTypeToString(shaderType) + ".");
    }

    const char* source = shaderFileContents.c_str();
    glShaderSource(shaderId, 1, &source, nullptr);
    glCompileShader(shaderId);
    verifyShaderCompilation(shaderId);

    return ShaderCore(
            shaderId, ShaderCore::convertShaderTypeToString(shaderType));
}

void ShaderCore::deleteShader() {
    if (this->m_id != 0) {
        std::cout << "Deleting " << this->m_shaderType << " with ID "
                  << this->m_id << ".\n";
        glDeleteShader(this->m_id);
        this->m_id = 0;
    }
}

GLenum ShaderCore::convertShaderTypeToGlenum(
        ShaderType shaderType) {
    switch (shaderType) {
        case ShaderType::VERTEX:
            return GL_VERTEX_SHADER;
        case ShaderType::FRAGMENT:
            return GL_FRAGMENT_SHADER;
        default:
            throw std::invalid_argument("Option "s
                                        + std::to_string((int)shaderType)
                                        + " is not implemented!");
    }
}

const char* ShaderCore::convertShaderTypeToString(
        ShaderType shaderType) {
    switch (shaderType) {
        case ShaderType::VERTEX:
            return "vertex shader";
        case ShaderType::FRAGMENT:
            return "fragment shader";
        default:
            throw std::invalid_argument("Option "s
                                        + std::to_string((int)shaderType)
                                        + " is not implemented!");
    }
}
