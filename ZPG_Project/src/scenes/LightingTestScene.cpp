// LightingTestScene.cpp - Contains definition of LightingTestScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "LightingTestScene.h"
#include "AbstractSceneTemplate.h"

#include <drawables/DrawableObject.h>
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
#include <resources/models/sphere.h>
#include <transformations/IGroupedTransformation.h>

LightingTestScene::LightingTestScene(
        int windowWidth, int windowHeight)
    : AbstractSceneTemplate{
              LightingTestScene::createCamera(windowWidth, windowHeight),
              std::unique_ptr<DrawableObject>{}},
      m_spheres{}, m_ambientShaderProgram{}, m_lambertShaderProgram{},
      m_phongShaderProgram{}, m_blinnShaderProgram{} {
    this->m_ambientShaderProgram =
            &this->addShaderProgramFromShaderFiles("_templates\\basic.vert",
                    "lighting_test_scene\\ambient.frag", false);
    this->m_lambertShaderProgram =
            &this->addShaderProgramFromShaderFiles("_templates\\basic.vert",
                    "lighting_test_scene\\lambert.frag", false);
    this->m_phongShaderProgram = &this->addShaderProgramFromShaderFiles(
            "_templates\\basic.vert", "lighting_test_scene\\phong.frag", false);
    this->m_blinnShaderProgram = &this->addShaderProgramFromShaderFiles(
            "_templates\\basic.vert", "lighting_test_scene\\blinn.frag", false);

    const float sphereOffset = 2.0f;
    for (size_t i = 0; i < this->m_spheres.size(); i++) {
        this->m_spheres[i] = &this->addDrawableObjectFromVerticesData(false,
                sphere, sizeof(sphere) / sizeof(sphere[0]), 2, false,
                *this->m_ambientShaderProgram);
        ScalePtr sphereScale =
                this->m_spheres[i]->getTransformation()->addNewScale();
        sphereScale->setScaleTo(0.1f, 0.1f, 0.1f);

        TranslationPtr sphereTranslation =
                this->m_spheres[i]->getTransformation()->addNewTranslation();

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
                for (DrawableObject* sph : this->m_spheres) {
                    this->changeShaderProgram(
                            sph, *this->m_ambientShaderProgram);
                }
                return;
            case KeyCodes::KEY_KP_2:
                for (DrawableObject* sph : this->m_spheres) {
                    this->changeShaderProgram(
                            sph, *this->m_lambertShaderProgram);
                }
                return;
            case KeyCodes::KEY_KP_3:
                for (DrawableObject* sph : this->m_spheres) {
                    this->changeShaderProgram(sph, *this->m_phongShaderProgram);
                }
                return;
            case KeyCodes::KEY_KP_4:
                for (DrawableObject* sph : this->m_spheres) {
                    this->changeShaderProgram(sph, *this->m_blinnShaderProgram);
                }
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
