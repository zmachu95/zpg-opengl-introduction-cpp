// DrawableObject.h - Contains declaration of DrawableObject class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>
#include <transformations/GroupedTransformation.h>

class Model;
class ShaderProgram;

using ModelPtr = std::shared_ptr<Model>;

/**
 * @brief Represents a drawable object with its spatial transformation.
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
    GroupedTransformation& getTransformation();

    /*
     *
     */

    /**
     * @brief Draws the object in the currently active scene.
     * @param shaderProgram Shader program to be used for drawing the model.
     */
    void draw(ShaderProgram& shaderProgram);

  private:
    ModelPtr m_model;
    GroupedTransformation m_transformation;
};
