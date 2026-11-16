// EventsManager.h - Contains declaration of EventsManager class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

struct GLFWwindow;
class IApplicationMediator;

/**
 * @brief Provides handlers for GLFW user input events.
 */
class EventsManager {
  public:
    /**
     * @brief EventsManager default constructor.
     */
    EventsManager();

    /**
     * @brief EventsManager copy constructor. Removed to prevent multiple
     * copies.
     */
    EventsManager(const EventsManager&) = delete;

    /**
     * @brief EventsManager move constructor. Removed to prevent dangling
     * pointer problems.
     */
    EventsManager(EventsManager&&) noexcept = delete;

    ~EventsManager();

    /*
     *
     */

    /**
     * @brief EventsManager copy operator. Removed to prevent multiple
     * copies.
     */
    EventsManager& operator=(const EventsManager&) = delete;

    /**
     * @brief EventsManager move operator. Removed to prevent dangling
     * pointer problems.
     */
    EventsManager& operator=(EventsManager&&) noexcept = delete;

    /*
     *
     */

    /**
     * @brief Destroys this instance and unhooks it from GLFW input events.
     */
    void destroy();

    /**
     * @brief Initializes the event manager.
     * @param application Pointer to owning application.
     */
    void initialize(IApplicationMediator* application);

  private:
    GLFWwindow* m_window;

    /**
     * @brief Handler function for key press event.
     */
    static void onKeyPress(
            GLFWwindow* window, int key, int scancode, int action, int mods);

    /**
     * @brief Handler function for mouse move event.
     */
    static void onMouseMove(GLFWwindow* window, double x, double y);

    /**
     * @brief Handler function for window resize event.
     */
    static void onWindowResize(GLFWwindow* window, int width, int height);

    /**
     * @brief Handler function for mouse click event.
     */
    static void onMouseClick(
            GLFWwindow* window, int button, int action, int mode);

    /**
     * @brief Handler function for window focus event.
     */
    static void onWindowFocus(GLFWwindow* window, int focused);

    /**
     * @brief Handler function for window iconify event.
     */
    static void onWindowIconify(GLFWwindow* window, int iconified);

    /**
     * @brief Handler function for error reporting.
     */
    static void onError(int error, const char* description);
};
