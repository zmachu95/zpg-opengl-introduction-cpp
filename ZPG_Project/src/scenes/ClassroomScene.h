// ClassroomScene.h - Contains declaration of ClassroomScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "AbstractSceneTemplate.h"

class DrawableObject;
class ShaderProgram;
enum class MouseButtonActions;
enum class MouseButtonCodes;
enum class KeyModifierFlags;

/**
 * @brief Scene with EB408 room.
 */
class ClassroomScene : public AbstractSceneTemplate {
  public:
    /**
     * @brief ClassroomScene standard constructor.
     * @param windowWidth Application window width in [px].
     * @param windowHeight Application window height in [px].
     */
    ClassroomScene(int windowWidth, int windowHeight);

    ~ClassroomScene() override = default;

  protected:
    /**
     * @brief Updates the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void updateSceneContents(float deltaT) override;

    /**
     * @brief Handles mouse click event.
     * @param button Clicked mouse button.
     * @param action The mouse button action.
     * @param mode Button modifier mode.
     */
    void handleMouseClick(MouseButtonCodes button, MouseButtonActions action,
            KeyModifierFlags mode) override;

    /**
     * @brief Updates the parameters of skybox shader program.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void updateSkyboxShaderProgram(float deltaT) override;

  private:
    ShaderProgram* m_shaderProgram;
    ShaderProgram* m_clockShaderProgram;
    bool m_useFlashlight;
    bool m_updatedSkyboxShader;
    bool m_initializedShaders;

    /**
     * @brief Creates camera in the scene.
     * @param windowWidth Application window width in [px].
     * @param windowHeight Application window height in [px].
     * @return Pointer to camera object.
     */
    static CameraPtr createCamera(int windowWidth, int windowHeight);

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
     * @brief Initializes uniform variables inside shader programs.
     */
    void initializeShaderPrograms();
};
