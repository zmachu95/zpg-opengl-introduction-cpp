// SceneRepository.h - Contains declaration of SceneRepository class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

class DrawableObject;
class PerspectiveCamera;
class ShaderProgram;

enum class KnownModels;

/**
 * @brief Alias for byte.
 */
using Byte = unsigned char;

/**
 * @brief Pointer to DrawableObject object.
 */
using DrawableObjectPtr = std::unique_ptr<DrawableObject>;

/**
 * @brief Pointer to ShaderProgram object.
 */
using ShaderProgramPtr = std::unique_ptr<ShaderProgram>;

/**
 * @brief Alias for tuple with DrawableObject and its ShaderProgram.
 */
using ObjectAndShader =
        std::pair<DrawableObjectPtr, std::reference_wrapper<ShaderProgram>>;

/**
 * @brief Manages scene's drawable objects and shaders.
 */
class SceneRepository {
  public:
    /**
     * @brief Enables iteration over stored drawable objects and their shaders.
     * @return Constant iterator.
     */
    std::unordered_multimap<Byte, ObjectAndShader>::const_iterator
    begin() const;

    /**
     * @brief Enables iteration over stored drawable objects and their
     * shaders.
     * @return Constant iterator.
     */
    std::unordered_multimap<Byte, ObjectAndShader>::const_iterator end() const;

    /**
     * @brief Finds drawn object by its ID.
     * @param id The ID of object to find.
     * @return Pointer to the object if object with such ID exists. Otherwise
     * returns nullptr.
     */
    DrawableObject* findObjectById(Byte id) const;

    /**
     * @brief Gets shader program for supplied drawable object.
     * @param object The drawable object.
     * @return If found, shader program belonging to given drawable object.
     * Otherwise returns nullptr.
     */
    ShaderProgram* getShaderProgram(DrawableObject& object) const;

    /*
     *
     */

    /**
     * @brief Changes the shader program of supplied drawable object.
     * @param object The drawable object.
     * @param newProgram The new shader program to use.
     * @return true if the drawable object was found and shader program was
     * changed, otherwise returns false.
     */
    bool changeShaderProgram(DrawableObject& object, ShaderProgram& newProgram);

    /**
     * @brief Makes copy of supplied drawable object.
     * @return Reference to newly inserted object.
     */
    DrawableObject& makeDrawableObjectCopy(DrawableObject& object);

    /**
     * @brief Removes the supplied drawable object from the scene.
     * @param object The object to be removed.
     * @return true if the object was removed, otherwise returns false.
     */
    bool removeDrawableObject(DrawableObject& object);

    /**
     * @brief Adds new drawable object into the scene.
     * @param generateId Flag whether the new object should receive unique ID.
     * @param verticesData Array of vertices data.
     * @param arrayElementsCount Total number of elements in the vertices data
     * array.
     * @param attributesCount Number of attributes in supplied vertices data.
     * @param uses2dTextures Supply true if model uses 2D textures, otherwise
     * false.
     * @param shaderProgram Shader program to use with the drawable object.
     * @return Reference to just created drawable object.
     */
    DrawableObject& addDrawableObjectFromVerticesData(bool generateId,
            const float* verticesData, size_t arrayElementsCount,
            unsigned int attributesCount, bool uses2dTextures,
            ShaderProgram& shaderProgram);

    /**
     * @brief Adds new drawable object into the scene from known model.
     * @param generateId Flag whether the new object should receive unique ID.
     * @param modelType Type of model to create.
     * @param shaderProgram Shader program to use with the drawable object.
     * @return Reference to just created drawable object.
     */
    DrawableObject& addDrawableObjectFromKnownModel(bool generateId,
            KnownModels modelType, ShaderProgram& shaderProgram);

    /**
     * @brief Adds new shader program into the scene and registers it to
     * camera's updates.
     * @param vertexShaderFile Path to file with vertex shader relative to
     * resources/shaders folder.
     * @param fragmentShaderFile Path to file with fragment shader relative to
     * resources/shaders folder.
     * @param rendersSkybox Flag whether the shader program is intended to
     * render skybox.
     * @param camera The scene's camera.
     * @return Reference to just created shader program.
     */
    ShaderProgram& addShaderProgramFromShaderFiles(
            const std::string& vertexShaderFile,
            const std::string& fragmentShaderFile, bool rendersSkybox,
            PerspectiveCamera* camera);

    /**
     * @brief Generates unique ID for drawable objects.
     * @return ID for drawable object.
     */
    Byte generateId() const;

  private:
    std::unordered_multimap<Byte, ObjectAndShader>
            m_drawableObjectsAndShadersLookup;
    std::vector<ShaderProgramPtr> m_shaderPrograms;
};
