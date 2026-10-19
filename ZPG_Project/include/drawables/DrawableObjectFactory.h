// DrawableObjectFactory.h - Contains declaration of DrawableObjectFactory
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>
#include <unordered_map>

class Model;
class DrawableObject;

using ModelPtr = std::shared_ptr<Model>;
using ModelWeakPtr = std::weak_ptr<Model>;
using DrawableObjectPtr = std::unique_ptr<DrawableObject>;

/**
 * @brief Creates drawable objects and caches their models.
 */
class DrawableObjectFactory {
  public:
    /**
     * @brief Creates drawable object from supplied vertices data.
     * @param verticesData Array of vertices data.
     * @param arrayElementsCount Total number of elements in the vertices data
     * array.
     * @param attributesCount Number of attributes in supplied vertices data.
     * @return New drawable object.
     * @throw std::invalid_argument - Thrown if number of arguments does not
     * correspond with total array elements count.
     */
    static DrawableObjectPtr createDrawableObjectFromVerticesData(
            const float* verticesData, size_t arrayElementsCount,
            int attributesCount);

  private:
    static DrawableObjectFactory s_instance;
    std::unordered_map<const float*, ModelWeakPtr> m_modelsCache;
};
