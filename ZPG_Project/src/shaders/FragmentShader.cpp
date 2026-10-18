// FragmentShader.cpp - Contains definition of FragmentShader class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include <shaders/FragmentShader.h>
#include <shaders/ShaderBase.h>

using GLenum = unsigned int;
using GLuint = unsigned int;

static constexpr GLenum SHADER_TYPE = GL_FRAGMENT_SHADER;

static constexpr char SHADER_TYPE_NAME[] = "fragment shader";

FragmentShader::FragmentShader(const GLuint id)
    : ShaderBase{id, SHADER_TYPE_NAME} {};

FragmentShader FragmentShader::compileShaderFromFile(
        const char* shaderFile) {
    GLuint shaderId = ShaderBase::compileShaderFromFile(
            shaderFile, SHADER_TYPE, SHADER_TYPE_NAME);
    return FragmentShader(shaderId);
}
