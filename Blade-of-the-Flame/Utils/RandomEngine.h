#pragma once

#include <random>

class RandomEngine
{
private:
    std::random_device randDevice_;
    std::default_random_engine engine_;

    RandomEngine() : engine_(randDevice_()) {}

    RandomEngine(const RandomEngine&) = delete;
    RandomEngine& operator =(const RandomEngine&) = delete;
    RandomEngine(RandomEngine&&) = delete;
    RandomEngine& operator =(RandomEngine&&) = delete;

public:
    static RandomEngine& GetInstance()
    {
        static RandomEngine instance;
        return instance;
    }

    std::default_random_engine& GetEngine() { return engine_; }
};