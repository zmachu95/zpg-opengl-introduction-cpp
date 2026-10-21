// ShaderProgram.cpp - Contains definition of ShaderProgram class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include <iostream>
#include <listeners/ICameraUpdateListener.h>
#include <memory>
#include <shaders/FragmentShader.h>
#include <shaders/ShaderFactory.h>
#include <shaders/ShaderProgram.h>
#include <shaders/UniformVariableManager.h>
#include <shaders/VertexShader.h>
#include <string>
#include <utility>

using namespace std::string_literals;

ShaderProgram::ShaderProgram(
        GLuint id, const UniformVariableManagerPtr& uniformVariableManager,
        const VertexShaderPtr& vertexShader,
        const FragmentShaderPtr& fragmentShader)
    : m_id{id}, m_uniformVarManager{uniformVariableManager},
      m_vertexShader{vertexShader}, m_fragmentShader{fragmentShader},
      m_supplementalUniformMatrices{} {
    std::cout << "Created shader program with ID " << id << ".\n";
}

ShaderProgram::ShaderProgram(
        ShaderProgram&& other) noexcept
    : m_id{std::exchange(other.m_id, 0)},
      m_uniformVarManager{std::move(other.m_uniformVarManager)},
      m_fragmentShader{std::move(other.m_fragmentShader)},
      m_vertexShader{std::move(other.m_vertexShader)},
      m_supplementalUniformMatrices{
              std::move(other.m_supplementalUniformMatrices)} {}

ShaderProgram::~ShaderProgram() { this->deleteProgram(); }

ShaderProgram& ShaderProgram::operator=(
        ShaderProgram&& other) noexcept {
    if (this != &other) {
        this->deleteProgram();

        this->m_id = std::exchange(other.m_id, 0);
        this->m_uniformVarManager = std::move(other.m_uniformVarManager);
        this->m_vertexShader = std::move(other.m_vertexShader);
        this->m_fragmentShader = std::move(other.m_fragmentShader);
        this->m_supplementalUniformMatrices =
                std::move(other.m_supplementalUniformMatrices);
    }

    return *this;
}

ShaderProgramPtr ShaderProgram::createFromShaderFiles(
        const std::string& vertexShaderFile,
        const std::string& fragmentShaderFile) {
    VertexShaderPtr vertexShader =
            ShaderFactory::createVertexShaderFromFile(vertexShaderFile);
    FragmentShaderPtr fragmentShader =
            ShaderFactory::createFragmentShaderFromFile(fragmentShaderFile);

    return std::make_unique<ShaderProgram>(
            ShaderProgram::link(vertexShader, fragmentShader));
}

ShaderProgram ShaderProgram::link(
        const VertexShaderPtr& vertexShader,
        const FragmentShaderPtr& fragmentShader) {
    GLuint shaderProgramId = glCreateProgram();
    if (shaderProgramId == 0) {
        throw ShaderProgramNotCreatedException{
                "Unable to create shader program."};
    }

    glAttachShader(shaderProgramId, fragmentShader->getId());
    glAttachShader(shaderProgramId, vertexShader->getId());
    glLinkProgram(shaderProgramId);
    verifyShaderProgramLinking(shaderProgramId);

    return ShaderProgram{shaderProgramId,
            std::make_shared<UniformVariableManager>(shaderProgramId),
            vertexShader, fragmentShader};
}

void ShaderProgram::deleteProgram() {
    if (this->m_id != 0) {
        std::cout << "Deleting shader program ID " << this->m_id << ".\n";
        glDetachShader(this->m_id, this->m_fragmentShader->getId());
        glDetachShader(this->m_id, this->m_vertexShader->getId());
        glDeleteProgram(this->m_id);
        this->m_id = 0;
    }
}

void ShaderProgram::verifyShaderProgramLinking(
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

GLuint ShaderProgram::getId() const { return this->m_id; }

std::weak_ptr<ICameraUpdateListener> ShaderProgram::asCameraUpdateListener() {
    return std::weak_ptr<UniformVariableManager>(this->m_uniformVarManager);
}

void ShaderProgram::use(
        const glm::mat4& transformationMatrix) {
    glUseProgram(this->m_id);
    this->m_uniformVarManager->applyTransformation(transformationMatrix);
    if (this->m_uniformVarManager->isCameraUpdated()) {
        this->m_uniformVarManager->applyCameraMatrices();
    }
    this->applySupplementalMatrices();
}

void ShaderProgram::setSupplementalUniformMatrices(
        const std::unordered_map<std::string, glm::mat4>&
                supplementalMatricesMap) {
    this->m_supplementalUniformMatrices = supplementalMatricesMap;
}

void ShaderProgram::applySupplementalMatrices() {
    if (!this->m_supplementalUniformMatrices.empty()) {
        this->m_uniformVarManager->applySupplementalMatrices(
                this->m_supplementalUniformMatrices);
        this->m_supplementalUniformMatrices.clear();
    }
}
