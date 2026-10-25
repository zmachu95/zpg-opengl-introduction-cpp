// ShaderProgram.h - Contains declaration of ShaderProgram class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

class VertexShader;
class FragmentShader;
class ICameraUpdateListener;
class ShaderProgram;
class UniformVariableManager;

using GLuint = unsigned int;
using VertexShaderPtr = std::shared_ptr<VertexShader>;
using FragmentShaderPtr = std::shared_ptr<FragmentShader>;
using UniformVariableManagerPtr = std::shared_ptr<UniformVariableManager>;
using ShaderProgramPtr = std::unique_ptr<ShaderProgram>;

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
     * @return Pointer to new shader program.
     * @throw std::invalid_argument - Thrown when the shader types are invalid.
     * @throw ShaderProgramNotCreatedException - Thrown when OpenGL could not
     * create the shader program.
     */
    static ShaderProgramPtr createFromShaderFiles(
            const std::string& vertexShaderFile,
            const std::string& fragmentShaderFile);

    /*
     *
     */

    /**
     * @brief Gets the ID of compiled shader program.
     * @return GLuint with shader program ID.
     */
    GLuint getId() const;

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
     * @brief Stores supplied supplemental matrices for application during next
     * draw call.
     * @param supplementalMatricesMap Map of shader matrix variables and their
     * values.
     * @throw UniformVariableNotFoundException - Thrown if the variable could
     * not be found.
     */
    void setSupplementalUniformMatrices(
            const std::unordered_map<std::string, glm::mat4>&
                    supplementalMatricesMap);

  private:
    GLuint m_id;
    UniformVariableManagerPtr m_uniformVarManager;
    VertexShaderPtr m_vertexShader;
    FragmentShaderPtr m_fragmentShader;
    std::unordered_map<std::string, glm::mat4> m_supplementalUniformMatrices;

    /**
     * @brief ShaderProgram default constructor.
     * @param id The shader program ID.
     * @param uniformVariableManager The uniform variable manager.
     * @param vertexShader The vertex shader.
     * @param fragmentShader The fragment shader.
     */
    ShaderProgram(GLuint id,
            const UniformVariableManagerPtr& uniformVariableManager,
            const VertexShaderPtr& vertexShader,
            const FragmentShaderPtr& fragmentShader);

    /**
     * @brief Verifies the shader program linking status.
     * @throw ShaderProgramLinkErrorException - Thrown if the shader program was
     * not linked successfully.
     */
    static void verifyShaderProgramLinking(GLuint programId);

    /**
     * @brief Links the new shader program with supplied shaders.
     * @param vertexShader The vertex shader to use.
     * @param fragmentShader The fragment shader to use.
     * @return New shader program.
     * @throw ShaderProgramLinkErrorException - Thrown if the shader program was
     * not linked successfully.
     * @throw ShaderProgramNotCreatedException - Thrown when OpenGL could not
     * create the shader program.
     */
    static ShaderProgram link(const VertexShaderPtr& vertexShader,
            const FragmentShaderPtr& fragmentShader);

    /**
     * @brief Deletes the shader program from OpenGL.
     */
    void deleteProgram();

    /**
     * @brief Applies supplied supplementary matrices in the shader.
     */
    void applySupplementalMatrices();
};
