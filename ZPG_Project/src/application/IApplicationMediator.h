// IApplicationMediator.h - Contains declaration of IApplicationMediator
// interface.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <array>

class IScene;
struct GLFWwindow;

/**
 * @brief Represents RGBA color values.
 */
using Color = std::array<unsigned char, 4>;

/**
 * @brief Mediator for Application class.
 */
class IApplicationMediator {
  public:
    virtual ~IApplicationMediator() = default;

    /**
     * @brief Closes the application main window.
     */
    virtual void closeWindow() = 0;

    /**
     * @brief Gets the currently active scene.
     * @return Pointer with currently active scene.
     */
    virtual IScene* getActiveScene() const = 0;

    /**
     * @brief Gets the last mouse cursor position.
     * @param x Output parameter with x coordinate.
     * @param y Output parameter with y coordinate.
     */
    virtual void getLastMousePosition(double& x, double& y) const = 0;

    /**
     * @brief Gets the application main window.
     * @return Pointer with application main window.
     */
    virtual GLFWwindow* getWindow() const = 0;

    /**
     * @brief Gets the application main window's size.
     * @param width Output parameter with window's width in [px].
     * @param height Output parameter with window's height in [px].
     */
    virtual void getWindowSize(int& width, int& height) = 0;

    /**
     * @brief Gets whether the mouse cursor has been activated in the
     * application main window.
     * @return true if cursor is active, otherwise returns false.
     */
    virtual bool isMouseCursorActivated() const = 0;

    /**
     * @brief Gets whether the currently active scene is paused.
     * @return true if the scene is paused, otherwise returns false.
     */
    virtual bool isPaused() const = 0;

    /**
     * @brief Queries the clicked pixel for its color, z-buffer depth and
     * stencil index.
     * @param color Output parameter with pixel color.
     * @param depthComponent Output parameter with z-buffer depth.
     * @param stencilIndex Output parameter with stencil index.
     */
    virtual void queryClickedPixel(Color& color, float& depthComponent,
            unsigned int& stencilIndex) = 0;

    /**
     * @brief Resizes the viewport to given size.
     * @param width New width in [px].
     * @param height New height in [px].
     */
    virtual void resizeViewPort(int width, int height) = 0;

    /**
     * @brief Sets the active scene by its index.
     * @param index The index.
     */
    virtual void setActiveSceneByIndex(size_t index) = 0;

    /**
     * @brief Sets the last mouse cursor position.
     * @param x X coordinate to store.
     * @param y Y coordinate to store.
     */
    virtual void setLastMousePosition(double x, double y) = 0;

    /**
     * @brief Toggles the activation mouse cursor.
     */
    virtual void toggleActivateMouseCursor() = 0;

    /**
     * @brief Toggles pause of currently active scene.
     */
    virtual void togglePause() = 0;
};
