// Application.cpp - Contains definition of Application class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <application/Application.h>
#include <application/EventManager.h>
#include <cstdlib>
#include <drawables/ModelManager.h>
#include <shaders/ShaderManager.h>

#include <ctime>
#include <scenes/ForestScene.h>
#include <scenes/LoginScene.h>
#include <scenes/SolarSystemScene.h>
#include <scenes/TriangleScene.h>

#include <iostream>

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

static void window_size_callback(
        GLFWwindow* window, int width, int height) {
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}

static void cursor_callback(
        GLFWwindow* window, double x, double y) {
    printf("cursor_callback \n");
}

static void button_callback(
        GLFWwindow* window, int button, int action, int mode) {
    if (action == GLFW_PRESS)
        printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

static void button_callback2(
        GLFWwindow* window, int button, int action, int mode) {
    printf("And this is another button callback!\n");
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
      m_activeScene{nullptr} {}

Application::~Application() {
    ModelManager::destroy();
    ShaderManager::destroy();
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

    ModelManager::initialize();

    EventManager::initialize(this->m_window);
    this->subscribeListeners();

    srand(time(nullptr));
    this->m_scenes.push_back(std::make_unique<TriangleScene>());
    this->m_scenes.push_back(std::make_unique<LoginScene>());
    this->m_scenes.push_back(std::make_unique<ForestScene>());
    this->m_scenes.push_back(std::make_unique<SolarSystemScene>());
    this->m_activeScene = this->m_scenes.front().get();

    glEnable(GL_DEPTH_TEST);
    this->m_initialized = true;
}

void Application::run() {
    if (!this->m_initialized) {
        throw ApplicationNotInitializedException();
    }

    glEnable(GL_DEPTH_TEST);
    applyOrthogonalProjection();
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

void Application::applyOrthogonalProjection() {
    int width, height;
    glfwGetFramebufferSize(this->m_window, &width, &height);
    float ratio = width / (float)height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
}

void Application::subscribeListeners() {
    EventManager::subscribeKeyListener(
            KeyCallback{[this](GLFWwindow* window, int key, int scancode,
                                int action, int mods) {
                this->keyPressesHandler(window, key, scancode, action, mods);
            }});
    EventManager::subscribeWindowFocusListener(
            WindowFocusCallback{window_focus_callback});
    EventManager::subscribeWindowIconifyListener(
            WindowIconifyCallback{window_iconify_callback});
    EventManager::subscribeWindowSizeListener(
            WindowSizeCallback{window_size_callback});
    EventManager::subscribeMouseCursorListener(
            MouseCursorCallback{cursor_callback});
    EventManager::subscribeMouseButtonListener(
            MouseButtonCallback{button_callback});
    EventManager::subscribeMouseButtonListener(
            MouseButtonCallback{button_callback2});
}

void Application::keyPressesHandler(
        GLFWwindow* window, int key, int scancode, int action, int mods) {
    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_1:
            this->m_activeScene = this->m_scenes[0].get();
            break;
        case GLFW_KEY_2:
            this->m_activeScene = this->m_scenes[1].get();
            break;
        case GLFW_KEY_3:
            this->m_activeScene = this->m_scenes[2].get();
            break;
        case GLFW_KEY_4:
            this->m_activeScene = this->m_scenes[3].get();
            break;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            std::cout << "Shutting application down ...\n";
            break;
        case GLFW_KEY_SPACE:
            this->m_pause = !this->m_pause;
            std::cout << (this->m_pause ? "Application is now paused..."
                                        : "Application is running again...")
                      << "\n";
            break;
        }
    }
}
