// ShrekFionaScene.h - Contains definition of ShrekFionaScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "ShrekFionaScene.h"

#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <memory>
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
            "_templates\\basic.vert", "_templates\\lighting.frag", false);

    DrawableObject& shrekObj = this->addDrawableObjectFromKnownModel(
            true, KnownModels::SHREK, shaderProgram);
    shrekObj.addTexture(TextureFactory::create2dTextureFromFile(
            "shrek_fiona\\shrek.png", TexturingUnit::UNIT0));
    RotationPtr shrekRotation =
            shrekObj.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    shrekRotation->setAngle(-90.0f);

    DrawableObject& fionaObj = this->addDrawableObjectFromKnownModel(
            true, KnownModels::FIONA, shaderProgram);
    fionaObj.addTexture(TextureFactory::create2dTextureFromFile(
            "shrek_fiona\\fiona.png", TexturingUnit::UNIT0));
    RotationPtr fionaRotation =
            fionaObj.getTransformation()->addNewRotation(1.0f, 0.0f, 0.0f);
    fionaRotation->setAngle(-90.0f);

    DrawableObject& toiletObj = this->addDrawableObjectFromKnownModel(
            true, KnownModels::TOILET, shaderProgram);
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
