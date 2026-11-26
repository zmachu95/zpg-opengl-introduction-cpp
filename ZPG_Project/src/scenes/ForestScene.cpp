// ForestScene.cpp - Contains definition of ForestScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "ForestScene.h"
#include "AbstractSceneTemplate.h"
#include <cstdlib>
#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <memory>
#include <shaders/ShaderProgram.h>
#include <transformations/IGroupedTransformation.h>
#include <transformations/IRotation.h>
#include <transformations/IScale.h>
#include <transformations/ITranslation.h>
#include <vector>

#include <cmath>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/trigonometric.hpp>
#include <others/WallclockUtils.h>
#include <string>

#include <constants/MouseButtonActions.h>
#include <constants/MouseButtonCodes.h>
#include <lighting/LightingManager.h>

using namespace std::string_literals;

/**
 * @brief Number of torchbugs in the scene.
 */
constexpr int TORCHBUGS_COUNT = 20;

/**
 * @brief X-coordinate of the moon.
 */
constexpr float MOON_X_COORDINATE = 20.0f;

/**
 * @brief Y-coordinate of the moon.
 */
constexpr float MOON_Y_COORDINATE = 20.0f;

ForestScene::ForestScene(
        int windowWidth, int windowHeight)
    : AbstractSceneTemplate{windowWidth, windowHeight}, m_bushShaderProgram{},
      m_clockShaderProgram{}, m_plainShaderProgram{}, m_treeShaderProgram{},
      m_torchbugs{}, m_moonTranslation{nullptr}, m_useFlashlight{false},
      m_updatedSkyboxShader{false} {
    // create shader programs
    this->m_plainShaderProgram = &this->addShaderProgramFromShaderFiles(
            "tree_scene\\plain.vert", "_templates\\lighting.frag", false);
    this->m_treeShaderProgram = &this->addShaderProgramFromShaderFiles(
            "tree_scene\\tree.vert", "_templates\\lighting.frag", false);
    this->m_bushShaderProgram = &this->addShaderProgramFromShaderFiles(
            "tree_scene\\bush.vert", "_templates\\lighting.frag", false);
    this->m_clockShaderProgram = &this->addShaderProgramFromShaderFiles(
            "wallclock_scene\\clock.vert", "_templates\\lighting.frag", false);
    ShaderProgram& torchbugAndMoonShaderProgram =
            this->addShaderProgramFromShaderFiles("_templates\\basic.vert",
                    "_templates\\lighting.frag", false);

    // create plain
    DrawableObject& plainObj = this->addDrawableObjectFromKnownModel(
            false, KnownModels::PLAIN, *this->m_plainShaderProgram);
    ScalePtr plainScale = plainObj.getTransformation()->addNewScale();
    plainScale->setScaleTo(100.f, 100.f, 100.f);

    // create clock
    DrawableObject& clock = this->addDrawableObjectFromKnownModel(
            true, KnownModels::CLOCK, *this->m_clockShaderProgram);
    TranslationPtr clockTranslation =
            clock.getTransformation()->addNewTranslation();
    ScalePtr clockScale = clock.getTransformation()->addNewScale();

    clockTranslation->move(0.0f, 8.0f, 0.0f);
    clockScale->setScaleTo(-3.0f, 3.0f, 3.0f);

    // create forest
    this->createRandomTrees(100);
    this->createRandomBushes(50);
    this->createRandomTorchbugs(TORCHBUGS_COUNT, torchbugAndMoonShaderProgram);

    // create moon
    DrawableObject& moonObj = this->addDrawableObjectFromKnownModel(
            false, KnownModels::MOON, torchbugAndMoonShaderProgram);
    this->m_moonTranslation = moonObj.getTransformation()->addNewTranslation();
}

void ForestScene::updateSceneContents(
        float deltaT) {
    glm::vec3 cameraPos = this->getCamera()->getCameraPosition();
    this->m_moonTranslation->translateTo(
            MOON_X_COORDINATE + cameraPos.x, MOON_Y_COORDINATE, cameraPos.z);

    this->drawTorchbugs(deltaT);
    this->drawClock(deltaT);
}

