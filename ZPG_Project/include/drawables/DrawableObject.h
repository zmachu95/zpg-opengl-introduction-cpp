// DrawableObject.h - Contains declaration of DrawableObject class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>
#include <transformations/IGroupedTransformation.h>
#include <vector>

class ITexture;
class Model;
class ShaderProgram;

/**
 * @brief Pointer to Model object.
 */
using ModelPtr = std::shared_ptr<Model>;

/**
 * @brief Pointer to ITexture object.
 */
using TexturePtr = std::shared_ptr<ITexture>;

/**
 * @brief Represents a drawable object with its spatial transformation and
 * potentially textures.
 */
class DrawableObject {
  public:
    /**
     * @brief DrawableObject standard constructor.
     * @param model The model to bind.
     */
    DrawableObject(const ModelPtr& model);

    /*
     *
     */

    /**
     * @brief Gets the spatial transformation.
     * @return Reference to GroupedTransformation object.
     */
    GroupedTransformationPtr getTransformation();

    /*
     *
     */

    /**
     * @brief Draws the object in the currently active scene.
     * @param shaderProgram Shader program to be used for drawing the model.
     */
    void draw(ShaderProgram& shaderProgram);

    /*
     *
     */

    /**
     * @brief Adds texture to the object.
     * @param texture Texture to be added.
     * @return Reference to self.
     */
    DrawableObject& addTexture(const TexturePtr& texture);

  private:
    ModelPtr m_model;
    GroupedTransformationPtr m_transformation;
    std::vector<TexturePtr> m_textures;
};
