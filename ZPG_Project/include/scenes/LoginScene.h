// LoginScene.h - Contains declaration of LoginScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>
#include <scenes/IScene.h>
#include <transformations/GroupedTransformation.h>

class DrawableObject;
class ShaderProgram;
enum class KeyCodes;
enum class KeyActions;
enum class KeyModifierFlags;

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

    /**
     * @brief Handles the mouse cursor position change.
     * @param cursorDeltaX X component of cursor position change.
     * @param cursorDeltaY Y component of cursor position change.
     */
    virtual void handleMouseMovement(int cursorDeltaX, int cursorDeltaY);

    /**
     * @brief Handles keyboard presses.
     * @param button The button which invoked the event.
     * @param action The button action.
     * @param mode Button modified mode.
     */
    virtual void handleKeyPresses(
            KeyCodes button, KeyActions action, KeyModifierFlags mode);

    /**
     * @brief Handles the window resizing.
     * @param width New window width.
     * @param height New window height.
     */
    virtual void handleWindowResize(int width, int height);

  private:
    DrawableObjectPtr m_login;
    ShaderProgramPtr m_shaderProgram;
    RotationPtr m_rotation;
};
