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
#include <utility>

using namespace std::string_literals;

/**
 * @brief Number of dimensions in 3D.
 */
constexpr int DIMENSIONS_COUNT = 3;

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
        int attributesCount) {
    size_t floatsPerVertex = (size_t)DIMENSIONS_COUNT * attributesCount;
    if (arrayElementsCount % floatsPerVertex != 0) {
        throw std::invalid_argument(
                "Supplied array is not divisible by "
                + std::to_string(DIMENSIONS_COUNT * attributesCount) + "!");
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

    addVertexAttributes(attributesCount);
    glBindVertexArray(0);

    return Model(vao, vbo, (GLsizei)verticesCount);
}

void Model::addVertexAttributes(
        GLuint attributesCount) {
    for (GLuint i = 0; i < attributesCount; i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, DIMENSIONS_COUNT, GL_FLOAT, GL_FALSE,
                (GLsizei)attributesCount * DIMENSIONS_COUNT * sizeof(float),
                (GLvoid*)((size_t)DIMENSIONS_COUNT * i * sizeof(float)));
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
        ShaderProgram& shaderProgram, const glm::mat4& transformation) const {
    if (this->m_vao != 0 && this->m_vbo != 0) {
        shaderProgram.use(transformation);
        glBindVertexArray(this->m_vao);
        glDrawArrays(GL_TRIANGLES, 0,
                this->m_verticesCount); // mode,first,count

        glBindVertexArray(0);
        glUseProgram(0);
    }
}
