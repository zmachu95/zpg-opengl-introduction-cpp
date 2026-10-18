// VertexShader.cpp - Contains definition of VertexShader class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include <shaders/ShaderBase.h>
#include <shaders/VertexShader.h>

static constexpr GLenum SHADER_TYPE = GL_VERTEX_SHADER;

static constexpr char SHADER_TYPE_NAME[] = "vertex shader";

VertexShader::VertexShader(const GLuint id)
    : ShaderBase{id, SHADER_TYPE_NAME} {};

VertexShader VertexShader::compileShaderFromFile(
        const char* shaderFile) {
    GLuint shaderId = ShaderBase::compileShaderFromFile(
            shaderFile, SHADER_TYPE, SHADER_TYPE_NAME);
    return VertexShader(shaderId);
}
