// CameraUpdatePublisher.h - Contains declaration of CameraUpdatePublisher
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <list>
#include <memory>
#include <utility>

class ICameraUpdateListener;

/**
 * @brief Pointer to ICameraUpdateListener instance.
 */
using CameraUpdateListenerPtr = std::weak_ptr<ICameraUpdateListener>;

/**
 * @brief Manages listeners for camera update event.
 */
class CameraUpdatePublisher {
  public:
    /**
     * @brief Standard CameraUpdatePublisher constructor.
     */
    CameraUpdatePublisher();

    /*
     *
     */

    /**
     * @brief Registers listener for camera update event and immediately gives
     * listener new camera matrices.
     * @param listener Listener to register.
     * @param projectionMatrix Projection matrix to send.
     * @param viewMatrix View matrix to send.
     * @return ID number which can be used to unregister the listener.
     */
    int registerCameraUpdateListener(const CameraUpdateListenerPtr& listener,
            const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);

    /**
     * @brief Unregisters listener with supplied ID.
     * @param listenerId The ID of listener to unregister.
     * @return true if the listener was found and unregistered, otherwise
     * returns false.
     */
    bool unregisterCameraUpdateListener(int listenerId);

    /**
     * @brief Notifies all camera update listeners with new camera matrices.
     * @param projectionMatrix Projection matrix to send.
     * @param viewMatrix View matrix to send.
     */
    void notifyListeners(
            const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);

  private:
    int m_lastListenerId;
    std::list<std::pair<int, CameraUpdateListenerPtr>> m_listeners;
};
