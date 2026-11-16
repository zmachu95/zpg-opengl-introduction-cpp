// WallclockScene.h - Contains declaration of WallclockScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "AbstractSceneTemplate.h"

class ShaderProgram;

/**
 * @brief Scene with a real-time clock.
 */
class WallclockScene : public AbstractSceneTemplate {
  public:
    /**
     * @brief WallclockScene standard constructor.
     * @param windowWidth Application window width in [px].
     * @param windowHeight Application window height in [px].
     */
    WallclockScene(int windowWidth, int windowHeight);

    ~WallclockScene() override = default;

  protected:
    /**
     * @brief Updates the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void updateSceneContents(float deltaT) override;

  private:
    ShaderProgram* m_shaderProgram;
};
