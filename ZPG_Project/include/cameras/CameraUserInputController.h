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
     * @brief Gets the requested camera movement direction.
     * @return Request camera movement direction as MovementDirection enum
     * value.
     */
    static MovementDirection getMovementDirection();

    /**
     * @brief Gets the raw camera rotation increment in horizontal direction.
     * The value can be read only once and then needs to be buffered again.
     * @return The raw camera rotation increment in horizontal direction.
     */
    static float getHorizontalRotationIncrement();

    /**
     * @brief Gets the raw camera rotation increment in vertical direction. The
     * value can be read only once and then needs to be buffered again.
     * @return The raw camera rotation increment in vertical direction.
     */
    static float getVerticalRotationIncrement();

    /*
     *
     */

    /**
     * @brief Handles the mouse cursor position change.
     * @param cursorX X component of current cursor position.
     * @param cursorY Y component of current cursor position.
     * @param discardUpdates Supply true to discard the cursor position updates.
     */
    static void handleMouseMove(
            double cursorX, double cursorY, bool discardUpdates);

    /**
     * @brief Handles keyboard presses.
     * @param button The button which invoked the event.
     * @param action The button action.
     * @param mode Button modified mode.
     */
    static void handleKeyPresses(
            KeyCodes button, KeyActions action, KeyModifierFlags mode);

  private:
    static CameraUserInputController s_instance;

    char m_moveDirection;
    double m_previousCursorX;
    double m_previousCursorY;
    double m_currentCursorX;
    double m_currentCursorY;

    /*
     *
     */

    /**
     * @brief Default CameraUserInputController constructor.
     */
    CameraUserInputController();

    /**
     * @brief Converts key code to a movement direction bit mask.
     * @param keyCode The keyCode key code.
     * @return Movement direction bit mask.
     */
    static char convertKeyCodeToMovementDirectionMask(KeyCodes keyCode);
};
