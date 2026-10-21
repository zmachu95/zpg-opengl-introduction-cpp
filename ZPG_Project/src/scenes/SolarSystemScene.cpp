// SolarSystemScene.cpp - Contains definition of SolarSystemScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <scenes/SolarSystemScene.h>

#include <cameras/CameraCommonSettings.h>
#include <cameras/CameraUserInputController.h>
#include <cameras/PerspectiveCamera.h>
#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <memory>
#include <resources/models/earth.h>
#include <resources/models/moon.h>
#include <resources/models/satellite.h>
#include <resources/models/sun.h>
#include <scenes/IScene.h>
#include <shaders/ShaderProgram.h>
#include <transformations/IGroupedTransformation.h>
#include <transformations/IRotation.h>
#include <transformations/IScale.h>
#include <transformations/ITranslation.h>

// planets sizing
const float sunScale = 0.25f;
const float sunToEarthSizeRatio = 109.2f / 20;
const float earthToMoonSizeRatio = 3.67f;
const float earthScale = sunScale / sunToEarthSizeRatio;
const float moonScale = earthScale / earthToMoonSizeRatio;
const float satelliteScale = 0.02f;

// offsets among planets
const float earthToSunOffset = 0.7f;
const float moonToEarthOffset = 0.15f;
const float satelliteToEarthOffset = 0.1f;

// orbital angular velocities
const float earthAroundSunOmega = 20.0f;
const float moonAroundEarthOmega = 12 * earthAroundSunOmega;
const float satelliteAroundEarthOmega = 30.0f;

// own axis angular velocities
const float sunOwnAxisOmega = 5.0f;
const float earthOwnAxisOmega = 250.0f;
const float moonOwnAxisOmega = moonAroundEarthOmega;

void SolarSystemScene::createSunTransformations(
        GroupedTransformationPtr sunModelRootTransformation) {
    this->m_sunOwnAxisRotation =
            sunModelRootTransformation->addNewRotation(0.0f, 1.0f, 0.0f);
    ScalePtr scale = sunModelRootTransformation->addNewScale();
    scale->setScaleTo(sunScale, sunScale, sunScale);
}

void SolarSystemScene::createEarthTransformations(
        GroupedTransformationPtr earthModelRootTransformation) {
    this->m_earthOrbitTransformation =
            earthModelRootTransformation->addNewGroup();
    this->m_earthAroundSunRotation =
            this->m_earthOrbitTransformation->addNewRotation(0.0f, 0.0f, 1.0f);
    TranslationPtr earthFromSunTranslation =
            this->m_earthOrbitTransformation->addNewTranslation();
    earthFromSunTranslation->translateTo(-earthToSunOffset, 0.0f, 0.0f);
    this->m_earthOwnAxisRotation =
            earthModelRootTransformation->addNewRotation(0.0f, 1.0f, 0.0f);
    ScalePtr scale = earthModelRootTransformation->addNewScale();
    scale->setScaleTo(earthScale, earthScale, earthScale);
}

void SolarSystemScene::createMoonTransformations(
        GroupedTransformationPtr moonModelRootTransformation) {
    moonModelRootTransformation->addReferenceToAnother(
            this->m_earthOrbitTransformation);
    this->m_moonAroundEarthRotation =
            moonModelRootTransformation->addNewRotation(0.0f, 0.0f, 1.0f);
    TranslationPtr moonFromEarthTranslation =
            moonModelRootTransformation->addNewTranslation();
    moonFromEarthTranslation->translateTo(moonToEarthOffset, 0.0f, 0.0f);
    this->m_moonOwnAxisRotation =
            moonModelRootTransformation->addNewRotation(0.0f, 1.0f, 0.0f);
    ScalePtr scale = moonModelRootTransformation->addNewScale();
    scale->setScaleTo(moonScale, moonScale, moonScale);
}

