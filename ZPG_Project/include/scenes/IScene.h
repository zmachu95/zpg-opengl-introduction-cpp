// IScene.h - Contains declaration of IScene interface.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <glm/ext/vector_float3.hpp>

enum class MouseButtonActions;
enum class MouseButtonCodes;
enum class KeyCodes;
enum class KeyActions;
enum class KeyModifierFlags;

/**
 * @brief Alias for byte.
 */
using Byte = unsigned char;

/**
 * @brief A scene interface based on Bridge design pattern.
 */
class IScene {
  public:
    virtual ~IScene() = default;

    /**
     * @brief Draws the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     * @param stencilModifier Callback which modifies stencil buffer test
     * function.
     */
    virtual void draw(float deltaT, void (*stencilModifier)(Byte)) = 0;

    /**
     * @brief Draws the scene's skybox.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    virtual void drawSkybox(float deltaT) = 0;

    /**
     * @brief Handles keyboard presses.
     * @param button The button which invoked the event.
     * @param action The button action.
     * @param mode Button modified mode.
     */
    virtual void handleKeyPresses(
            KeyCodes button, KeyActions action, KeyModifierFlags mode) = 0;

    /**
     * @brief Handles mouse click event.
     * @param button Clicked mouse button.
     * @param action The mouse button action.
     * @param mode Button modifier mode.
     */
    virtual void handleMouseClick(MouseButtonCodes button,
            MouseButtonActions action, KeyModifierFlags mode) = 0;

    /**
     * @brief Handles mouse click event with object selection.
     * @param clickCoords Mouse click coordinates in window space.
     * @param windowWidth Window width in [px].
     * @param windowHeight Window height in [px].
     * @param objectId ID of selected object.
     * @param button Clicked mouse button.
     * @param action The mouse button action.
     * @param mode Button modifier mode.
     */
    virtual void handleMouseClickWithObjectSelection(
            const glm::vec3& clickCoords, int windowWidth, int windowHeight,
            Byte objectId, MouseButtonCodes button, MouseButtonActions action,
            KeyModifierFlags mode) = 0;

    /**
     * @brief Handles the mouse cursor position change.
     * @param cursorX X component of current cursor position.
     * @param cursorY Y component of current cursor position.
     * @param discardUpdates Flag whether cursor position updates shall be
     * discarded.
     */
    virtual void handleMouseMovement(
            double cursorX, double cursorY, bool discardUpdates) = 0;

    /**
     * @brief Handles the window resizing.
     * @param width New window width.
     * @param height New window height.
     */
    virtual void handleWindowResize(int width, int height) = 0;

    /**
     * @brief Highlights the selected object in the scene.
     * @param stencilModifier Callback which modifies stencil buffer test
     * function.
     */
    virtual void highlightSelectedObject(void (*stencilModifier)(Byte)) = 0;
};
