// VertexShader.cpp - Contains definition of VertexShader class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "VertexShader.h"
#include "ShaderCore.h"
#include <utility>

VertexShader::VertexShader(
        ShaderCore&& shaderCore)
    : m_shaderCore{std::move(shaderCore)} {}

GLuint VertexShader::getId() const { return this->m_shaderCore.getId(); }
