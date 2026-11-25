// ClassroomScene.cpp - Contains definition of ClassroomScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "ClassroomScene.h"
#include "AbstractSceneTemplate.h"

#include <cameras/CameraCommonSettings.h>
#include <cameras/PerspectiveCamera.h>
#include <constants/MouseButtonActions.h>
#include <constants/MouseButtonCodes.h>
#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <memory>
#include <others/WallclockUtils.h>
#include <shaders/ShaderProgram.h>
#include <textures/ITexture.h>
#include <textures/TextureFactory.h>
#include <transformations/IGroupedTransformation.h>
#include <transformations/IRotation.h>
#include <transformations/IScale.h>
#include <transformations/ITranslation.h>

ClassroomScene::ClassroomScene(
        int windowWidth, int windowHeight)
    : AbstractSceneTemplate{
              ClassroomScene::createCamera(windowWidth, windowHeight)},
      m_clockShaderProgram{nullptr}, m_shaderProgram{nullptr},
      m_useFlashlight{false}, m_updatedSkyboxShader{false},
      m_initializedShaders{false} {
    this->m_shaderProgram = &this->addShaderProgramFromShaderFiles(
            "_templates\\basic.vert", "_templates\\lighting.frag", false);
    this->m_clockShaderProgram = &this->addShaderProgramFromShaderFiles(
            "wallclock_scene\\clock.vert", "_templates\\lighting.frag", false);

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
    this->initializeShaderPrograms();

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
    DrawableObject* newTable = &this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_TABLE, *this->m_shaderProgram);
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

    DrawableObject* firstChair = &this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_CHAIR, *this->m_shaderProgram);
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

    DrawableObject* secondChair = &this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_CHAIR, *this->m_shaderProgram);
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

    DrawableObject* firstCase = &this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_CASE, *this->m_shaderProgram);
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

    DrawableObject* secondCase = &this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_CASE, *this->m_shaderProgram);
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

    DrawableObject* firstMonitor = &this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_MONITOR, *this->m_shaderProgram);
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

    DrawableObject* secondMonitor = &this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_MONITOR, *this->m_shaderProgram);
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
    DrawableObject& classroom = this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408, *this->m_shaderProgram);
    classroom.addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\eb408.png", TexturingUnit::UNIT0));
    RotationPtr classroomRotationX =
            classroom.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    classroomRotationX->setAngle(-90.0f);

    DrawableObject& clock = this->addDrawableObjectFromKnownModel(
            true, KnownModels::CLOCK, *this->m_clockShaderProgram);
    TranslationPtr clockTranslation =
            clock.getTransformation()->addNewTranslation();
    RotationPtr clockRotation =
            clock.getTransformation()->addNewRotation(0.0f, 1.0f, 0.0f);
    ScalePtr clockScale = clock.getTransformation()->addNewScale();
    clockTranslation->translateTo(-3.8f, 2.0f, 5.5f);
    clockRotation->setAngle(-90.0f);
    clockScale->setScaleTo(-0.3f, 0.3f, 0.3f);

    DrawableObject& doorObj = this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_DOOR, *this->m_shaderProgram);
    doorObj.addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\doorAndFrame.png", TexturingUnit::UNIT0));
    TranslationPtr doorTranslation =
            doorObj.getTransformation()->addNewTranslation();
    RotationPtr doorRotationX =
            doorObj.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    doorTranslation->translateTo(-2.45f, 0.0f, 7.8f);
    doorRotationX->setAngle(-90.0f);

    DrawableObject& doorFrameObj = this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_DOOR_FRAME, *this->m_shaderProgram);
    doorFrameObj.addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\doorAndFrame.png", TexturingUnit::UNIT0));
    TranslationPtr doorFrameTranslation =
            doorFrameObj.getTransformation()->addNewTranslation();
    RotationPtr doorFrameRotationX =
            doorFrameObj.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    doorFrameTranslation->translateTo(-2.45f, 0.0f, 7.8f);
    doorFrameRotationX->setAngle(-90.0f);

    DrawableObject& shrekObj = this->addDrawableObjectFromKnownModel(
            true, KnownModels::SHREK, *this->m_shaderProgram);
    shrekObj.addTexture(TextureFactory::create2dTextureFromFile(
            "shrek_fiona\\shrek.png", TexturingUnit::UNIT0));
    TranslationPtr shrekTranslation =
            shrekObj.getTransformation()->addNewTranslation();
    RotationPtr shrekRotationX =
            shrekObj.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    RotationPtr shrekRotationZ =
            shrekObj.getTransformation()->addNewRotation(0.0f, 0.0f, 1.0f);
    shrekTranslation->translateTo(-3.23f, 0.0f, 1.73f);
    shrekRotationX->setAngle(-90.0f);
    shrekRotationZ->setAngle(90.0f);

    DrawableObject& toiletObj = this->addDrawableObjectFromKnownModel(
            true, KnownModels::TOILET, *this->m_shaderProgram);
    toiletObj.addTexture(TextureFactory::create2dTextureFromFile(
            "shrek_fiona\\toilet.jpg", TexturingUnit::UNIT0));
    TranslationPtr toiletTranslation =
            toiletObj.getTransformation()->addNewTranslation();
    RotationPtr toiletRotationX =
            toiletObj.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    RotationPtr toiletRotationZ =
            toiletObj.getTransformation()->addNewRotation(0.0f, 0.0f, 1.0f);
    ScalePtr toiletScale = toiletObj.getTransformation()->addNewScale();
    toiletTranslation->translateTo(-2.44f, 0.664f, 0.57f);
    toiletRotationX->setAngle(-90.0f);
    toiletRotationZ->setAngle(30.0f);
    toiletScale->setScaleTo(0.1f, 0.1f, 0.1f);

    DrawableObject& whiteboardObj = this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_WHITEBOARD, *this->m_shaderProgram);
    whiteboardObj.addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\whiteboard.png", TexturingUnit::UNIT0));
    TranslationPtr whiteboardTranslation =
            whiteboardObj.getTransformation()->addNewTranslation();
    RotationPtr whiteboardRotation =
            whiteboardObj.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    whiteboardTranslation->translateTo(-3.8f, 0.0f, 2.5f);
    whiteboardRotation->setAngle(-90.0f);

    DrawableObject& teacherChair = this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_CHAIR, *this->m_shaderProgram);
    teacherChair.addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\chair.png", TexturingUnit::UNIT0));
    TranslationPtr teacherChairTranslation =
            teacherChair.getTransformation()->addNewTranslation();
    RotationPtr teacherChairRotation =
            teacherChair.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    teacherChairTranslation->translateTo(-3.3f, 0.0f, 0.55f);
    teacherChairRotation->setAngle(-90.0f);

    DrawableObject& teacherTable = this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_TABLE, *this->m_shaderProgram);
    teacherTable.addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\table.png", TexturingUnit::UNIT0));
    TranslationPtr teacherTableTranslation =
            teacherTable.getTransformation()->addNewTranslation();
    RotationPtr teacherTableRotationX =
            teacherTable.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    RotationPtr teacherTableRotationZ =
            teacherTable.getTransformation()->addNewRotation(0.0f, 0.0f, 1.0f);
    teacherTableTranslation->translateTo(-2.515f, 0.0f, 1.27f);
    teacherTableRotationX->setAngle(-90.0f);
    teacherTableRotationZ->setAngle(-90.0f);

    DrawableObject& teacherCase = this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_CASE, *this->m_shaderProgram);
    teacherCase.addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\case.png", TexturingUnit::UNIT0));
    TranslationPtr teacherCaseTranslation =
            teacherCase.getTransformation()->addNewTranslation();
    RotationPtr teacherCaseRotationX =
            teacherCase.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    RotationPtr teacherCaseRotationZ =
            teacherCase.getTransformation()->addNewRotation(0.0f, 0.0f, 1.0f);
    ScalePtr teacherCaseScale = teacherCase.getTransformation()->addNewScale();
    teacherCaseTranslation->translateTo(-2.414f, 0.0f, 2.067f);
    teacherCaseRotationX->setAngle(-90.0f);
    teacherCaseRotationZ->setAngle(-90.0f);
    teacherCaseScale->setScaleTo(1.2f, 1.2f, 1.2f);

    DrawableObject& teacherMonitor = this->addDrawableObjectFromKnownModel(
            true, KnownModels::EB408_MONITOR, *this->m_shaderProgram);
    teacherMonitor.addTexture(TextureFactory::create2dTextureFromFile(
            "eb408\\monitor.png", TexturingUnit::UNIT0));
    TranslationPtr teacherMonitorTranslation =
            teacherMonitor.getTransformation()->addNewTranslation();
    RotationPtr teacherMonitorRotationX =
            teacherMonitor.getTransformation()->addNewRotation(
                    1.0f, 0.0f, 0.0f);
    RotationPtr teacherMonitorRotationZ =
            teacherMonitor.getTransformation()->addNewRotation(
                    0.0f, 0.0f, 1.0f);
    ScalePtr teacherMonitorScale =
            teacherMonitor.getTransformation()->addNewScale();
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

