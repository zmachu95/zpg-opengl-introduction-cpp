// ShaderBase.cpp - Contains definition of ShaderBase class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <shaders/ShaderBase.h>

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>

using namespace std::string_literals;

static void deleteShader(
        GLuint shaderId, const char* shaderTypeName) {
    if (shaderId != 0) {
        std::cout << "Deleting " << shaderTypeName << " shader ID " << shaderId
                  << ".\n";
        glDeleteShader(shaderId);
    }
}

static std::string readShaderFileContents(
        const char* shaderFileName) {
    std::ifstream file{shaderFileName};
    if (!file.is_open()) {
        throw ShaderFileNotFoundException(
                "Unable to open file "s + shaderFileName + ".");
    }
    return std::string{std::istreambuf_iterator<char>{file},
            std::istreambuf_iterator<char>{}};
}

static void verifyShaderCompilation(
        const GLuint shaderId) {
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

ShaderBase::ShaderBase(
        const GLuint id, const char* shaderTypeName)
    : m_id{id}, m_shaderTypeName{shaderTypeName} {
    std::cout << "Created " << this->getShaderTypeName() << " shader with ID "
              << this->m_id << ".\n";
}

ShaderBase::ShaderBase(
        ShaderBase&& other) noexcept
    : m_id{std::exchange(other.m_id, 0)},
      m_shaderTypeName{std::exchange(other.m_shaderTypeName, nullptr)} {}

ShaderBase::~ShaderBase() {
    deleteShader(this->m_id, this->getShaderTypeName());
}

ShaderBase& ShaderBase::operator=(
        ShaderBase&& other) noexcept {
    if (&other != this) {
        deleteShader(this->m_id, this->getShaderTypeName());

        this->m_id = std::exchange(other.m_id, 0);
        this->m_shaderTypeName = std::exchange(other.m_shaderTypeName, nullptr);
    }

    return *this;
}

GLuint ShaderBase::compileShaderFromFile(
        const char* shaderFile, GLenum shaderType, const char* shaderTypeName) {
    // Creates an empty shader
    GLuint shaderID = glCreateShader(shaderType);
    if (shaderID == 0) {
        throw ShaderNotCreatedException(
                "Unable to create "s + shaderTypeName + ".");
    }

    // Loading the contents of a file into a variable
    std::string shaderCode;
    try {
        shaderCode = readShaderFileContents(shaderFile);
    } catch (const ShaderFileNotFoundException&) {
        glDeleteShader(shaderID);
        throw;
    }

    // Set the shader source code
    const char* source = shaderCode.c_str();
    glShaderSource(shaderID, 1, &source, nullptr);

    // Compile the shader source code
    glCompileShader(shaderID);

    // Check specialization/compilation status
    verifyShaderCompilation(shaderID);
    return shaderID;
}

const GLuint ShaderBase::getId() const { return this->m_id; }

const char* ShaderBase::getShaderTypeName() const {
    return this->m_shaderTypeName;
}
