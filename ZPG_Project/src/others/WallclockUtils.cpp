// WallclockUtils.cpp - Contains definition of functions regarding wall clock
// scenes.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#include <others/WallclockUtils.h>

#include <chrono>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

time_t getCurrentTime() {
    return std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());
}

int convertTimeTtoSeconds(
        time_t value) {
    return value % 60;
}

int convertTimeTtoMinutes(
        time_t value) {
    return (value / 60) % 60;
}

int convertTimeTtoHours(
        time_t value) {
    return (value / 3600) % 60 + 2; // +2 due to UTC timezone and summer time
}

glm::mat4 getHoursPinRotationMatrix(
        int hours, int minutes, int seconds) {
    float angle_deg = (float)360 / 12 * hours + (float)360 / (12 * 60) * minutes
                      + (float)360 / (12 * 60 * 60) * seconds;
    return glm::rotate(glm::mat4{1.0f}, glm::radians(angle_deg),
            glm::vec3{0.0f, 0.0f, -1.0f});
}

glm::mat4 getMinutesPinRotationMatrix(
        int minutes, int seconds) {
    float angle_deg =
            (float)360 / 60 * minutes + (float)360 / (60 * 60) * seconds;
    return glm::rotate(glm::mat4{1.0f}, glm::radians(angle_deg),
            glm::vec3{0.0f, 0.0f, -1.0f});
}
glm::mat4 getSecondsPinRotationMatrix(
        int seconds) {
    float angle_deg = (float)360 / 60 * seconds;
    return glm::rotate(glm::mat4{1.0f}, glm::radians(angle_deg),
            glm::vec3{0.0f, 0.0f, -1.0f});
}
