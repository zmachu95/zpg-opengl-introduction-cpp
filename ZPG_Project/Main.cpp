// Main.cpp - Launches the application.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#define GLAD_GL_IMPLEMENTATION

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif
#include <GLFW/glfw3.h>

#include <application/Application.h>
#include <exception>
#include <iostream>

int main(
        void) {
    try {
        Application app{};
        app.initialize();
        app.run();
    } catch (const std::exception& ex) {
        std::cout << ex.what();
    }
}
