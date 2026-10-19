// DrawableObjectFactory.cpp - Contains definition of DrawableObjectFactory
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <drawables/Model.h>
#include <memory>

DrawableObjectFactory DrawableObjectFactory::s_instance{};

DrawableObjectPtr DrawableObjectFactory::createDrawableObjectFromVerticesData(
        const float* verticesData, size_t arrayElementsCount,
        int attributesCount) {
    if (ModelPtr cachedModel = s_instance.m_modelsCache[verticesData].lock()) {
        return std::make_unique<DrawableObject>(cachedModel);
    }

    ModelPtr model = std::make_shared<Model>(Model::fromVerticesData(
            verticesData, arrayElementsCount, attributesCount));

    s_instance.m_modelsCache[verticesData] = model;
    return std::make_unique<DrawableObject>(model);
}
