#pragma once

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
#include <string>
#include <array>
#include <unordered_map>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Algorithm.hpp"
#include "SFML/OpenGL.hpp"

enum class SortType
{
    Insertion,
    Selection,
    Bubble,
    Shell,
    Merge,
    Quick,
    Heap,
    LSD_Radix,
    MSD_Radix,
    Bogo
};

enum class HightlightType
{
    Compare,
    Write,
    Done
};