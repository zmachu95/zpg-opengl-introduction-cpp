// CameraUserInputController.h - Contains declaration of
// CameraUserInputController class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

enum class MovementDirection;
enum class KeyCodes;
enum class KeyActions;
enum class KeyModifierFlags;

/**
 * @brief Buffers user input for controlling camera.
 */
class CameraUserInputController {
  public:
    /**
     * @brief Default CameraUserInputController constructor.
     */
    CameraUserInputController();

    /*
     *
     */

    /**
     * @brief Gets the requested camera movement direction.
     * @return Request camera movement direction as MovementDirection enum
     * value.
     */
    MovementDirection getMovementDirection() const;

    /**
     * @brief Gets the raw camera rotation increment in horizontal direction.
     * The value can be read only once and then needs to be buffered again.
     * @return The raw camera rotation increment in horizontal direction.
     */
    int getHorizontalRotationIncrement();

    /**
     * @brief Gets the raw camera rotation increment in vertical direction. The
     * value can be read only once and then needs to be buffered again.
     * @return The raw camera rotation increment in vertical direction.
     */
    int getVerticalRotationIncrement();

    /*
     *
     */

    /**
     * @brief Handles the mouse cursor position change.
     * @param cursorDeltaX X component of cursor position change.
     * @param cursorDeltaY Y component of cursor position change.
     */
    void handleMouseMove(int cursorDeltaX, int cursorDeltaY);

    /**
     * @brief Handles keyboard presses.
     * @param button The button which invoked the event.
     * @param action The button action.
     * @param mode Button modified mode.
     */
    void handleKeyPresses(
            KeyCodes button, KeyActions action, KeyModifierFlags mode);

  private:
    char m_moveDirection;
    int m_cursorDeltaX;
    int m_cursorDeltaY;

    /**
     * @brief Converts key code to a movement direction bit mask.
     * @param keyCode The keyCode key code.
     * @return
     */
    static char convertKeyCodeToMovementDirectionMask(KeyCodes keyCode);
};
