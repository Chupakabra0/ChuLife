#pragma once
#include <chrono>
#include <memory>

class Timer {
public:
    explicit Timer() {
        this->FixBeginAndEndTime();
    }

    Timer(const Timer&) = default;

    Timer(Timer&&) noexcept = default;

    ~Timer() = default;

    Timer& operator=(const Timer&) = default;

    Timer& operator=(Timer&&) noexcept = default;

    std::pair<std::chrono::time_point<std::chrono::system_clock>, std::chrono::time_point<std::chrono::system_clock>> FixBeginAndEndTime() {
        this->begin_ = std::chrono::system_clock::now();
        this->end_   = std::chrono::system_clock::now();

        return std::make_pair(this->begin_, this->end_);
    }

    std::chrono::time_point<std::chrono::system_clock> FixBeginTime() {
        return this->begin_ = std::chrono::system_clock::now();
    }

    std::chrono::time_point<std::chrono::system_clock> FixEndTime() {
        return this->end_ = std::chrono::system_clock::now();
    }

    template<class T>
    std::time_t GetDurationCount() const {
        return std::chrono::duration_cast<T>(this->end_ - this->begin_).count();
    }

private:
    std::chrono::time_point<std::chrono::system_clock> begin_{};
    std::chrono::time_point<std::chrono::system_clock> end_{};
};
