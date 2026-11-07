// Model.cpp - Contains definition of Model class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include "Model.h"
#include <shaders/ShaderProgram.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <textures/ITexture.h>
#include <utility>
#include <vector>

using namespace std::string_literals;

/**
 * @brief Number of dimensions in 3D.
 */
constexpr int DIMENSIONS_COUNT = 3;

/**
 * @brief Number of values needed for textures.
 */
constexpr int TEXTURE_DIMS_COUNT = 2;

Model::Model(
        GLuint vao, GLuint vbo, GLsizei verticeCount)
    : m_vao{vao}, m_vbo{vbo}, m_verticesCount{verticeCount} {
    std::cout << "Creating model with VAO ID " << vao << ", VBO ID " << vbo
              << " and " << verticeCount << " vertices.\n";
}

Model::Model(
        Model&& other) noexcept
    : m_vao{std::exchange(other.m_vao, 0)},
      m_vbo{std::exchange(other.m_vbo, 0)},
      m_verticesCount{std::exchange(other.m_verticesCount, 0)} {}

Model::~Model() {
    this->deleteVao();
    this->deleteVbo();
}

Model& Model::operator=(
        Model&& other) noexcept {
    if (this != &other) {
        deleteVao();
        deleteVbo();

        this->m_vao = std::exchange(other.m_vao, 0);
        this->m_vbo = std::exchange(other.m_vbo, 0);
        this->m_verticesCount = std::exchange(other.m_verticesCount, 0);
    }

    return *this;
}

Model Model::fromVerticesData(
        const float* verticesData, size_t arrayElementsCount,
        int attributesCount, bool uses2dTextures) {
    size_t floatsPerVertex = (size_t)DIMENSIONS_COUNT * attributesCount
                             + uses2dTextures * TEXTURE_DIMS_COUNT;
    if (arrayElementsCount % floatsPerVertex != 0) {
        throw std::invalid_argument(
                "Supplied array is not divisible by "
                + std::to_string(DIMENSIONS_COUNT * attributesCount
                                 + uses2dTextures * TEXTURE_DIMS_COUNT)
                + "!");
    }

    size_t verticesCount = arrayElementsCount / floatsPerVertex;
    GLuint vbo = 0;
    GLuint vao = 0;
    glGenBuffers(1, &vbo);      // generate the VBO
    glGenVertexArrays(1, &vao); // generate the VAO

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
            (GLsizeiptr)arrayElementsCount * sizeof(float),
            (const void*)verticesData, GL_STATIC_DRAW);

    addVertexAttributes(attributesCount, uses2dTextures);
    glBindVertexArray(0);

    return Model(vao, vbo, (GLsizei)verticesCount);
}

void Model::addVertexAttributes(
        GLuint attributesCount, bool uses2dTextures) {
    // attributes
    const GLint attributeSize = DIMENSIONS_COUNT;
    const GLsizei stride = (GLsizei)(attributesCount * DIMENSIONS_COUNT
                                     + uses2dTextures * TEXTURE_DIMS_COUNT)
                           * sizeof(float);
    const int offsetStep = (DIMENSIONS_COUNT * sizeof(float));
    for (GLuint i = 0; i < attributesCount; i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attributeSize, GL_FLOAT, GL_FALSE, stride,
                (GLvoid*)((size_t)offsetStep * i));
    }

    // texture mapping
    if (uses2dTextures) {
        glEnableVertexAttribArray(attributesCount);
        glVertexAttribPointer(attributesCount, TEXTURE_DIMS_COUNT, GL_FLOAT,
                GL_FALSE, stride,
                (GLvoid*)((size_t)offsetStep * attributesCount));
    }
}

void Model::deleteVao() {
    if (this->m_vao != 0) {
        std::cout << "Deleting VAO with id " << this->m_vao << ".\n";
        glDeleteVertexArrays(1, &this->m_vao);
        this->m_vao = 0;
    }
}

void Model::deleteVbo() {
    if (this->m_vbo != 0) {
        std::cout << "Deleting VBO with id " << this->m_vbo << ".\n";
        glDeleteBuffers(1, &this->m_vbo);
        this->m_vbo = 0;
    }
}

const GLuint Model::getVao() const { return this->m_vao; }

const GLuint Model::getVbo() const { return this->m_vbo; }

const GLsizei Model::getVerticesCount() const { return this->m_verticesCount; }

void Model::draw(
        ShaderProgram& shaderProgram, const glm::mat4& transformation,
        const std::vector<TexturePtr>& textures) const {
    if (this->m_vao != 0 && this->m_vbo != 0) {
        shaderProgram.use(transformation, textures);

        // apply textures to their texturing units
        for (const TexturePtr& texture : textures) {
            glActiveTexture(texture->getTexturingUnit());
            glBindTexture(texture->getTextureTarget(), texture->getId());
        }

        // make draw call
        glBindVertexArray(this->m_vao);
        glDrawArrays(GL_TRIANGLES, 0,
                this->m_verticesCount); // mode,first,count

        // unbind VAO and textures from texturing units
        glBindVertexArray(0);
        for (auto it = textures.crbegin(); it != textures.crend(); it++) {
            glActiveTexture((*it)->getTexturingUnit());
            glBindTexture((*it)->getTextureTarget(), 0);
        }

        glUseProgram(0);
    }
}
