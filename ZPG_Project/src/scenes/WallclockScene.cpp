// WallclockScene.cpp - Contains definition of TriangleScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <scenes/WallclockScene.h>

#include <drawables/DrawableObject.h>
#include <memory>
#include <scenes/IScene.h>
#include <shaders/ShaderProgram.h>
#include <transformations/IRotation.h>
#include <transformations/IScale.h>
#include <transformations/ITranslation.h>

#include <cameras/CameraCommonSettings.h>
#include <cameras/PerspectiveCamera.h>
#include <drawables/DrawableObjectFactory.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>
#include <others/WallclockUtils.h>
#include <resources/models/clock.h>

WallclockScene::WallclockScene() : m_program{}, m_clock{}, m_pinsRotations{} {
    this->m_program =
            ShaderProgram::createFromShaderFiles("clock.vert", "basic.frag");
    this->m_clock = DrawableObjectFactory::createDrawableObjectFromVerticesData(
            clockModel, sizeof(clockModel) / sizeof(clockModel[0]), 3);
}

void WallclockScene::draw(
        const float deltaT) {
    time_t currentTime = getCurrentTime();
    int seconds = convertTimeTtoSeconds(currentTime);
    int minutes = convertTimeTtoMinutes(currentTime);
    int hours = convertTimeTtoHours(currentTime);

    m_pinsRotations["secondsPinTransformation"] =
            getSecondsPinRotationMatrix(seconds);
    m_pinsRotations["minutesPinTransformation"] =
            getMinutesPinRotationMatrix(minutes, seconds);
    m_pinsRotations["hoursPinTransformation"] =
            getHoursPinRotationMatrix(hours, minutes, seconds);

    this->m_program->setSupplementalUniformMatrices(this->m_pinsRotations);
    this->m_clock->draw(*this->m_program);
}

void WallclockScene::handleMouseMovement(
        int cursorDeltaX, int cursorDeltaY) {}

void WallclockScene::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {}

void WallclockScene::handleWindowResize(
        int width, int height) {}
