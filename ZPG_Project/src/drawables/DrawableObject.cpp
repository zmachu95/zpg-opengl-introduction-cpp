// DrawableObject.cpp - Contains definition of DrawableObject class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#ifndef GLAD_GL_H_
#include <glad/gl.h>
#endif

#include <drawables/DrawableObject.h>
#include <drawables/Model.h>
#include <shaders/ShaderProgram.h>
#include <transformations/GroupedTransformation.h>

void DrawableObject::draw(
        ShaderProgram& shaderProgram) {
    if (this->m_model.get().getVao() != 0
            && this->m_model.get().getVbo() != 0) {
        shaderProgram.use(this->m_transformation.getMatrix());
        glBindVertexArray(this->m_model.get().getVao());
        glDrawArrays(GL_TRIANGLES, 0,
                this->m_model.get().getVerticesCount()); // mode,first,count

        glBindVertexArray(0);
        shaderProgram.remove();
    }
}

GroupedTransformation& DrawableObject::getTransformation() {
    return this->m_transformation;
}

DrawableObject::DrawableObject(
        std::reference_wrapper<Model> model)
    : m_transformation{}, m_model{model} {}
