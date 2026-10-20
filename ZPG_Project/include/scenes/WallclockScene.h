// WallclockScene.h - Contains declaration of WallclockScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#include <scenes/IScene.h>
#include <string>
#include <unordered_map>

class DrawableObject;
class ShaderProgram;
enum class KeyCodes;
enum class KeyActions;
enum class KeyModifierFlags;

using DrawableObjectPtr = std::unique_ptr<DrawableObject>;
using ShaderProgramPtr = std::unique_ptr<ShaderProgram>;

/**
 * @brief Scene with a real-time clock.
 */
class WallclockScene : public IScene {
  public:
    /**
     * @brief WallclockScene standard constructor.
     */
    WallclockScene();

    virtual ~WallclockScene() = default;

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
    ShaderProgramPtr m_program;
    DrawableObjectPtr m_clock;
    std::unordered_map<std::string, glm::mat4> m_pinsRotations;
};