void SolarSystemScene::createSatelliteTransformations(
        GroupedTransformationPtr satelliteModelRootTransformation) {
    satelliteModelRootTransformation->addReferenceToAnother(
            this->m_earthOrbitTransformation);
    this->m_satelliteAroundEarthRotation =
            satelliteModelRootTransformation->addNewRotation(0.0f, 0.0f, 1.0f);
    TranslationPtr satelliteFromEarthTranslation =
            satelliteModelRootTransformation->addNewTranslation();
    satelliteFromEarthTranslation->translateTo(
            satelliteToEarthOffset, 0.0f, 0.0f);
    ScalePtr scale = satelliteModelRootTransformation->addNewScale();
    scale->setScaleTo(satelliteScale, satelliteScale, satelliteScale);
}

SolarSystemScene::SolarSystemScene()
    : IScene{}, m_sunModel{}, m_earthModel{}, m_moonModel{}, m_satelliteModel{},
      m_sunShaderProgram{}, m_planetsShaderProgram{},
      m_satelliteShaderProgram{}, m_sunOwnAxisRotation{},
      m_earthAroundSunRotation{}, m_earthOrbitTransformation{},
      m_earthOwnAxisRotation{}, m_moonAroundEarthRotation{},
      m_moonOwnAxisRotation{}, m_satelliteAroundEarthRotation{}, m_camera{},
      m_cameraController{} {
    this->m_sunModel =
            DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    sun, sizeof(sun) / sizeof(sun[0]), 3);
    this->m_earthModel =
            DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    earth, sizeof(earth) / sizeof(earth[0]), 3);
    this->m_moonModel =
            DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    moon, sizeof(moon) / sizeof(moon[0]), 3);
    this->m_satelliteModel =
            DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    satellite, sizeof(satellite) / sizeof(satellite[0]), 2);

    this->m_sunShaderProgram = ShaderProgram::createFromShaderFiles(
            "solar_system_scene\\planets.vert",
            "solar_system_scene\\ambient.frag");
    this->m_planetsShaderProgram = ShaderProgram::createFromShaderFiles(
            "solar_system_scene\\planets.vert",
            "solar_system_scene\\phong.frag");
    this->m_satelliteShaderProgram = ShaderProgram::createFromShaderFiles(
            "solar_system_scene\\satellite.vert",
            "solar_system_scene\\phong.frag");

    this->createSunTransformations(this->m_sunModel->getTransformation());
    this->createEarthTransformations(this->m_earthModel->getTransformation());
    this->createMoonTransformations(this->m_moonModel->getTransformation());
    this->createSatelliteTransformations(
            this->m_satelliteModel->getTransformation());

    std::shared_ptr<CameraCommonSettings> commonSettings =
            std::make_shared<CameraCommonSettings>();

    this->m_camera = std::make_unique<PerspectiveCamera>(
            commonSettings, 1.0f, glm::vec3{0.0f, 0.0f, 2.0f});

    this->m_camera->registerCameraUpdateListener(
            this->m_sunShaderProgram->asCameraUpdateListener());
    this->m_camera->registerCameraUpdateListener(
            this->m_planetsShaderProgram->asCameraUpdateListener());
    this->m_camera->registerCameraUpdateListener(
            this->m_satelliteShaderProgram->asCameraUpdateListener());
}

void SolarSystemScene::draw(
        const float deltaT) {
    this->m_sunOwnAxisRotation->incrementAngle(sunOwnAxisOmega * deltaT);
    this->m_earthAroundSunRotation->incrementAngle(
            earthAroundSunOmega * deltaT);
    this->m_earthOwnAxisRotation->incrementAngle(earthOwnAxisOmega * deltaT);
    this->m_moonAroundEarthRotation->incrementAngle(
            moonAroundEarthOmega * deltaT);
    this->m_moonOwnAxisRotation->incrementAngle(moonOwnAxisOmega * deltaT);
    this->m_satelliteAroundEarthRotation->incrementAngle(
            -satelliteAroundEarthOmega * deltaT);

    this->m_sunModel->draw(*this->m_sunShaderProgram);
    this->m_earthModel->draw(*this->m_planetsShaderProgram);
    this->m_moonModel->draw(*this->m_planetsShaderProgram);
    this->m_satelliteModel->draw(*this->m_satelliteShaderProgram);
}

void SolarSystemScene::handleMouseMovement(
        int cursorDeltaX, int cursorDeltaY) {}

void SolarSystemScene::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {}

void SolarSystemScene::handleWindowResize(
        int width, int height) {
    this->m_camera->setAspectRatio(width, height);
}
