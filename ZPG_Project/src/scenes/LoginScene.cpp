// LoginScene.cpp - Contains definition of LoginScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <scenes/LoginScene.h>

#include <drawables/DrawableObject.h>
#include <drawables/Model.h>
#include <drawables/ModelManager.h>
#include <memory>
#include <scenes/IScene.h>
#include <shaders/FragmentShader.h>
#include <shaders/ShaderManager.h>
#include <shaders/ShaderProgram.h>
#include <shaders/VertexShader.h>
#include <transformations/GroupedTransformation.h>
#include <transformations/Rotation.h>
#include <transformations/Scale.h>
#include <transformations/Translation.h>

LoginScene::LoginScene()
    : IScene{}, m_login{}, m_shaderProgram{}, m_rotation{} {
    Model& loginModel = ModelManager::getModel(AvailableModels::LOGIN);

    FragmentShader& fragmentShader =
            ShaderManager::getFragmentShader(AvailableFragmentShaders::LOGIN);
    VertexShader& vertexShader =
            ShaderManager::getVertexShader(AvailableVertexShaders::BASIC);

    this->m_login = std::make_unique<DrawableObject>(loginModel);
    this->m_shaderProgram = std::make_unique<ShaderProgram>(
            ShaderProgram::createFromShaders(vertexShader, fragmentShader));
    this->m_rotation =
            this->m_login->getTransformation().addNewRotation(0.0f, 1.0f, 0.0f);
    ScalePtr scale = this->m_login->getTransformation().addNewScale();
    scale->setScaleTo(0.7f, 0.7f, 0.7f);
}

void LoginScene::draw(
        const float deltaT) {
    const float omega = 20.0f;
    this->m_rotation->incrementAngle(omega * deltaT);
    this->m_login->draw(*this->m_shaderProgram);
}
