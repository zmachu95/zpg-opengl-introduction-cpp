// ImageData.cpp - Contains definition of ImageData class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#include "ImageData.h"
#include <iostream>
#include <stb_image.h>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std::string_literals;

ImageData::ImageData(
        int height, int width, int channelsCount, unsigned char* data,
        const std::string& textureFileName)
    : m_height{height}, m_width{width}, m_channelsCount{channelsCount},
      m_data{data}, m_textureFileName{textureFileName} {
    std::cout << "Loaded texture data from file `" << textureFileName << "`.\n";
}

ImageData::ImageData(
        ImageData&& other) noexcept
    : m_height{std::exchange(other.m_height, 0)},
      m_width{std::exchange(other.m_width, 0)},
      m_channelsCount{std::exchange(other.m_channelsCount, 0)},
      m_data{std::exchange(other.m_data, nullptr)},
      m_textureFileName{std::move(other.m_textureFileName)} {}

ImageData::~ImageData() { this->releaseData(); }

ImageData& ImageData::operator=(
        ImageData&& other) noexcept {
    if (this != &other) {
        this->releaseData();

        this->m_height = std::exchange(other.m_height, 0);
        this->m_width = std::exchange(other.m_width, 0);
        this->m_channelsCount = std::exchange(other.m_channelsCount, 0);
        this->m_data = std::exchange(other.m_data, nullptr);
        this->m_textureFileName = std::move(other.m_textureFileName);
    }

    return *this;
}

ImageData ImageData::fromFile(
        const std::string& textureFileFullPath, bool invertVerticalAxis) {
    int width, height, channelsCount;

    stbi_set_flip_vertically_on_load(invertVerticalAxis);

    unsigned char* data = stbi_load(
            textureFileFullPath.c_str(), &width, &height, &channelsCount, 0);
    if (!data) {
        throw std::invalid_argument(
                "Could not find or load data from image file `"s
                + textureFileFullPath + "`!");
    }

    return ImageData{height, width, channelsCount, data, textureFileFullPath};
}

int ImageData::getHeight() const { return this->m_height; }

int ImageData::getWidth() const { return this->m_width; }

int ImageData::getChannelsCount() const { return this->m_channelsCount; }

unsigned char* ImageData::getData() const { return this->m_data; }

void ImageData::releaseData() {
    if (this->m_data) {
        stbi_image_free((void*)this->m_data);
        std::cout << "Released in-memory texture data from file `"
                  << this->m_textureFileName << "`.\n";
    }
}
