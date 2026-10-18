// ModelManager.h - Contains declaration of ModelManager class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <drawables/Model.h>
#include <unordered_map>

/**
 * @brief Enlists the available models.
 */
enum class AvailableModels {
    BUSHES,
    EARTH,
    GIFT,
    MOON,
    PLAIN,
    SPHERE,
    SUN,
    SUZI_FLAT,
    SUZI_SMOOTH,
    TREE,
    TRIANGLE,
    LOGIN
};

/**
 * @brief Caches Model objects.
 */
class ModelManager {
  public:
    /**
     * @brief Initializes the manager. To be used directly after OpenGL
     * initialization.
     */
    static void initialize();

    /**
     * @brief Destroys the manager and its cached contents. To be used
     * upon application closing.
     */
    static void destroy();

    /**
     * @brief Gets specific model from the cache.
     * @param model Enum value representing the model.
     * @return Refernce to model object.
     */
    static Model& getModel(AvailableModels model);

  private:
    static ModelManager s_instance;

    bool m_initialized;
    std::unordered_map<AvailableModels, Model> m_modelsCache;

    ModelManager();
};
