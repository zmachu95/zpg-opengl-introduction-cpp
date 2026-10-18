// Model.cpp - Contains definition of Model class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include <drawables/Model.h>

#include <iostream>
#include <stdexcept>
#include <utility>

constexpr int DIMENSIONS_COUNT = 3;

static void enableVertexAttributes(
        GLuint attributesCount) {
    for (GLuint i = 0; i < attributesCount; i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, DIMENSIONS_COUNT, GL_FLOAT, GL_FALSE,
                (GLsizei)attributesCount * DIMENSIONS_COUNT * sizeof(float),
                (GLvoid*)((size_t)DIMENSIONS_COUNT * i * sizeof(float)));
    }
}

static void createVaoAndVboObjects(
        GLuint& vao, GLuint& vbo, const float* verticesData,
        size_t elementsCount) {
    glGenBuffers(1, &vbo);      // generate the VBO
    glGenVertexArrays(1, &vao); // generate the VAO

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)elementsCount * sizeof(float),
            (const void*)verticesData, GL_STATIC_DRAW);
}

static void deleteVao(
        GLuint& vao) {
    if (vao != 0) {
        std::cout << "Deleting VAO with id " << vao << ".\n";
        glDeleteVertexArrays(1, &vao);
    }
}

static void deleteVbo(
        GLuint& vbo) {
    if (vbo != 0) {
        std::cout << "Deleting VBO with id " << vbo << ".\n";
        glDeleteBuffers(1, &vbo);
    }
}

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
    deleteVao(this->m_vao);
    deleteVbo(this->m_vbo);
}

Model& Model::operator=(
        Model&& other) noexcept {
    if (this != &other) {
        deleteVao(this->m_vao);
        deleteVbo(this->m_vbo);

        this->m_vao = other.m_vao;
        this->m_vbo = other.m_vbo;
        this->m_verticesCount = other.m_verticesCount;

        other.m_vao = 0;
        other.m_vbo = 0;
        other.m_verticesCount = 0;
    }

    return *this;
}

Model Model::fromVerticePositionsAndColors(
        const float* verticesPositionsAndColors, const size_t elementsCount) {
    if (elementsCount % 6 != 0) {
        throw std::invalid_argument("Supplied array is not divisible by 6!");
    }

    GLuint vbo = 0;
    GLuint vao = 0;
    createVaoAndVboObjects(vao, vbo, verticesPositionsAndColors, elementsCount);
    enableVertexAttributes(2);
    glBindVertexArray(0);

    return Model(vao, vbo, (GLsizei)(elementsCount / 6));
}

Model Model::fromVerticePositionsColorsNormals(
        const float* verticesPositionsColorsNormals,
        const size_t elementsCount) {
    if (elementsCount % 9 != 0) {
        throw std::invalid_argument("Supplied array is not divisible by 9!");
    }

    GLuint vbo = 0;
    GLuint vao = 0;
    createVaoAndVboObjects(
            vao, vbo, verticesPositionsColorsNormals, elementsCount);
    enableVertexAttributes(3);
    glBindVertexArray(0);

    return Model(vao, vbo, (GLsizei)(elementsCount / 9));
}

const GLuint Model::getVao() const { return this->m_vao; }

const GLuint Model::getVbo() const { return this->m_vbo; }

const GLsizei Model::getVerticesCount() const { return this->m_verticesCount; }
