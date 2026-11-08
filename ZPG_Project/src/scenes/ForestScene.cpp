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
#include <resources/models/skybox.h>
#include <resources/models/tree.h>

#include <cameras/CameraCommonSettings.h>
#include <cameras/PerspectiveCamera.h>
#include <cmath>
#include <glm/trigonometric.hpp>
#include <others/WallclockUtils.h>
#include <resources/models/sun.h>
#include <string>
#include <textures/TextureFactory.h>

using namespace std::string_literals;

ForestScene::ForestScene()
    : m_trees{}, m_bushes{}, m_plain{}, m_plainShaderProgram{},
      m_treesShaderProgram{}, m_bushesShaderProgram{}, m_cameraController{},
      m_camera{}, m_clock{}, m_clockShaderProgram{}, m_skybox{},
      m_skyboxProgram{}, m_torchbugsShaderProgram{}, m_torchbugPhaseAngles{},
      m_torchbugLocalTranslations{} {
    // create plain
    this->m_plain = DrawableObjectFactory::createDrawableObjectFromVerticesData(
            plain, sizeof(plain) / sizeof(plain[0]), 2, false);
    ScalePtr plainScale = this->m_plain->getTransformation()->addNewScale();
    plainScale->setScaleTo(100.f, 100.f, 100.f);

    // create clock
    this->m_clock = DrawableObjectFactory::createDrawableObjectFromVerticesData(
            clockModel, sizeof(clockModel) / sizeof(clockModel[0]), 3, false);

    TranslationPtr clockTranslation =
            this->m_clock->getTransformation()->addNewTranslation();
    ScalePtr clockScale = this->m_clock->getTransformation()->addNewScale();

    clockTranslation->move(0.0f, 8.0f, 0.0f);
    clockScale->setScaleTo(-3.0f, 3.0f, 3.0f);

    // create skybox
    this->m_skybox =
            DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    skyboxVertices,
                    sizeof(skyboxVertices) / sizeof(skyboxVertices[0]), 1,
                    false);
    this->m_skybox->addTexture(TextureFactory::createDefaultSkyBoxTexture());

    // create forest
    this->createRandomTrees(100);
    this->createRandomBushes(50);
    this->createRandomTorchbugs(10);

    // create shader programs
    this->m_plainShaderProgram = ShaderProgram::createFromShaderFiles(
            "tree_scene\\plain.vert", "tree_scene\\lambert.frag", false);
    this->m_treesShaderProgram = ShaderProgram::createFromShaderFiles(
            "tree_scene\\tree.vert", "tree_scene\\lambert.frag", false);
    this->m_bushesShaderProgram = ShaderProgram::createFromShaderFiles(
            "tree_scene\\bush.vert", "tree_scene\\lambert.frag", false);
    this->m_clockShaderProgram = ShaderProgram::createFromShaderFiles(
            "wallclock_scene\\clock.vert", "tree_scene\\lambert.frag", false);
    this->m_skyboxProgram = ShaderProgram::createFromShaderFiles(
            "_templates\\skybox.vert", "tree_scene\\skybox.frag", true);
    this->m_torchbugsShaderProgram = ShaderProgram::createFromShaderFiles(
            "_templates\\basic.vert", "tree_scene\\ambient.frag", false);

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
    this->m_camera->registerCameraUpdateListener(
            this->m_skyboxProgram->asCameraUpdateListener());
    this->m_camera->registerCameraUpdateListener(
            this->m_torchbugsShaderProgram->asCameraUpdateListener());
}

void ForestScene::draw(
        const float deltaT) {
    this->drawTorchbugs(deltaT);

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
        float scaleXZ = (float)(rand() % 20 + 80) / 100;
        float scaleY = (float)(rand() % 20 + 80) / 100;
        float positionX = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);
        float positionZ = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);

        this->m_trees.push_back(
                DrawableObjectFactory::createDrawableObjectFromVerticesData(
                        tree, sizeof(tree) / sizeof(tree[0]), 2, false));
        DrawableObject* drawableTree = this->m_trees.back().get();
        TranslationPtr translation =
                drawableTree->getTransformation()->addNewTranslation();
        ScalePtr scale = drawableTree->getTransformation()->addNewScale();

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

        this->m_bushes.push_back(
                DrawableObjectFactory::createDrawableObjectFromVerticesData(
                        bushes, sizeof(bushes) / sizeof(bushes[0]), 2, false));
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

void ForestScene::drawSkybox(
        const float deltaT) {
    this->m_skybox->draw(*this->m_skyboxProgram);
}

void ForestScene::drawTorchbugs(
        float deltaT) {
    int i = 0;
    for (DrawableObjectPtr& torchbug : this->m_torchbugs) {
        float phaseAngle = this->m_torchbugPhaseAngles[i];
        TranslationPtr localTranslation = this->m_torchbugLocalTranslations[i];
        localTranslation->translateTo(
                0.0f, sinf(glm::radians(phaseAngle)), 0.0f);
        this->m_torchbugPhaseAngles[i] += 10 * deltaT;

        glm::vec3 worldLocation = torchbug->getTransformation()->getMatrix()
                                  * glm::vec4{glm::vec3{0.0f}, 1.0f};
        this->m_torchbugLocations["lightPositions["s + std::to_string(i)
                                  + "]"] = worldLocation;

        torchbug->draw(*this->m_torchbugsShaderProgram);
        i += 1;
    }

    this->m_plainShaderProgram->setSupplementalUniformVectors(
            this->m_torchbugLocations);
    this->m_treesShaderProgram->setSupplementalUniformVectors(
            this->m_torchbugLocations);
    this->m_bushesShaderProgram->setSupplementalUniformVectors(
            this->m_torchbugLocations);
    this->m_clockShaderProgram->setSupplementalUniformVectors(
            this->m_torchbugLocations);
}

void ForestScene::createRandomTorchbugs(
        int count) {
    for (int i = 0; i < count; i++) {
        float positionX = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);
        float positionY = (float)(rand() % 3) + 1;
        float positionZ = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);

        DrawableObjectPtr torchbug =
                DrawableObjectFactory::createDrawableObjectFromVerticesData(
                        sun, sizeof(sun) / sizeof(sun[0]), 3, false);
        TranslationPtr translation =
                torchbug->getTransformation()->addNewTranslation();
        this->m_torchbugLocalTranslations.push_back(
                torchbug->getTransformation()->addNewTranslation());
        ScalePtr scale = torchbug->getTransformation()->addNewScale();
        translation->translateTo(positionX, positionY, positionZ);
        scale->setScaleTo(0.02f, 0.02f, 0.02f);

        this->m_torchbugs.push_back(std::move(torchbug));
        this->m_torchbugPhaseAngles.push_back((float)(rand() % 360));
    }
}
