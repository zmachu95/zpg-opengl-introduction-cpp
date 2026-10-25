// CameraUpdatePublisher.cpp - Contains definition of CameraUpdatePublisher
// class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include "CameraUpdatePublisher.h"
#include <cameras/ICameraUpdateListener.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <list>
#include <memory>
#include <utility>

CameraUpdatePublisher::CameraUpdatePublisher()
    : m_lastListenerId{0}, m_listeners{} {}

int CameraUpdatePublisher::registerCameraUpdateListener(
        const CameraUpdateListenerPtr& listener,
        const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix,
        const glm::vec3& cameraPosition) {
    this->m_lastListenerId += 1;

    this->m_listeners.push_back(std::pair<int, CameraUpdateListenerPtr>(
            this->m_lastListenerId, CameraUpdateListenerPtr{listener}));

    /* make sure that the just registered listener uses the current camera
     * matrices */
    listener.lock()->handleCameraUpdate(
            projectionMatrix, viewMatrix, cameraPosition);
    return this->m_lastListenerId;
}

bool CameraUpdatePublisher::unregisterCameraUpdateListener(
        int listenerId) {
    for (auto listenerIt = this->m_listeners.begin();
            listenerIt != this->m_listeners.end(); listenerIt++) {
        if (listenerIt->first == listenerId) {
            this->m_listeners.erase(listenerIt);
            return true;
        }
    }

    return false;
}

void CameraUpdatePublisher::notifyListeners(
        const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix,
        const glm::vec3& cameraPosition) {
    auto listenerIt = this->m_listeners.begin();
    while (listenerIt != this->m_listeners.end()) {
        if (auto listener = listenerIt->second.lock()) {
            listener->handleCameraUpdate(
                    projectionMatrix, viewMatrix, cameraPosition);
            listenerIt++;
        } else {
            listenerIt = this->m_listeners.erase(listenerIt);
        }
    }
}
