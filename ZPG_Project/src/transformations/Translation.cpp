// Translation.h - Contains definition of Translation class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <transformations/SingleTransformationBase.h>
#include <transformations/Translation.h>

Translation::Translation()
    : SingleTransformationBase{}, m_x{0}, m_y{0}, m_z{0} {}

void Translation::move(
        const float dx, const float dy, const float dz) {
    this->m_x += dx;
    this->m_y += dy;
    this->m_z += dz;
    SingleTransformationBase::translateTo(this->m_x, this->m_y, this->m_z);
}

void Translation::translateTo(
        const float x, const float y, const float z) {
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
    SingleTransformationBase::translateTo(this->m_x, this->m_y, this->m_z);
}
