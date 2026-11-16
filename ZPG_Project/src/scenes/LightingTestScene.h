// LightingTestScene.h - Contains declaration of LightingTestScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "AbstractSceneTemplate.h"
#include <array>

enum class KeyCodes;
enum class KeyActions;
enum class KeyModifierFlags;

class DrawableObject;
class ShaderProgram;

/**
 * @brief Scene with 4 spheres to test shader lighting.
 */
class LightingTestScene : public AbstractSceneTemplate {
  public:
    /**
     * @brief LightingTestScene standard constructor.
     * @param windowWidth Application window width in [px].
     * @param windowHeight Application window height in [px].
     */
    LightingTestScene(int windowWidth, int windowHeight);

    ~LightingTestScene() override = default;

    /**
     * @brief Handles keyboard presses.
     * @param button The button which invoked the event.
     * @param action The button action.
     * @param mode Button modified mode.
     */
    void handleKeyPresses(
            KeyCodes button, KeyActions action, KeyModifierFlags mode) override;

  protected:
    /**
     * @brief Updates the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void updateSceneContents(float deltaT) override;

  private:
    ShaderProgram* m_shaderProgram;
    bool m_initializedPointLight;

    /**
     * @brief Creates camera in the scene.
     * @param windowWidth Application window width in [px].
     * @param windowHeight Application window height in [px].
     * @return Pointer to camera object.
     */
    static CameraPtr createCamera(int windowWidth, int windowHeight);

    /**
     * @brief Initializes uniform variables inside shader programs.
     */
    void initializeShaderPrograms();
};
