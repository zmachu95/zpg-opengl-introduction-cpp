// ApplicationFactory.cpp - Contains definition of ApplicationFactory class.
//
// Coded by Zdenek Machu (MAC0690), November 2026

#include "Application.h"
#include <application/ApplicationFactory.h>
#include <memory>

ApplicationPtr ApplicationFactory::createApplication(
        int windowWidth, int windowHeight) {
    return std::make_unique<Application>(windowWidth, windowHeight);
}
