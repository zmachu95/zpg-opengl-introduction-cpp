// Application.cpp - Contains definition of Application class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <application/Application.h>
#include <application/EventManager.h>
#include <constants/KeyActions.h>
#include <constants/KeyCodes.h>
#include <constants/KeyModifiers.h>
#include <cstdlib>
#include <ctime>
#include <scenes/ForestScene.h>
#include <scenes/LoginScene.h>
#include <scenes/SolarSystemScene.h>
#include <scenes/TriangleScene.h>

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include <cstdio>

#include <GLFW/glfw3.h>
#include <memory>

static void initializeSpecificOpenGlVersion() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
            GLFW_OPENGL_CORE_PROFILE); //
}

static void window_focus_callback(
        GLFWwindow* window, int focused) {
    printf("window_focus_callback \n");
}

static void window_iconify_callback(
        GLFWwindow* window, int iconified) {
    printf("window_iconify_callback \n");
}

static GLFWwindow* initializeGlfw() {
    // Initialize GLFW
    if (!glfwInit()) {
        throw GlfwInitializationException{};
    }

    GLFWwindow* window = glfwCreateWindow(800, 800, "ZPG", nullptr, nullptr);
    if (!window) {
        throw GlfwInitializationException{};
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    return window;
}

static void initializeGlad() {
    // Initialize GLAD and load OpenGL function pointers
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        throw GladInitializationException{};
    }

    // Get version info
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

Application::Application()
    : m_initialized{false}, m_pause{false}, m_window{nullptr}, m_scenes{},
      m_activeScene{nullptr}, m_halfWindowWidth{0}, m_halfWindowHeight{0} {}

Application::~Application() {
    EventManager::destroy(this->m_window);

    // Clean up and terminate GLFW
    if (this->m_window) {
        glfwDestroyWindow(this->m_window);
    }
    this->m_window = nullptr;
    glfwTerminate();
}

void Application::initialize() {
    this->m_window = initializeGlfw();
    initializeGlad();

    // save current window half-size
    int width, height;
    glfwGetWindowSize(this->m_window, &width, &height);
    this->m_halfWindowHeight = height / 2;
    this->m_halfWindowWidth = width / 2;

    EventManager::initialize(this->m_window);
    this->subscribeListeners();

    srand(time(nullptr));
    this->m_scenes.push_back(std::make_unique<TriangleScene>());
    this->m_scenes.push_back(std::make_unique<LoginScene>());
    this->m_scenes.push_back(std::make_unique<ForestScene>());
    this->m_scenes.push_back(std::make_unique<SolarSystemScene>());
    this->m_activeScene = this->m_scenes.front().get();

    glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glEnable(GL_DEPTH_TEST);
    this->m_initialized = true;
}

void Application::run() {
    if (!this->m_initialized) {
        throw ApplicationNotInitializedException();
    }

    glEnable(GL_DEPTH_TEST);
    // applyOrthogonalProjection();
    float lastTimeUpdate = (float)glfwGetTime();
    while (!glfwWindowShouldClose(this->m_window)) {
        float deltaT = (float)glfwGetTime() - lastTimeUpdate;

        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (this->m_activeScene) {
            this->m_activeScene->draw(!this->m_pause * deltaT);
        }

        // Display the rendered frame and process events
        glfwSwapBuffers(this->m_window);

        lastTimeUpdate += deltaT;
        glfwPollEvents();
    }
}

void Application::subscribeListeners() {
    EventManager::subscribeKeyListener(
            KeyCallback{[this](GLFWwindow* window, int key, int scancode,
                                int action, int mods) {
                this->handleKeyPresses(window, key, scancode, action, mods);
            }});
    EventManager::subscribeWindowFocusListener(
            WindowFocusCallback{window_focus_callback});
    EventManager::subscribeWindowIconifyListener(
            WindowIconifyCallback{window_iconify_callback});
    EventManager::subscribeWindowSizeListener(WindowSizeCallback{
            [this](GLFWwindow* window, int width, int height) {
                this->handleWindowResizeCallback(window, width, height);
            }});
    EventManager::subscribeMouseCursorListener(
            MouseCursorCallback{[this](GLFWwindow* window, double x, double y) {
                this->handleMouseMovement(window, x, y);
            }});
}

void Application::handleKeyPresses(
        GLFWwindow* window, int key, int scancode, int action, int mods) {
    if ((KeyActions)action == KeyActions::PRESSED) {
        switch ((KeyCodes)key) {
            case KeyCodes::KEY_KP_1:
                this->m_activeScene = this->m_scenes[0].get();
                return;
            case KeyCodes::KEY_KP_2:
                this->m_activeScene = this->m_scenes[1].get();
                return;
            case KeyCodes::KEY_KP_3:
                this->m_activeScene = this->m_scenes[2].get();
                return;
            case KeyCodes::KEY_KP_4:
                this->m_activeScene = this->m_scenes[3].get();
                return;
            case KeyCodes::KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GL_TRUE);
                printf("Shutting application down ...\n");
                return;
            case KeyCodes::KEY_SPACE:
                this->m_pause = !this->m_pause;
                printf("%s\n",
                        (this->m_pause ? "Application is now paused..."
                                       : "Application is running again..."));
                return;
        }
    }

    if (this->m_activeScene) {
        this->m_activeScene->handleKeyPresses(
                (KeyCodes)key, (KeyActions)action, (KeyModifierFlags)mods);
    }
}

void Application::handleMouseMovement(
        GLFWwindow* window, double x, double y) {
    if (this->m_activeScene) {
        this->m_activeScene->handleMouseMovement(
                (int)x - this->m_halfWindowWidth,
                (int)y - this->m_halfWindowHeight);
    }

    // reset cursor to the middle of screen
    glfwSetCursorPos(window, this->m_halfWindowWidth, this->m_halfWindowHeight);
}

void Application::handleWindowResizeCallback(
        GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    this->m_halfWindowHeight = height / 2;
    this->m_halfWindowWidth = width / 2;

    if (this->m_activeScene && width > 0 && height > 0) {
        this->m_activeScene->handleWindowResize(width, height);
    }
}
