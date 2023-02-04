#pragma once

#include <iostream>
#include <algorithm>
#include <random>
#include <functional>
#include <string>
#include <array>
#include <unordered_map>

#include "SFML/Graphics.hpp"
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
    Heap
};

enum class HightlightType
{
    Compare,
    Write,
    Done
};