void ClassroomScene::handleMouseClick(
        MouseButtonCodes button, MouseButtonActions action,
        KeyModifierFlags mode) {
    if (action == MouseButtonActions::PRESSED) {
        switch (button) {
            case MouseButtonCodes::RIGHT_BUTTON:
                this->m_useFlashlight = !this->m_useFlashlight;
                for (ShaderProgram* shaderProgram :
                        {this->m_clockShaderProgram, this->m_shaderProgram}) {
                    shaderProgram->setSupplementalUniformIntValue(
                            "spotLightsCount", (int)this->m_useFlashlight);
                }
                break;
        }
    }

    AbstractSceneTemplate::handleMouseClick(button, action, mode);
}

void ClassroomScene::updateSkyboxShaderProgram(
        float deltaT) {
    if (!this->m_updatedSkyboxShader) {
        this->getSkyboxShaderProgram()->setSupplementalUniformVector(
                "ambientFactors", glm::vec3{0.1f});
        this->m_updatedSkyboxShader = true;
    }
}

void ClassroomScene::initializeShaderPrograms() {
    if (!this->m_initializedShaders) {
        for (ShaderProgram* shaderProgram :
                {this->m_clockShaderProgram, this->m_shaderProgram}) {
            shaderProgram->setSupplementalUniformIntValue(
                    "directedLightsCount", 1);
            shaderProgram->setSupplementalUniformIntValue(
                    "spotLightsCount", (int)this->m_useFlashlight);
            shaderProgram->setSupplementalUniformVector(
                    "ambientFactors", glm::vec3{0.01f});

            // define directed light
            shaderProgram->setSupplementalUniformVector(
                    "directedLights[0].direction",
                    glm::vec3{-0.8f, -0.5f, -0.2f});
            shaderProgram->setSupplementalUniformVector(
                    "directedLights[0].color", glm::vec3{0.1f, 0.08f, 0.08f});
            shaderProgram->setSupplementalUniformFloatValue(
                    "directedLights[0].shininessExponent", 128.0f);
            shaderProgram->setSupplementalUniformBoolValue(
                    "directedLights[0].useSpecular", false);
            shaderProgram->setSupplementalUniformBoolValue(
                    "directedLights[0].useBlinn", false);

            // define spotlight
            shaderProgram->setSupplementalUniformFloatValue(
                    "spotLights[0].innerCosineCutOff",
                    glm::cos(glm::radians(5.0f)));
            shaderProgram->setSupplementalUniformFloatValue(
                    "spotLights[0].outerCosineCutOff",
                    glm::cos(glm::radians(15.0f)));
            shaderProgram->setSupplementalUniformFloatValue(
                    "spotLights[0].attConstant", 1.0f);
            shaderProgram->setSupplementalUniformFloatValue(
                    "spotLights[0].attLinear", 0.3f);
            shaderProgram->setSupplementalUniformFloatValue(
                    "spotLights[0].attQuadratic", 0.01f);
            shaderProgram->setSupplementalUniformVector(
                    "spotLights[0].color", glm::vec3{0.7f, 0.7f, 1.0f});
            shaderProgram->setSupplementalUniformFloatValue(
                    "spotLights[0].shininessExponent", 2.0f);
            shaderProgram->setSupplementalUniformBoolValue(
                    "spotLights[0].useSpecular", true);
            shaderProgram->setSupplementalUniformBoolValue(
                    "spotLights[0].useBlinn", true);
        }

        this->m_initializedShaders = true;
    }
}
