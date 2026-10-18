// EventManager.h - Contains declaration of EventManager class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <functional>
#include <vector>

struct GLFWwindow;

/**
 * @brief Signature for key press / release callback.
 */
using KeyCallback = std::function<void(
        GLFWwindow* window, int key, int scancode, int action, int mods)>;

/**
 * @brief Signature for window focus callback.
 */
using WindowFocusCallback =
        std::function<void(GLFWwindow* window, int focused)>;

/**
 * @brief Signature for window iconify callback.
 */
using WindowIconifyCallback =
        std::function<void(GLFWwindow* window, int iconified)>;

/**
 * @brief Signature for window resize callback.
 */
using WindowSizeCallback =
        std::function<void(GLFWwindow* window, int width, int height)>;

/**
 * @brief Signature for mouse cursor move callback.
 */
using MouseCursorCallback =
        std::function<void(GLFWwindow* window, double x, double y)>;

/**
 * @brief Signature for mouse button press / release callback.
 */
using MouseButtonCallback = std::function<void(
        GLFWwindow* window, int button, int action, int mode)>;

/**
 * @brief Provides means for registering custom callbacks to OpenGL application.
 */
class EventManager {
  public:
    /**
     * @brief Initializes the event manager for supplied OpenGL window.
     * @param window The OpenGL window.
     */
    static void initialize(GLFWwindow* window);

    /**
     * @brief Destroys the manager and unregisters listeners. To be used
     * upon application closing.
     * @param window The OpenGL window.
     */
    static void destroy(GLFWwindow* window);

    /*
     *
     */

    /**
     * @brief Subscribes listener to Key callback
     * @param listener The listener.
     */
    static void subscribeKeyListener(KeyCallback&& listener);

    /**
     * @brief Subscribes listener to WindowFocus callback
     * @param listener The listener.
     */
    static void subscribeWindowFocusListener(WindowFocusCallback&& listener);

    /**
     * @brief Subscribes listener to WindowIconify callback
     * @param listener The listener.
     */
    static void subscribeWindowIconifyListener(
            WindowIconifyCallback&& listener);

    /**
     * @brief Subscribes listener to WindowResize callback
     * @param listener The listener.
     */
    static void subscribeWindowSizeListener(WindowSizeCallback&& listener);

    /**
     * @brief Subscribes listener to MouseCursorMove callback
     * @param listener The listener.
     */
    static void subscribeMouseCursorListener(MouseCursorCallback&& listener);

    /**
     * @brief Subscribes listener to MouseButton callback
     * @param listener The listener.
     */
    static void subscribeMouseButtonListener(MouseButtonCallback&& listener);

  private:
    static EventManager s_instance;

    bool m_initialized;
    std::vector<KeyCallback> m_keyListeners;
    std::vector<WindowFocusCallback> m_windowFocusListeners;
    std::vector<WindowIconifyCallback> m_windowIconifyListeners;
    std::vector<WindowSizeCallback> m_windowSizeListeners;
    std::vector<MouseCursorCallback> m_mouseCursorListeners;
    std::vector<MouseButtonCallback> m_mouseButtonListeners;

    /**
     * @brief Standard EventManager constructor.
     */
    EventManager();

    /**
     * @brief Notifies all key press / release listeners,
     */
    static void notifyKeyListeners(
            GLFWwindow* window, int key, int scancode, int action, int mods);

    /**
     * @brief Notifies WindowFocus listeners.
     */
    static void notifyWindowFocusListeners(GLFWwindow* window, int focused);

    /**
     * @brief Notifies WindowIconify listeners.
     */
    static void notifyWindowIconifyListeners(GLFWwindow* window, int iconified);

    /**
     * @brief Notifies WindowResized listeners.
     */
    static void notifyWindowSizeListeners(
            GLFWwindow* window, int width, int height);

    /**
     * @brief Notifies MouseCursorMove listeners.
     */
    static void notifyMouseCursorListeners(
            GLFWwindow* window, double x, double y);

    /**
     * @brief Notifies MouseButton listeners.
     */
    static void notifyMouseButtonListeners(
            GLFWwindow* window, int button, int action, int mode);
};
