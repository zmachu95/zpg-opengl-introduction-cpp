// SolarSystemScene.h - Contains declaration of SolarSystemScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>
#include <scenes/IScene.h>
#include <transformations/GroupedTransformation.h>

class DrawableObject;
class ShaderProgram;

using DrawableObjectPtr = std::unique_ptr<DrawableObject>;
using ShaderProgramPtr = std::unique_ptr<ShaderProgram>;

/**
 * @brief Scene which simulates movement of Sun, Earth and Moon.
 */
class SolarSystemScene : public IScene {
  public:
    /**
     * @brief SolarSystemScene standard constructor.
     */
    SolarSystemScene();

    /**
     * @brief Draws the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    virtual void draw(const float deltaT);

  private:
    DrawableObjectPtr m_sunModel;
    DrawableObjectPtr m_earthModel;
    DrawableObjectPtr m_moonModel;
    ShaderProgramPtr m_shaderProgram;

    RotationPtr m_sunOwnAxisRotation;
    RotationPtr m_earthAroundSunRotation;
    GroupedTransformationPtr m_earthOrbitTransformation;
    RotationPtr m_earthOwnAxisRotation;
    RotationPtr m_moonAroundEarthRotation;
    RotationPtr m_moonOwnAxisRotation;

    /**
     * @brief Creates transformations for Sun.
     * @param sunModelRootTransformation
     */
    void createSunTransformations(
            GroupedTransformation& sunModelRootTransformation);

    /**
     * @brief Creates transformations for Earth.
     * @param earthModelRootTransformation
     */
    void createEarthTransformations(
            GroupedTransformation& earthModelRootTransformation);

    /**
     * @brief Creates transformations for Moon.
     * @param moonModelRootTransformation
     */
    void createMoonTransformations(
            GroupedTransformation& moonModelRootTransformation);
};
