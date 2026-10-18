// LoginScene.h - Contains declaration of LoginScene class.
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
 * @brief Scene with rotating MAC0690 login.
 */
class LoginScene : public IScene {
  public:
    /**
     * @brief LoginScene standard constructor.
     */
    LoginScene();

    /**
     * @brief Draws the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    virtual void draw(const float deltaT);

  private:
    DrawableObjectPtr m_login;
    ShaderProgramPtr m_shaderProgram;
    RotationPtr m_rotation;
};
