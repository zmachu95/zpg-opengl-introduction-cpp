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
#include <transformations/IGroupedTransformation.h>

LightingTestScene::LightingTestScene(
        int windowWidth, int windowHeight)
    : AbstractSceneTemplate{
              LightingTestScene::createCamera(windowWidth, windowHeight),
              std::unique_ptr<DrawableObject>{}},
      m_shaderProgram{}, m_initializedPointLight{false} {
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
        float deltaT) {
    this->initializeShaderPrograms();
}

void LightingTestScene::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {
    if ((char)mode & (char)KeyModifierFlags::CTRL) {
        switch (button) {
            case KeyCodes::KEY_KP_1:
                this->m_shaderProgram->setSupplementalUniformVector(
                        "pointLights[0].color", glm::vec3{0.0f});
                this->m_shaderProgram->setSupplementalUniformBoolValue(
                        "pointLights[0].useSpecular", false);
                this->m_shaderProgram->setSupplementalUniformBoolValue(
                        "pointLights[0].useBlinn", false);
                return;
            case KeyCodes::KEY_KP_2:
                this->m_shaderProgram->setSupplementalUniformVector(
                        "pointLights[0].color", glm::vec3{1.0f});
                this->m_shaderProgram->setSupplementalUniformBoolValue(
                        "pointLights[0].useSpecular", false);
                this->m_shaderProgram->setSupplementalUniformBoolValue(
                        "pointLights[0].useBlinn", false);
                return;
            case KeyCodes::KEY_KP_3:
                this->m_shaderProgram->setSupplementalUniformVector(
                        "pointLights[0].color", glm::vec3{1.0f});
                this->m_shaderProgram->setSupplementalUniformBoolValue(
                        "pointLights[0].useSpecular", true);
                this->m_shaderProgram->setSupplementalUniformBoolValue(
                        "pointLights[0].useBlinn", false);
                return;
            case KeyCodes::KEY_KP_4:
                this->m_shaderProgram->setSupplementalUniformVector(
                        "pointLights[0].color", glm::vec3{1.0f});
                this->m_shaderProgram->setSupplementalUniformBoolValue(
                        "pointLights[0].useSpecular", true);
                this->m_shaderProgram->setSupplementalUniformBoolValue(
                        "pointLights[0].useBlinn", true);
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

void LightingTestScene::initializeShaderPrograms() {
    if (!this->m_initializedPointLight) {
        this->m_shaderProgram->setSupplementalUniformIntValue(
                "pointLightsCount", 1);
        this->m_shaderProgram->setSupplementalUniformVector(
                "ambientFactors", glm::vec3{0.1f});
        this->m_shaderProgram->setSupplementalUniformVector(
                "pointLights[0].color", glm::vec3{0.0f});
        this->m_shaderProgram->setSupplementalUniformFloatValue(
                "pointLights[0].shininessExponent", 4.0f);
        this->m_shaderProgram->setSupplementalUniformFloatValue(
                "pointLights[0].attConstant", 1.0f);
        this->m_shaderProgram->setSupplementalUniformFloatValue(
                "pointLights[0].attLinear", 0.0f);
        this->m_shaderProgram->setSupplementalUniformFloatValue(
                "pointLights[0].attQuadratic", 0.0f);

        this->m_initializedPointLight = true;
    }
}
