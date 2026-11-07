// TextureFactory.h - Contains declaration of TextureFactory class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

/**
 * @brief Indicates that texture source file could not be found.
 */
class TextureFileNotFoundException : public std::runtime_error {
  public:
    TextureFileNotFoundException(
            const std::string& message)
        : std::runtime_error(message) {}
};

enum class TextureWrapping;
enum class TextureMagnifyFiltering;
enum class TextureMinifyFiltering;
enum class TexturingUnit;

class ITexture;
class Texture2D;
class Texture2dCore;
class SkyboxTexture;
using TexturePtr = std::shared_ptr<ITexture>;
using Texture2dPtr = std::shared_ptr<Texture2dCore>;
using Texture2dWeakPtr = std::weak_ptr<Texture2dCore>;
using SkyboxTexturePtr = std::shared_ptr<SkyboxTexture>;
using SkyboxTextureWeakPtr = std::weak_ptr<SkyboxTexture>;

/**
 * @brief Provides means for creating and caching new textures.
 */
class TextureFactory {
  public:
    /**
     * @brief Creates 2D texture from supplied image file.
     * @param textureFile Path to file with an image relative to
     * resources/textures folder.
     * @param horizontalWrapping Texture wrapping option to use in horizontal
     * direction.
     * @param verticalWrapping Texture wrapping option to use in vertical
     * direction.
     * @param minifyFiltering Texture filtering option to use when minifying.
     * @param magnifyFiltering Texture filtering option to use when magnifying.
     * @param unit The texturing unit to bind to.
     * @return Pointer to 2D texture.
     * @throw TextureFileNotFoundException - Thrown when the image file cannot
     * be found or read.
     */
    static TexturePtr create2dTextureFromFile(const std::string& textureFile,
            TextureWrapping horizontalWrapping,
            TextureWrapping verticalWrapping,
            TextureMinifyFiltering minifyFiltering,
            TextureMagnifyFiltering magnifyFiltering, TexturingUnit unit);

    /**
     * @brief Creates 2D texture from supplied image file.
     * @param textureFile Path to file with an image relative to
     * resources/textures folder.
     * @param wrapping Texture wrapping option to use in both directions.
     * @param minifyFiltering Texture filtering option to use when minifying.
     * @param magnifyFiltering Texture filtering option to use when magnifying.
     * @param unit The texturing unit to bind to.
     * @return Pointer to 2D texture.
     * @throw TextureFileNotFoundException - Thrown when the image file cannot
     * be found or read.
     */
    static TexturePtr create2dTextureFromFile(const std::string& textureFile,
            TextureWrapping wrapping, TextureMinifyFiltering minifyFiltering,
            TextureMagnifyFiltering magnifyFiltering, TexturingUnit unit);

    /**
     * @brief Creates 2D texture from supplied image file with repeat behavior
     * for wrapping.
     * @param textureFile Path to file with an image relative to
     * resources/textures folder.
     * @param minifyFiltering Texture filtering option to use when minifying.
     * @param magnifyFiltering Texture filtering option to use when magnifying.
     * @param unit The texturing unit to bind to.
     * @return Pointer to 2D texture.
     * @throw TextureFileNotFoundException - Thrown when the image file cannot
     * be found or read.
     */
    static TexturePtr create2dTextureFromFile(const std::string& textureFile,
            TextureMinifyFiltering minifyFiltering,
            TextureMagnifyFiltering magnifyFiltering, TexturingUnit unit);

    /**
     * @brief Creates 2D texture from supplied image file with repeat behavior
     * for wrapping, nearest and nearest mipmap filtering for minimizing and
     * linear filtering for magnifying.
     * @param textureFile Path to file with an image relative to
     * resources/textures folder.
     * @param unit The texturing unit to bind to.
     * @return Pointer to 2D texture.
     * @throw TextureFileNotFoundException - Thrown when the image file cannot
     * be found or read.
     */
    static TexturePtr create2dTextureFromFile(
            const std::string& textureFile, TexturingUnit unit);

    /**
     * @brief Creates default skybox texture.
     * @return Pointer to skybox texture.
     * @throw TextureFileNotFoundException - Thrown when any of image files
     * cannot be found or read.
     */
    static TexturePtr createDefaultSkyBoxTexture();

    /**
     * @brief Creates skybox texture from supplied files.
     * @param filePositiveX Skybox file for +X face.
     * @param fileNegativeX Skybox file for -X face.
     * @param filePositiveY Skybox file for +Y face.
     * @param fileNegativeY Skybox file for -Y face.
     * @param filePositiveZ Skybox file for +Z face.
     * @param fileNegativeZ Skybox file for -Z face.
     * @return Pointer to skybox texture.
     * @throw TextureFileNotFoundException - Thrown when any of image files
     * cannot be found or read.
     */
    static TexturePtr createSkyBoxTextureFromFiles(
            const std::string& filePositiveX, const std::string& fileNegativeX,
            const std::string& filePositiveY, const std::string& fileNegativeY,
            const std::string& filePositiveZ, const std::string& fileNegativeZ);

  private:
    static TextureFactory s_instance;

    std::unordered_map<std::string, Texture2dWeakPtr> m_textures2dCache;
    std::unordered_map<std::string, SkyboxTextureWeakPtr> m_skyboxTexturesCache;

    /**
     * @brief TextureFactory default constructor.
     */
    TextureFactory() = default;
};