void ForestScene::createRandomTrees(
        const int treesCount) {
    for (int i = 0; i < treesCount; i++) {
        float scaleXZ = (float)(rand() % 20 + 80) / 100;
        float scaleY = (float)(rand() % 20 + 80) / 100;
        float positionX = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);
        float positionZ = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);

        DrawableObject& drawableTree = this->addDrawableObjectFromKnownModel(
                true, KnownModels::TREE, *this->m_treeShaderProgram);
        TranslationPtr translation =
                drawableTree.getTransformation()->addNewTranslation();
        ScalePtr scale = drawableTree.getTransformation()->addNewScale();

        translation->translateTo(positionX, 0.0f, positionZ);
        scale->setScaleTo(scaleXZ, scaleY, scaleXZ);
    }
}

void ForestScene::createRandomBushes(
        const int bushesCount) {
    for (int i = 0; i < bushesCount; i++) {
        float scaleX = (float)(rand() % 20 + 80) / 100;
        float scaleY = (float)(rand() % 20 + 80) / 100;
        float positionX = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);
        float positionZ = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);

        DrawableObject& drawableBush = this->addDrawableObjectFromKnownModel(
                true, KnownModels::BUSH, *this->m_bushShaderProgram);
        TranslationPtr translation =
                drawableBush.getTransformation()->addNewTranslation();
        ScalePtr scale = drawableBush.getTransformation()->addNewScale();

        translation->translateTo(positionX, 0.0f, positionZ);
        scale->setScaleTo(scaleX, scaleY, scaleX);
    }
}

void ForestScene::drawClock(
        float deltaT) {
    time_t currentTime = getCurrentTime();
    int seconds = convertTimeTtoSeconds(currentTime);
    int minutes = convertTimeTtoMinutes(currentTime);
    int hours = convertTimeTtoHours(currentTime);

    this->m_clockShaderProgram->setSupplementalUniformMatrix(
            SECONDS_PIN_SHADER_MATRIX_NAME,
            getSecondsPinRotationMatrix(seconds));
    this->m_clockShaderProgram->setSupplementalUniformMatrix(
            MINUTES_PIN_SHADER_MATRIX_NAME,
            getMinutesPinRotationMatrix(minutes, seconds));
    this->m_clockShaderProgram->setSupplementalUniformMatrix(
            HOURS_PIN_SHADER_MATRIX_NAME,
            getHoursPinRotationMatrix(hours, minutes, seconds));
}

void ForestScene::drawTorchbugs(
        float deltaT) {
    int i = 0;
    for (TorchbugData& torchbugData : this->m_torchbugs) {
        torchbugData.localTranslation->translateTo(
                0.0f, sinf(glm::radians(torchbugData.phaseAngle_deg)), 0.0f);
        torchbugData.phaseAngle_deg += 10 * deltaT;

        glm::vec3 worldLocation =
                torchbugData.torchbug->getTransformation()->getMatrix()
                * glm::vec4{glm::vec3{0.0f}, 1.0f};

        for (ShaderProgram* shaderProgram : {this->m_bushShaderProgram,
                     this->m_clockShaderProgram, this->m_plainShaderProgram,
                     this->m_treeShaderProgram}) {
            LightingManager::PointLights::setLightPosition(
                    *shaderProgram, i, worldLocation);
        }
        i += 1;
    }
}

void ForestScene::createRandomTorchbugs(
        int count, ShaderProgram& torchbugsShaderProgram) {
    for (int i = 0; i < count; i++) {
        float positionX = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);
        float positionY = (float)(rand() % 3) + 1;
        float positionZ = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);

        DrawableObject& torchbug = this->addDrawableObjectFromKnownModel(
                true, KnownModels::SUN, torchbugsShaderProgram);
        TranslationPtr worldTranslation =
                torchbug.getTransformation()->addNewTranslation();
        TranslationPtr localTranslation =
                torchbug.getTransformation()->addNewTranslation();
        ScalePtr scale = torchbug.getTransformation()->addNewScale();
        worldTranslation->translateTo(positionX, positionY, positionZ);
        scale->setScaleTo(0.02f, 0.02f, 0.02f);

        this->m_torchbugs.push_back(TorchbugData{
                &torchbug, (float)(rand() % 360), localTranslation});
    }
}

