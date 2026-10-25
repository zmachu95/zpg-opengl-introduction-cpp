// MovementDirectionEnum.h - Contains definition of MovementDirection enum.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

/**
 * @brief Groups permissible camera movement directions.
 */
enum class MovementDirection {
    NONE,

    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,

    FORWARD_AND_RIGHT,
    FORWARD_AND_LEFT,
    BACKWARD_AND_RIGHT,
    BACKWARD_AND_LEFT
};
