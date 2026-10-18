// TriangleScene.h - Contains declaration of TriangleScene class.
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
 * @brief Scene with a single rainbow triangle.
 */
class TriangleScene : public IScene {
  public:
    /**
     * @brief TriangleScene standard constructor.
     */
    TriangleScene();

    /**
     * @brief Draws the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    virtual void draw(const float deltaT);

  private:
    ShaderProgramPtr m_program;
    DrawableObjectPtr m_triangle;
    TranslationPtr m_translation;
    RotationPtr m_rotation;
};
