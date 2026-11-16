// SceneFactory.h - Contains declaration of SceneFactory class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <memory>

/**
 * @brief Groups all available scenes.
 */
enum class AvailableScenes {
    CLASSROOM,
    FOREST,
    LIGHTING_TEST,
    LOGIN,
    SHREK_AND_FIONA,
    SOLAR_SYSTEM,
    TRIANGLE,
    WALLCLOCK
};

class IScene;

/**
 * @brief Pointer with IScene object.
 */
using ScenePtr = std::unique_ptr<IScene>;

/**
 * @brief Creates new scenes.
 */
class SceneFactory {
  public:
    /**
     * @brief Create new scene.
     * @param scene Type of scene to create.
     * @param windowWidth Window width in [px].
     * @param windowHeight Window height in [px].
     * @return Pointer with IScene object.
     */
    static ScenePtr createScene(
            AvailableScenes scene, int windowWidth, int windowHeight);
};
