// ShrekFionaScene.h - Contains declaration of ShrekFionaScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "AbstractSceneTemplate.h"

class DrawableObject;
class ShaderProgram;

/**
 * @brief Scene with Shrek, Fiona and toilet.
 */
class ShrekFionaScene : public AbstractSceneTemplate {
  public:
    /**
     * @brief ShrekFionaScene standard constructor.
     * @param windowWidth Application window width in [px].
     * @param windowHeight Application window height in [px].
     */
    ShrekFionaScene(int windowWidth, int windowHeight);

    virtual ~ShrekFionaScene() = default;

  protected:
    /**
     * @brief Updates the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void updateSceneContents(float deltaT) override;
};
