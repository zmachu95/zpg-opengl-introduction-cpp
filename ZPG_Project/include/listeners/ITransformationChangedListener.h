// ITransformationChangedListener.h - Contains declaration of
// ITransformationChangedListener interface.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

/**
 * @brief Interface for transformation change listeners.
 */
class ITransformationChangedListener {
  public:
    virtual ~ITransformationChangedListener() = default;

    /**
     * @brief Handles the signal that atleast one underlying transformation
     * matrix has changed.
     */
    virtual void handleTransformationChange() = 0;
};
