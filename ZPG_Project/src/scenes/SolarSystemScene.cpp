// SolarSystemScene.cpp - Contains definition of SolarSystemScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "SolarSystemScene.h"
#include "AbstractSceneTemplate.h"

#include <cameras/CameraCommonSettings.h>
#include <cameras/PerspectiveCamera.h>
#include <drawables/DrawableObject.h>
#include <memory>
#include <resources/models/earth.h>
#include <resources/models/moon.h>
#include <resources/models/satellite.h>
#include <resources/models/sun.h>
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

SolarSystemScene::SolarSystemScene(
        int windowWidth, int windowHeight)
    : AbstractSceneTemplate{
              SolarSystemScene::createCamera(windowWidth, windowHeight),
              std::unique_ptr<DrawableObject>()},
      m_sunOwnAxisRotation{}, m_earthAroundSunRotation{},
      m_earthOrbitTransformation{}, m_earthOwnAxisRotation{},
      m_moonAroundEarthRotation{}, m_moonOwnAxisRotation{},
      m_satelliteAroundEarthRotation{}, m_sunShaderProgram{nullptr},
      m_planetsShaderProgram{nullptr}, m_satelliteShaderProgram{nullptr},
      m_initializedShaders{false} {
    // shader programs
    this->m_sunShaderProgram = &this->addShaderProgramFromShaderFiles(
            "solar_system_scene\\planets.vert", "_templates\\lighting.frag",
            false);
    this->m_planetsShaderProgram = &this->addShaderProgramFromShaderFiles(
            "solar_system_scene\\planets.vert", "_templates\\lighting.frag",
            false);
    this->m_satelliteShaderProgram = &this->addShaderProgramFromShaderFiles(
            "solar_system_scene\\satellite.vert", "_templates\\lighting.frag",
            false);

    // models
    DrawableObject& sunModel = this->addDrawableObjectFromVerticesData(false,
            sun, sizeof(sun) / sizeof(sun[0]), 3, false,
            *this->m_sunShaderProgram);
    DrawableObject& earthModel = this->addDrawableObjectFromVerticesData(false,
            earth, sizeof(earth) / sizeof(earth[0]), 3, false,
            *this->m_planetsShaderProgram);
    DrawableObject& moonModel = this->addDrawableObjectFromVerticesData(false,
            moon, sizeof(moon) / sizeof(moon[0]), 3, false,
            *this->m_planetsShaderProgram);
    DrawableObject& satelliteModel = this->addDrawableObjectFromVerticesData(
            false, satellite, sizeof(satellite) / sizeof(satellite[0]), 2,
            false, *this->m_satelliteShaderProgram);

    this->createSunTransformations(sunModel.getTransformation());
    this->createEarthTransformations(earthModel.getTransformation());
    this->createMoonTransformations(moonModel.getTransformation());
    this->createSatelliteTransformations(satelliteModel.getTransformation());
}

void SolarSystemScene::updateSceneContents(
        float deltaT) {
    this->initializeShaderPrograms();

    this->m_sunOwnAxisRotation->incrementAngle(sunOwnAxisOmega * deltaT);
    this->m_earthAroundSunRotation->incrementAngle(
            earthAroundSunOmega * deltaT);
    this->m_earthOwnAxisRotation->incrementAngle(earthOwnAxisOmega * deltaT);
    this->m_moonAroundEarthRotation->incrementAngle(
            moonAroundEarthOmega * deltaT);
    this->m_moonOwnAxisRotation->incrementAngle(moonOwnAxisOmega * deltaT);
    this->m_satelliteAroundEarthRotation->incrementAngle(
            -satelliteAroundEarthOmega * deltaT);
}

CameraPtr SolarSystemScene::createCamera(
        int windowWidth, int windowHeight) {
    return std::make_unique<PerspectiveCamera>(
            std::make_shared<CameraCommonSettings>(),
            (float)windowWidth / windowHeight, glm::vec3{0.0f, 0.0f, 2.0f});
}

void SolarSystemScene::initializeShaderPrograms() {
    if (!this->m_initializedShaders) {
        for (ShaderProgram* shaderProgram : {this->m_planetsShaderProgram,
                     this->m_satelliteShaderProgram}) {
            shaderProgram->setSupplementalUniformIntValue(
                    "pointLightsCount", 1);
            shaderProgram->setSupplementalUniformVector(
                    "ambientFactors", glm::vec3{0.3f});
            shaderProgram->setSupplementalUniformVector(
                    "pointLights[0].color", glm::vec3{1.0f, 0.8f, 0.8f});
            shaderProgram->setSupplementalUniformFloatValue(
                    "pointLights[0].shininessExponent", 6.0f);
            shaderProgram->setSupplementalUniformFloatValue(
                    "pointLights[0].attConstant", 1.0f);
            shaderProgram->setSupplementalUniformFloatValue(
                    "pointLights[0].attLinear", 0.05f);
            shaderProgram->setSupplementalUniformFloatValue(
                    "pointLights[0].attQuadratic", 0.001f);
            shaderProgram->setSupplementalUniformBoolValue(
                    "pointLights[0].useSpecular", true);
            shaderProgram->setSupplementalUniformBoolValue(
                    "pointLights[0].useBlinn", true);
        }

        this->m_initializedShaders = true;
    }
}
