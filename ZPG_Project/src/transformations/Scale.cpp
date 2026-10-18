// Scale.h - Contains declaration of Scale class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <transformations/Scale.h>
#include <transformations/SingleTransformationBase.h>

Scale::Scale() : SingleTransformationBase{}, m_x{0}, m_y{0}, m_z{0} {}

void Scale::increment(
        const float dx, const float dy, const float dz) {
    this->m_x += dx;
    this->m_y += dy;
    this->m_z += dz;
    SingleTransformationBase::scale(this->m_x, this->m_y, this->m_z);
}

void Scale::setScaleTo(
        const float x, const float y, const float z) {
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
    SingleTransformationBase::scale(this->m_x, this->m_y, this->m_z);
}
