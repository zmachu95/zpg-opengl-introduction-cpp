// Application.h - Contains declaration of Application class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "EventsManager.h"
#include "IApplicationMediator.h"
#include <application/IApplication.h>
#include <memory>
#include <vector>

class IScene;
struct GLFWwindow;

using Byte = unsigned char;
using ScenePtr = std::unique_ptr<IScene>;

/**
 * @brief The main application class.
 */
class Application : public IApplicationMediator, public IApplication {
  public:
    /**
     * @brief Standard Application constructor.
     */
    Application(int windowWidth, int windowHeight);

    /**
     * @brief Application copy constructor. Removed to prevent multiple copies.
     */
    Application(const Application&) = delete;

    /**
     * @brief Application copy constructor. Removed to prevent dangling
     * reference problems.
     */
    Application(Application&&) noexcept = delete;

    ~Application() override;

    /*
     *
     */

    /**
     * @brief Application copy operator. Removed to prevent multiple copies.
     */
    Application& operator=(const Application&) = delete;

    /**
     * @brief Application copy constructor. Removed to prevent dangling
     * reference problems.
     */
    Application& operator=(Application&&) noexcept = delete;

    /*
     *
     */

    /**
     * @brief Gets the currently active scene.
     * @return Pointer with currently active scene.
     */
    IScene* getActiveScene() const override;

    /**
     * @brief Gets the last mouse cursor position.
     * @param x Output parameter with x coordinate.
     * @param y Output parameter with y coordinate.
     */
    void getLastMousePosition(double& x, double& y) const override;

    /**
     * @brief Gets the application main window.
     * @return Pointer with application main window.
     */
    GLFWwindow* getWindow() const override;

    /**
     * @brief Gets the application main window's size.
     * @param width Output parameter with window's width in [px].
     * @param height Output parameter with window's height in [px].
     */
    void getWindowSize(int& width, int& height) override;

    /**
     * @brief Gets whether the mouse cursor has been activated in the
     * application main window.
     * @return true if cursor is active, otherwise returns false.
     */
    bool isMouseCursorActivated() const override;

    /**
     * @brief Gets whether the currently active scene is paused.
     * @return true if the scene is paused, otherwise returns false.
     */
    bool isPaused() const override;

    /**
     * @brief Queries the clicked pixel for its color, z-buffer depth and
     * stencil index.
     * @param color Output parameter with pixel color.
     * @param depthComponent Output parameter with z-buffer depth.
     * @param stencilIndex Output parameter with stencil index.
     */
    void queryClickedPixel(Color& color, float& depthComponent,
            unsigned int& stencilIndex) override;

    /*
     *
     */

    /**
     * @brief Resizes the viewport to given size.
     * @param width New width in [px].
     * @param height New height in [px].
     */
    void resizeViewPort(int width, int height) override;

    /**
     * @brief Sets the active scene by its index.
     * @param index The index.
     */
    void setActiveSceneByIndex(size_t index) override;

    /**
     * @brief Sets the last mouse cursor position.
     * @param x X coordinate to store.
     * @param y Y coordinate to store.
     */
    void setLastMousePosition(double x, double y) override;

    /**
     * @brief Toggles the activation mouse cursor.
     */
    void toggleActivateMouseCursor() override;

    /**
     * @brief Toggles pause of currently active scene.
     */
    void togglePause() override;

    /*
     *
     */

    /**
     * @brief Closes the application main window.
     */
    void closeWindow() override;

    /**
     * @brief Initializes the OpenGL application.
     * @throw GlfwInitializationException - Thrown if GLFW could not be
     * initialized.
     * @throw GladInitializationException - Thrown if GLAD could not be
     * initialized.
     */
    void initialize() override;

    /**
     * @brief Runs the application.
     * @throw ApplicationNotInitializedException - Thrown if the application is
     * not initialized.
     */
    void run() override;

  private:
    IScene* m_activeScene;
    bool m_cursorActive;
    EventsManager m_eventsManager;
    bool m_initialized;
    double m_mouseX;
    double m_mouseY;
    bool m_pause;
    std::vector<ScenePtr> m_scenes;
    GLFWwindow* m_window;
    int m_windowHeight;
    int m_windowWidth;

    /*
     *
     */

    /**
     * @brief Modifies stencil test function so that ID of currently drawn
     * object is stored into stencil buffer.
     * @param objectId ID of object to store into stencil buffer.
     */
    static void modifyDrawingStencilFunction(Byte objectId);

    /**
     * @brief Modifies stencil test function so that object with supplied ID is
     * not replaced with new pixels.
     * @param objectId ID of object to keep.
     */
    static void modifyHighlightingStencilFunction(Byte objectId);

    /*
     *
     */

    /**
     * @brief Initializes specific OpenGL version.
     */
    void initializeSpecificOpenGlVersion();

    /**
     * @brief Initializes GLFW library.
     */
    void initializeGlfw();

    /**
     * @brief Initializes GLAD library.
     */
    void initializeGlad();
};
