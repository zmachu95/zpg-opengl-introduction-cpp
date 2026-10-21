// ICameraUpdateListener.h - Contains declaration of ICameraUpdateListener
// interface.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <glm/fwd.hpp>

/**
 * @brief Interface for camera update listeners.
 */
class ICameraUpdateListener {
  public:
    virtual ~ICameraUpdateListener() = default;

    /**
     * @brief Handles the camera update.
     * @param projectionMatrix The new camera projection matrix.
     * @param viewMatrix The new camera view matrix.
     * @param cameraPosition The new camera position.
     */
    virtual void handleCameraUpdate(const glm::mat4& projectionMatrix,
            const glm::mat4& viewMatrix, const glm::vec3& cameraPosition) = 0;
};
