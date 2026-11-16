// ApplicationFactory.h - Contains declaration of ApplicationFactory class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <memory>

class IApplication;

/**
 * @brief Pointer to IApplication object.
 */
using ApplicationPtr = std::unique_ptr<IApplication>;

/**
 * @brief Creates IApplication objects.
 */
class ApplicationFactory {
  public:
    /**
     * @brief Creates new IApplication object with specified window size.
     * @param windowWidth Window width in [px].
     * @param windowHeight Window height in [px].
     * @return Pointer to IApplication object.
     */
    static ApplicationPtr createApplication(int windowWidth, int windowHeight);

  private:
    /**
     * @brief ApplicationFactory default constructor.
     */
    ApplicationFactory() = default;
};
