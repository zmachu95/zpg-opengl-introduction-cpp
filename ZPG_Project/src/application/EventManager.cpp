// EventManager.cpp - Contains definition of EventManager class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <GLFW/glfw3.h>
#include <application/EventManager.h>
#include <cstdio>
#include <utility>

EventManager EventManager::s_instance = EventManager{};

EventManager::EventManager()
    : m_keyListeners{}, m_windowFocusListeners{}, m_windowIconifyListeners{},
      m_windowSizeListeners{}, m_mouseCursorListeners{},
      m_mouseButtonListeners{}, m_initialized{false} {}

void EventManager::destroy(
        GLFWwindow* window) {
    glfwSetErrorCallback(nullptr);
    glfwSetKeyCallback(window, nullptr);
    glfwSetWindowFocusCallback(window, nullptr);
    glfwSetWindowIconifyCallback(window, nullptr);
    glfwSetWindowSizeCallback(window, nullptr);
    glfwSetCursorPosCallback(window, nullptr);
    glfwSetMouseButtonCallback(window, nullptr);

    s_instance.m_keyListeners.clear();
    s_instance.m_windowFocusListeners.clear();
    s_instance.m_windowIconifyListeners.clear();
    s_instance.m_windowSizeListeners.clear();
    s_instance.m_mouseCursorListeners.clear();
    s_instance.m_mouseButtonListeners.clear();
}

static void errorCallback(
        int error, const char* description) {
    fputs(description, stderr);
}

void EventManager::initialize(
        GLFWwindow* window) {
    if (s_instance.m_initialized) {
        return;
    }

    // register all master callbacks which can then notify individual listeners
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, notifyKeyListeners);
    glfwSetWindowFocusCallback(window, notifyWindowFocusListeners);
    glfwSetWindowIconifyCallback(window, notifyWindowIconifyListeners);
    glfwSetWindowSizeCallback(window, notifyWindowSizeListeners);
    glfwSetCursorPosCallback(window, notifyMouseCursorListeners);
    glfwSetMouseButtonCallback(window, notifyMouseButtonListeners);

    s_instance.m_initialized = true;
}

void EventManager::notifyKeyListeners(
        GLFWwindow* window, int key, int scancode, int action, int mods) {
    for (const auto& listener : s_instance.m_keyListeners) {
        listener(window, key, scancode, action, mods);
    }
}

void EventManager::notifyWindowFocusListeners(
        GLFWwindow* window, int focused) {
    for (const auto& listener : s_instance.m_windowFocusListeners) {
        listener(window, focused);
    }
}

void EventManager::notifyWindowIconifyListeners(
        GLFWwindow* window, int iconified) {
    for (const auto& listener : s_instance.m_windowIconifyListeners) {
        listener(window, iconified);
    }
}

void EventManager::notifyWindowSizeListeners(
        GLFWwindow* window, int width, int height) {
    for (const auto& listener : s_instance.m_windowSizeListeners) {
        listener(window, width, height);
    }
}

void EventManager::notifyMouseCursorListeners(
        GLFWwindow* window, double x, double y) {
    for (const auto& listener : s_instance.m_mouseCursorListeners) {
        listener(window, x, y);
    }
}

void EventManager::notifyMouseButtonListeners(
        GLFWwindow* window, int button, int action, int mode) {
    for (const auto& listener : s_instance.m_mouseButtonListeners) {
        listener(window, button, action, mode);
    }
}

void EventManager::subscribeKeyListener(
        KeyCallback&& listener) {
    s_instance.m_keyListeners.push_back(std::move(listener));
}

void EventManager::subscribeWindowFocusListener(
        WindowFocusCallback&& listener) {
    s_instance.m_windowFocusListeners.push_back(std::move(listener));
}

void EventManager::subscribeWindowIconifyListener(
        WindowIconifyCallback&& listener) {
    s_instance.m_windowIconifyListeners.push_back(std::move(listener));
}

void EventManager::subscribeWindowSizeListener(
        WindowSizeCallback&& listener) {
    s_instance.m_windowSizeListeners.push_back(std::move(listener));
}

void EventManager::subscribeMouseCursorListener(
        MouseCursorCallback&& listener) {
    s_instance.m_mouseCursorListeners.push_back(std::move(listener));
}

void EventManager::subscribeMouseButtonListener(
        MouseButtonCallback&& listener) {
    s_instance.m_mouseButtonListeners.push_back(std::move(listener));
}
