// TriangleScene.h - Contains declaration of TriangleScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "AbstractSceneTemplate.h"
#include <memory>

class ITranslation;
class IRotation;

/**
 * @brief Pointer to ITranslation object.
 */
using TranslationPtr = std::shared_ptr<ITranslation>;

/**
 * @brief Pointer to IRotation object.
 */
using RotationPtr = std::shared_ptr<IRotation>;

/**
 * @brief Scene with a single rainbow triangle.
 */
class TriangleScene : public AbstractSceneTemplate {
  public:
    /**
     * @brief TriangleScene standard constructor.
     * @param windowWidth Application window width in [px].
     * @param windowHeight Application window height in [px].
     */
    TriangleScene(int windowWidth, int windowHeight);

    ~TriangleScene() override = default;

  protected:
    /**
     * @brief Updates the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void updateSceneContents(float deltaT) override;

  private:
    TranslationPtr m_translation;
    RotationPtr m_rotation;
};
