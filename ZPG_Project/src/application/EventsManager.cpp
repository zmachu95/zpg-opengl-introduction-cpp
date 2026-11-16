// EventsManager.cpp - Contains definition of EventsManager class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#include "EventsManager.h"
#include "IApplicationMediator.h"
#include <GLFW/glfw3.h>
#include <constants/KeyActions.h>
#include <constants/KeyCodes.h>
#include <constants/KeyModifiers.h>
#include <constants/MouseButtonActions.h>
#include <constants/MouseButtonCodes.h>
#include <cstdio>
#include <glm/ext/vector_float3.hpp>
#include <scenes/IScene.h>

EventsManager::EventsManager() : m_window{nullptr} {}

EventsManager::~EventsManager() { this->destroy(); }

void EventsManager::destroy() {
    if (m_window) {
        glfwSetErrorCallback(nullptr);
        glfwSetKeyCallback(m_window, nullptr);
        glfwSetWindowFocusCallback(m_window, nullptr);
        glfwSetWindowIconifyCallback(m_window, nullptr);
        glfwSetWindowSizeCallback(m_window, nullptr);
        glfwSetCursorPosCallback(m_window, nullptr);
        glfwSetMouseButtonCallback(m_window, nullptr);
        glfwSetWindowUserPointer(m_window, nullptr);
    }
}

void EventsManager::initialize(
        IApplicationMediator* application) {
    // store the application pointer into GLFW window
    this->m_window = application->getWindow();
    glfwSetWindowUserPointer(this->m_window, application);

    glfwSetErrorCallback(EventsManager::onError);
    glfwSetKeyCallback(this->m_window, EventsManager::onKeyPress);
    glfwSetWindowFocusCallback(this->m_window, EventsManager::onWindowFocus);
    glfwSetWindowIconifyCallback(
            this->m_window, EventsManager::onWindowIconify);
    glfwSetWindowSizeCallback(this->m_window, EventsManager::onWindowResize);
    glfwSetCursorPosCallback(this->m_window, EventsManager::onMouseMove);
    glfwSetMouseButtonCallback(this->m_window, EventsManager::onMouseClick);

    double mouseX, mouseY;
    glfwGetCursorPos(this->m_window, &mouseX, &mouseY);
    onMouseMove(this->m_window, mouseX, mouseY);
}

void EventsManager::onError(
        int error, const char* description) {
    fputs(description, stderr);
}

void EventsManager::onKeyPress(
        GLFWwindow* window, int key, int scancode, int action, int mods) {
    IApplicationMediator* application =
            (IApplicationMediator*)glfwGetWindowUserPointer(window);

    if ((KeyActions)action == KeyActions::PRESSED
            && (KeyModifierFlags)mods == KeyModifierFlags::NONE) {
        size_t index;
        switch ((KeyCodes)key) {
            case KeyCodes::KEY_KP_1:
            case KeyCodes::KEY_KP_2:
            case KeyCodes::KEY_KP_3:
            case KeyCodes::KEY_KP_4:
            case KeyCodes::KEY_KP_5:
            case KeyCodes::KEY_KP_6:
            case KeyCodes::KEY_KP_7:
            case KeyCodes::KEY_KP_8:
                index = (size_t)key - (size_t)KeyCodes::KEY_KP_1;
                application->setActiveSceneByIndex(index);
                return;
            case KeyCodes::KEY_ESCAPE:
                application->closeWindow();
                return;
            case KeyCodes::KEY_SPACE:
                application->togglePause();
                return;
            case KeyCodes::KEY_TAB:
                application->toggleActivateMouseCursor();
                return;
        }
    }

    // send the key press event to currently active scene
    if (IScene* activeScene = application->getActiveScene()) {
        activeScene->handleKeyPresses(
                (KeyCodes)key, (KeyActions)action, (KeyModifierFlags)mods);
    }
}

void EventsManager::onMouseMove(
        GLFWwindow* window, double x, double y) {
    IApplicationMediator* application =
            (IApplicationMediator*)glfwGetWindowUserPointer(window);
    application->setLastMousePosition(x, y);

    // send the mouse move event to currently active scene
    if (IScene* activeScene = application->getActiveScene()) {
        activeScene->handleMouseMovement(x, y,
                application->isMouseCursorActivated()
                        || application->isPaused());
    }
}

void EventsManager::onWindowResize(
        GLFWwindow* window, int width, int height) {
    IApplicationMediator* application =
            (IApplicationMediator*)glfwGetWindowUserPointer(window);
    application->resizeViewPort(width, height);

    // send the window resize event to currently active scene
    if (IScene* activeScene = application->getActiveScene()) {
        activeScene->handleWindowResize(width, height);
    }
}

void EventsManager::onMouseClick(
        GLFWwindow* window, int button, int action, int mode) {
    IApplicationMediator* application =
            (IApplicationMediator*)glfwGetWindowUserPointer(window);

    if (application->isMouseCursorActivated()
            && (MouseButtonActions)action == MouseButtonActions::PRESSED) {
        Color color{};
        float depth;
        unsigned int stencilIndex;
        application->queryClickedPixel(color, depth, stencilIndex);
        printf("Clicked object ID: %d\n", stencilIndex);

        if (IScene* activeScene = application->getActiveScene()) {
            double x, y;
            application->getLastMousePosition(x, y);

            int windowWidth, windowHeight;
            application->getWindowSize(windowWidth, windowHeight);

            activeScene->handleMouseClickWithObjectSelection(
                    glm::vec3{x, windowHeight - y - 1, depth}, windowWidth,
                    windowHeight, (Byte)stencilIndex, (MouseButtonCodes)button,
                    (MouseButtonActions)action, (KeyModifierFlags)mode);
        }
    } else {
        if (IScene* activeScene = application->getActiveScene()) {
            activeScene->handleMouseClick((MouseButtonCodes)button,
                    (MouseButtonActions)action, (KeyModifierFlags)mode);
        }
    }
}

void EventsManager::onWindowFocus(
        GLFWwindow* window, int focused) {
    printf("window_focus_callback \n");
}

void EventsManager::onWindowIconify(
        GLFWwindow* window, int iconified) {
    printf("window_iconify_callback \n");
}
