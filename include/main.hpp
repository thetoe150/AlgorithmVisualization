#pragma once

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
#include <memory.h>
#include <string>
#include <array>
#include <unordered_map>
#include <cassert>

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
