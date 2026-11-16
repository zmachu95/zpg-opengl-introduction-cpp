// Main.cpp - Launches the application.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define GLAD_GL_IMPLEMENTATION

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif
#include <GLFW/glfw3.h>

#include <application/ApplicationFactory.h>
#include <application/IApplication.h>
#include <exception>
#include <iostream>

int main() {
    int windowWidth = 800;  // window width in [px]
    int windowHeight = 600; // window height in [px]

    try {
        ApplicationPtr app = ApplicationFactory::createApplication(
                windowWidth, windowHeight);
        app->initialize();
        app->run();
    } catch (const std::exception& ex) {
        std::cout << ex.what();
    }
}
