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

  private:
    static DrawableObjectFactory s_instance;

    std::unordered_map<const float*, ModelWeakPtr> m_modelsCache;
};
