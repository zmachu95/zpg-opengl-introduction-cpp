// ClassroomScene.h - Contains declaration of ClassroomScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "AbstractSceneTemplate.h"

class DrawableObject;
class ShaderProgram;

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

  private:
    DrawableObject* m_shrek;
    DrawableObject* m_toilet;
    DrawableObject* m_classroom;
    DrawableObject* m_whiteboard;
    DrawableObject* m_door;
    DrawableObject* m_doorFrame;

    DrawableObject* m_teacherTable;
    DrawableObject* m_teacherChair;
    DrawableObject* m_teacherMonitor;
    DrawableObject* m_teacherCase;

    DrawableObject* m_clock;

    ShaderProgram* m_shaderProgram;
    ShaderProgram* m_clockShaderProgram;

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
};
