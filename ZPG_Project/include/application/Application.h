// Application.h - Contains declaration of Application class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

class IScene;
struct GLFWwindow;

/**
 * @brief Indicates that GLFW could not be initialized.
 */
class GlfwInitializationException : public std::runtime_error {
  public:
    GlfwInitializationException()
        : std::runtime_error("Failed to initialize GLFW!") {}
};

/**
 * @brief Indicates that GLAD could not initialized.
 */
class GladInitializationException : public std::runtime_error {
  public:
    GladInitializationException()
        : std::runtime_error("Failed to initialize GLAD!") {}
};

/**
 * @brief Indicates that the application is not fully initialized.
 */
class ApplicationNotInitializedException : public std::runtime_error {
  public:
    ApplicationNotInitializedException()
        : std::runtime_error("The application is not initialized!") {}
};

using ScenePtr = std::unique_ptr<IScene>;

/**
 * @brief The main application class.
 */
class Application {
  public:
    /**
     * @brief Standard Application constructor.
     */
    Application();

    /**
     * @brief Application copy constructor. Deleted to avoid unwanted copies.
     */
    Application(const Application&) = delete;

    virtual ~Application();

    /*
     *
     */

    /**
     * @brief Application copy-by-reference operator. Deleted to avoid unwanted
     * copies.
     */
    Application& operator=(const Application&) = delete;

    /**
     * @brief Initializes the OpenGL application.
     * @throw GlfwInitializationException - Thrown if GLFW could not be
     * initialized.
     * @throw GladInitializationException - Thrown if GLAD could not be
     * initialized.
     */
    void initialize();

    /**
     * @brief Runs the application.
     * @throw ApplicationNotInitializedException - Thrown if the application is
     * not initialized.
     */
    void run();

  private:
    bool m_initialized;
    bool m_pause;
    GLFWwindow* m_window;
    std::vector<ScenePtr> m_scenes;
    IScene* m_activeScene;
    int m_halfWindowWidth;
    int m_halfWindowHeight;

    /*
     *
     */

    /**
     * @brief Handler function for key press event.
     */
    void handleKeyPresses(
            GLFWwindow* window, int key, int scancode, int action, int mods);

    /**
     * @brief Handler function for mouse move event.
     */
    void handleMouseMovement(GLFWwindow* window, double x, double y);

    /**
     * @brief Handler function for window resize event.
     */
    void handleWindowResizeCallback(GLFWwindow* window, int width, int height);

    /*
     *
     */

    /**
     * @brief Subscribes all OpenGL application listeners.
     */
    void subscribeListeners();
};
