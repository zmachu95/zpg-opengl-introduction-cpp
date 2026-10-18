// ShaderProgram.cpp - Contains definition of ShaderProgram class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include <iostream>
#include <shaders/FragmentShader.h>
#include <shaders/ShaderProgram.h>
#include <shaders/UniformVariableManager.h>
#include <shaders/VertexShader.h>
#include <string>
#include <type_traits>
#include <utility>

using namespace std::string_literals;
using GLuint = unsigned int;

GLuint ShaderProgram::s_activeProgramId = 0;

static void deleteShaderProgram(
        GLuint programId) {
    if (programId != 0) {
        std::cout << "Deleting shader program ID " << programId << ".\n";
        glDeleteProgram(programId);
    }
}

static void verifyShaderProgramLinking(
        const GLuint programId) {
    GLint success;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(programId, sizeof(infoLog), nullptr, infoLog);
        glDeleteProgram(programId);
        throw ShaderProgramLinkErrorException{
                "Shader program linking failed:\n"s + infoLog};
    }
}

ShaderProgram::ShaderProgram(
        GLuint id, UniformVariableManager&& uniformVariableManager,
        std::reference_wrapper<VertexShader> vertexShader,
        std::reference_wrapper<FragmentShader> fragmentShader)
    : m_id{id}, m_uniformVarManager{std::move(uniformVariableManager)},
      m_vertexShader{vertexShader}, m_fragmentShader{fragmentShader} {
    std::cout << "Created shader program with ID " << id << ".\n";
}

ShaderProgram ShaderProgram::createFromShaders(
        VertexShader& vertexShader, FragmentShader& fragmentShader) {
    GLuint shaderProgramId = glCreateProgram();
    if (shaderProgramId == 0) {
        throw ShaderProgramNotCreatedException{
                "Unable to create shader program."};
    }

    glAttachShader(shaderProgramId, fragmentShader.getId());
    glAttachShader(shaderProgramId, vertexShader.getId());
    glLinkProgram(shaderProgramId);
    verifyShaderProgramLinking(shaderProgramId);

    return ShaderProgram{shaderProgramId,
            UniformVariableManager{shaderProgramId},
            std::reference_wrapper<VertexShader>{vertexShader},
            std::reference_wrapper<FragmentShader>{fragmentShader}};
}

void ShaderProgram::remove() {
    if (s_activeProgramId == this->m_id) {
        // std::cout << "Shader program: " << s_activeProgramId << "
        // deactivated.\n";
        s_activeProgramId = 0;
        this->m_uniformVarManager.setIsParentShaderProgramActive(false);
        glUseProgram(0);
    } else {
        std::cout << "Cannot remove shader program with ID " << this->m_id
                  << " because program with ID " << s_activeProgramId
                  << " is currently in use!";
    }
}

ShaderProgram::ShaderProgram(
        ShaderProgram&& other) noexcept
    : m_id{std::exchange(other.m_id, 0)},
      m_uniformVarManager{std::move(other.m_uniformVarManager)},
      m_fragmentShader{std::move(other.m_fragmentShader)},
      m_vertexShader{std::move(other.m_vertexShader)} {}

ShaderProgram::~ShaderProgram() { deleteShaderProgram(this->m_id); }

ShaderProgram& ShaderProgram::operator=(
        ShaderProgram&& other) noexcept {
    if (this != &other) {
        deleteShaderProgram(this->m_id);

        this->m_id = std::exchange(other.m_id, 0);
        this->m_uniformVarManager = std::move(other.m_uniformVarManager);
        this->m_vertexShader = std::move(other.m_vertexShader);
        this->m_fragmentShader = std::move(other.m_fragmentShader);
    }

    return *this;
}

const GLuint ShaderProgram::getId() const { return this->m_id; }

const VertexShader& ShaderProgram::getVertexShader() const {
    return this->m_vertexShader;
}

const FragmentShader& ShaderProgram::getFragmentShader() const {
    return this->m_fragmentShader;
}

UniformVariableManager& ShaderProgram::getUniformVariableManager() {
    return this->m_uniformVarManager;
}

void ShaderProgram::use() {
    if (this->m_id != 0 && s_activeProgramId == 0) {
        glUseProgram(this->m_id);
        s_activeProgramId = this->m_id;
        this->m_uniformVarManager.setIsParentShaderProgramActive(true);
        // std::cout << "Activated shader program: " << this->m_id << ".\n";
    } else {
        std::cout << "Cannot use shader program with ID " << this->m_id
                  << " because program with ID " << s_activeProgramId
                  << " is currently in use!";
    }
}
