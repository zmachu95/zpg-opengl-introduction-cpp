// Model.h - Contains declaration of Model class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

using GLuint = unsigned int;
using GLsizei = int;

/**
 * @brief Represents single OpenGL with its VBO and VAO objects.
 */
class Model {
  public:
    /**
     * @brief Model move constructor.
     * @param other The source model to be moved.
     */
    Model(Model&& other) noexcept;

    /**
     * @brief Model copy constructor. This constructor is intentionally deleted
     * to prevent OpenGL from accidentally discarding the VBO and VAO objects.
     */
    Model(const Model&) = delete;

    virtual ~Model();

    /*
     *
     */

    /**
     * @brief Model move operator.
     * @param other The source model to be moved.
     * @return Moved Model object.
     */
    Model& operator=(Model&& other) noexcept;

    /**
     * @brief Copy-by-reference operator. This operator is intentionally deleted
     * to prevent OpenGL from accidentally discarding the VBO and VAO objects.
     */
    Model& operator=(const Model& other) = delete;

    /*
     *
     */

    /**
     * @brief Factory method for creating new model from supplied vertices data
     * array.
     * @param verticesPositionsAndColors Array containing vertice positions and
     * colors.
     * @param elementsCount The total number of floats in the array.
     * @return New Model object.
     * @throw std::invalid_argument Thrown when the supplied array is not
     * divisible by 6 (3 position floats + 3 color floats).
     */
    static Model fromVerticePositionsAndColors(
            const float* verticesPositionsAndColors,
            const size_t elementsCount);

    /**
     * @brief Factory method for creating new model from supplied vertices data
     * array.
     * @param verticesPositionsColorsNormals Array containing vertice positions,
     * colors and normals.
     * @param elementsCount The total number of floats in the array.
     * @return New Model object.
     * @throw std::invalid_argument Thrown when the supplied array is not
     * divisible by 9 (3 position floats + 3 color floats + 3 normal floats).
     */
    static Model fromVerticePositionsColorsNormals(
            const float* verticesPositionsColorsNormals,
            const size_t elementsCount);

    /*
     *
     */

    /**
     * @brief Gets ID of bound VAO object.
     * @return GLuint with VAO ID.
     */
    const GLuint getVao() const;

    /**
     * @brief Gets ID of bound VBO object.
     * @return GLuint with VBO ID.
     */
    const GLuint getVbo() const;

    /**
     * @brief Gets the number of vertices in the model.
     * @return Vertices count.
     */
    const GLsizei getVerticesCount() const;

  private:
    GLuint m_vao;
    GLuint m_vbo;
    GLsizei m_verticesCount;

    /**
     * @brief Default Model constructor.
     * @param vao ID of VAO array.
     * @param vbo ID of VBO array.
     * @param verticeCount Number of vertices in the model.
     */
    Model(GLuint vao, GLuint vbo, GLsizei verticeCount);
};
