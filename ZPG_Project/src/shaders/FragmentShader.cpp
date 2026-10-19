// FragmentShader.cpp - Contains definition of FragmentShader class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <shaders/FragmentShader.h>
#include <shaders/ShaderCore.h>
#include <utility>

FragmentShader::FragmentShader(
        ShaderCore&& shaderCore)
    : m_shaderCore{std::move(shaderCore)} {}

GLuint FragmentShader::getId() const { return this->m_shaderCore.getId(); }
