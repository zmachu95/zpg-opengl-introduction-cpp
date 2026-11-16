// ForestScene.cpp - Contains definition of ForestScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "ForestScene.h"
#include "AbstractSceneTemplate.h"
#include <cstdlib>
#include <drawables/DrawableObject.h>
#include <memory>
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

#include <cmath>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/trigonometric.hpp>
#include <others/WallclockUtils.h>
#include <resources/models/sun.h>
#include <string>

using namespace std::string_literals;

ForestScene::ForestScene(
        int windowWidth, int windowHeight)
    : AbstractSceneTemplate{windowWidth, windowHeight}, m_clockShaderProgram{},
      m_dynamicShaderPrograms{}, m_torchbugs{} {
    // create shader programs
    ShaderProgram& plainShaderProgram = this->addShaderProgramFromShaderFiles(
            "tree_scene\\plain.vert", "tree_scene\\lambert.frag", false);
    ShaderProgram& treeShaderProgram = this->addShaderProgramFromShaderFiles(
            "tree_scene\\tree.vert", "tree_scene\\lambert.frag", false);
    ShaderProgram& bushShaderProgram = this->addShaderProgramFromShaderFiles(
            "tree_scene\\bush.vert", "tree_scene\\lambert.frag", false);
    this->m_clockShaderProgram = &this->addShaderProgramFromShaderFiles(
            "wallclock_scene\\clock.vert", "tree_scene\\lambert.frag", false);
    ShaderProgram& torchbugShaderProgram =
            this->addShaderProgramFromShaderFiles("_templates\\basic.vert",
                    "tree_scene\\ambient.frag", false);
    this->m_dynamicShaderPrograms = {plainShaderProgram, treeShaderProgram,
            bushShaderProgram, *this->m_clockShaderProgram};

    // create plain
    DrawableObject& plainObj = this->addDrawableObjectFromVerticesData(false,
            plain, sizeof(plain) / sizeof(plain[0]), 2, false,
            plainShaderProgram);
    ScalePtr plainScale = plainObj.getTransformation()->addNewScale();
    plainScale->setScaleTo(100.f, 100.f, 100.f);

    // create clock
    DrawableObject& clock = this->addDrawableObjectFromVerticesData(true,
            clockModel, sizeof(clockModel) / sizeof(clockModel[0]), 3, false,
            *this->m_clockShaderProgram);
    TranslationPtr clockTranslation =
            clock.getTransformation()->addNewTranslation();
    ScalePtr clockScale = clock.getTransformation()->addNewScale();

    clockTranslation->move(0.0f, 8.0f, 0.0f);
    clockScale->setScaleTo(-3.0f, 3.0f, 3.0f);

    // create forest
    this->createRandomTrees(100, treeShaderProgram);
    this->createRandomBushes(50, bushShaderProgram);
    this->createRandomTorchbugs(10, torchbugShaderProgram);
}

void ForestScene::updateSceneContents(
        float deltaT) {
    this->drawTorchbugs(deltaT);
    this->drawClock(deltaT);
}

void ForestScene::createRandomTrees(
        const int treesCount, ShaderProgram& treeShaderProgram) {
    for (int i = 0; i < treesCount; i++) {
        float scaleXZ = (float)(rand() % 20 + 80) / 100;
        float scaleY = (float)(rand() % 20 + 80) / 100;
        float positionX = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);
        float positionZ = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);

        DrawableObject& drawableTree = this->addDrawableObjectFromVerticesData(
                true, tree, sizeof(tree) / sizeof(tree[0]), 2, false,
                treeShaderProgram);
        TranslationPtr translation =
                drawableTree.getTransformation()->addNewTranslation();
        ScalePtr scale = drawableTree.getTransformation()->addNewScale();

        translation->translateTo(positionX, 0.0f, positionZ);
        scale->setScaleTo(scaleXZ, scaleY, scaleXZ);
    }
}

void ForestScene::createRandomBushes(
        const int bushesCount, ShaderProgram& bushShaderProgram) {
    for (int i = 0; i < bushesCount; i++) {
        float scaleX = (float)(rand() % 20 + 80) / 100;
        float scaleY = (float)(rand() % 20 + 80) / 100;
        float positionX = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);
        float positionZ = (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 50)
                          + (rand() % 5);

        DrawableObject& drawableBush = this->addDrawableObjectFromVerticesData(
                true, bushes, sizeof(bushes) / sizeof(bushes[0]), 2, false,
                bushShaderProgram);
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

        for (ShaderProgram& shaderProgram : this->m_dynamicShaderPrograms) {
            shaderProgram.setSupplementalUniformVector(
                    "lightPositions["s + std::to_string(i) + "]",
                    worldLocation);
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

        DrawableObject& torchbug = this->addDrawableObjectFromVerticesData(true,
                sun, sizeof(sun) / sizeof(sun[0]), 3, false,
                torchbugsShaderProgram);
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
