// ForestScene.h - Contains declaration of ForestScene class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include "AbstractSceneTemplate.h"
#include <memory>
#include <type_traits>
#include <vector>

class DrawableObject;
class ShaderProgram;
class ITranslation;
enum class MouseButtonActions;
enum class MouseButtonCodes;
enum class KeyModifierFlags;

/**
 * @brief Pointer for ITranslation object.
 */
using TranslationPtr = std::shared_ptr<ITranslation>;

/**
 * @brief Holds torchbug data.
 */
struct TorchbugData {
    DrawableObject* torchbug;
    float phaseAngle_deg;
    TranslationPtr localTranslation;
};

/**
 * @brief Scene with random trees and bushes.
 */
class ForestScene : public AbstractSceneTemplate {
  public:
    /**
     * @brief ForestScene standard constructor.
     * @param windowWidth Application window width in [px].
     * @param windowHeight Application window height in [px].
     */
    ForestScene(int windowWidth, int windowHeight);

    ~ForestScene() override = default;

    /**
     * @brief Handles mouse click event.
     * @param button Clicked mouse button.
     * @param action The mouse button action.
     * @param mode Button modifier mode.
     */
    void handleMouseClick(MouseButtonCodes button, MouseButtonActions action,
            KeyModifierFlags mode) override;

  protected:
    /**
     * @brief Updates the scene contents.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void updateSceneContents(float deltaT) override;

    /**
     * @brief Updates the parameters of skybox shader program.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void updateSkyboxShaderProgram(float deltaT) override;

  private:
    ShaderProgram* m_clockShaderProgram;
    std::vector<std::reference_wrapper<ShaderProgram>> m_dynamicShaderPrograms;
    std::vector<TorchbugData> m_torchbugs;
    bool m_useFlashlight;
    bool m_updatedSkyboxShader;
    bool m_initializedShaders;

    /**
     * @brief Creates random trees.
     * @param treesCount Number of trees to create.
     */
    void createRandomTrees(
            const int treesCount, ShaderProgram& treeShaderProgram);

    /**
     * @brief Creates random bushes.
     * @param treesCount Number of bushes to create.
     */
    void createRandomBushes(
            const int bushesCount, ShaderProgram& bushShaderProgram);

    /**
     * @brief Draws clock with current system time.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void drawClock(float deltaT);

    /**
     * @brief Provides logic for drawing torchbugs in the scene.
     * @param deltaT Time elapsed since the last drawn frame.
     */
    void drawTorchbugs(float deltaT);

    /**
     * @brief Creates specified number of torchbugs with random locations.
     * @param count Number of torchbugs to create.
     */
    void createRandomTorchbugs(
            int count, ShaderProgram& torchbugsShaderProgram);

    /**
     * @brief Initializes uniform variables inside shader programs.
     */
    void initializeShaderPrograms();
};
