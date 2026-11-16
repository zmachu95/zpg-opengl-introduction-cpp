// AbstractSceneTemplate.h - Contains declaration of AbstractSceneTemplate
// class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include "DrawableObjectInteractionProvider.h"
#include "ISceneMediator.h"
#include "SceneRepository.h"
#include <cameras/PerspectiveCamera.h>
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <scenes/IScene.h>
#include <string>

class DrawableObject;
class ShaderProgram;
enum class MouseButtonActions;
enum class MouseButtonCodes;
enum class KeyCodes;
enum class KeyActions;
enum class KeyModifierFlags;

/**
 * @brief Alias for byte.
 */
using Byte = unsigned char;

/**
 * @brief Pointer to PerspectiveCamera object.
 */
using CameraPtr = std::unique_ptr<PerspectiveCamera>;

/**
 * @brief Pointer to DrawableObject object.
 */
using DrawableObjectPtr = std::unique_ptr<DrawableObject>;

/**
 * @brief Pointer to ShaderProgram object.
 */
using ShaderProgramPtr = std::unique_ptr<ShaderProgram>;

/**
 * @brief Template method class for scenes.
 */
class AbstractSceneTemplate : public IScene, public ISceneMediator {
  public:
    /**
     * @brief AbstractSceneTemplate standard constructor with custom camera and
     * custom skybox.
     * @param camera Pointer with custom camera.
     * @param skybox Pointer with custom skybox.
     */
    AbstractSceneTemplate(CameraPtr&& camera, DrawableObjectPtr&& skybox);

    /**
     * @brief AbstractSceneTemplate standard constructor with default camera and
     * default skybox.
     * @param windowWidth Application window width in [px].
     * @param windowHeight Application window height in [px].
     */
    AbstractSceneTemplate(int windowWidth, int windowHeight);

    /**
     * @brief AbstractSceneTemplate standard constructor with custom camera and
     * default skybox.
     * @param camera Pointer with custom camera.
     */
    AbstractSceneTemplate(CameraPtr&& camera);

    /**
     * @brief AbstractSceneTemplate standard constructor with default camera and
     * custom skybox.
     * @param windowWidth Application window width in [px].
     * @param windowHeight Application window height in [px].
     * @param skybox Pointer with custom skybox.
     */
    AbstractSceneTemplate(
            int windowWidth, int windowHeight, DrawableObjectPtr&& skybox);

    ~AbstractSceneTemplate() override = default;

    /*
     *
     */

    /**
     * @brief Finds drawn object by its ID.
     * @param id The ID of object to find.
     * @return Pointer to the object if object with such ID exists. Otherwise
     * returns nullptr.
     */
    DrawableObject* findObjectById(Byte id) override;

    /**
     * @brief Gets pointer to scene's camera.
     * @return Pointer to scene's camera. If camera is not defined, returns
     * nullptr.
     */
    PerspectiveCamera* getCamera() const override;

    /**
     * @brief Gets the currently selected drawable object in the scene.
     * @return The currently selected drawable object in the scene. If none is
     * selected, returns nullptr.
     */
    DrawableObject* getSelectedObject() const override;

    /**
     * @brief Gets shader program for supplied drawable object.
     * @param object The drawable object.
     * @return If found, shader program belonging to given drawable object.
     * Otherwise returns nullptr.
     */
    ShaderProgram* getShaderProgram(DrawableObject* object) const;

    /*
     *
     */

    /**
     * @brief Changes the shader program of supplied drawable object.
     * @param object The drawable object.
     * @param newProgram The new shader program to use.
     */
    void changeShaderProgram(DrawableObject* object, ShaderProgram& newProgram);

    /**
     * @brief Sets the selected object.
     * @param object Drawable object to set.
     */
    void setSelectedObject(DrawableObject* object) override;

    /*
     *
     */

    /**
     * @brief Draws the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     * @param stencilModifier Callback which modifies stencil buffer test
     * function.
     */
    void draw(float deltaT, void (*stencilModifier)(Byte)) override;

    /**
     * @brief Draws the scene's skybox.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void drawSkybox(float deltaT) override;

    /**
     * @brief Handles keyboard presses.
     * @param button The button which invoked the event.
     * @param action The button action.
     * @param mode Button modified mode.
     */
    void handleKeyPresses(
            KeyCodes button, KeyActions action, KeyModifierFlags mode) override;

