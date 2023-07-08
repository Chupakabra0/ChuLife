#pragma once
#include <limits>
#include <numbers>
#include <glm/glm.hpp>

inline const float pi = static_cast<float>(std::numbers::pi);

inline bool isFloatEqual(float x, float y, float epsilon = std::numeric_limits<float>::epsilon()) {
    return std::abs(x - y) <= epsilon;
}

inline bool isFloatNotEqual(float x, float y, float epsilon = std::numeric_limits<float>::epsilon()) {
    return !isFloatEqual(x, y, epsilon);
}

inline bool isFloatGreater(float x, float y, float epsilon = std::numeric_limits<float>::epsilon()) {
    return x - y > epsilon;
}

inline bool isFloatLessEqual(float x, float y, float epsilon = std::numeric_limits<float>::epsilon()) {
    return !isFloatGreater(x, y, epsilon);
}

inline bool isFloatLess(float x, float y, float epsilon = std::numeric_limits<float>::epsilon()) {
    return isFloatGreater(y, x, epsilon);
}

inline bool isFloatGreaterEqual(float x, float y, float epsilon = std::numeric_limits<float>::epsilon()) {
    return !isFloatLess(x, y, epsilon);
}

inline bool isVec4Equal(const glm::vec4& first, const glm::vec4& second,
    float epsilon = std::numeric_limits<float>::epsilon()) {
    return isFloatEqual(first.x, second.x, epsilon) &&
        isFloatEqual(first.y, second.y, epsilon) &&
        isFloatEqual(first.z, second.z, epsilon) &&
        isFloatEqual(first.w, second.w, epsilon);
}

inline bool isVec4NotEqual(const glm::vec4& first, const glm::vec4& second,
    float epsilon = std::numeric_limits<float>::epsilon()) {
    return !isVec4Equal(first, second, epsilon);
}

inline bool isVec4Less(const glm::vec4& first, const glm::vec4& second,
    float epsilon = std::numeric_limits<float>::epsilon()) {
    if (isFloatLess(first.x, second.x, epsilon)) {
        return true;
    }
    else if (isFloatGreater(first.x, second.x, epsilon)) {
        return false;
    }

    if (isFloatLess(first.y, second.y, epsilon)) {
        return true;
    }
    else if (isFloatGreater(first.y, second.y, epsilon)) {
        return false;
    }

    if (isFloatLess(first.z, second.z, epsilon)) {
        return true;
    }
    else if (isFloatGreater(first.z, second.z, epsilon)) {
        return false;
    }

    if (isFloatLess(first.w, second.w, epsilon)) {
        return true;
    }
    else if (isFloatGreater(first.w, second.w, epsilon)) {
        return false;
    }

    return false;
}

inline bool isVec4GreaterEqual(const glm::vec4& first, const glm::vec4& second,
    float epsilon = std::numeric_limits<float>::epsilon()) {
    return !isVec4Less(first, second, epsilon);
}

inline bool isVec4Greater(const glm::vec4& first, const glm::vec4& second,
    float epsilon = std::numeric_limits<float>::epsilon()) {
    return isVec4Less(second, first, epsilon);
}

inline bool isVec4LessEqual(const glm::vec4& first, const glm::vec4& second,
    float epsilon = std::numeric_limits<float>::epsilon()) {
    return !isVec4Greater(first, second, epsilon);
}
