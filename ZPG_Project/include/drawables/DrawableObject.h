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
 * @brief Alias for byte.
 */
using Byte = unsigned char;

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
     * @param id ID to assign.
     */
    DrawableObject(const ModelPtr& model, Byte id);

    /**
     * @brief DrawableObject copy constructor. This constructor is deleted to
     * prevent two objects sharing the same ID and same transformations.
     */
    DrawableObject(const DrawableObject&) = delete;

    /**
     * @brief DrawableObject move constructor.
     */
    DrawableObject(DrawableObject&& other) noexcept;

    ~DrawableObject() = default;

    /*
     *
     */

    /**
     * @brief DrawableObject copy operator. This operator is deleted to
     * prevent two objects sharing the same ID and same transformations.
     */
    DrawableObject& operator=(const DrawableObject&) = delete;

    /**
     * @brief DrawableObject move operator. This operator is deleted to
     * prevent dangling reference problems.
     */
    DrawableObject& operator=(DrawableObject&& other) noexcept = delete;

    /**
     * @brief Clones this drawable object into a standalone copy with supplied
     * ID. Only textures are copied to the clone; transformations are completely
     * ignored.
     * @param newId The ID assigned to the new copy.
     * @return Standalone clone with given ID.
     */
    DrawableObject cloneWithoutTransformations(Byte newId) const;

    /*
     *
     */

    /**
     * @brief Gets this object's ID.
     * @return This object's ID.
     */
    Byte getId() const;

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
    Byte m_id;
    ModelPtr m_model;
    GroupedTransformationPtr m_transformation;
    std::vector<TexturePtr> m_textures;
};
