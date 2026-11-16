// ClassroomScene.cpp - Contains definition of ClassroomScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "ClassroomScene.h"
#include "AbstractSceneTemplate.h"

#include <cameras/CameraCommonSettings.h>
#include <cameras/PerspectiveCamera.h>
#include <drawables/DrawableObject.h>
#include <memory>
#include <others/WallclockUtils.h>
#include <shaders/ShaderProgram.h>
#include <transformations/IGroupedTransformation.h>
#include <transformations/IRotation.h>
#include <transformations/IScale.h>
#include <transformations/ITranslation.h>

#include <resources/models/clock.h>
#include <resources/models/eb408/case.h>
#include <resources/models/eb408/chair.h>
#include <resources/models/eb408/door.h>
#include <resources/models/eb408/doorFrame.h>
#include <resources/models/eb408/eb408.h>
#include <resources/models/eb408/monitor.h>
#include <resources/models/eb408/table.h>
#include <resources/models/eb408/whiteboard.h>
#include <resources/models/shrek.h>
#include <resources/models/toilet.h>

#include <glm/ext/vector_float3.hpp>
#include <textures/ITexture.h>
#include <textures/TextureFactory.h>

ClassroomScene::ClassroomScene(
        int windowWidth, int windowHeight)
    : AbstractSceneTemplate{
              ClassroomScene::createCamera(windowWidth, windowHeight)},
      m_shrek{}, m_toilet{}, m_classroom{}, m_whiteboard{}, m_door{},
      m_doorFrame{}, m_teacherTable{}, m_teacherChair{}, m_teacherMonitor{},
      m_teacherCase{}, m_shaderProgram{}, m_clock{}, m_clockShaderProgram{} {
    this->m_shaderProgram = &this->addShaderProgramFromShaderFiles(
            "_templates\\basic.vert", "classroom\\lambert.frag", false);
    this->m_clockShaderProgram = &this->addShaderProgramFromShaderFiles(
            "wallclock_scene\\clock.vert", "classroom\\lambert.frag", false);

    this->initializeClassroom();

    this->createTableWithChairsAndPcs(-1.7f, 1.2f);
    this->createTableWithChairsAndPcs(-1.7f, 3.0f);
    this->createTableWithChairsAndPcs(-1.7f, 4.8f);

    this->createTableWithChairsAndPcs(0.0f, 1.2f);
    this->createTableWithChairsAndPcs(0.0f, 3.0f);
    this->createTableWithChairsAndPcs(0.0f, 4.8f);

    this->createTableWithChairsAndPcs(2.0f, 1.2f);
    this->createTableWithChairsAndPcs(2.0f, 3.0f);
    this->createTableWithChairsAndPcs(2.0f, 4.8f);
}

