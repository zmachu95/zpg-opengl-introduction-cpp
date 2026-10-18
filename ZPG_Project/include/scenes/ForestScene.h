// ForestScene.h - Contains declaration of ForestScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>
#include <scenes/IScene.h>
#include <vector>

class DrawableObject;
class ShaderProgram;

using DrawableObjectPtr = std::unique_ptr<DrawableObject>;
using ShaderProgramPtr = std::unique_ptr<ShaderProgram>;

/**
 * @brief Scene with random trees and bushes.
 */
class ForestScene : public IScene {
  public:
    /**
     * @brief ForestScene standard constructor.
     */
    ForestScene();

    /**
     * @brief Draws the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    virtual void draw(const float deltaT);

  private:
    std::vector<DrawableObjectPtr> m_treesAndBushes;
    ShaderProgramPtr m_shaderProgram;
};
