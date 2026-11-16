// CameraUserInputController.cpp - Contains definition of
// CameraUserInputController class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "MovementDirectionEnum.h"
#include <cameras/CameraUserInputController.h>
#include <constants/KeyActions.h>
#include <constants/KeyCodes.h>
#include <constants/KeyModifiers.h>

/**
 * @brief Defines bit masks for requested movement directions.
 */
enum MovementDirectionBitMasks {
    NONE = 0,

    FORWARD = 1 << 0,
    BACKWARD = 1 << 1,
    LEFT = 1 << 2,
    RIGHT = 1 << 3
};

CameraUserInputController CameraUserInputController::s_instance{};

CameraUserInputController::CameraUserInputController()
    : m_moveDirection{0}, m_previousCursorX{0}, m_previousCursorY{0},
      m_currentCursorX{0}, m_currentCursorY{0} {}

MovementDirection CameraUserInputController::getMovementDirection() {
    switch (s_instance.m_moveDirection) {
        case FORWARD | RIGHT:
            return MovementDirection::FORWARD_AND_RIGHT;
        case FORWARD | LEFT:
            return MovementDirection::FORWARD_AND_LEFT;
        case BACKWARD | RIGHT:
            return MovementDirection::BACKWARD_AND_RIGHT;
        case BACKWARD | LEFT:
            return MovementDirection::BACKWARD_AND_LEFT;
        case FORWARD:
            return MovementDirection::FORWARD;
        case BACKWARD:
            return MovementDirection::BACKWARD;
        case RIGHT:
            return MovementDirection::RIGHT;
        case LEFT:
            return MovementDirection::LEFT;
        default:
            return MovementDirection::NONE;
    }
}

float CameraUserInputController::getHorizontalRotationIncrement() {
    double returnedValue =
            s_instance.m_currentCursorX - s_instance.m_previousCursorX;
    s_instance.m_previousCursorX = s_instance.m_currentCursorX;
    return (float)returnedValue;
}

float CameraUserInputController::getVerticalRotationIncrement() {
    double returnedValue =
            s_instance.m_currentCursorY - s_instance.m_previousCursorY;
    s_instance.m_previousCursorY = s_instance.m_currentCursorY;
    return (float)returnedValue;
}

void CameraUserInputController::handleMouseMove(
        double cursorX, double cursorY, bool discardUpdates) {
    s_instance.m_currentCursorX = cursorX;
    s_instance.m_currentCursorY = cursorY;
    if (discardUpdates) {
        s_instance.m_previousCursorX = cursorX;
        s_instance.m_previousCursorY = cursorY;
    }
}

void CameraUserInputController::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {
    char dirFlag =
            CameraUserInputController::convertKeyCodeToMovementDirectionMask(
                    button);

    switch (action) {
        case KeyActions::RELEASED:
            /* remove the bit mask */
            s_instance.m_moveDirection =
                    ~(~s_instance.m_moveDirection | dirFlag);
            break;
        case KeyActions::PRESSED:
            /* add the bit mask */
            s_instance.m_moveDirection = s_instance.m_moveDirection | dirFlag;
            break;
    }
}

char CameraUserInputController::convertKeyCodeToMovementDirectionMask(
        KeyCodes keyCode) {
    switch (keyCode) {
        case KeyCodes::KEY_W:
            return FORWARD;
        case KeyCodes::KEY_A:
            return LEFT;
        case KeyCodes::KEY_S:
            return BACKWARD;
        case KeyCodes::KEY_D:
            return RIGHT;
        default:
            return NONE;
    }
}
