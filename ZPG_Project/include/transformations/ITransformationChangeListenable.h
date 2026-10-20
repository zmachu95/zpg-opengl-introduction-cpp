// ITransformationChangeListenable.h - Contains declaration of
// ITransformationChangeListenable interface.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <memory>

class ITransformationChangedListener;

/**
 * @brief Enables the implementing class to register transformation change
 * listeners.
 */
class ITransformationChangeListenable {
  public:
    virtual ~ITransformationChangeListenable() = default;

    /**
     * @brief Registers listener for transformation change event.
     * @param listener Listener to register.
     */
    virtual void registerTransformationChangeListener(
            const std::weak_ptr<ITransformationChangedListener>& listener) = 0;
};
