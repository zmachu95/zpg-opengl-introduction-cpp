// ImageData.h - Contains declaration of ImageData class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#pragma once

#include <string>

/**
 * @brief Wraps image data loaded into memory.
 */
class ImageData {
  public:
    /**
     * @brief ImageData copy constructor. Deliberately deleted to prevent
     * application from accidentally releasing the image data.
     */
    ImageData(const ImageData& other) = delete;

    /**
     * @brief ImageData move constructor.
     * @param other Object to be moved.
     */
    ImageData(ImageData&& other) noexcept;

    ~ImageData();

    /*
     *
     */

    /**
     * @brief ImageData copy-by-reference operator. Deliberately deleted to
     * prevent application from accidentally releasing the image data.
     */
    ImageData& operator=(const ImageData& other) = delete;

    /**
     * @brief ImageData move operator.
     * @param other Object to be moved.
     * @return Moved ImageData object.
     */
    ImageData& operator=(ImageData&& other) noexcept;

    /*
     *
     */

    /**
     * @brief Creates new ImageData object by reading image contents from given
     * file.
     * @param textureFileFullPath Full path to file with an image.
     * @param invertVerticalAxis Supply true to flip image vertically (needed
     * for 2D textures).
     * @return New ImageData object with encapsulated file data.
     * @throw std::invalid_argument - Thrown when the image file cannot be found
     * or read.
     */
    static ImageData fromFile(
            const std::string& textureFileFullPath, bool invertVerticalAxis);

    /*
     *
     */

    /**
     * @brief Gets image height in [px].
     * @return Image height in [px].
     */
    int getHeight() const;

    /**
     * @brief Gets image width in [px].
     * @return Image width in [px].
     */
    int getWidth() const;

    /**
     * @brief Gets number of channels per pixel.
     * @return Number of channels per pixel.
     */
    int getChannelsCount() const;

    /**
     * @brief Gets the raw pixel data.
     * @return The raw pixel data.
     */
    unsigned char* getData() const;

  private:
    std::string m_textureFileName;
    unsigned char* m_data;
    int m_height;
    int m_width;
    int m_channelsCount;

    /**
     * @brief ImageData default constructor.
     * @param height Height of image in [px].
     * @param width Width of image in [px].
     * @param channelsCount Number of channels per pixel.
     * @param data Raw pixel data.
     * @param textureFileName Name of source file.
     */
    ImageData(int height, int width, int channelsCount, unsigned char* data,
            const std::string& textureFileName);

    /*
     *
     */

    /**
     * @brief Releases the raw image data from memory.
     */
    void releaseData();
};
