// IApplication.h - Contains declaration of IApplication interface.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <stdexcept>

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

/**
 * @brief Represents the OpenGL application.
 */
class IApplication {
  public:
    virtual ~IApplication() = default;

    /**
     * @brief Initializes the OpenGL application.
     * @throw GlfwInitializationException - Thrown if GLFW could not be
     * initialized.
     * @throw GladInitializationException - Thrown if GLAD could not be
     * initialized.
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the application.
     * @throw ApplicationNotInitializedException - Thrown if the application is
     * not initialized.
     */
    virtual void run() = 0;
};
