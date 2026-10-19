// TriangleScene.cpp - Contains definition of TriangleScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <scenes/TriangleScene.h>

#include <drawables/DrawableObject.h>
#include <drawables/Model.h>
#include <drawables/ModelManager.h>
#include <memory>
#include <scenes/IScene.h>
#include <shaders/FragmentShader.h>
#include <shaders/ShaderProgram.h>
#include <shaders/VertexShader.h>
#include <transformations/Rotation.h>
#include <transformations/Scale.h>
#include <transformations/Translation.h>

#include <cameras/CameraCommonSettings.h>
#include <cameras/PerspectiveCamera.h>

TriangleScene::TriangleScene()
    : IScene{}, m_program{}, m_rotation{}, m_translation{}, m_triangle{},
      m_cameraController{}, m_camera{} {
    Model& triangleModel = ModelManager::getModel(AvailableModels::TRIANGLE);

    this->m_program = std::make_unique<ShaderProgram>(
            ShaderProgram::createFromShaderFiles("basic.vert", "basic.frag"));
    this->m_triangle = std::make_unique<DrawableObject>(triangleModel);

    this->m_rotation =
            this->m_triangle->getTransformation().addNewRotation(0, 0, 1);
    this->m_translation =
            this->m_triangle->getTransformation().addNewTranslation();

    std::shared_ptr<CameraCommonSettings> commonSettings =
            std::make_shared<CameraCommonSettings>();

    this->m_camera = std::make_unique<PerspectiveCamera>(commonSettings, 1.0f);

    this->m_camera->registerCameraUpdateListener(
            this->m_program->asCameraUpdateListener());
}

void TriangleScene::draw(
        const float deltaT) {
    float angle = 90;
    this->m_rotation->setAngle(angle);
    this->m_translation->translateTo(0.5f, 0, 0);

    this->m_camera->update(this->m_cameraController.getMovementDirection(),
            this->m_cameraController.getHorizontalRotationIncrement(),
            this->m_cameraController.getVerticalRotationIncrement(), deltaT);
    this->m_triangle->draw(*this->m_program);
}

void TriangleScene::handleMouseMovement(
        int cursorDeltaX, int cursorDeltaY) {
    this->m_cameraController.handleMouseMove(cursorDeltaX, cursorDeltaY);
}

void TriangleScene::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {
    this->m_cameraController.handleKeyPresses(button, action, mode);
}

void TriangleScene::handleWindowResize(
        int width, int height) {
    this->m_camera->setAspectRatio(width, height);
}
