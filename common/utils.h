#pragma once

#define WORLD_MIN (uint16_t)0
#define WORLD_MAX (uint16_t)1000

template <typename T>
T clamp(const T& n, const T& lower, const T& upper) {
    return std::max(lower, std::min(n, upper));
}
