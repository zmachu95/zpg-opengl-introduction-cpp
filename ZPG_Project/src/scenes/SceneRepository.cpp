// SceneRepository.cpp - Contains definition of SceneRepository class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#include "SceneRepository.h"
#include <cameras/PerspectiveCamera.h>
#include <climits>
#include <cstdio>
#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <memory>
#include <shaders/ShaderProgram.h>
#include <string>
#include <unordered_map>
#include <utility>

DrawableObject* SceneRepository::findObjectById(
        Byte id) const {
    if (auto it = this->m_drawableObjectsAndShadersLookup.find(id);
            it != this->m_drawableObjectsAndShadersLookup.end()) {
        return it->second.first.get();
    } else {
        return nullptr;
    }
}

ShaderProgram* SceneRepository::getShaderProgram(
        DrawableObject& object) const {
    auto rangeIts =
            this->m_drawableObjectsAndShadersLookup.equal_range(object.getId());
    auto endIt = this->m_drawableObjectsAndShadersLookup.end();

    // check that ID is registered
    if (rangeIts.first == endIt && rangeIts.second == endIt) {
        return nullptr;
    }

    // find the correct object among objects with the same ID
    for (auto it = rangeIts.first; it != rangeIts.second; it++) {
        if (it->second.first.get() == &object) {
            return &it->second.second.get();
        }
    }

    return nullptr;
}

bool SceneRepository::changeShaderProgram(
        DrawableObject& object, ShaderProgram& newProgram) {
    auto rangeIts =
            this->m_drawableObjectsAndShadersLookup.equal_range(object.getId());
    auto endIt = this->m_drawableObjectsAndShadersLookup.end();

    // check that ID is registered
    if (rangeIts.first == endIt && rangeIts.second == endIt) {
        return false;
    }

    // find the correct object among objects with the same ID
    for (auto it = rangeIts.first; it != rangeIts.second; it++) {
        if (it->second.first.get() == &object) {
            it->second.second = newProgram;
            return true;
        }
    }

    return false;
}

DrawableObject& SceneRepository::makeDrawableObjectCopy(
        DrawableObject& object) {
    ShaderProgram* shaderProgram = this->getShaderProgram(object);
    if (!shaderProgram) {
        printf("WARNING! Could not find shader program for object with ID "
               "%hhd.\n",
                object.getId());
        shaderProgram = this->m_shaderPrograms.back().get();
    }

    DrawableObjectPtr clonedObjPtr = std::make_unique<DrawableObject>(
            object.cloneWithoutTransformations(this->generateId()));
    DrawableObject& clonedObj = *clonedObjPtr.get();

    this->m_drawableObjectsAndShadersLookup.insert(
            std::pair<Byte, ObjectAndShader>{clonedObj.getId(),
                    ObjectAndShader{std::move(clonedObjPtr), *shaderProgram}});

    return clonedObj;
}

bool SceneRepository::removeDrawableObject(
        DrawableObject& object) {
    auto rangeIts =
            this->m_drawableObjectsAndShadersLookup.equal_range(object.getId());
    auto endIt = this->m_drawableObjectsAndShadersLookup.end();

    // check that ID is registered
    if (rangeIts.first == endIt && rangeIts.second == endIt) {
        return false;
    }

    // find the correct object among objects with the same ID
    for (auto it = rangeIts.first; it != rangeIts.second; it++) {
        if (it->second.first.get() == &object) {
            this->m_drawableObjectsAndShadersLookup.erase(it);
            return true;
        }
    }

    return false;
}

DrawableObject& SceneRepository::addDrawableObjectFromVerticesData(
        bool generateId, const float* verticesData, size_t arrayElementsCount,
        unsigned int attributesCount, bool uses2dTextures,
        ShaderProgram& shaderProgram) {
    Byte id = generateId ? this->generateId() : (Byte)0;

    DrawableObjectPtr newObj =
            DrawableObjectFactory::createDrawableObjectFromVerticesData(id,
                    verticesData, arrayElementsCount, attributesCount,
                    uses2dTextures);
    DrawableObject& objRef = *newObj.get();
    this->m_drawableObjectsAndShadersLookup.insert(
            std::pair<Byte, ObjectAndShader>{objRef.getId(),
                    ObjectAndShader{std::move(newObj), shaderProgram}});

    return objRef;
}

ShaderProgram& SceneRepository::addShaderProgramFromShaderFiles(
        const std::string& vertexShaderFile,
        const std::string& fragmentShaderFile, bool rendersSkybox,
        PerspectiveCamera* camera) {
    ShaderProgramPtr newShaderProgram = ShaderProgram::createFromShaderFiles(
            vertexShaderFile, fragmentShaderFile, rendersSkybox);
    ShaderProgram& programRef = *newShaderProgram.get();

    this->m_shaderPrograms.push_back(std::move(newShaderProgram));
    if (camera) {
        camera->registerCameraUpdateListener(
                programRef.asCameraUpdateListener());
    }

    return programRef;
}

Byte SceneRepository::generateId() const {
    Byte id = 1;
    while (id < UCHAR_MAX
            && this->m_drawableObjectsAndShadersLookup.count(id) > 0) {
        id++;
    }

    if (id == UCHAR_MAX) {
        printf("WARNING! The scene contains more than %d objects! Stencil "
               "picking might fail!\n",
                UCHAR_MAX);
    }

    return id;
}

std::unordered_multimap<Byte, ObjectAndShader>::const_iterator
SceneRepository::begin() const {
    return this->m_drawableObjectsAndShadersLookup.begin();
}

std::unordered_multimap<Byte, ObjectAndShader>::const_iterator
SceneRepository::end() const {
    return this->m_drawableObjectsAndShadersLookup.end();
}
