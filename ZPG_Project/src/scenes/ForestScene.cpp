// ForestScene.cpp - Contains definition of ForestScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <scenes/ForestScene.h>

#include <cstdlib>
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
#include <vector>

const float groundYCoordinate = -0.9f;

static void createRandomTrees(
        const int treesCount, Model& treeModel,
        std::vector<DrawableObjectPtr>& drawableObjects) {
    for (int i = 0; i < treesCount; i++) {
        float scaleX = (float)(rand() % 4 + 4) / 100;
        float scaleY = (float)(rand() % 8 + 4) / 100;
        float positionX = -0.8f + (1.6f * i) / (treesCount - 1);

        drawableObjects.push_back(std::make_unique<DrawableObject>(treeModel));
        DrawableObject* drawableTree = drawableObjects.back().get();
        TranslationPtr translation =
                drawableTree->getTransformation().addNewTranslation();
        ScalePtr scale = drawableTree->getTransformation().addNewScale();

        translation->translateTo(positionX, groundYCoordinate, 0.f);
        scale->setScaleTo(scaleX, scaleY, scaleX);
    }
}

static void createRandomBushes(
        const int bushesCount, Model& bushModel,
        std::vector<DrawableObjectPtr>& drawableObjects) {
    for (int i = 0; i < bushesCount; i++) {
        float scaleX = (float)(rand() % 5 + 10) / 100;
        float scaleY = (float)(rand() % 10 + 10) / 100;
        float positionX =
                -0.95f + (1.9f * i) / (bushesCount - 1)
                + (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 4) / 100;

        drawableObjects.push_back(std::make_unique<DrawableObject>(bushModel));
        DrawableObject* drawableBush = drawableObjects.back().get();
        TranslationPtr translation =
                drawableBush->getTransformation().addNewTranslation();
        ScalePtr scale = drawableBush->getTransformation().addNewScale();

        translation->translateTo(positionX, groundYCoordinate, 0.f);
        scale->setScaleTo(scaleX, scaleY, scaleX);
    }
}

ForestScene::ForestScene() : IScene{}, m_treesAndBushes{}, m_shaderProgram{} {
    Model& treeModel = ModelManager::getModel(AvailableModels::TREE);
    Model& bushModel = ModelManager::getModel(AvailableModels::BUSHES);

    FragmentShader& fragmentShader =
            ShaderManager::getFragmentShader(AvailableFragmentShaders::BASIC);
    VertexShader& vertexShader =
            ShaderManager::getVertexShader(AvailableVertexShaders::BASIC);

    createRandomTrees(8, treeModel, this->m_treesAndBushes);
    createRandomBushes(20, bushModel, this->m_treesAndBushes);

    m_shaderProgram = std::make_unique<ShaderProgram>(
            ShaderProgram::createFromShaders(vertexShader, fragmentShader));
}

void ForestScene::draw(
        const float deltaT) {
    for (DrawableObjectPtr& ptr : this->m_treesAndBushes) {
        ptr->draw(*this->m_shaderProgram.get());
    }
}
