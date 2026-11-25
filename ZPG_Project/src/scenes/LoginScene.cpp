// LoginScene.cpp - Contains definition of LoginScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "LoginScene.h"
#include "AbstractSceneTemplate.h"

#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <memory>
#include <shaders/ShaderProgram.h>
#include <transformations/IGroupedTransformation.h>
#include <transformations/IRotation.h>
#include <transformations/IScale.h>
#include <transformations/ITranslation.h>

#include <cameras/PerspectiveCamera.h>

LoginScene::LoginScene(
        int windowWidth, int windowHeight)
    : AbstractSceneTemplate{std::unique_ptr<PerspectiveCamera>{},
              std::unique_ptr<DrawableObject>{}},
      m_rotation{} {
    ShaderProgram& shaderProgram = this->addShaderProgramFromShaderFiles(
            "_templates\\basic.vert", "_templates\\basic.frag", false);

    DrawableObject& login = this->addDrawableObjectFromKnownModel(
            false, KnownModels::LOGIN, shaderProgram);

    this->m_rotation =
            login.getTransformation()->addNewRotation(0.0f, 1.0f, 0.0f);
    ScalePtr scale = login.getTransformation()->addNewScale();
    scale->setScaleTo(0.7f, 0.7f, 0.7f);
}

void LoginScene::updateSceneContents(
        float deltaT) {
    const float omega = 20.0f;
    this->m_rotation->incrementAngle(omega * deltaT);
}
