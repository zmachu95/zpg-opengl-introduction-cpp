// TriangleScene.cpp - Contains definition of TriangleScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <scenes/TriangleScene.h>

#include <drawables/DrawableObject.h>
#include <drawables/Model.h>
#include <drawables/ModelManager.h>
#include <memory>
#include <scenes/IScene.h>
#include <shaders/FragmentShader.h>
#include <shaders/ShaderManager.h>
#include <shaders/ShaderProgram.h>
#include <shaders/VertexShader.h>
#include <transformations/Rotation.h>
#include <transformations/Scale.h>
#include <transformations/Translation.h>

TriangleScene::TriangleScene()
    : IScene{}, m_program{}, m_rotation{}, m_translation{}, m_triangle{} {
    FragmentShader& fragmentShader =
            ShaderManager::getFragmentShader(AvailableFragmentShaders::BASIC);
    VertexShader& vertexShader =
            ShaderManager::getVertexShader(AvailableVertexShaders::BASIC);

    Model& triangleModel = ModelManager::getModel(AvailableModels::TRIANGLE);

    this->m_program = std::make_unique<ShaderProgram>(
            ShaderProgram::createFromShaders(vertexShader, fragmentShader));
    this->m_triangle = std::make_unique<DrawableObject>(triangleModel);

    this->m_rotation =
            this->m_triangle->getTransformation().addNewRotation(0, 0, 1);
    this->m_translation =
            this->m_triangle->getTransformation().addNewTranslation();
}

void TriangleScene::draw(
        const float deltaT) {
    float angle = 90;
    this->m_rotation->setAngle(angle);
    this->m_translation->translateTo(0.5f, 0, 0);
    this->m_triangle->draw(*this->m_program);
}
