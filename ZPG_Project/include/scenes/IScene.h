// IScene.h - Contains declaration of IScene interface.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

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
};