void ClassroomScene::updateSceneContents(
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

void ClassroomScene::createTableWithChairsAndPcs(
        float x, float z) {
    DrawableObject* newTable = &this->addDrawableObjectFromVerticesData(true,
            table, sizeof(table) / sizeof(table[0]), 2, true,
            *this->m_shaderProgram);
    newTable->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\table.png", TexturingUnit::UNIT0));
    TranslationPtr tableTranslation =
            newTable->getTransformation()->addNewTranslation();
    RotationPtr tableRotationX =
            newTable->getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    RotationPtr tableRotationZ =
            newTable->getTransformation()->addNewRotation(0.0f, 0.0f, 1.0f);
    tableTranslation->translateTo(x, 0.0f, z);
    tableRotationX->setAngle(-90.0f);
    tableRotationZ->setAngle(90.0f);

    DrawableObject* firstChair = &this->addDrawableObjectFromVerticesData(true,
            chair, sizeof(chair) / sizeof(chair[0]), 2, true,
            *this->m_shaderProgram);
    firstChair->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\chair.png", TexturingUnit::UNIT0));
    TranslationPtr firstChairTranslation =
            firstChair->getTransformation()->addNewTranslation();
    RotationPtr firstChairRotationX =
            firstChair->getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    RotationPtr firstChairRotationZ =
            firstChair->getTransformation()->addNewRotation(0.0f, 0.0f, 1.0f);
    firstChairTranslation->translateTo(x + 0.4f, 0.0f, z - 0.45f);
    firstChairRotationX->setAngle(-90.0f);
    firstChairRotationZ->setAngle(-90.0f);

    DrawableObject* secondChair = &this->addDrawableObjectFromVerticesData(true,
            chair, sizeof(chair) / sizeof(chair[0]), 2, true,
            *this->m_shaderProgram);
    secondChair->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\chair.png", TexturingUnit::UNIT0));
    TranslationPtr secondChairTranslation =
            secondChair->getTransformation()->addNewTranslation();
    RotationPtr secondChairRotationX =
            secondChair->getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    RotationPtr secondChairRotationZ =
            secondChair->getTransformation()->addNewRotation(0.0f, 0.0f, 1.0f);
    secondChairTranslation->translateTo(x + 0.4f, 0.0f, z + 0.45f);
    secondChairRotationX->setAngle(-90.0f);
    secondChairRotationZ->setAngle(-90.0f);

    DrawableObject* firstCase = &this->addDrawableObjectFromVerticesData(true,
            computerCase, sizeof(computerCase) / sizeof(computerCase[0]), 2,
            true, *this->m_shaderProgram);
    firstCase->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\case.png", TexturingUnit::UNIT0));
    TranslationPtr firstCaseTranslation =
            firstCase->getTransformation()->addNewTranslation();
    RotationPtr firstCaseRotationX =
            firstCase->getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    RotationPtr firstCaseRotationZ =
            firstCase->getTransformation()->addNewRotation(0.0f, 0.0f, 1.0f);
    ScalePtr firstCaseScale = firstCase->getTransformation()->addNewScale();
    firstCaseTranslation->translateTo(x - 0.1f, 0.0f, z - 0.65f);
    firstCaseRotationX->setAngle(-90.0f);
    firstCaseRotationZ->setAngle(90.0f);
    firstCaseScale->setScaleTo(1.2f, 1.2f, 1.2f);

    DrawableObject* secondCase = &this->addDrawableObjectFromVerticesData(true,
            computerCase, sizeof(computerCase) / sizeof(computerCase[0]), 2,
            true, *this->m_shaderProgram);
    secondCase->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\case.png", TexturingUnit::UNIT0));
    TranslationPtr secondCaseTranslation =
            secondCase->getTransformation()->addNewTranslation();
    RotationPtr secondCaseRotationX =
            secondCase->getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    RotationPtr secondCaseRotationZ =
            secondCase->getTransformation()->addNewRotation(0.0f, 0.0f, 1.0f);
    ScalePtr secondCaseScale = secondCase->getTransformation()->addNewScale();
    secondCaseTranslation->translateTo(x - 0.1f, 0.0f, z + 0.65f);
    secondCaseRotationX->setAngle(-90.0f);
    secondCaseRotationZ->setAngle(90.0f);
    secondCaseScale->setScaleTo(1.2f, 1.2f, 1.2f);

    DrawableObject* firstMonitor = &this->addDrawableObjectFromVerticesData(
            true, monitor, sizeof(monitor) / sizeof(monitor[0]), 2, true,
            *this->m_shaderProgram);
    firstMonitor->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\monitor.png", TexturingUnit::UNIT0));
    TranslationPtr firstMonitorTranslation =
            firstMonitor->getTransformation()->addNewTranslation();
    RotationPtr firstMonitorRotationX =
            firstMonitor->getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    RotationPtr firstMonitorRotationZ =
            firstMonitor->getTransformation()->addNewRotation(0.0f, 0.0f, 1.0f);
    ScalePtr firstMonitorScale =
            firstMonitor->getTransformation()->addNewScale();
    firstMonitorTranslation->translateTo(x - 0.206f, 0.664f, z - 0.45f);
    firstMonitorRotationX->setAngle(-90.0f);
    firstMonitorRotationZ->setAngle(180.0f);
    firstMonitorScale->setScaleTo(0.01f, 0.01f, 0.01f);

    DrawableObject* secondMonitor = &this->addDrawableObjectFromVerticesData(
            true, monitor, sizeof(monitor) / sizeof(monitor[0]), 2, true,
            *this->m_shaderProgram);
    secondMonitor->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\monitor.png", TexturingUnit::UNIT0));
    TranslationPtr secondMonitorTranslation =
            secondMonitor->getTransformation()->addNewTranslation();
    RotationPtr secondMonitorRotationX =
            secondMonitor->getTransformation()->addNewRotation(
                    1.0f, 0.0f, 0.0f);
    RotationPtr secondMonitorRotationZ =
            secondMonitor->getTransformation()->addNewRotation(
                    0.0f, 0.0f, 1.0f);
    ScalePtr secondMonitorScale =
            secondMonitor->getTransformation()->addNewScale();
    secondMonitorTranslation->translateTo(x - 0.206f, 0.664f, z + 0.45f);
    secondMonitorRotationX->setAngle(-90.0f);
    secondMonitorRotationZ->setAngle(180.0f);
    secondMonitorScale->setScaleTo(0.01f, 0.01f, 0.01f);
}

void ClassroomScene::initializeClassroom() {
    this->m_classroom = &this->addDrawableObjectFromVerticesData(true, eb408,
            sizeof(eb408) / sizeof(eb408[0]), 2, true, *this->m_shaderProgram);
    this->m_classroom->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\eb408.png", TexturingUnit::UNIT0));
    RotationPtr classroomRotationX =
            this->m_classroom->getTransformation()->addNewRotation(
                    1.0f, 0.0f, 0.0f);
    classroomRotationX->setAngle(-90.0f);

    this->m_clock = &this->addDrawableObjectFromVerticesData(true, clockModel,
            sizeof(clockModel) / sizeof(clockModel[0]), 3, false,
            *this->m_clockShaderProgram);
    TranslationPtr clockTranslation =
            this->m_clock->getTransformation()->addNewTranslation();
    RotationPtr clockRotation =
            this->m_clock->getTransformation()->addNewRotation(
                    0.0f, 1.0f, 0.0f);
    ScalePtr clockScale = this->m_clock->getTransformation()->addNewScale();
    clockTranslation->translateTo(-3.8f, 2.0f, 5.5f);
    clockRotation->setAngle(-90.0f);
    clockScale->setScaleTo(-0.3f, 0.3f, 0.3f);

    this->m_door = &this->addDrawableObjectFromVerticesData(true, door,
            sizeof(door) / sizeof(door[0]), 2, true, *this->m_shaderProgram);
    this->m_door->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\doorAndFrame.png", TexturingUnit::UNIT0));
    TranslationPtr doorTranslation =
            this->m_door->getTransformation()->addNewTranslation();
    RotationPtr doorRotationX =
            this->m_door->getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    doorTranslation->translateTo(-2.45f, 0.0f, 7.8f);
    doorRotationX->setAngle(-90.0f);

    this->m_doorFrame = &this->addDrawableObjectFromVerticesData(true,
            doorFrame, sizeof(doorFrame) / sizeof(doorFrame[0]), 2, true,
            *this->m_shaderProgram);
    this->m_doorFrame->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\doorAndFrame.png", TexturingUnit::UNIT0));
    TranslationPtr doorFrameTranslation =
            this->m_doorFrame->getTransformation()->addNewTranslation();
    RotationPtr doorFrameRotationX =
            this->m_doorFrame->getTransformation()->addNewRotation(
                    1.0f, 0.0f, 0.0f);
    doorFrameTranslation->translateTo(-2.45f, 0.0f, 7.8f);
    doorFrameRotationX->setAngle(-90.0f);

    this->m_shrek = &this->addDrawableObjectFromVerticesData(true, shrek,
            sizeof(shrek) / sizeof(shrek[0]), 2, true, *this->m_shaderProgram);
    this->m_shrek->addTexture(TextureFactory::create2dTextureFromFile(
            "shrek_fiona\\shrek.png", TexturingUnit::UNIT0));
    TranslationPtr shrekTranslation =
            this->m_shrek->getTransformation()->addNewTranslation();
    RotationPtr shrekRotationX =
            this->m_shrek->getTransformation()->addNewRotation(
                    1.0f, 0.0f, 0.0f);
    RotationPtr shrekRotationZ =
            this->m_shrek->getTransformation()->addNewRotation(
                    0.0f, 0.0f, 1.0f);
    shrekTranslation->translateTo(-3.23f, 0.0f, 1.73f);
    shrekRotationX->setAngle(-90.0f);
    shrekRotationZ->setAngle(90.0f);

    this->m_toilet = &this->addDrawableObjectFromVerticesData(true, toilet,
            sizeof(toilet) / sizeof(toilet[0]), 2, true,
            *this->m_shaderProgram);
    this->m_toilet->addTexture(TextureFactory::create2dTextureFromFile(
            "shrek_fiona\\toilet.jpg", TexturingUnit::UNIT0));
    TranslationPtr toiletTranslation =
            this->m_toilet->getTransformation()->addNewTranslation();
    RotationPtr toiletRotationX =
            this->m_toilet->getTransformation()->addNewRotation(
                    1.0f, 0.0f, 0.0f);
    RotationPtr toiletRotationZ =
            this->m_toilet->getTransformation()->addNewRotation(
                    0.0f, 0.0f, 1.0f);
    ScalePtr toiletScale = this->m_toilet->getTransformation()->addNewScale();
    toiletTranslation->translateTo(-2.44f, 0.664f, 0.57f);
    toiletRotationX->setAngle(-90.0f);
    toiletRotationZ->setAngle(30.0f);
    toiletScale->setScaleTo(0.1f, 0.1f, 0.1f);

    this->m_whiteboard = &this->addDrawableObjectFromVerticesData(true,
            whiteboard, sizeof(whiteboard) / sizeof(whiteboard[0]), 2, true,
            *this->m_shaderProgram);
    this->m_whiteboard->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\whiteboard.png", TexturingUnit::UNIT0));
    TranslationPtr whiteboardTranslation =
            this->m_whiteboard->getTransformation()->addNewTranslation();
    RotationPtr whiteboardRotation =
            this->m_whiteboard->getTransformation()->addNewRotation(
                    1.0f, 0.0f, 0.0f);
    whiteboardTranslation->translateTo(-3.8f, 0.0f, 2.5f);
    whiteboardRotation->setAngle(-90.0f);

    this->m_teacherChair = &this->addDrawableObjectFromVerticesData(true, chair,
            sizeof(chair) / sizeof(chair[0]), 2, true, *this->m_shaderProgram);
    this->m_teacherChair->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\chair.png", TexturingUnit::UNIT0));
    TranslationPtr teacherChairTranslation =
            this->m_teacherChair->getTransformation()->addNewTranslation();
    RotationPtr teacherChairRotation =
            this->m_teacherChair->getTransformation()->addNewRotation(
                    1.0f, 0.0f, 0.0f);
    teacherChairTranslation->translateTo(-3.3f, 0.0f, 0.55f);
    teacherChairRotation->setAngle(-90.0f);

    this->m_teacherTable = &this->addDrawableObjectFromVerticesData(true, table,
            sizeof(table) / sizeof(table[0]), 2, true, *this->m_shaderProgram);
    this->m_teacherTable->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\table.png", TexturingUnit::UNIT0));
    TranslationPtr teacherTableTranslation =
            this->m_teacherTable->getTransformation()->addNewTranslation();
    RotationPtr teacherTableRotationX =
            this->m_teacherTable->getTransformation()->addNewRotation(
                    1.0f, 0.0f, 0.0f);
    RotationPtr teacherTableRotationZ =
            this->m_teacherTable->getTransformation()->addNewRotation(
                    0.0f, 0.0f, 1.0f);
    teacherTableTranslation->translateTo(-2.515f, 0.0f, 1.27f);
    teacherTableRotationX->setAngle(-90.0f);
    teacherTableRotationZ->setAngle(-90.0f);

    this->m_teacherCase = &this->addDrawableObjectFromVerticesData(true,
            computerCase, sizeof(computerCase) / sizeof(computerCase[0]), 2,
            true, *this->m_shaderProgram);
    this->m_teacherCase->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\case.png", TexturingUnit::UNIT0));
    TranslationPtr teacherCaseTranslation =
            this->m_teacherCase->getTransformation()->addNewTranslation();
    RotationPtr teacherCaseRotationX =
            this->m_teacherCase->getTransformation()->addNewRotation(
                    1.0f, 0.0f, 0.0f);
    RotationPtr teacherCaseRotationZ =
            this->m_teacherCase->getTransformation()->addNewRotation(
                    0.0f, 0.0f, 1.0f);
    ScalePtr teacherCaseScale =
            this->m_teacherCase->getTransformation()->addNewScale();
    teacherCaseTranslation->translateTo(-2.414f, 0.0f, 2.067f);
    teacherCaseRotationX->setAngle(-90.0f);
    teacherCaseRotationZ->setAngle(-90.0f);
    teacherCaseScale->setScaleTo(1.2f, 1.2f, 1.2f);

    this->m_teacherMonitor = &this->addDrawableObjectFromVerticesData(true,
            monitor, sizeof(monitor) / sizeof(monitor[0]), 2, true,
            *this->m_shaderProgram);
    this->m_teacherMonitor->addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\monitor.png", TexturingUnit::UNIT0));
    TranslationPtr teacherMonitorTranslation =
            this->m_teacherMonitor->getTransformation()->addNewTranslation();
    RotationPtr teacherMonitorRotationX =
            this->m_teacherMonitor->getTransformation()->addNewRotation(
                    1.0f, 0.0f, 0.0f);
    RotationPtr teacherMonitorRotationZ =
            this->m_teacherMonitor->getTransformation()->addNewRotation(
                    0.0f, 0.0f, 1.0f);
    ScalePtr teacherMonitorScale =
            this->m_teacherMonitor->getTransformation()->addNewScale();
    teacherMonitorTranslation->translateTo(-2.428f, 0.664f, 1.311f);
    teacherMonitorRotationX->setAngle(-90.0f);
    teacherMonitorRotationZ->setAngle(0.0f);
    teacherMonitorScale->setScaleTo(0.01f, 0.01f, 0.01f);
}

CameraPtr ClassroomScene::createCamera(
        int windowWidth, int windowHeight) {
    return std::make_unique<PerspectiveCamera>(
            std::make_shared<CameraCommonSettings>(),
            (float)windowWidth / windowHeight, glm::vec3{1.0f, 1.7f, 2.0f},
            glm::vec3{-1.0f, 0.0f, 0.0f});
}
