// DrawableObjectInteractionProvider.cpp - Contains definition of
// DrawableObjectInteractionProvider class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#include "DrawableObjectInteractionProvider.h"
#include "ISceneMediator.h"
#include <cameras/PerspectiveCamera.h>
#include <cstdio>
#include <drawables/DrawableObject.h>
#include <glm/common.hpp>
#include <glm/ext/matrix_float3x3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <transformations/ITranslation.h>

#include <constants/KeyActions.h>
#include <constants/KeyCodes.h>
#include <constants/KeyModifiers.h>
#include <constants/MouseButtonActions.h>
#include <constants/MouseButtonCodes.h>

DrawableObjectInteractionProvider::DrawableObjectInteractionProvider(
        ISceneMediator& owningScene)
    : m_animatedObjects{}, m_clickedWorldCoords{0.0f}, m_lineSegmentStart{0.0f},
      m_lineSegmentEnd{0.0f}, m_owningScene{owningScene} {}

void DrawableObjectInteractionProvider::animateObjects(
        float deltaT) {
    for (auto& kvPair : this->m_animatedObjects) {
        LineSegmentPointsAndTransformation& pointsAndTrans = kvPair.second;

        // update parameter t
        if (pointsAndTrans.t == 0.0f) {
            pointsAndTrans.sign = 1;
        } else if (pointsAndTrans.t == 1.0f) {
            pointsAndTrans.sign = -1;
        }
        pointsAndTrans.t = glm::clamp(
                pointsAndTrans.t + pointsAndTrans.sign * deltaT, 0.0f, 1.0f);

        // calculate new position using interpolation
        glm::vec3 newPos = (1 - pointsAndTrans.t) * pointsAndTrans.start
                           + pointsAndTrans.t * pointsAndTrans.end;

        pointsAndTrans.translation->translateTo(newPos.x, newPos.y, newPos.z);
    }
}

void DrawableObjectInteractionProvider::handleMouseClick(
        const glm::vec3& clickCoords, int windowWidth, int windowHeight,
        Byte objectId, MouseButtonCodes button, MouseButtonActions action,
        KeyModifierFlags mode) {
    if (action == MouseButtonActions::PRESSED) {
        PerspectiveCamera* camera = this->m_owningScene.getCamera();
        this->setClickedWorldCoordinates(
                camera, clickCoords, windowWidth, windowHeight);

        if (button == MouseButtonCodes::LEFT_BUTTON) {
            switch (mode) {
                case KeyModifierFlags::SHIFT:
                    this->selectModel(objectId);
                    return;
                case KeyModifierFlags::CTRL:
                    this->m_lineSegmentStart = this->m_clickedWorldCoords;
                    printf("Set line segment start coordinates [%f, %f, %f].\n",
                            this->m_clickedWorldCoords.x,
                            this->m_clickedWorldCoords.y,
                            this->m_clickedWorldCoords.z);
                    return;
                case KeyModifierFlags::ALT:
                    this->m_lineSegmentEnd = this->m_clickedWorldCoords;
                    printf("Set line segment end coordinates [%f, %f, %f].\n",
                            this->m_clickedWorldCoords.x,
                            this->m_clickedWorldCoords.y,
                            this->m_clickedWorldCoords.z);
                    return;
            }
        }
    }
}

void DrawableObjectInteractionProvider::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {
    if (action == KeyActions::PRESSED) {
        switch (button) {
            case KeyCodes::KEY_INSERT:
                if (mode == KeyModifierFlags::NONE) {
                    this->insertStaticObject();
                } else if ((int)mode & (int)KeyModifierFlags::SHIFT) {
                    this->insertAnimatedObject();
                }
                return;
            case KeyCodes::KEY_DELETE:
                this->deleteSelectedObject();
                return;
        }
    }
}

void DrawableObjectInteractionProvider::selectModel(
        Byte objectId) {
    this->m_owningScene.setSelectedObject(
            objectId > 0 ? this->m_owningScene.findObjectById(objectId)
                         : nullptr);
}

void DrawableObjectInteractionProvider::setClickedWorldCoordinates(
        PerspectiveCamera* camera, const glm::vec3& clickCoords,
        int windowWidth, int windowHeight) {
    if (!camera) {
        return;
    }

    glm::vec4 viewport{0, 0, windowWidth, windowHeight};
    this->m_clickedWorldCoords =
            glm::unProject(clickCoords, camera->calculateViewMatrix(),
                    camera->calculateProjectionMatrix(), viewport);

    printf("Clicked model coordinates: [%f, %f, %f]\n",
            this->m_clickedWorldCoords.x, this->m_clickedWorldCoords.y,
            this->m_clickedWorldCoords.z);
}

void DrawableObjectInteractionProvider::insertSelectedObjectIntoScene(
        DrawableObject*& insertedObject, ITranslation*& translationPtr) {
    DrawableObject* insertedObj =
            this->m_owningScene.insertSelectedObjectIntoScene();
    if (insertedObj) {
        glm::mat3 transformationWithoutTranslation =
                this->m_owningScene.getSelectedObject()
                        ->getTransformation()
                        ->getMatrix();

        TranslationPtr translation =
                insertedObj->getTransformation()->addNewTranslation();
        insertedObj->getTransformation()->addConstant(
                glm::mat4{transformationWithoutTranslation});

        insertedObject = insertedObj;
        translationPtr = translation.get();
    }
}

void DrawableObjectInteractionProvider::insertStaticObject() {
    DrawableObject* insertedObj;
    ITranslation* translation;
    this->insertSelectedObjectIntoScene(insertedObj, translation);

    if (insertedObj && translation) {
        translation->translateTo(this->m_clickedWorldCoords.x,
                this->m_clickedWorldCoords.y, this->m_clickedWorldCoords.z);

        printf("Inserted static object with ID %hhd at world "
               "coordinates [%f, %f, %f]\n",
                insertedObj->getId(), this->m_clickedWorldCoords.x,
                this->m_clickedWorldCoords.y, this->m_clickedWorldCoords.z);
    }
}

void DrawableObjectInteractionProvider::insertAnimatedObject() {
    DrawableObject* insertedObj;
    ITranslation* translation;
    this->insertSelectedObjectIntoScene(insertedObj, translation);

    if (insertedObj && translation) {
        this->m_animatedObjects[insertedObj] =
                LineSegmentPointsAndTransformation{this->m_lineSegmentStart,
                        this->m_lineSegmentEnd, translation, 0.0f, 1};

        translation->translateTo(this->m_lineSegmentStart.x,
                this->m_lineSegmentStart.y, this->m_lineSegmentStart.z);

        printf("Inserted line-segment-animated object with ID %hhd at world "
               "coordinates [%f, %f, %f]\n",
                insertedObj->getId(), this->m_lineSegmentStart.x,
                this->m_lineSegmentStart.y, this->m_lineSegmentStart.z);
    }
}

void DrawableObjectInteractionProvider::deleteSelectedObject() {
    this->m_animatedObjects.erase(this->m_owningScene.getSelectedObject());
    this->m_owningScene.removeSelectedObjectFromScene();
}
