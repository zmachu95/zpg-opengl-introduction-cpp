// LoginScene.cpp - Contains definition of LoginScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <scenes/LoginScene.h>

#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <memory>
#include <scenes/IScene.h>
#include <shaders/ShaderProgram.h>
#include <transformations/GroupedTransformation.h>
#include <transformations/IRotation.h>
#include <transformations/IScale.h>
#include <transformations/ITranslation.h>

#include <resources/models/mac0690.h>

LoginScene::LoginScene()
    : IScene{}, m_login{}, m_shaderProgram{}, m_rotation{} {
    this->m_login = DrawableObjectFactory::createDrawableObjectFromVerticesData(
            mac0690, sizeof(mac0690) / sizeof(mac0690[0]), 2);
    this->m_shaderProgram =
            ShaderProgram::createFromShaderFiles("basic.vert", "basic.frag");
    this->m_rotation = this->m_login->getTransformation()->addNewRotation(
            0.0f, 1.0f, 0.0f);
    ScalePtr scale = this->m_login->getTransformation()->addNewScale();
    scale->setScaleTo(0.7f, 0.7f, 0.7f);
}

void LoginScene::draw(
        const float deltaT) {
    const float omega = 20.0f;
    this->m_rotation->incrementAngle(omega * deltaT);
    this->m_login->draw(*this->m_shaderProgram);
}

void LoginScene::handleMouseMovement(
        int cursorDeltaX, int cursorDeltaY) {}

void LoginScene::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {}

void LoginScene::handleWindowResize(
        int width, int height) {}
