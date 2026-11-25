// WallclockScene.cpp - Contains definition of TriangleScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "WallclockScene.h"
#include "AbstractSceneTemplate.h"

#include <cameras/PerspectiveCamera.h>
#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <memory>
#include <others/WallclockUtils.h>
#include <shaders/ShaderProgram.h>

WallclockScene::WallclockScene(
        int windowWidth, int windowHeight)
    : AbstractSceneTemplate{std::unique_ptr<PerspectiveCamera>{},
              std::unique_ptr<DrawableObject>{}} {
    this->m_shaderProgram = &this->addShaderProgramFromShaderFiles(
            "wallclock_scene\\clock.vert", "_templates\\basic.frag", false);
    DrawableObject& clock = this->addDrawableObjectFromKnownModel(
            false, KnownModels::CLOCK, *this->m_shaderProgram);
}

void WallclockScene::updateSceneContents(
        float deltaT) {
    time_t currentTime = getCurrentTime();
    int seconds = convertTimeTtoSeconds(currentTime);
    int minutes = convertTimeTtoMinutes(currentTime);
    int hours = convertTimeTtoHours(currentTime);

    this->m_shaderProgram->setSupplementalUniformMatrix(
            SECONDS_PIN_SHADER_MATRIX_NAME,
            getSecondsPinRotationMatrix(seconds));
    this->m_shaderProgram->setSupplementalUniformMatrix(
            MINUTES_PIN_SHADER_MATRIX_NAME,
            getMinutesPinRotationMatrix(minutes, seconds));
    this->m_shaderProgram->setSupplementalUniformMatrix(
            HOURS_PIN_SHADER_MATRIX_NAME,
            getHoursPinRotationMatrix(hours, minutes, seconds));
}
