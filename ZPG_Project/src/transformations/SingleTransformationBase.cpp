// SingleTransformationBase.cpp - Contains definition of
// SingleTransformationBase class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.inl>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <transformations/ITransformation.h>
#include <transformations/SingleTransformationBase.h>

const glm::mat4 SingleTransformationBase::s_identityMatrix = glm::mat4{1.f};

SingleTransformationBase::SingleTransformationBase()
    : ITransformation{}, m_matrix{s_identityMatrix} {}

void SingleTransformationBase::translateTo(
        float x, float y, float z) {
    this->m_matrix = glm::translate(s_identityMatrix, glm::vec3(x, y, z));
}

void SingleTransformationBase::scale(
        float x, float y, float z) {
    this->m_matrix = glm::scale(s_identityMatrix, glm::vec3(x, y, z));
}

void SingleTransformationBase::rotateAboutAxis(
        float angle_deg, float axisX, float axisY, float axisZ) {
    float angle_rad = glm::radians(angle_deg);
    this->m_matrix = glm::rotate(
            s_identityMatrix, angle_rad, glm::vec3(axisX, axisY, axisZ));
}

glm::mat4 SingleTransformationBase::getMatrix() const { return this->m_matrix; }
