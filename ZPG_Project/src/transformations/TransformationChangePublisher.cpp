// TransformationChangePublisher.cpp - Contains definition of
// TransformationChangePublisher class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <listeners/ITransformationChangedListener.h>
#include <transformations/TransformationChangePublisher.h>

#include <list>
#include <memory>

void TransformationChangePublisher::registerTransformationChangeListener(
        const TransformationChangeListenerPtr& listener) {
    this->m_listeners.push_back(listener);

    /* immediately notify new listener to receive the transformation matrix */
    listener.lock()->handleTransformationChange();
}

void TransformationChangePublisher::notifyListeners() {
    auto listenerIt = this->m_listeners.begin();
    while (listenerIt != this->m_listeners.end()) {
        if (auto listener = listenerIt->lock()) {
            listener->handleTransformationChange();
            listenerIt++;
        } else {
            listenerIt = this->m_listeners.erase(listenerIt);
        }
    }
}
