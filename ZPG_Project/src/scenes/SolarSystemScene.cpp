// SolarSystemScene.cpp - Contains definition of SolarSystemScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <scenes/SolarSystemScene.h>

#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <memory>
#include <resources/models/earth.h>
#include <resources/models/moon.h>
#include <resources/models/sun.h>
#include <scenes/IScene.h>
#include <shaders/ShaderProgram.h>
#include <transformations/GroupedTransformation.h>
#include <transformations/Rotation.h>
#include <transformations/Scale.h>
#include <transformations/Translation.h>

// planets sizing
const float sunScale = 0.25f;
const float sunToEarthSizeRatio = 109.2f / 20;
const float earthToMoonSizeRatio = 3.67f;
const float earthScale = sunScale / sunToEarthSizeRatio;
const float moonScale = earthScale / earthToMoonSizeRatio;

// offsets among planets
const float earthToSunOffset = 0.7f;
const float moonToEarthOffset = 0.15f;

// orbital angular velocities
const float earthAroundSunOmega = 20.0f;
const float moonAroundEarthOmega = 12 * earthAroundSunOmega;

// own axis angular velocities
const float sunOwnAxisOmega = 5.0f;
const float earthOwnAxisOmega = 25.0f;
const float moonOwnAxisOmega = moonAroundEarthOmega;

void SolarSystemScene::createSunTransformations(
        GroupedTransformation& sunModelRootTransformation) {
    this->m_sunOwnAxisRotation =
            sunModelRootTransformation.addNewRotation(0.0f, 1.0f, 0.0f);
    ScalePtr scale = sunModelRootTransformation.addNewScale();
    scale->setScaleTo(sunScale, sunScale, sunScale);
}

void SolarSystemScene::createEarthTransformations(
        GroupedTransformation& earthModelRootTransformation) {
    this->m_earthOrbitTransformation =
            earthModelRootTransformation.addNewGroup();
    this->m_earthAroundSunRotation =
            this->m_earthOrbitTransformation->addNewRotation(0.0f, 0.0f, 1.0f);
    TranslationPtr earthFromSunTranslation =
            this->m_earthOrbitTransformation->addNewTranslation();
    earthFromSunTranslation->translateTo(earthToSunOffset, 0.0f, 0.0f);
    this->m_earthOwnAxisRotation =
            earthModelRootTransformation.addNewRotation(0.0f, 1.0f, 0.0f);
    ScalePtr scale = earthModelRootTransformation.addNewScale();
    scale->setScaleTo(earthScale, earthScale, earthScale);
}

void SolarSystemScene::createMoonTransformations(
        GroupedTransformation& moonModelRootTransformation) {
    moonModelRootTransformation.addReferenceToAnother(
            this->m_earthOrbitTransformation);
    this->m_moonAroundEarthRotation =
            moonModelRootTransformation.addNewRotation(0.0f, 0.0f, 1.0f);
    TranslationPtr moonFromEarthTranslation =
            moonModelRootTransformation.addNewTranslation();
    moonFromEarthTranslation->translateTo(moonToEarthOffset, 0.0f, 0.0f);
    this->m_moonOwnAxisRotation =
            moonModelRootTransformation.addNewRotation(0.0f, 1.0f, 0.0f);
    ScalePtr scale = moonModelRootTransformation.addNewScale();
    scale->setScaleTo(moonScale, moonScale, moonScale);
}

SolarSystemScene::SolarSystemScene()
    : IScene{}, m_sunModel{}, m_earthModel{}, m_moonModel{}, m_shaderProgram{},
      m_sunOwnAxisRotation{}, m_earthAroundSunRotation{},
      m_earthOrbitTransformation{}, m_earthOwnAxisRotation{},
      m_moonAroundEarthRotation{}, m_moonOwnAxisRotation{} {
    this->m_sunModel =
            DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    sun, sizeof(sun) / sizeof(sun[0]), 3);
    this->m_earthModel =
            DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    earth, sizeof(earth) / sizeof(earth[0]), 3);
    this->m_moonModel =
            DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    moon, sizeof(moon) / sizeof(moon[0]), 3);
    this->m_shaderProgram =
            ShaderProgram::createFromShaderFiles("basic.vert", "basic.frag");

    this->createSunTransformations(this->m_sunModel->getTransformation());
    this->createEarthTransformations(this->m_earthModel->getTransformation());
    this->createMoonTransformations(this->m_moonModel->getTransformation());
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

    this->m_sunModel->draw(*this->m_shaderProgram);
    this->m_earthModel->draw(*this->m_shaderProgram);
    this->m_moonModel->draw(*this->m_shaderProgram);
}

void SolarSystemScene::handleMouseMovement(
        int cursorDeltaX, int cursorDeltaY) {}

void SolarSystemScene::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {}

void SolarSystemScene::handleWindowResize(
        int width, int height) {}