    /**
     * @brief Handles mouse click event.
     * @param button Clicked mouse button.
     * @param action The mouse button action.
     * @param mode Button modifier mode.
     */
    void handleMouseClick(MouseButtonCodes button, MouseButtonActions action,
            KeyModifierFlags mode) override;

    /**
     * @brief Handles mouse click event with object selection.
     * @param clickCoords Mouse click coordinates in window space.
     * @param windowWidth Window width in [px].
     * @param windowHeight Window height in [px].
     * @param objectId ID of selected object.
     * @param button Clicked mouse button.
     * @param action The mouse button action.
     * @param mode Button modifier mode.
     */
    void handleMouseClickWithObjectSelection(const glm::vec3& clickCoords,
            int windowWidth, int windowHeight, Byte objectId,
            MouseButtonCodes button, MouseButtonActions action,
            KeyModifierFlags mode) override;

    /**
     * @brief Handles the mouse cursor position change.
     * @param cursorX X component of current cursor position.
     * @param cursorY Y component of current cursor position.
     * @param discardUpdates Flag whether cursor position updates shall be
     * discarded.
     */
    void handleMouseMovement(
            double cursorX, double cursorY, bool discardUpdates) override;

    /**
     * @brief Handles the window resizing.
     * @param width New window width.
     * @param height New window height.
     */
    void handleWindowResize(int width, int height) override;

    /**
     * @brief Highlights the selected object in the scene.
     * @param stencilModifier Callback which modifies stencil buffer test
     * function.
     */
    void highlightSelectedObject(void (*stencilModifier)(Byte)) override;

    /**
     * @brief Inserts copy of the selected object into the scene.
     * @return Pointer to newly inserted object if successful, otherwise returns
     * nullptr.
     */
    DrawableObject* insertSelectedObjectIntoScene() override;

    /**
     * @brief Removes the selected object from the scene.
     */
    void removeSelectedObjectFromScene() override;

  protected:
    /**
     * @brief Adds new drawable object into the scene.
     * @param generateId Flag whether the new object should receive unique ID.
     * @param verticesData Array of vertices data.
     * @param arrayElementsCount Total number of elements in the vertices data
     * array.
     * @param attributesCount Number of attributes in supplied vertices data.
     * @param uses2dTextures Supply true if model uses 2D textures, otherwise
     * false.
     * @param shaderProgram Shader program to use with the drawable object.
     * @return Reference to just created drawable object.
     */
    DrawableObject& addDrawableObjectFromVerticesData(bool generateId,
            const float* verticesData, size_t arrayElementsCount,
            unsigned int attributesCount, bool uses2dTextures,
            ShaderProgram& shaderProgram);

    /**
     * @brief Adds new shader program into the scene.
     * @param vertexShaderFile Path to file with vertex shader relative to
     * resources/shaders folder.
     * @param fragmentShaderFile Path to file with fragment shader relative to
     * resources/shaders folder.
     * @param rendersSkybox Flag whether the shader program is intended to
     * render skybox.
     * @return Reference to just created shader program.
     */
    ShaderProgram& addShaderProgramFromShaderFiles(
            const std::string& vertexShaderFile,
            const std::string& fragmentShaderFile, bool rendersSkybox);

    /**
     * @brief Updates the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    virtual void updateSceneContents(float deltaT) = 0;

  private:
    CameraPtr m_camera;
    ShaderProgram* m_highlightedObjectsProgram;
    DrawableObjectInteractionProvider m_interactionProvider;
    SceneRepository m_repository;
    DrawableObject* m_selectedObject;
    DrawableObjectPtr m_selectedObjectClone;
    DrawableObjectPtr m_skybox;
    ShaderProgram* m_skyboxShaderProgram;

    /*
     *
     */

    /**
     * @brief Creates default skybox.
     * @return Pointer with skybox drawable object.
     */
    static DrawableObjectPtr createDefaultSkybox();

    /**
     * @brief Creates default camera.
     * @param windowWidth Application window width in [px].
     * @param windowHeight Application window height in [px].
     * @return Pointer with camera.
     */
    static CameraPtr createDefaultCamera(int windowWidth, int windowHeight);

    /*
     *
     */

    /**
     * @brief Updates the scene camera.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void updateCamera(float deltaT);
};
