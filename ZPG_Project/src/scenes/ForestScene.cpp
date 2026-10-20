// ForestScene.cpp - Contains definition of ForestScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <scenes/ForestScene.h>

#include <cstdlib>
#include <drawables/DrawableObject.h>
#include <drawables/DrawableObjectFactory.h>
#include <memory>
#include <scenes/IScene.h>
#include <shaders/ShaderProgram.h>
#include <transformations/IGroupedTransformation.h>
#include <transformations/IRotation.h>
#include <transformations/IScale.h>
#include <transformations/ITranslation.h>
#include <vector>

#include <resources/models/bushes.h>
#include <resources/models/tree.h>

const float groundYCoordinate = -0.9f;

static void createRandomTrees(
        const int treesCount, std::vector<DrawableObjectPtr>& drawableObjects) {
    for (int i = 0; i < treesCount; i++) {
        float scaleX = (float)(rand() % 4 + 4) / 100;
        float scaleY = (float)(rand() % 8 + 4) / 100;
        float positionX = -0.8f + (1.6f * i) / (treesCount - 1);

        drawableObjects.push_back(
                DrawableObjectFactory::createDrawableObjectFromVerticesData(
                        tree, sizeof(tree) / sizeof(tree[0]), 2));
        DrawableObject* drawableTree = drawableObjects.back().get();
        TranslationPtr translation =
                drawableTree->getTransformation()->addNewTranslation();
        ScalePtr scale = drawableTree->getTransformation()->addNewScale();

        translation->translateTo(positionX, groundYCoordinate, 0.f);
        scale->setScaleTo(scaleX, scaleY, scaleX);
    }
}

static void createRandomBushes(
        const int bushesCount,
        std::vector<DrawableObjectPtr>& drawableObjects) {
    for (int i = 0; i < bushesCount; i++) {
        float scaleX = (float)(rand() % 5 + 10) / 100;
        float scaleY = (float)(rand() % 10 + 10) / 100;
        float positionX =
                -0.95f + (1.9f * i) / (bushesCount - 1)
                + (rand() % 2 == 1 ? 1 : -1) * (float)(rand() % 4) / 100;

        drawableObjects.push_back(
                DrawableObjectFactory::createDrawableObjectFromVerticesData(
                        bushes, sizeof(bushes) / sizeof(bushes[0]), 2));
        DrawableObject* drawableBush = drawableObjects.back().get();
        TranslationPtr translation =
                drawableBush->getTransformation()->addNewTranslation();
        ScalePtr scale = drawableBush->getTransformation()->addNewScale();

        translation->translateTo(positionX, groundYCoordinate, 0.f);
        scale->setScaleTo(scaleX, scaleY, scaleX);
    }
}

ForestScene::ForestScene() : IScene{}, m_treesAndBushes{}, m_shaderProgram{} {
    createRandomTrees(8, this->m_treesAndBushes);
    createRandomBushes(20, this->m_treesAndBushes);

    m_shaderProgram =
            ShaderProgram::createFromShaderFiles("basic.vert", "basic.frag");
}

void ForestScene::draw(
        const float deltaT) {
    for (DrawableObjectPtr& ptr : this->m_treesAndBushes) {
        ptr->draw(*this->m_shaderProgram.get());
    }
}

void ForestScene::handleMouseMovement(
        int cursorDeltaX, int cursorDeltaY) {}

void ForestScene::handleKeyPresses(
        KeyCodes button, KeyActions action, KeyModifierFlags mode) {}

void ForestScene::handleWindowResize(
        int width, int height) {}
