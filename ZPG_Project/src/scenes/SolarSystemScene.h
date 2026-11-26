// SolarSystemScene.h - Contains declaration of SolarSystemScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "AbstractSceneTemplate.h"
#include <memory>

class IGroupedTransformation;
class ITranslation;
class IRotation;

class DrawableObject;
class ShaderProgram;

/**
 * @brief Pointer to IGroupedTransformation object.
 */
using GroupedTransformationPtr = std::shared_ptr<IGroupedTransformation>;

/**
 * @brief Pointer to ITranslation object.
 */
using TranslationPtr = std::shared_ptr<ITranslation>;

/**
 * @brief Pointer to IRotation object.
 */
using RotationPtr = std::shared_ptr<IRotation>;

/**
 * @brief Scene which simulates movement of Sun, Earth and Moon.
 */
class SolarSystemScene : public AbstractSceneTemplate {
  public:
    /**
     * @brief SolarSystemScene standard constructor.
     * @param windowWidth Application window width in [px].
     * @param windowHeight Application window height in [px].
     */
    SolarSystemScene(int windowWidth, int windowHeight);

    ~SolarSystemScene() override = default;

  protected:
    /**
     * @brief Updates the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void updateSceneContents(float deltaT) override;

    /**
     * @brief Initializes scene lights.
     */
    void initializeLights() override;

  private:
    RotationPtr m_sunOwnAxisRotation;
    RotationPtr m_earthAroundSunRotation;
    GroupedTransformationPtr m_earthOrbitTransformation;
    RotationPtr m_earthOwnAxisRotation;
    RotationPtr m_moonAroundEarthRotation;
    RotationPtr m_moonOwnAxisRotation;
    RotationPtr m_satelliteAroundEarthRotation;
    ShaderProgram* m_sunShaderProgram;
    ShaderProgram* m_planetsShaderProgram;
    ShaderProgram* m_satelliteShaderProgram;
    bool m_initializedShaders;

    /**
     * @brief Creates camera in the scene.
     * @param windowWidth Application window width in [px].
     * @param windowHeight Application window height in [px].
     * @return Pointer to camera object.
     */
    static CameraPtr createCamera(int windowWidth, int windowHeight);

    /**
     * @brief Creates transformations for Sun.
     * @param sunModelRootTransformation
     */
    void createSunTransformations(
            GroupedTransformationPtr sunModelRootTransformation);

    /**
     * @brief Creates transformations for Earth.
     * @param earthModelRootTransformation
     */
    void createEarthTransformations(
            GroupedTransformationPtr earthModelRootTransformation);

    /**
     * @brief Creates transformations for Moon.
     * @param moonModelRootTransformation
     */
    void createMoonTransformations(
            GroupedTransformationPtr moonModelRootTransformation);

    /**
     * @brief Creates transformations for satellite.
     * @param satelliteModelRootTransformation
     */
    void createSatelliteTransformations(
            GroupedTransformationPtr satelliteModelRootTransformation);
};
