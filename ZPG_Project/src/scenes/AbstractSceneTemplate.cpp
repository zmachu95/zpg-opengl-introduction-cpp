// AbstractSceneTemplate.cpp - Contains definition of AbstractSceneTemplate
// class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#include "AbstractSceneTemplate.h"
#include "DrawableObjectInteractionProvider.h"
#include "SceneRepository.h"
#include <cameras/CameraCommonSettings.h>
#include <cameras/CameraUserInputController.h>
#include <cameras/PerspectiveCamera.h>
#include <constants/KeyActions.h>
#include <constants/KeyCodes.h>
#include <constants/KeyModifiers.h>
#include <cstdio>
#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <resources/models/skybox.h>
#include <shaders/ShaderProgram.h>
#include <string>
#include <textures/TextureFactory.h>
#include <transformations/IGroupedTransformation.h>
#include <transformations/IScale.h>
#include <utility>

constexpr float HIGHLIGHTED_OBJECT_SCALE = 1.05f;

AbstractSceneTemplate::AbstractSceneTemplate(
        CameraPtr&& camera, DrawableObjectPtr&& skybox)
    : m_camera{std::move(camera)}, m_highlightedObjectsProgram{nullptr},
      m_interactionProvider{*this}, m_initializedLights{false}, m_repository{},
      m_selectedObject{nullptr}, m_selectedObjectClone{},
      m_skybox{std::move(skybox)}, m_skyboxShaderProgram{nullptr} {
    if (this->m_skybox.get()) {
        this->m_skyboxShaderProgram = &this->addShaderProgramFromShaderFiles(
                "_templates\\skybox.vert", "_templates\\skybox.frag", true);
    }
    this->m_highlightedObjectsProgram = &this->addShaderProgramFromShaderFiles(
            "_templates\\basic.vert", "_templates\\highlight.frag", false);
}

AbstractSceneTemplate::AbstractSceneTemplate(
        int windowWidth, int windowHeight, DrawableObjectPtr&& skybox)
    : AbstractSceneTemplate{AbstractSceneTemplate::createDefaultCamera(
                                    windowWidth, windowHeight),
              std::move(skybox)} {}

AbstractSceneTemplate::AbstractSceneTemplate(
        CameraPtr&& camera)
    : AbstractSceneTemplate{std::move(camera),
              AbstractSceneTemplate::createDefaultSkybox()} {}

AbstractSceneTemplate::AbstractSceneTemplate(
        int windowWidth, int windowHeight)
    : AbstractSceneTemplate{AbstractSceneTemplate::createDefaultCamera(
                                    windowWidth, windowHeight),
              AbstractSceneTemplate::createDefaultSkybox()} {}

void AbstractSceneTemplate::draw(
        float deltaT, void (*stencilModifier)(Byte)) {
    if (!this->m_initializedLights) {
        this->initializeLights();
        this->m_initializedLights = true;
    }

    if (deltaT > 0) {
        this->updateSceneContents(deltaT);
        this->m_interactionProvider.animateObjects(deltaT);
        this->updateCamera(deltaT);
    }

    for (const auto& idObjAndShaderProgram : this->m_repository) {
        stencilModifier(idObjAndShaderProgram.first);
        idObjAndShaderProgram.second.first->draw(
                idObjAndShaderProgram.second.second);
    }
}

void AbstractSceneTemplate::highlightSelectedObject(
        void (*stencilModifier)(Byte)) {
    if (this->m_selectedObject) {
        stencilModifier(this->m_selectedObject->getId());

        if (!this->m_selectedObjectClone.get()
                || this->m_selectedObject->getId()
                           != this->m_selectedObjectClone.get()->getId()) {
            // create temporary scaled clone of the selected object with exactly
            // the same transformations
            this->m_selectedObjectClone = std::make_unique<DrawableObject>(
                    this->m_selectedObject->cloneWithoutTransformations(
                            this->m_selectedObject->getId()));
            this->m_selectedObjectClone->getTransformation()
                    ->addReferenceToAnother(
                            this->m_selectedObject->getTransformation());
            ScalePtr scale = this->m_selectedObjectClone->getTransformation()
                                     ->addNewScale();
            scale->setScaleTo(HIGHLIGHTED_OBJECT_SCALE,
                    HIGHLIGHTED_OBJECT_SCALE, HIGHLIGHTED_OBJECT_SCALE);
        }

        this->m_selectedObjectClone->draw(*this->m_highlightedObjectsProgram);
    }
}

void AbstractSceneTemplate::drawSkybox(
        const float deltaT) {
    if (this->m_skybox.get()) {
        this->updateSkyboxShaderProgram(deltaT);
        this->m_skybox->draw(*this->m_skyboxShaderProgram);
    }
}

void AbstractSceneTemplate::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {
    this->m_interactionProvider.handleKeyPresses(button, action, mode);
    CameraUserInputController::handleKeyPresses(button, action, mode);
}

void AbstractSceneTemplate::handleMouseMovement(
        double cursorX, double cursorY, bool discardUpdates) {
    CameraUserInputController::handleMouseMove(
            cursorX, cursorY, discardUpdates);
}

