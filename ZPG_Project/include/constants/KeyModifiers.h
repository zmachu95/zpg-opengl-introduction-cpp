// KeyModifierFlags.h - Contains definition of KeyModifierFlags enum.
//
// Coded by Zdenek Machu (MAC0690), October 2026
// Copied from https://www.glfw.org/docs/3.3/group__mods.html

#pragma once

/**
 * @brief Enlists possible bit flags for various keyboard modifiers.
 */
enum class KeyModifierFlags {
    NONE = 0,

    SHIFT = 0x0001,
    CTRL = 0x0002,
    ALT = 0x0004,
    SUPER = 0x0008,

    CAPS_LOCK = 0x0010,
    NUM_LOCK = 0x0020
};
