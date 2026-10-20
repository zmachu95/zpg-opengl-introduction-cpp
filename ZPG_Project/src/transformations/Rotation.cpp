// Rotation.cpp - Contains definition of Rotation class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <transformations/Rotation.h>
#include <transformations/TransformationChangePublisher.h>

Rotation::Rotation(
        const float axisX, const float axisY, const float axisZ)
    : m_angle_deg{0.0f}, m_axisX{axisX}, m_axisY{axisY}, m_axisZ{axisZ},
      m_matrix{1.0f}, m_publisher{} {}

void Rotation::incrementAngle(
        const float angle_increment_deg) {
    if (angle_increment_deg != 0) {
        this->m_angle_deg += angle_increment_deg;
        this->calculateRotationMatrix();
        this->notifyListeners();
    }
}

void Rotation::setAngle(
        const float angle_deg) {
    if (this->m_angle_deg != angle_deg) {
        this->m_angle_deg = angle_deg;
        this->calculateRotationMatrix();
        this->notifyListeners();
    }
}

const glm::mat4& Rotation::getMatrix() { return this->m_matrix; }

void Rotation::registerTransformationChangeListener(
        const TransformationChangeListenerPtr& listener) {
    this->m_publisher.registerTransformationChangeListener(listener);
}

void Rotation::calculateRotationMatrix() {
    float angle_rad = glm::radians(this->m_angle_deg);
    this->m_matrix = glm::rotate(glm::mat4{1.0f}, angle_rad,
            glm::vec3(this->m_axisX, this->m_axisY, this->m_axisZ));
}

void Rotation::notifyListeners() { this->m_publisher.notifyListeners(); }
