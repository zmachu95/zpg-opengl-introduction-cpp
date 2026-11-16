// Application.cpp - Contains definition of Application class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "Application.h"
#include "EventsManager.h"
#include "IApplicationMediator.h"
#include <application/IApplication.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <scenes/IScene.h>
#include <scenes/SceneFactory.h>

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include <GLFW/glfw3.h>

Application::Application(
        int windowWidth, int windowHeight)
    : m_activeScene{nullptr}, m_cursorActive{true}, m_eventsManager{},
      m_initialized{false}, m_mouseX{0}, m_mouseY{0}, m_pause{false},
      m_scenes{}, m_window{nullptr}, m_windowHeight{windowHeight},
      m_windowWidth{windowWidth} {}

Application::~Application() {
    this->m_eventsManager.destroy();

    // Clean up and terminate GLFW
    if (this->m_window) {
        glfwDestroyWindow(this->m_window);
    }
    this->m_window = nullptr;
    glfwTerminate();
}

void Application::initialize() {
    if (this->m_initialized) {
        return;
    }

    initializeGlfw();
    initializeGlad();

    srand(time(nullptr));
    this->m_scenes.push_back(
            SceneFactory::createScene(AvailableScenes::CLASSROOM,
                    this->m_windowWidth, this->m_windowHeight));
    this->m_scenes.push_back(
            SceneFactory::createScene(AvailableScenes::SHREK_AND_FIONA,
                    this->m_windowWidth, this->m_windowHeight));
    this->m_scenes.push_back(
            SceneFactory::createScene(AvailableScenes::TRIANGLE,
                    this->m_windowWidth, this->m_windowHeight));
    this->m_scenes.push_back(SceneFactory::createScene(
            AvailableScenes::LOGIN, this->m_windowWidth, this->m_windowHeight));
    this->m_scenes.push_back(SceneFactory::createScene(AvailableScenes::FOREST,
            this->m_windowWidth, this->m_windowHeight));
    this->m_scenes.push_back(
            SceneFactory::createScene(AvailableScenes::SOLAR_SYSTEM,
                    this->m_windowWidth, this->m_windowHeight));
    this->m_scenes.push_back(
            SceneFactory::createScene(AvailableScenes::WALLCLOCK,
                    this->m_windowWidth, this->m_windowHeight));
    this->m_scenes.push_back(
            SceneFactory::createScene(AvailableScenes::LIGHTING_TEST,
                    this->m_windowWidth, this->m_windowHeight));

    this->m_activeScene = this->m_scenes.front().get();
    this->m_eventsManager.initialize(this);
    this->toggleActivateMouseCursor();

    this->m_initialized = true;
}

void Application::initializeSpecificOpenGlVersion() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Application::initializeGlfw() {
    // Initialize GLFW
    if (!glfwInit()) {
        throw GlfwInitializationException{};
    }

    GLFWwindow* window = glfwCreateWindow(
            this->m_windowWidth, this->m_windowHeight, "ZPG", nullptr, nullptr);
    if (!window) {
        throw GlfwInitializationException{};
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    this->m_window = window;
}

void Application::initializeGlad() {
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

void Application::run() {
    if (!this->m_initialized) {
        throw ApplicationNotInitializedException();
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    float lastTimeUpdate = (float)glfwGetTime();

    while (!glfwWindowShouldClose(this->m_window)) {
        float deltaT = (float)glfwGetTime() - lastTimeUpdate;

        // Clear color, depth and stencil buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
                | GL_STENCIL_BUFFER_BIT);

        if (this->m_activeScene) {
            glStencilMask(0);
            this->m_activeScene->drawSkybox(!this->m_pause * deltaT);
            glStencilMask(0xFF);
            glClear(GL_DEPTH_BUFFER_BIT);

            this->m_activeScene->draw(!this->m_pause * deltaT,
                    Application::modifyDrawingStencilFunction);

            glStencilMask(0);
            this->m_activeScene->highlightSelectedObject(
                    Application::modifyHighlightingStencilFunction);
            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
        }

        // Display the rendered frame and process events
        glfwPollEvents();
        glfwSwapBuffers(this->m_window);
        lastTimeUpdate += deltaT;
    }
}

void Application::closeWindow() {
    glfwSetWindowShouldClose(this->m_window, GL_TRUE);
    printf("Shutting application down ...\n");
}

IScene* Application::getActiveScene() const { return this->m_activeScene; }

void Application::getLastMousePosition(
        double& x, double& y) const {
    x = this->m_mouseX;
    y = this->m_mouseY;
}

GLFWwindow* Application::getWindow() const { return this->m_window; }

void Application::getWindowSize(
        int& width, int& height) {
    width = this->m_windowWidth;
    height = this->m_windowHeight;
}

bool Application::isMouseCursorActivated() const {
    return this->m_cursorActive;
}

bool Application::isPaused() const { return this->m_pause; }

void Application::queryClickedPixel(
        Color& color, float& depthComponent, unsigned int& stencilIndex) {
    // calculate pixel coordinates relative to bottom left corner
    int pixelX = (int)((long long)this->m_mouseX % this->m_windowWidth);
    int pixelY = this->m_windowHeight
                 - (int)((long long)this->m_mouseY % this->m_windowHeight) - 1;

    glReadPixels(pixelX, pixelY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color._Elems);
    glReadPixels(pixelX, pixelY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT,
            &depthComponent);
    glReadPixels(pixelX, pixelY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT,
            &stencilIndex);

    printf("Clicked coords: x = %d, y=%d\n", pixelX, pixelY);
}

void Application::resizeViewPort(
        int width, int height) {
    glViewport(0, 0, width, height);
    this->m_windowHeight = height;
    this->m_windowWidth = width;
}

void Application::setActiveSceneByIndex(
        size_t index) {
    this->m_activeScene = this->m_scenes.at(index).get();
    this->m_activeScene->handleWindowResize(
            this->m_windowWidth, this->m_windowHeight);
}

void Application::setLastMousePosition(
        double x, double y) {
    this->m_mouseX = x;
    this->m_mouseY = y;
}

void Application::toggleActivateMouseCursor() {
    this->m_cursorActive = !this->m_cursorActive;
    glfwSetInputMode(this->m_window, GLFW_CURSOR,
            this->m_cursorActive ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

    // prevent "mouse jump"
    if (!this->m_cursorActive && this->m_activeScene) {
        this->m_activeScene->handleMouseMovement(
                this->m_mouseX, this->m_mouseY, true);
    }
}

void Application::togglePause() {
    this->m_pause = !this->m_pause;
    printf("%s\n", (this->m_pause ? "Application is now paused..."
                                  : "Application is running again..."));
}

void Application::modifyDrawingStencilFunction(
        Byte objectId) {
    glStencilFunc(GL_ALWAYS, objectId, 0xFF);
}

void Application::modifyHighlightingStencilFunction(
        Byte objectId) {
    glStencilFunc(GL_NOTEQUAL, objectId, 0xFF);
}
