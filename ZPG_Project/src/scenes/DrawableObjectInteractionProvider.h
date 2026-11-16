// DrawableObjectInteractionProvider.h - Contains declaration of
// DrawableObjectInteractionProvider class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <unordered_map>

enum class MouseButtonActions;
enum class MouseButtonCodes;
enum class KeyCodes;
enum class KeyActions;
enum class KeyModifierFlags;
class DrawableObject;
class ISceneMediator;
class ITranslation;
class PerspectiveCamera;

/**
 * @brief Pointer to ITranslation object.
 */
using TranslationPtr = std::shared_ptr<ITranslation>;

/**
 * @brief Contains parameters for animation over a line segment.
 */
struct LineSegmentPointsAndTransformation {
    glm::vec3 start;
    glm::vec3 end;
    ITranslation* translation;
    float t;
    int sign;
};

/**
 * @brief Alias for byte.
 */
using Byte = unsigned char;

/**
 * @brief Provides interaction with scene's drawable objects.
 */
class DrawableObjectInteractionProvider {
  public:
    /**
     * @brief DrawableObjectInteractionProvider standard constructor.
     * @param owningScene Reference to scene which will own the new
     * DrawableObjectInteractionProvider object.
     */
    DrawableObjectInteractionProvider(ISceneMediator& owningScene);

    /**
     * @brief Animates all tracked models.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void animateObjects(float deltaT);

    /**
     * @brief Handles mouse click event.
     * @param clickCoords Mouse click coordinates in window space.
     * @param windowWidth Window width in [px].
     * @param windowHeight Window height in [px].
     * @param objectId ID of selected object.
     * @param button Clicked mouse button.
     * @param action The mouse button action.
     * @param mode Button modifier mode.
     */
    void handleMouseClick(const glm::vec3& clickCoords, int windowWidth,
            int windowHeight, Byte objectId, MouseButtonCodes button,
            MouseButtonActions action, KeyModifierFlags mode);

    /**
     * @brief Handles keyboard presses.
     * @param button The button which invoked the event.
     * @param action The button action.
     * @param mode Button modified mode.
     */
    void handleKeyPresses(
            KeyCodes button, KeyActions action, KeyModifierFlags mode);

  private:
    std::unordered_map<DrawableObject*, LineSegmentPointsAndTransformation>
            m_animatedObjects;
    glm::vec3 m_clickedWorldCoords;
    glm::vec3 m_lineSegmentStart;
    glm::vec3 m_lineSegmentEnd;
    ISceneMediator& m_owningScene;

    /**
     * @brief Selects the object in scene by its ID.
     * @param objectId The object's ID.
     */
    void selectModel(Byte objectId);

    /**
     * @brief Sets the currently clicked world coordinates via unprojecting.
     * @param camera Pointer to scene's camera.
     * @param clickCoords Mouse click coordinates in window space.
     * @param windowWidth Window width in [px].
     * @param windowHeight Window height in [px].
     */
    void setClickedWorldCoordinates(PerspectiveCamera* camera,
            const glm::vec3& clickCoords, int windowWidth, int windowHeight);

    /**
     * @brief Inserts currently selected drawable object as animated.
     */
    void insertAnimatedObject();

    /**
     * @brief Inserts currently selected drawable object as static.
     */
    void insertStaticObject();

    /**
     * @brief Base function for inserting drawable objects into scene.
     * @param insertedObject Output parameter for inserted object.
     * @param translationPtr Output parameter for inserted object's translation.
     */
    void insertSelectedObjectIntoScene(
            DrawableObject*& insertedObject, ITranslation*& translationPtr);

    /**
     * @brief Deletes selected drawable object from the scene.
     */
    void deleteSelectedObject();
};