void AbstractSceneTemplate::handleWindowResize(
        int width, int height) {
    if (this->m_camera.get() && width > 0 && height > 0) {
        this->m_camera->setAspectRatio(width, height);
    }
}

void AbstractSceneTemplate::handleMouseClickWithObjectSelection(
        const glm::vec3& clickCoords, int windowWidth, int windowHeight,
        Byte objectId, MouseButtonCodes button, MouseButtonActions action,
        KeyModifierFlags mode) {
    this->m_interactionProvider.handleMouseClick(clickCoords, windowWidth,
            windowHeight, objectId, button, action, mode);
}

void AbstractSceneTemplate::handleMouseClick(
        MouseButtonCodes button, MouseButtonActions action,
        KeyModifierFlags mode) {
    /* do nothing */
}

DrawableObjectPtr AbstractSceneTemplate::createDefaultSkybox() {
    DrawableObjectPtr skybox =
            DrawableObjectFactory::createDrawableObjectFromVerticesData(0,
                    skyboxVertices,
                    sizeof(skyboxVertices) / sizeof(skyboxVertices[0]), 1,
                    false);
    skybox->addTexture(TextureFactory::createDefaultSkyBoxTexture());
    return skybox;
}

ShaderProgram& AbstractSceneTemplate::addShaderProgramFromShaderFiles(
        const std::string& vertexShaderFile,
        const std::string& fragmentShaderFile, bool rendersSkybox) {
    return this->m_repository.addShaderProgramFromShaderFiles(vertexShaderFile,
            fragmentShaderFile, rendersSkybox, this->m_camera.get());
}

DrawableObject& AbstractSceneTemplate::addDrawableObjectFromVerticesData(
        bool generateId, const float* verticesData, size_t arrayElementsCount,
        unsigned int attributesCount, bool uses2dTextures,
        ShaderProgram& shaderProgram) {
    return this->m_repository.addDrawableObjectFromVerticesData(generateId,
            verticesData, arrayElementsCount, attributesCount, uses2dTextures,
            shaderProgram);
}

DrawableObject& AbstractSceneTemplate::addDrawableObjectFromKnownModel(
        bool generateId, KnownModels modelType, ShaderProgram& shaderProgram) {
    return this->m_repository.addDrawableObjectFromKnownModel(
            generateId, modelType, shaderProgram);
}

CameraPtr AbstractSceneTemplate::createDefaultCamera(
        int windowWidth, int windowHeight) {
    return std::make_unique<PerspectiveCamera>(
            std::make_shared<CameraCommonSettings>(),
            (float)windowWidth / windowHeight);
}

void AbstractSceneTemplate::updateCamera(
        float deltaT) {
    if (this->m_camera.get()) {
        this->m_camera->update(
                CameraUserInputController::getMovementDirection(),
                CameraUserInputController::getHorizontalRotationIncrement(),
                CameraUserInputController::getVerticalRotationIncrement(),
                deltaT);
    }
}

void AbstractSceneTemplate::changeShaderProgram(
        DrawableObject* object, ShaderProgram& newProgram) {
    if (object) {
        bool programChanged =
                this->m_repository.changeShaderProgram(*object, newProgram);
        if (!programChanged) {
            printf("Warning! Could not change shader program for drawable "
                   "object with ID %hhd!\n",
                    object->getId());
        }
    }
}

DrawableObject* AbstractSceneTemplate::findObjectById(
        Byte id) {
    return this->m_repository.findObjectById(id);
}

PerspectiveCamera* AbstractSceneTemplate::getCamera() const {
    return this->m_camera.get();
}

DrawableObject* AbstractSceneTemplate::getSelectedObject() const {
    return this->m_selectedObject;
}

void AbstractSceneTemplate::setSelectedObject(
        DrawableObject* object) {
    if (object) {
        printf("Selected model with ID %hhd.\n", object->getId());
    } else if (this->m_selectedObject && !object) {
        printf("Selection cleared.\n");
    }
    this->m_selectedObject = object;
}

DrawableObject* AbstractSceneTemplate::insertSelectedObjectIntoScene() {
    if (!this->m_selectedObject) {
        return nullptr;
    }

    return &this->m_repository.makeDrawableObjectCopy(*this->m_selectedObject);
}

void AbstractSceneTemplate::removeSelectedObjectFromScene() {
    if (!this->m_selectedObject) {
        return;
    }

    if (this->m_repository.removeDrawableObject(*this->m_selectedObject)) {
        printf("Removed object with ID %hhd.\n",
                this->m_selectedObject->getId());

        this->m_selectedObject = nullptr;
        this->m_selectedObjectClone = std::unique_ptr<DrawableObject>{};
    }
}

ShaderProgram* AbstractSceneTemplate::getShaderProgram(
        DrawableObject* object) const {
    if (!object) {
        return nullptr;
    }

    return this->m_repository.getShaderProgram(*object);
}

ShaderProgram* AbstractSceneTemplate::getSkyboxShaderProgram() {
    return this->m_skyboxShaderProgram;
}

void AbstractSceneTemplate::updateSkyboxShaderProgram(
        float deltaT) {
    /* do nothing */
}

void AbstractSceneTemplate::initializeLights() { /* do nothing */ }
