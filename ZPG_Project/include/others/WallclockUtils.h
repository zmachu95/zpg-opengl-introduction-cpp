// WallclockUtils.h - Contains declaration of functions regarding wall clock
// scenes.
//
// Coded by Zdenek Machu (MAC0690), October 2026

#pragma once

#include <glm/ext/matrix_float4x4.hpp>

/**
 * @brief Gets the current system time.
 * @return time_t value with system time.
 */
time_t getCurrentTime();

/**
 * @brief Converts time_t value to seconds.
 * @param value time_t value.
 * @return Seconds.
 */
int convertTimeTtoSeconds(time_t value);

/**
 * @brief Converts time_t value to minutes.
 * @param value time_t value.
 * @return Minutes.
 */
int convertTimeTtoMinutes(time_t value);

/**
 * @brief Converts time_t value to hours.
 * @param value time_t value.
 * @return Hours.
 */
int convertTimeTtoHours(time_t value);

/**
 * @brief Gets rotation matrix for hours pin based on supplied values.
 * @param hours Current hours.
 * @param minutes Current minutes.
 * @param seconds Current seconds.
 * @return Rotation matrix.
 */
glm::mat4 getHoursPinRotationMatrix(int hours, int minutes, int seconds);

/**
 * @brief Gets rotation matrix for minutes pin based on supplied values.
 * @param minutes Current minutes.
 * @param seconds Current seconds.
 * @return Rotation matrix.
 */
glm::mat4 getMinutesPinRotationMatrix(int minutes, int seconds);

/**
 * @brief Gets rotation matrix for seconds pin based on supplied values.
 * @param seconds Current seconds.
 * @return Rotation matrix.
 */
glm::mat4 getSecondsPinRotationMatrix(int seconds);
