// Rotation.cpp - Contains definition of Rotation class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <transformations/Rotation.h>
#include <transformations/SingleTransformationBase.h>

Rotation::Rotation(
        const float axisX, const float axisY, const float axisZ)
    : SingleTransformationBase{}, m_axisX{axisX}, m_axisY{axisY},
      m_axisZ{axisZ}, m_angle_deg{0.0f} {}

void Rotation::incrementAngle(
        const float angle_increment_deg) {
    this->m_angle_deg += angle_increment_deg;
    SingleTransformationBase::rotateAboutAxis(
            this->m_angle_deg, this->m_axisX, this->m_axisY, this->m_axisZ);
}

void Rotation::setAngle(
        const float angle_deg) {
    this->m_angle_deg = angle_deg;
    SingleTransformationBase::rotateAboutAxis(
            this->m_angle_deg, this->m_axisX, this->m_axisY, this->m_axisZ);
}
