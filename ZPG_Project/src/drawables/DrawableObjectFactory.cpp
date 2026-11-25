// DrawableObjectFactory.cpp - Contains definition of DrawableObjectFactory
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "Model.h"
#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <memory>
#include <stdexcept>
#include <string>

#include <resources/models/bushes.h>
#include <resources/models/clock.h>
#include <resources/models/earth.h>
#include <resources/models/eb408/case.h>
#include <resources/models/eb408/chair.h>
#include <resources/models/eb408/door.h>
#include <resources/models/eb408/doorFrame.h>
#include <resources/models/eb408/eb408.h>
#include <resources/models/eb408/monitor.h>
#include <resources/models/eb408/table.h>
#include <resources/models/eb408/whiteboard.h>
#include <resources/models/fiona.h>
#include <resources/models/gift.h>
#include <resources/models/mac0690.h>
#include <resources/models/moon.h>
#include <resources/models/plain.h>
#include <resources/models/satellite.h>
#include <resources/models/shrek.h>
#include <resources/models/sphere.h>
#include <resources/models/sun.h>
#include <resources/models/suzi_flat.h>
#include <resources/models/suzi_smooth.h>
#include <resources/models/toilet.h>
#include <resources/models/tree.h>
#include <resources/models/triangle.h>

using namespace std::string_literals;

DrawableObjectFactory DrawableObjectFactory::s_instance{};

DrawableObjectPtr DrawableObjectFactory::createDrawableObjectFromVerticesData(
        Byte id, const float* verticesData, size_t arrayElementsCount,
        unsigned int attributesCount, bool uses2dTextures) {
    if (ModelPtr cachedModel = s_instance.m_modelsCache[verticesData].lock()) {
        return std::make_unique<DrawableObject>(cachedModel, id);
    }

    ModelPtr model = std::make_shared<Model>(Model::fromVerticesData(
            verticesData, arrayElementsCount, attributesCount, uses2dTextures));

    s_instance.m_modelsCache[verticesData] = model;
    return std::make_unique<DrawableObject>(model, id);
}

DrawableObjectPtr DrawableObjectFactory::createKnownModel(
        Byte id, KnownModels modelType) {
    switch (modelType) {
        case KnownModels::BUSH:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, bushes, sizeof(bushes) / sizeof(bushes[0]), 2, false);
        case KnownModels::CLOCK:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, clockModel, sizeof(clockModel) / sizeof(clockModel[0]),
                    3, false);
        case KnownModels::EARTH:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, earth, sizeof(earth) / sizeof(earth[0]), 3, false);
        case KnownModels::FIONA:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, fiona, sizeof(fiona) / sizeof(fiona[0]), 2, true);
        case KnownModels::GIFT:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, gift, sizeof(gift) / sizeof(gift[0]), 2, false);
        case KnownModels::LOGIN:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, mac0690, sizeof(mac0690) / sizeof(mac0690[0]), 2,
                    false);
        case KnownModels::MOON:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, moon, sizeof(moon) / sizeof(moon[0]), 3, false);
        case KnownModels::PLAIN:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, plain, sizeof(plain) / sizeof(plain[0]), 2, false);
        case KnownModels::SATELLITE:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, satellite, sizeof(satellite) / sizeof(satellite[0]), 2,
                    false);
        case KnownModels::SHREK:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, shrek, sizeof(shrek) / sizeof(shrek[0]), 2, true);
        case KnownModels::SPHERE:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, sphere, sizeof(sphere) / sizeof(sphere[0]), 2, false);
        case KnownModels::SUN:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, sun, sizeof(sun) / sizeof(sun[0]), 3, false);
        case KnownModels::SUZI_FLAT:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, suziFlat, sizeof(suziFlat) / sizeof(suziFlat[0]), 2,
                    false);
        case KnownModels::SUZI_SMOOTH:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, suziSmooth, sizeof(suziSmooth) / sizeof(suziSmooth[0]),
                    2, false);
        case KnownModels::TOILET:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, toilet, sizeof(toilet) / sizeof(toilet[0]), 2, true);
        case KnownModels::TREE:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, tree, sizeof(tree) / sizeof(tree[0]), 2, false);
        case KnownModels::TRIANGLE:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, triangle, sizeof(triangle) / sizeof(triangle[0]), 2,
                    false);
        case KnownModels::EB408:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, eb408, sizeof(eb408) / sizeof(eb408[0]), 2, true);
        case KnownModels::EB408_CASE:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, computerCase,
                    sizeof(computerCase) / sizeof(computerCase[0]), 2, true);
        case KnownModels::EB408_CHAIR:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, chair, sizeof(chair) / sizeof(chair[0]), 2, true);
        case KnownModels::EB408_DOOR:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, door, sizeof(door) / sizeof(door[0]), 2, true);
        case KnownModels::EB408_DOOR_FRAME:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, doorFrame, sizeof(doorFrame) / sizeof(doorFrame[0]), 2,
                    true);
        case KnownModels::EB408_MONITOR:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, monitor, sizeof(monitor) / sizeof(monitor[0]), 2, true);
        case KnownModels::EB408_TABLE:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, table, sizeof(table) / sizeof(table[0]), 2, true);
        case KnownModels::EB408_WHITEBOARD:
            return DrawableObjectFactory::createDrawableObjectFromVerticesData(
                    id, whiteboard, sizeof(whiteboard) / sizeof(whiteboard[0]),
                    2, true);
        default:
            throw std::invalid_argument("Option "s
                                        + std::to_string((int)modelType)
                                        + " is not implemented!");
    }
}
