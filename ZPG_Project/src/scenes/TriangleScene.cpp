// TriangleScene.cpp - Contains definition of TriangleScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "TriangleScene.h"
#include "AbstractSceneTemplate.h"

#include <memory>
#include <shaders/ShaderProgram.h>
#include <transformations/IRotation.h>
#include <transformations/IScale.h>
#include <transformations/ITranslation.h>

#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>

TriangleScene::TriangleScene(
        int windowWidth, int windowHeight)
    : AbstractSceneTemplate{
              windowWidth, windowHeight, std::unique_ptr<DrawableObject>{}},
      m_rotation{}, m_translation{} {
    ShaderProgram& shaderProgram = this->addShaderProgramFromShaderFiles(
            "_templates\\basic.vert", "_templates\\basic.frag", false);
    DrawableObject& triangleObj = this->addDrawableObjectFromKnownModel(
            false, KnownModels::TRIANGLE, shaderProgram);

    this->m_rotation = triangleObj.getTransformation()->addNewRotation(0, 0, 1);
    this->m_translation = triangleObj.getTransformation()->addNewTranslation();
}

void TriangleScene::updateSceneContents(
        float deltaT) {
    float angle = 90;
    this->m_rotation->setAngle(angle);
    this->m_translation->translateTo(0.5f, 0, 0);
}
