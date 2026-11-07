// ShrekFionaScene.h - Contains definition of ShrekFionaScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <scenes/ShrekFionaScene.h>

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
#include <resources/models/fiona.h>
#include <resources/models/shrek.h>
#include <resources/models/skybox.h>
#include <resources/models/toilet.h>
#include <textures/ITexture.h>
#include <textures/TextureFactory.h>
#include <transformations/IGroupedTransformation.h>

ShrekFionaScene::ShrekFionaScene()
    : m_shrek{}, m_objectsProgram{}, m_camera{}, m_cameraController{},
      m_fiona{}, m_toilet{}, m_skybox{}, m_skyboxProgram{} {
    this->m_objectsProgram = ShaderProgram::createFromShaderFiles(
            "_templates\\basic.vert", "_templates\\ambient.frag", false);
    this->m_shrek = DrawableObjectFactory::createDrawableObjectFromVerticesData(
            shrekVertices, sizeof(shrekVertices) / sizeof(shrekVertices[0]), 2,
            true);
    this->m_shrek->addTexture(TextureFactory::create2dTextureFromFile(
            "shrek_fiona\\shrek.png", TexturingUnit::UNIT0));

    this->m_fiona = DrawableObjectFactory::createDrawableObjectFromVerticesData(
            fionaVertices, sizeof(fionaVertices) / sizeof(fionaVertices[0]), 2,
            true);
    this->m_fiona->addTexture(TextureFactory::create2dTextureFromFile(
            "shrek_fiona\\fiona.png", TexturingUnit::UNIT0));

    this->m_toilet =
            DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    toiletVertices,
                    sizeof(toiletVertices) / sizeof(toiletVertices[0]), 2,
                    true);
    this->m_toilet->addTexture(TextureFactory::create2dTextureFromFile(
            "shrek_fiona\\toilet.jpg", TexturingUnit::UNIT0));

    this->m_skyboxProgram = ShaderProgram::createFromShaderFiles(
            "_templates\\skybox.vert", "_templates\\skybox.frag", true);
    this->m_skybox =
            DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    skyboxVertices,
                    sizeof(skyboxVertices) / sizeof(skyboxVertices[0]), 1,
                    false);
    this->m_skybox->addTexture(TextureFactory::createDefaultSkyBoxTexture());

    TranslationPtr shrekTranslation =
            this->m_shrek->getTransformation()->addNewTranslation();
    shrekTranslation->move(2.0f, 0.0f, 0.0f);

    TranslationPtr fionaTranslation =
            this->m_fiona->getTransformation()->addNewTranslation();
    fionaTranslation->move(-2.0f, 0.0f, 0.0f);

    // add camera
    std::shared_ptr<CameraCommonSettings> commonSettings =
            std::make_shared<CameraCommonSettings>();
    this->m_camera = std::make_unique<PerspectiveCamera>(commonSettings, 1.0f);

    this->m_camera->registerCameraUpdateListener(
            this->m_objectsProgram->asCameraUpdateListener());
    this->m_camera->registerCameraUpdateListener(
            this->m_skyboxProgram->asCameraUpdateListener());
}

void ShrekFionaScene::draw(
        const float deltaT) {
    this->m_fiona->draw(*this->m_objectsProgram);
    this->m_shrek->draw(*this->m_objectsProgram);
    this->m_toilet->draw(*this->m_objectsProgram);

    this->m_camera->update(this->m_cameraController.getMovementDirection(),
            this->m_cameraController.getHorizontalRotationIncrement(),
            this->m_cameraController.getVerticalRotationIncrement(), deltaT);
}

void ShrekFionaScene::handleMouseMovement(
        int cursorDeltaX, int cursorDeltaY) {
    this->m_cameraController.handleMouseMove(cursorDeltaX, cursorDeltaY);
}

void ShrekFionaScene::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {
    this->m_cameraController.handleKeyPresses(button, action, mode);
}

void ShrekFionaScene::handleWindowResize(
        int width, int height) {
    this->m_camera->setAspectRatio(width, height);
}

void ShrekFionaScene::drawSkybox(
        const float deltaT) {
    this->m_skybox->draw(*this->m_skyboxProgram);
}
