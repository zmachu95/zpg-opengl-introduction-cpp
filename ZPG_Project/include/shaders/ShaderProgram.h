// ShaderProgram.h - Contains declaration of ShaderProgram class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>
#include <shaders/UniformVariableManager.h>
#include <stdexcept>
#include <string>
#include <type_traits>

class VertexShader;
class FragmentShader;
class ICameraUpdateListener;

using GLuint = unsigned int;

/**
 * @brief Indicates that OpenGL could not create the shader program.
 */
class ShaderProgramNotCreatedException : public std::runtime_error {
  public:
    ShaderProgramNotCreatedException(const std::string& message)
        : std::runtime_error(message) {};
};

/**
 * @brief Indicates that shader program could not be linked.
 */
class ShaderProgramLinkErrorException : public std::runtime_error {
  public:
    ShaderProgramLinkErrorException(const std::string& message)
        : std::runtime_error(message) {};
};

/**
 * @brief Represents compiled OpenGL shader program.
 */
class ShaderProgram {
  public:
    /**
     * @brief ShaderProgram move constructor.
     * @param other The source shader program to be moved.
     */
    ShaderProgram(ShaderProgram&& other) noexcept;

    /**
     * @brief ShaderProgram copy constructor. This constructor is intentionally
     * deleted to prevent OpenGL from accidentally discarding the compiled
     * shader program.
     */
    ShaderProgram(const ShaderProgram&) = delete;

    virtual ~ShaderProgram();

    /*
     *
     */

    /**
     * @brief ShaderProgram move operator
     * @param other The source shader program to be moved.
     * @return Moved ShaderProgram object.
     */
    ShaderProgram& operator=(ShaderProgram&& other) noexcept;

    /**
     * @brief Copy-by-reference operator. This operator is intentionally deleted
     * to prevent OpenGL from accidentally discarding the compiled shader
     * program.
     */
    ShaderProgram& operator=(const ShaderProgram& other) = delete;

    /*
     *
     */

    /**
     * @brief Factory method which creates a shader program from vertex and
     * fragment shader.
     * @param vertexShader The vertex shader.
     * @param fragmentShader The fragment shader.
     * @return
     * @throw std::invalid_argument - Thrown when the shader types are invalid.
     * @throw ShaderProgramNotCreatedException - Thrown when OpenGL could not
     * create the shader program.
     */
    static ShaderProgram createFromShaders(
            VertexShader& vertexShader, FragmentShader& fragmentShader);

    /*
     *
     */

    /**
     * @brief Gets the ID of compiled shader program.
     * @return GLuint with shader program ID.
     */
    const GLuint getId() const;

    /**
     * @brief Gets the used vertex shader.
     * @return VertexShader object.
     */
    const VertexShader& getVertexShader() const;

    /**
     * @brief Gets the used fragment shader.
     * @return FragmentShader object.
     */
    const FragmentShader& getFragmentShader() const;

    /**
     * @brief Converts the shader program to camera update event listener.
     * @return Weak pointer to ICameraUpdateListener object.
     */
    std::weak_ptr<ICameraUpdateListener> asCameraUpdateListener();

    /*
     *
     */

    /**
     * @brief Uses the shader program in currently active scene.
     */
    void use(const glm::mat4& transformationMatrix);

    /**
     * @brief Removes the currently active shader program from OpenGL, but does
     * not destroy it.
     */
    void remove();

  private:
    static GLuint s_activeProgramId;

    GLuint m_id;
    std::shared_ptr<UniformVariableManager> m_uniformVarManager;
    std::reference_wrapper<VertexShader> m_vertexShader;
    std::reference_wrapper<FragmentShader> m_fragmentShader;

    /**
     * @brief ShaderProgram default constructor.
     * @param id The shader program ID.
     * @param uniformVariableManager The uniform variable manager.
     * @param vertexShader Used vertex shader.
     * @param fragmentShader Used fragment shader.
     */
    ShaderProgram(GLuint id,
            std::shared_ptr<UniformVariableManager>&& uniformVariableManager,
            std::reference_wrapper<VertexShader> vertexShader,
            std::reference_wrapper<FragmentShader> fragmentShader);
};
