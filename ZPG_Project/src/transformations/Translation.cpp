// Translation.h - Contains definition of Translation class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <transformations/TransformationChangePublisher.h>
#include <transformations/Translation.h>

Translation::Translation()
    : m_x{0}, m_y{0}, m_z{0}, m_matrix{1.0f}, m_publisher{} {}

void Translation::move(
        const float dx, const float dy, const float dz) {
    if (dx != 0 || dy != 0 || dz != 0) {
        this->m_x += dx;
        this->m_y += dy;
        this->m_z += dz;
        this->calculateTranslationMatrix();
        this->notifyListeners();
    }
}

void Translation::translateTo(
        const float x, const float y, const float z) {
    if (x != this->m_x || y != this->m_y || z != this->m_z) {
        this->m_x = x;
        this->m_y = y;
        this->m_z = z;
        this->calculateTranslationMatrix();
        this->notifyListeners();
    }
}

const glm::mat4& Translation::getMatrix() { return this->m_matrix; }

void Translation::registerTransformationChangeListener(
        const TransformationChangeListenerPtr& listener) {
    this->m_publisher.registerTransformationChangeListener(listener);
}

void Translation::calculateTranslationMatrix() {
    this->m_matrix = glm::translate(
            glm::mat4{1.0f}, glm::vec3(this->m_x, this->m_y, this->m_z));
}

void Translation::notifyListeners() { this->m_publisher.notifyListeners(); }
