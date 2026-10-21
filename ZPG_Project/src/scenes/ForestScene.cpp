// ForestScene.cpp - Contains definition of ForestScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <scenes/ForestScene.h>

#include <cstdlib>
#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <memory>
#include <scenes/IScene.h>
#include <shaders/ShaderProgram.h>
#include <transformations/IGroupedTransformation.h>
#include <transformations/IRotation.h>
#include <transformations/IScale.h>
#include <transformations/ITranslation.h>
#include <vector>

#include <resources/models/bushes.h>
#include <resources/models/clock.h>
#include <resources/models/plain.h>
#include <resources/models/tree.h>

#include <cameras/CameraCommonSettings.h>
#include <cameras/PerspectiveCamera.h>
#include <others/WallclockUtils.h>

ForestScene::ForestScene()
    : m_trees{}, m_bushes{}, m_plain{}, m_plainShaderProgram{},
      m_treesShaderProgram{}, m_bushesShaderProgram{}, m_cameraController{},
      m_camera{}, m_clock{}, m_clockShaderProgram{} {
    // create plain
    this->m_plain = DrawableObjectFactory::createDrawableObjectFromVerticesData(
            plain, sizeof(plain) / sizeof(plain[0]), 2);

    TranslationPtr plainTranslation =
            this->m_plain->getTransformation()->addNewTranslation();
    ScalePtr plainScale = this->m_plain->getTransformation()->addNewScale();

    plainTranslation->move(0.0f, -0.2f, 0.0f);
    plainScale->setScaleTo(100.f, 100.f, 100.f);

    // create clock
    this->m_clock = DrawableObjectFactory::createDrawableObjectFromVerticesData(
            clockModel, sizeof(clockModel) / sizeof(clockModel[0]), 3);

    TranslationPtr clockTranslation =
            this->m_clock->getTransformation()->addNewTranslation();
    ScalePtr clockScale = this->m_clock->getTransformation()->addNewScale();

    clockTranslation->move(0.0f, 0.5f, 0.0f);
    clockScale->setScaleTo(-0.25f, 0.25f, 0.25f);

    // create forest
    this->createRandomTrees(100);
    this->createRandomBushes(50);

    // create shader programs
    this->m_plainShaderProgram = ShaderProgram::createFromShaderFiles(
            "tree_scene\\plain.vert", "_templates\\basic.frag");
    this->m_treesShaderProgram = ShaderProgram::createFromShaderFiles(
            "tree_scene\\tree.vert", "_templates\\basic.frag");
    this->m_bushesShaderProgram = ShaderProgram::createFromShaderFiles(
            "tree_scene\\bush.vert", "_templates\\basic.frag");
    this->m_clockShaderProgram = ShaderProgram::createFromShaderFiles(
            "wallclock_scene\\clock.vert", "_templates\\basic.frag");

    // add camera
    std::shared_ptr<CameraCommonSettings> commonSettings =
            std::make_shared<CameraCommonSettings>();
    this->m_camera = std::make_unique<PerspectiveCamera>(commonSettings, 1.0f);

    this->m_camera->registerCameraUpdateListener(
            this->m_plainShaderProgram->asCameraUpdateListener());
    this->m_camera->registerCameraUpdateListener(
            this->m_treesShaderProgram->asCameraUpdateListener());
    this->m_camera->registerCameraUpdateListener(
            this->m_bushesShaderProgram->asCameraUpdateListener());
    this->m_camera->registerCameraUpdateListener(
            this->m_clockShaderProgram->asCameraUpdateListener());
}

void ForestScene::draw(
        const float deltaT) {
    for (DrawableObjectPtr& ptr : this->m_trees) {
        ptr->draw(*this->m_treesShaderProgram);
    }
    for (DrawableObjectPtr& ptr : this->m_bushes) {
        ptr->draw(*this->m_bushesShaderProgram);
    }
    this->m_plain->draw(*this->m_plainShaderProgram);
    this->drawClock(deltaT);

    this->m_camera->update(this->m_cameraController.getMovementDirection(),
            this->m_cameraController.getHorizontalRotationIncrement(),
            this->m_cameraController.getVerticalRotationIncrement(), deltaT);
}

void ForestScene::handleMouseMovement(
        int cursorDeltaX, int cursorDeltaY) {
    this->m_cameraController.handleMouseMove(cursorDeltaX, cursorDeltaY);
}

void ForestScene::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {
    this->m_cameraController.handleKeyPresses(button, action, mode);
}

void ForestScene::handleWindowResize(
        int width, int height) {
    this->m_camera->setAspectRatio(width, height);
}

void ForestScene::createRandomTrees(
        const int treesCount) {
    for (int i = 0; i < treesCount; i++) {
        float scaleX = (float)(rand() % 4 + 2) / 100;
        float scaleY = (float)(rand() % 8 + 2) / 100;
        float positionX =
                (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 100) / 100 * 3;
        float positionZ =
                (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 100) / 100 * 3;

        this->m_trees.push_back(
                DrawableObjectFactory::createDrawableObjectFromVerticesData(
                        tree, sizeof(tree) / sizeof(tree[0]), 2));
        DrawableObject* drawableTree = this->m_trees.back().get();
        TranslationPtr translation =
                drawableTree->getTransformation()->addNewTranslation();
        ScalePtr scale = drawableTree->getTransformation()->addNewScale();

        translation->translateTo(positionX, 0.0f, positionZ);
        scale->setScaleTo(scaleX, scaleY, scaleX);
    }
}

void ForestScene::createRandomBushes(
        const int bushesCount) {
    for (int i = 0; i < bushesCount; i++) {
        float scaleX = (float)(rand() % 5 + 2) / 100;
        float scaleY = (float)(rand() % 10 + 2) / 100;
        float positionX =
                (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 100) / 100 * 3;
        float positionZ =
                (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 100) / 100 * 3;

        this->m_bushes.push_back(
                DrawableObjectFactory::createDrawableObjectFromVerticesData(
                        bushes, sizeof(bushes) / sizeof(bushes[0]), 2));
        DrawableObject* drawableBush = this->m_bushes.back().get();
        TranslationPtr translation =
                drawableBush->getTransformation()->addNewTranslation();
        ScalePtr scale = drawableBush->getTransformation()->addNewScale();

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

    m_pinsRotations["secondsPinTransformation"] =
            getSecondsPinRotationMatrix(seconds);
    m_pinsRotations["minutesPinTransformation"] =
            getMinutesPinRotationMatrix(minutes, seconds);
    m_pinsRotations["hoursPinTransformation"] =
            getHoursPinRotationMatrix(hours, minutes, seconds);

    this->m_clockShaderProgram->setSupplementalUniformMatrices(
            this->m_pinsRotations);
    this->m_clock->draw(*this->m_clockShaderProgram);
}
