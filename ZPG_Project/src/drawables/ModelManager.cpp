// ModelManager.cpp - Contains definition of ModelManager class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <drawables/Model.h>
#include <drawables/ModelManager.h>
#include <resources/models/MAC0690.h>
#include <resources/models/bushes.h>
#include <resources/models/earth.h>
#include <resources/models/gift.h>
#include <resources/models/moon.h>
#include <resources/models/plain.h>
#include <resources/models/sphere.h>
#include <resources/models/sun.h>
#include <resources/models/suzi_flat.h>
#include <resources/models/suzi_smooth.h>
#include <resources/models/tree.h>
#include <resources/models/triangle.h>
#include <utility>

using CachedPair = std::pair<AvailableModels, Model>;

ModelManager ModelManager::s_instance{};

ModelManager::ModelManager() : m_modelsCache{}, m_initialized{false} {}

void ModelManager::destroy() { s_instance.m_modelsCache.clear(); }

void ModelManager::initialize() {
    if (s_instance.m_initialized) {
        return;
    }

    s_instance.m_modelsCache.insert(CachedPair{AvailableModels::BUSHES,
            Model::fromVerticePositionsAndColors(
                    bushes, sizeof(bushes) / sizeof(bushes[0]))});
    s_instance.m_modelsCache.insert(CachedPair{AvailableModels::EARTH,
            Model::fromVerticePositionsColorsNormals(
                    earth, sizeof(earth) / sizeof(earth[0]))});
    s_instance.m_modelsCache.insert(CachedPair{
            AvailableModels::GIFT, Model::fromVerticePositionsAndColors(gift,
                                           sizeof(gift) / sizeof(gift[0]))});
    s_instance.m_modelsCache.insert(CachedPair{AvailableModels::MOON,
            Model::fromVerticePositionsColorsNormals(
                    moon, sizeof(moon) / sizeof(moon[0]))});
    s_instance.m_modelsCache.insert(CachedPair{
            AvailableModels::PLAIN, Model::fromVerticePositionsAndColors(plain,
                                            sizeof(plain) / sizeof(plain[0]))});
    s_instance.m_modelsCache.insert(CachedPair{AvailableModels::SPHERE,
            Model::fromVerticePositionsAndColors(
                    sphere, sizeof(sphere) / sizeof(sphere[0]))});
    s_instance.m_modelsCache.insert(CachedPair{
            AvailableModels::SUN, Model::fromVerticePositionsColorsNormals(
                                          sun, sizeof(sun) / sizeof(sun[0]))});
    s_instance.m_modelsCache.insert(CachedPair{AvailableModels::SUZI_FLAT,
            Model::fromVerticePositionsAndColors(
                    suziFlat, sizeof(suziFlat) / sizeof(suziFlat[0]))});
    s_instance.m_modelsCache.insert(CachedPair{AvailableModels::SUZI_SMOOTH,
            Model::fromVerticePositionsAndColors(
                    suziSmooth, sizeof(suziSmooth) / sizeof(suziSmooth[0]))});
    s_instance.m_modelsCache.insert(CachedPair{
            AvailableModels::TREE, Model::fromVerticePositionsAndColors(tree,
                                           sizeof(tree) / sizeof(tree[0]))});
    s_instance.m_modelsCache.insert(CachedPair{AvailableModels::TRIANGLE,
            Model::fromVerticePositionsAndColors(
                    triangle, sizeof(triangle) / sizeof(triangle[0]))});
    s_instance.m_modelsCache.insert(CachedPair{AvailableModels::LOGIN,
            Model::fromVerticePositionsAndColors(
                    mac0690, sizeof(mac0690) / sizeof(mac0690[0]))});

    s_instance.m_initialized = true;
}

Model& ModelManager::getModel(
        AvailableModels model) {
    return s_instance.m_modelsCache.at(model);
}