void ForestScene::handleMouseClick(
        MouseButtonCodes button, MouseButtonActions action,
        KeyModifierFlags mode) {
    if (action == MouseButtonActions::PRESSED) {
        switch (button) {
            case MouseButtonCodes::RIGHT_BUTTON:
                this->m_useFlashlight = !this->m_useFlashlight;

                for (ShaderProgram* shaderProgram :
                        {this->m_bushShaderProgram, this->m_clockShaderProgram,
                                this->m_plainShaderProgram,
                                this->m_treeShaderProgram}) {
                    LightingManager::CameraSpotLight::enable(
                            *shaderProgram, this->m_useFlashlight);
                }
                break;
        }
    }

    AbstractSceneTemplate::handleMouseClick(button, action, mode);
}

void ForestScene::updateSkyboxShaderProgram(
        float deltaT) {
    if (!this->m_updatedSkyboxShader) {
        this->getSkyboxShaderProgram()->setSupplementalUniformVector(
                "ambientFactors", glm::vec3{0.1f});
        this->m_updatedSkyboxShader = true;
    }
}

void ForestScene::initializeLights() {
    for (ShaderProgram* shaderProgram :
            {this->m_bushShaderProgram, this->m_clockShaderProgram,
                    this->m_plainShaderProgram, this->m_treeShaderProgram}) {
        LightingManager::PointLights::setLightsCount(
                *shaderProgram, TORCHBUGS_COUNT);
        LightingManager::DirectedLights::setLightsCount(*shaderProgram, 1);
        LightingManager::CameraSpotLight::enable(
                *shaderProgram, this->m_useFlashlight);
        LightingManager::setAmbientFactors(*shaderProgram, glm::vec3{0.15f});

        // define torchbug lights
        for (int i = 0; i < TORCHBUGS_COUNT; i++) {
            LightingManager::PointLights::setLightAttenuation(
                    *shaderProgram, i, 1.0f, 0.8f, 0.2f);
            LightingManager::PointLights::setLightColor(
                    *shaderProgram, i, glm::vec3{0.6f, 0.3f, 0.0f});
            LightingManager::PointLights::setLightShininessExponent(
                    *shaderProgram, i, 4.0f);
            LightingManager::PointLights::setLightSpecularFlag(*shaderProgram,
                    i, shaderProgram != this->m_plainShaderProgram);
            LightingManager::PointLights::setLightBlinnFlag(*shaderProgram, i,
                    shaderProgram != this->m_plainShaderProgram);
        }
        // define directed moon light
        LightingManager::DirectedLights::setLightDirection(
                *shaderProgram, 0, glm::vec3{-1.0f, -1.0f, 0.0f});
        LightingManager::DirectedLights::setLightColor(
                *shaderProgram, 0, glm::vec3{0.2f, 0.18f, 0.18f});
        LightingManager::DirectedLights::setLightShininessExponent(
                *shaderProgram, 0, 128.0f);
        LightingManager::DirectedLights::setLightSpecularFlag(
                *shaderProgram, 0, shaderProgram != this->m_plainShaderProgram);
        LightingManager::DirectedLights::setLightBlinnFlag(
                *shaderProgram, 0, false);

        // define spotlight
        LightingManager::CameraSpotLight::setCutoffAngles(
                *shaderProgram, 5.0f, 25.0f);
        LightingManager::CameraSpotLight::setAttenuation(
                *shaderProgram, 1.0f, 0.05f, 0.01f);
        LightingManager::CameraSpotLight::setColor(
                *shaderProgram, glm::vec3{0.7f, 0.7f, 1.0f});
        LightingManager::CameraSpotLight::setShininessExponent(
                *shaderProgram, 2.0f);
        LightingManager::CameraSpotLight::setSpecularFlag(*shaderProgram, true);
        LightingManager::CameraSpotLight::setBlinnFlag(*shaderProgram, false);
    }
}
