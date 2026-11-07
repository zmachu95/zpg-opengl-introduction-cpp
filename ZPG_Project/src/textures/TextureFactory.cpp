#include <textures/TextureFactory.h>

#include "SkyBoxTexture.h"
#include "Texture2D.h"
#include "Texture2dCore.h"
#include <array>
#include <memory>
#include <stdexcept>
#include <string>
#include <textures/ITexture.h>

/**
 * @brief Path to texture files folder.
 */
const std::string TEXTURES_FOLDER = "resources\\textures\\";

/*
 * @brief Path to folder with default skybox files.
 */
const std::string DEFAULT_SKYBOX_FOLDER = "skybox\\";

/**
 * @brief Prepares array of skybox files in correct order.
 * @param filePositiveX Skybox file for +X face.
 * @param fileNegativeX Skybox file for -X face.
 * @param filePositiveY Skybox file for +Y face.
 * @param fileNegativeY Skybox file for -Y face.
 * @param filePositiveZ Skybox file for +Z face.
 * @param fileNegativeZ Skybox file for -Z face.
 * @return Array with correctly ordered skybox files.
 */
static std::array<std::string, SKYBOX_TEXTURES_COUNT> createSkyboxFilesArray(
        const std::string& filePositiveX, const std::string& fileNegativeX,
        const std::string& filePositiveY, const std::string& fileNegativeY,
        const std::string& filePositiveZ, const std::string& fileNegativeZ) {
    return std::array<std::string, SKYBOX_TEXTURES_COUNT>{
            TEXTURES_FOLDER + filePositiveX, TEXTURES_FOLDER + fileNegativeX,
            TEXTURES_FOLDER + filePositiveY, TEXTURES_FOLDER + fileNegativeY,
            TEXTURES_FOLDER + filePositiveZ, TEXTURES_FOLDER + fileNegativeZ};
}

/**
 * @brief Merges filenames into a single string.
 * @param filenames Filenames to merge.
 * @return Single std::string object.
 */
static std::string mergeFilenames(
        const std::array<std::string, SKYBOX_TEXTURES_COUNT>& filenames) {
    return filenames[0] + filenames[1] + filenames[2] + filenames[3]
           + filenames[4] + filenames[5];
}

TextureFactory TextureFactory::s_instance{};

TexturePtr TextureFactory::create2dTextureFromFile(
        const std::string& textureFile, TextureWrapping horizontalWrapping,
        TextureWrapping verticalWrapping,
        TextureMinifyFiltering minifyFiltering,
        TextureMagnifyFiltering magnifyFiltering, TexturingUnit unit) {
    if (Texture2dPtr cachedTexture =
                    s_instance.m_textures2dCache[textureFile].lock()) {
        return std::make_shared<Texture2D>(cachedTexture, unit);
    }

    Texture2dPtr newTexture;
    try {
        newTexture = std::make_shared<Texture2dCore>(Texture2dCore::fromFile(
                TEXTURES_FOLDER + textureFile, horizontalWrapping,
                verticalWrapping, minifyFiltering, magnifyFiltering));
    } catch (const std::invalid_argument& ex) {
        throw TextureFileNotFoundException(ex.what());
    }

    s_instance.m_textures2dCache[textureFile] =
            std::weak_ptr<Texture2dCore>(newTexture);
    return std::make_shared<Texture2D>(newTexture, unit);
}

TexturePtr TextureFactory::create2dTextureFromFile(
        const std::string& textureFile, TextureWrapping wrapping,
        TextureMinifyFiltering minifyFiltering,
        TextureMagnifyFiltering magnifyFiltering, TexturingUnit unit) {
    return create2dTextureFromFile(textureFile, wrapping, wrapping,
            minifyFiltering, magnifyFiltering, unit);
}

TexturePtr TextureFactory::create2dTextureFromFile(
        const std::string& textureFile, TextureMinifyFiltering minifyFiltering,
        TextureMagnifyFiltering magnifyFiltering, TexturingUnit unit) {
    return create2dTextureFromFile(textureFile, TextureWrapping::REPEAT,
            minifyFiltering, magnifyFiltering, unit);
}

TexturePtr TextureFactory::create2dTextureFromFile(
        const std::string& textureFile, TexturingUnit unit) {
    return create2dTextureFromFile(textureFile,
            TextureMinifyFiltering::NEAREST_WITH_MIPMAP_NEAREST,
            TextureMagnifyFiltering::LINEAR, unit);
}

TexturePtr TextureFactory::createDefaultSkyBoxTexture() {
    return TextureFactory::createSkyBoxTextureFromFiles(
            DEFAULT_SKYBOX_FOLDER + "posx.jpg",
            DEFAULT_SKYBOX_FOLDER + "negx.jpg",
            DEFAULT_SKYBOX_FOLDER + "posy.jpg",
            DEFAULT_SKYBOX_FOLDER + "negy.jpg",
            DEFAULT_SKYBOX_FOLDER + "posz.jpg",
            DEFAULT_SKYBOX_FOLDER + "negz.jpg");
}

TexturePtr TextureFactory::createSkyBoxTextureFromFiles(
        const std::string& filePositiveX, const std::string& fileNegativeX,
        const std::string& filePositiveY, const std::string& fileNegativeY,
        const std::string& filePositiveZ, const std::string& fileNegativeZ) {
    std::array<std ::string, SKYBOX_TEXTURES_COUNT> textureFiles =
            createSkyboxFilesArray(filePositiveX, fileNegativeX, filePositiveY,
                    fileNegativeY, filePositiveZ, fileNegativeZ);
    std::string key = mergeFilenames(textureFiles);
    if (SkyboxTexturePtr cachedTexture =
                    s_instance.m_skyboxTexturesCache[key].lock()) {
        return cachedTexture;
    }

    SkyboxTexturePtr newTexture;
    try {
        newTexture = std::make_shared<SkyboxTexture>(
                SkyboxTexture::fromFiles(textureFiles));
    } catch (const std::invalid_argument& ex) {
        throw TextureFileNotFoundException(ex.what());
    }

    s_instance.m_skyboxTexturesCache[key] =
            std::weak_ptr<SkyboxTexture>(newTexture);
    return newTexture;
}
