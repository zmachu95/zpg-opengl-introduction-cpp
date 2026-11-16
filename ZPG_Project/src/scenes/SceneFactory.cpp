// SceneFactory.cpp - Contains definition of SceneFactory class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#include "ClassroomScene.h"
#include "ForestScene.h"
#include "LightingTestScene.h"
#include "LoginScene.h"
#include "ShrekFionaScene.h"
#include "SolarSystemScene.h"
#include "TriangleScene.h"
#include "WallclockScene.h"
#include <memory>
#include <scenes/SceneFactory.h>
#include <stdexcept>
#include <string>

using namespace std::string_literals;

ScenePtr SceneFactory::createScene(
        AvailableScenes scene, int windowWidth, int windowHeight) {
    switch (scene) {
        case AvailableScenes::CLASSROOM:
            return std::make_unique<ClassroomScene>(windowWidth, windowHeight);
        case AvailableScenes::FOREST:
            return std::make_unique<ForestScene>(windowWidth, windowHeight);
        case AvailableScenes::LIGHTING_TEST:
            return std::make_unique<LightingTestScene>(
                    windowWidth, windowHeight);
        case AvailableScenes::LOGIN:
            return std::make_unique<LoginScene>(windowWidth, windowHeight);
        case AvailableScenes::SHREK_AND_FIONA:
            return std::make_unique<ShrekFionaScene>(windowWidth, windowHeight);
        case AvailableScenes::SOLAR_SYSTEM:
            return std::make_unique<SolarSystemScene>(
                    windowWidth, windowHeight);
        case AvailableScenes::TRIANGLE:
            return std::make_unique<TriangleScene>(windowWidth, windowHeight);
        case AvailableScenes::WALLCLOCK:
            return std::make_unique<WallclockScene>(windowWidth, windowHeight);
        default:
            throw std::invalid_argument{"Option "s + std::to_string((int)scene)
                                        + " is not supported!"};
    }
}
