// ClassroomScene.h - Contains declaration of ClassroomScene class.
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
 * @brief Scene with EB408 room.
 */
class ClassroomScene : public IScene {
  public:
    /**
     * @brief ClassroomScene standard constructor.
     */
    ClassroomScene();

    virtual ~ClassroomScene() = default;

    /**
     * @brief Draws the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    virtual void draw(const float deltaT);

    /**
     * @brief Draws the scene's skybox.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    virtual void drawSkybox(const float deltaT);

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
    std::vector<DrawableObjectPtr> m_classroomItems;
    DrawableObjectPtr m_shrek;
    DrawableObjectPtr m_toilet;
    DrawableObjectPtr m_classroom;
    DrawableObjectPtr m_whiteboard;
    DrawableObjectPtr m_door;
    DrawableObjectPtr m_doorFrame;

    DrawableObjectPtr m_teacherTable;
    DrawableObjectPtr m_teacherChair;
    DrawableObjectPtr m_teacherMonitor;
    DrawableObjectPtr m_teacherCase;

    DrawableObjectPtr m_clock;

    DrawableObjectPtr m_skybox;

    ShaderProgramPtr m_shaderProgram;
    ShaderProgramPtr m_skyboxProgram;
    ShaderProgramPtr m_clockShaderProgram;

    std::unordered_map<std::string, glm::mat4> m_pinsRotations;
    CameraUserInputController m_cameraController;
    std::unique_ptr<PerspectiveCamera> m_camera;

    /**
     * @brief Creates group of consisting of table, 2 chairs and 2 PCs at given
     * [x,0,z] coordinates.
     * @param x X coordinate.
     * @param z Z coordinate.
     */
    void createTableWithChairsAndPcs(float x, float z);

    /**
     * @brief Initializes classroom items.
     */
    void initializeClassroom();

    /**
     * @brief Draws clock with current system time.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void drawClock(float deltaT);
};
