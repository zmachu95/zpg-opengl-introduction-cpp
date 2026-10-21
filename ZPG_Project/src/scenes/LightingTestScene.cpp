// LightingTestScene.cpp - Contains definition of LightingTestScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <scenes/LightingTestScene.h>

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
#include <drawables/DrawableObjectFactory.h>
#include <resources/models/sphere.h>

LightingTestScene::LightingTestScene()
    : m_activeShaderProgram{}, m_ambientShaderProgram{},
      m_lambertShaderProgram{}, m_phongShaderProgram{}, m_blinnShaderProgram{},
      m_spheres{}, m_cameraController{}, m_camera{} {
    this->m_ambientShaderProgram = ShaderProgram::createFromShaderFiles(
            "_templates\\basic.vert", "lighting_test_scene\\ambient.frag");
    this->m_lambertShaderProgram = ShaderProgram::createFromShaderFiles(
            "_templates\\basic.vert", "lighting_test_scene\\lambert.frag");
    this->m_phongShaderProgram = ShaderProgram::createFromShaderFiles(
            "_templates\\basic.vert", "lighting_test_scene\\phong.frag");
    this->m_blinnShaderProgram = ShaderProgram::createFromShaderFiles(
            "_templates\\basic.vert", "lighting_test_scene\\blinn.frag");

    this->m_activeShaderProgram = this->m_ambientShaderProgram;

    const float sphereOffset = 2.0f;
    for (int i = 0; i < this->m_spheres.size(); i++) {
        this->m_spheres[i] =
                DrawableObjectFactory::createDrawableObjectFromVerticesData(
                        sphere, sizeof(sphere) / sizeof(sphere[0]), 2);
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

    std::shared_ptr<CameraCommonSettings> commonSettings =
            std::make_shared<CameraCommonSettings>();

    this->m_camera = std::make_unique<PerspectiveCamera>(
            commonSettings, 1.0f, glm::vec3{0.0f, 0.0f, 1.0f});

    this->m_camera->registerCameraUpdateListener(
            this->m_ambientShaderProgram->asCameraUpdateListener());
    this->m_camera->registerCameraUpdateListener(
            this->m_lambertShaderProgram->asCameraUpdateListener());
    this->m_camera->registerCameraUpdateListener(
            this->m_phongShaderProgram->asCameraUpdateListener());
    this->m_camera->registerCameraUpdateListener(
            this->m_blinnShaderProgram->asCameraUpdateListener());
}

void LightingTestScene::draw(
        const float deltaT) {
    for (const DrawableObjectPtr& sphere : this->m_spheres) {
        sphere->draw(*this->m_activeShaderProgram);
    }

    this->m_camera->update(this->m_cameraController.getMovementDirection(),
            this->m_cameraController.getHorizontalRotationIncrement(),
            this->m_cameraController.getVerticalRotationIncrement(), deltaT);
}

void LightingTestScene::handleMouseMovement(
        int cursorDeltaX, int cursorDeltaY) {
    this->m_cameraController.handleMouseMove(cursorDeltaX, cursorDeltaY);
}

void LightingTestScene::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {
    if ((char)mode & (char)KeyModifierFlags::CTRL) {
        switch (button) {
            case KeyCodes::KEY_KP_1:
                this->m_activeShaderProgram = this->m_ambientShaderProgram;
                return;
            case KeyCodes::KEY_KP_2:
                this->m_activeShaderProgram = this->m_lambertShaderProgram;
                return;
            case KeyCodes::KEY_KP_3:
                this->m_activeShaderProgram = this->m_phongShaderProgram;
                return;
            case KeyCodes::KEY_KP_4:
                this->m_activeShaderProgram = this->m_blinnShaderProgram;
                return;
        }
    }

    this->m_cameraController.handleKeyPresses(button, action, mode);
}

void LightingTestScene::handleWindowResize(
        int width, int height) {
    this->m_camera->setAspectRatio(width, height);
}
