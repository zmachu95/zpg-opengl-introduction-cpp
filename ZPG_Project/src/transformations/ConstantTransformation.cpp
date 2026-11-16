// ConstantTransformation.cpp - Contains definition of ConstantTransformation
// class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#include "ConstantTransformation.h"
#include <glm/ext/matrix_float4x4.hpp>

ConstantTransformation::ConstantTransformation(
        const glm::mat4& matrix)
    : m_matrix{matrix} {}

const glm::mat4& ConstantTransformation::getMatrix() { return this->m_matrix; }
