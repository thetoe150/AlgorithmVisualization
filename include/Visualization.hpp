#pragma once

#include "main.hpp"
#include "VisualizedSort.hpp"

static inline sf::Font ConfigFont();
static inline void SetSortNameText(sf::Text& sortType, sf::Font font, SortType type);
static inline void randomizePillarVal(int* pillar_value);
void visualizeSorting(SortType type);