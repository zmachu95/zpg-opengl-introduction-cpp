// LightingTestScene.h - Contains declaration of LightingTestScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>
#include <scenes/IScene.h>

#include <array>
#include <cameras/CameraUserInputController.h>
#include <cameras/PerspectiveCamera.h>

class DrawableObject;
class ShaderProgram;
enum class KeyCodes;
enum class KeyActions;
enum class KeyModifierFlags;

using DrawableObjectPtr = std::unique_ptr<DrawableObject>;

/**
 * @brief Scene with 4 spheres to test shader lighting.
 */
class LightingTestScene : public IScene {
  public:
    /**
     * @brief TriangleScene standard constructor.
     */
    LightingTestScene();

    virtual ~LightingTestScene() = default;

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
    std::shared_ptr<ShaderProgram> m_activeShaderProgram;
    std::shared_ptr<ShaderProgram> m_ambientShaderProgram;
    std::shared_ptr<ShaderProgram> m_lambertShaderProgram;
    std::shared_ptr<ShaderProgram> m_phongShaderProgram;
    std::shared_ptr<ShaderProgram> m_blinnShaderProgram;
    std::array<DrawableObjectPtr, 4> m_spheres;

    CameraUserInputController m_cameraController;
    std::unique_ptr<PerspectiveCamera> m_camera;
};
