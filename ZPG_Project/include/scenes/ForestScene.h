// ForestScene.h - Contains declaration of ForestScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>
#include <scenes/IScene.h>
#include <vector>

#include <cameras/CameraUserInputController.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <string>
#include <unordered_map>

class DrawableObject;
class ShaderProgram;
class PerspectiveCamera;
enum class KeyCodes;
enum class KeyActions;
enum class KeyModifierFlags;

using DrawableObjectPtr = std::unique_ptr<DrawableObject>;
using ShaderProgramPtr = std::unique_ptr<ShaderProgram>;

/**
 * @brief Scene with random trees and bushes.
 */
class ForestScene : public IScene {
  public:
    /**
     * @brief ForestScene standard constructor.
     */
    ForestScene();

    virtual ~ForestScene() = default;

    /**
     * @brief Draws the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    virtual void draw(const float deltaT);

    /**
     * @brief Handles the mouse cursor position change.
     * @param cursorDeltaX X component of cursor position change.
     * @param cursorDeltaY Y component of cursor position change.
     */
    virtual void handleMouseMovement(int cursorDeltaX, int cursorDeltaY);

    /**
     * @brief Handles keyboard presses.
     * @param button The button which invoked the event.
     * @param action The button action.
     * @param mode Button modified mode.
     */
    virtual void handleKeyPresses(
            KeyCodes button, KeyActions action, KeyModifierFlags mode);

    /**
     * @brief Handles the window resizing.
     * @param width New window width.
     * @param height New window height.
     */
    virtual void handleWindowResize(int width, int height);

  private:
    std::vector<DrawableObjectPtr> m_trees;
    std::vector<DrawableObjectPtr> m_bushes;
    DrawableObjectPtr m_plain;
    DrawableObjectPtr m_clock;

    ShaderProgramPtr m_plainShaderProgram;
    ShaderProgramPtr m_treesShaderProgram;
    ShaderProgramPtr m_bushesShaderProgram;
    ShaderProgramPtr m_clockShaderProgram;

    CameraUserInputController m_cameraController;
    std::unique_ptr<PerspectiveCamera> m_camera;
    std::unordered_map<std::string, glm::mat4> m_pinsRotations;

    /**
     * @brief Creates random trees.
     * @param treesCount Number of trees to create.
     */
    void createRandomTrees(const int treesCount);

    /**
     * @brief Creates random bushes.
     * @param treesCount Number of bushes to create.
     */
    void createRandomBushes(const int bushesCount);

    /**
     * @brief Draws clock with current system time.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void drawClock(float deltaT);
};
