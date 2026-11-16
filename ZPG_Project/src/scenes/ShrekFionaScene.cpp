// ShrekFionaScene.h - Contains definition of ShrekFionaScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "ShrekFionaScene.h"

#include <drawables/DrawableObject.h>
#include <memory>
#include <resources/models/fiona.h>
#include <resources/models/shrek.h>
#include <resources/models/toilet.h>
#include <shaders/ShaderProgram.h>
#include <src/scenes/AbstractSceneTemplate.h>
#include <textures/ITexture.h>
#include <textures/TextureFactory.h>
#include <transformations/IGroupedTransformation.h>
#include <transformations/IRotation.h>
#include <transformations/IScale.h>
#include <transformations/ITranslation.h>

ShrekFionaScene::ShrekFionaScene(
        int windowWidth, int windowHeight)
    : AbstractSceneTemplate{windowWidth, windowHeight} {
    ShaderProgram& shaderProgram = this->addShaderProgramFromShaderFiles(
            "_templates\\basic.vert", "_templates\\ambient.frag", false);

    DrawableObject& shrekObj = this->addDrawableObjectFromVerticesData(true,
            shrek, sizeof(shrek) / sizeof(shrek[0]), 2, true, shaderProgram);
    shrekObj.addTexture(TextureFactory::create2dTextureFromFile(
            "shrek_fiona\\shrek.png", TexturingUnit::UNIT0));
    RotationPtr shrekRotation =
            shrekObj.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    shrekRotation->setAngle(-90.0f);

    DrawableObject& fionaObj = this->addDrawableObjectFromVerticesData(true,
            fiona, sizeof(fiona) / sizeof(fiona[0]), 2, true, shaderProgram);
    fionaObj.addTexture(TextureFactory::create2dTextureFromFile(
            "shrek_fiona\\fiona.png", TexturingUnit::UNIT0));
    RotationPtr fionaRotation =
            fionaObj.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    fionaRotation->setAngle(-90.0f);

    DrawableObject& toiletObj = this->addDrawableObjectFromVerticesData(true,
            toilet, sizeof(toilet) / sizeof(toilet[0]), 2, true, shaderProgram);
    toiletObj.addTexture(TextureFactory::create2dTextureFromFile(
            "shrek_fiona\\toilet.jpg", TexturingUnit::UNIT0));
    RotationPtr toiletRotation =
            toiletObj.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    toiletRotation->setAngle(-90.0f);

    TranslationPtr shrekTranslation =
            shrekObj.getTransformation()->addNewTranslation();
    shrekTranslation->move(2.0f, 0.0f, 0.0f);

    TranslationPtr fionaTranslation =
            fionaObj.getTransformation()->addNewTranslation();
    fionaTranslation->move(-2.0f, 0.0f, 0.0f);
}

void ShrekFionaScene::updateSceneContents(
        const float deltaT) {}
