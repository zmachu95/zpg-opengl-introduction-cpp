// DrawableObject.h - Contains declaration of DrawableObject class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <transformations/GroupedTransformation.h>
#include <type_traits>

class Model;
class ShaderProgram;

/**
 * @brief Represents a drawable object with its spatial transformation.
 */
class DrawableObject {
  public:
    /**
     * @brief DrawableObject standard constructor.
     * @param model The model to bind.
     */
    DrawableObject(std::reference_wrapper<Model> model);

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
    std::reference_wrapper<Model> m_model;
    GroupedTransformation m_transformation;
};
