// IScene.h - Contains declaration of IScene interface.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

enum class KeyCodes;
enum class KeyActions;
enum class KeyModifierFlags;

/**
 * @brief A scene interface based on State design pattern.
 */
class IScene {
  public:
    virtual ~IScene() {}

    /**
     * @brief Draws the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    virtual void draw(const float deltaT) = 0;

    /**
     * @brief Handles the mouse cursor position change.
     * @param cursorDeltaX X component of cursor position change.
     * @param cursorDeltaY Y component of cursor position change.
     */
    virtual void handleMouseMovement(int cursorDeltaX, int cursorDeltaY) = 0;

    /**
     * @brief Handles keyboard presses.
     * @param button The button which invoked the event.
     * @param action The button action.
     * @param mode Button modified mode.
     */
    virtual void handleKeyPresses(
            KeyCodes button, KeyActions action, KeyModifierFlags mode) = 0;

    /**
     * @brief Handles the window resizing.
     * @param width New window width.
     * @param height New window height.
     */
    virtual void handleWindowResize(int width, int height) = 0;
};
