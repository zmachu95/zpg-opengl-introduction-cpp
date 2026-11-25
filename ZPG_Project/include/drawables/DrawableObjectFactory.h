// DrawableObjectFactory.h - Contains declaration of DrawableObjectFactory
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>
#include <unordered_map>

class Model;
class DrawableObject;

/**
 * @brief Alias for byte.
 */
using Byte = unsigned char;

/**
 * @brief Pointer to Model object.
 */
using ModelPtr = std::shared_ptr<Model>;

/**
 * @brief Weak pointer to Model object.
 */
using ModelWeakPtr = std::weak_ptr<Model>;

/**
 * @brief Pointer to DrawableObject object.
 */
using DrawableObjectPtr = std::unique_ptr<DrawableObject>;

/**
 * @brief Enlists known models for quick creation.
 */
enum class KnownModels {
    BUSH,
    CLOCK,
    EARTH,
    FIONA,
    GIFT,
    LOGIN,
    MOON,
    PLAIN,
    SATELLITE,
    SHREK,
    SPHERE,
    SUN,
    SUZI_FLAT,
    SUZI_SMOOTH,
    TOILET,
    TREE,
    TRIANGLE,

    EB408,
    EB408_CASE,
    EB408_CHAIR,
    EB408_DOOR,
    EB408_DOOR_FRAME,
    EB408_MONITOR,
    EB408_TABLE,
    EB408_WHITEBOARD
};

/**
 * @brief Creates drawable objects and caches their models.
 */
class DrawableObjectFactory {
  public:
    /**
     * @brief Creates drawable object from supplied vertices data.
     * @param id Assigned object ID.
     * @param verticesData Array of vertices data.
     * @param arrayElementsCount Total number of elements in the vertices data
     * array.
     * @param attributesCount Number of attributes in supplied vertices data.
     * @param uses2dTextures Supply true if model uses 2D textures, otherwise
     * false.
     * @return New drawable object.
     * @throw std::invalid_argument - Thrown if number of arguments does not
     * correspond with total array elements count.
     */
    static DrawableObjectPtr createDrawableObjectFromVerticesData(Byte id,
            const float* verticesData, size_t arrayElementsCount,
            unsigned int attributesCount, bool uses2dTextures);

    /**
     * @brief Creates drawable object from known model.
     * @param id Assigned object ID.
     * @param modelType Type of model to create.
     * @return New drawable object.
     */
    static DrawableObjectPtr createKnownModel(Byte id, KnownModels modelType);

  private:
    static DrawableObjectFactory s_instance;

    std::unordered_map<const float*, ModelWeakPtr> m_modelsCache;
};
