// TransformationChangePublisher.h - Contains declaration of
// TransformationChangePublisher class.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <list>
#include <memory>

class ITransformationChangedListener;

/**
 * @brief Pointer to ITransformationChangedListener object.
 */
using TransformationChangeListenerPtr =
        std::weak_ptr<ITransformationChangedListener>;

/**
 * @brief Manages listeners for transformation change event.
 */
class TransformationChangePublisher {
  public:
    /**
     * @brief Registers listener for transformation change event.
     * @param listener Listener to register.
     */
    void registerTransformationChangeListener(
            const TransformationChangeListenerPtr& listener);

    /**
     * @brief Notifies all listeners that the translation matrix changed.
     */
    void notifyListeners();

  private:
    std::list<TransformationChangeListenerPtr> m_listeners;
};
