// ISceneMediator.h - Contains declaration of ISceneMediator interface.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

class DrawableObject;
class PerspectiveCamera;

/**
 * @brief Alias for byte.
 */
using Byte = unsigned char;

/**
 * @brief Mediator for AbstractSceneTemplate class.
 */
class ISceneMediator {
  public:
    virtual ~ISceneMediator() = default;

    /**
     * @brief Gets pointer to scene's camera.
     * @return Pointer to scene's camera. If camera is not defined, returns
     * nullptr.
     */
    virtual PerspectiveCamera* getCamera() const = 0;

    /**
     * @brief Gets the currently selected drawable object in the scene.
     * @return The currently selected drawable object in the scene. If none is
     * selected, returns nullptr.
     */
    virtual DrawableObject* getSelectedObject() const = 0;

    /**
     * @brief Finds drawn object by its ID.
     * @param id The ID of object to find.
     * @return Pointer to the object if object with such ID exists. Otherwise
     * returns nullptr.
     */
    virtual DrawableObject* findObjectById(Byte id) = 0;

    /**
     * @brief Inserts copy of the selected object into the scene.
     * @return Pointer to newly inserted object if successful, otherwise returns
     * nullptr.
     */
    virtual DrawableObject* insertSelectedObjectIntoScene() = 0;

    /**
     * @brief Removes the selected object from the scene.
     */
    virtual void removeSelectedObjectFromScene() = 0;

    /**
     * @brief Sets the selected object.
     * @param object Drawable object to set.
     */
    virtual void setSelectedObject(DrawableObject* object) = 0;
};
