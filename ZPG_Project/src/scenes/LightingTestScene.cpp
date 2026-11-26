// LightingTestScene.cpp - Contains definition of LightingTestScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "LightingTestScene.h"
#include "AbstractSceneTemplate.h"

#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <memory>
#include <scenes/IScene.h>
#include <shaders/ShaderProgram.h>
#include <transformations/IRotation.h>
#include <transformations/IScale.h>
#include <transformations/ITranslation.h>

#include <cameras/CameraCommonSettings.h>
#include <cameras/PerspectiveCamera.h>

#include <constants/KeyCodes.h>
#include <constants/KeyModifiers.h>
#include <glm/ext/vector_float3.hpp>
#include <lighting/LightingManager.h>
#include <transformations/IGroupedTransformation.h>

LightingTestScene::LightingTestScene(
        int windowWidth, int windowHeight)
    : AbstractSceneTemplate{
              LightingTestScene::createCamera(windowWidth, windowHeight),
              std::unique_ptr<DrawableObject>{}},
      m_shaderProgram{} {
    this->m_shaderProgram = &this->addShaderProgramFromShaderFiles(
            "lighting_test_scene\\spheres.vert", "_templates\\lighting.frag",
            false);

    const float sphereOffset = 2.0f;
    for (size_t i = 0; i < 4; i++) {
        DrawableObject& sphereObj = this->addDrawableObjectFromKnownModel(
                false, KnownModels::SPHERE, *this->m_shaderProgram);
        ScalePtr sphereScale = sphereObj.getTransformation()->addNewScale();
        sphereScale->setScaleTo(0.1f, 0.1f, 0.1f);

        TranslationPtr sphereTranslation =
                sphereObj.getTransformation()->addNewTranslation();

        switch (i) {
            case 0:
                sphereTranslation->translateTo(-sphereOffset, 0.0f, 0.0f);
                break;
            case 1:
                sphereTranslation->translateTo(sphereOffset, 0.0f, 0.0f);
                break;
            case 2:
                sphereTranslation->translateTo(0.0f, -sphereOffset, 0.0f);
                break;
            case 3:
                sphereTranslation->translateTo(0.0f, sphereOffset, 0.0f);
                break;
        }
    }
}

void LightingTestScene::updateSceneContents(
        float deltaT) {}

void LightingTestScene::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {
    if ((char)mode & (char)KeyModifierFlags::CTRL) {
        switch (button) {
            case KeyCodes::KEY_KP_1:
                LightingManager::PointLights::setLightColor(
                        *this->m_shaderProgram, 0, glm::vec3{0.0f});
                LightingManager::PointLights::setLightSpecularFlag(
                        *this->m_shaderProgram, 0, false);
                LightingManager::PointLights::setLightBlinnFlag(
                        *this->m_shaderProgram, 0, false);
                return;
            case KeyCodes::KEY_KP_2:
                LightingManager::PointLights::setLightColor(
                        *this->m_shaderProgram, 0, glm::vec3{1.0f});
                LightingManager::PointLights::setLightSpecularFlag(
                        *this->m_shaderProgram, 0, false);
                LightingManager::PointLights::setLightBlinnFlag(
                        *this->m_shaderProgram, 0, false);
                return;
            case KeyCodes::KEY_KP_3:
                LightingManager::PointLights::setLightColor(
                        *this->m_shaderProgram, 0, glm::vec3{1.0f});
                LightingManager::PointLights::setLightSpecularFlag(
                        *this->m_shaderProgram, 0, true);
                LightingManager::PointLights::setLightBlinnFlag(
                        *this->m_shaderProgram, 0, false);
                return;
            case KeyCodes::KEY_KP_4:
                LightingManager::PointLights::setLightColor(
                        *this->m_shaderProgram, 0, glm::vec3{1.0f});
                LightingManager::PointLights::setLightSpecularFlag(
                        *this->m_shaderProgram, 0, true);
                LightingManager::PointLights::setLightBlinnFlag(
                        *this->m_shaderProgram, 0, true);
                return;
        }
    }

    AbstractSceneTemplate::handleKeyPresses(button, action, mode);
}

CameraPtr LightingTestScene::createCamera(
        int windowWidth, int windowHeight) {
    return std::make_unique<PerspectiveCamera>(
            std::make_shared<CameraCommonSettings>(),
            (float)windowWidth / windowHeight, glm::vec3{0.0f, 0.0f, 1.0f});
}

void LightingTestScene::initializeLights() {
    LightingManager::setAmbientFactors(*this->m_shaderProgram, glm::vec3{0.1f});
    LightingManager::PointLights::setLightsCount(*this->m_shaderProgram, 1);
    LightingManager::PointLights::setLightColor(
            *this->m_shaderProgram, 0, glm::vec3{0.0f});
    LightingManager::PointLights::setLightShininessExponent(
            *this->m_shaderProgram, 0, 4.0f);
    LightingManager::PointLights::setLightAttenuation(
            *this->m_shaderProgram, 0, 1.0f, 0.0f, 0.0f);
}
