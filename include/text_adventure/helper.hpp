#ifndef HELPER_H
#define HELPER_H
#pragma once

#include "raylib-cpp.hpp"
#include "game_constants.hpp"
#include "json.hpp"
using json = nlohmann::json;

#include <functional>

raylib::Color LoadColorFromJSON(const json &colorData);
raylib::Color GetColorFromJSON(const json &colorData,
                               const raylib::Color &fallback = raylib::Color::Black());

template <typename T>
bool Compare(const T &a, const T &b, const std::string &op);

// Specialization for bool (only == and != make sense)
template <>
bool Compare<bool>(const bool &a, const bool &b, const std::string &op);

template <typename T>
inline bool Compare(const T &a, const T &b, const std::string &op)
{
    {
        using namespace GameConsts::condition;

        static const std::unordered_map<std::string, std::function<bool(T, T)>> comparators = {
            {comp::EQUAL, [](T a, T b)
             { return a == b; }},
            {comp::NOT_EQUAL, [](T a, T b)
             { return a != b; }},
            {comp::GREATER_THAN, [](T a, T b)
             { return a > b; }},
            {comp::LESS_THAN, [](T a, T b)
             { return a < b; }},
            {comp::GREATER_EQUAL, [](T a, T b)
             { return a >= b; }},
            {comp::LESS_EQUAL, [](T a, T b)
             { return a <= b; }}};

        auto it = comparators.find(op);
        if (it != comparators.end())
        {
            return it->second(a, b);
        }
        return a == b; // Default
    }
}

template <>
inline bool Compare(const bool &a, const bool &b, const std::string &op)
{
    {
        using namespace GameConsts::condition;
        if (op == comp::EQUAL)
            return a == b;
        if (op == comp::NOT_EQUAL)
            return a != b;
        return a == b; // Default
    }
}

#endif