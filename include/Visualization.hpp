#pragma once

#include "main.hpp"
#include "VisualizedSort.hpp"
#include "globalConstant.hpp"

static inline sf::Font ConfigFont();
static inline void SetSortNameText(sf::Text& sorttype, SortType type);
static inline void RandomizePillarVal(int* pillars_value, int n);
static inline void ConfigSound(sf::Sound soundPool[], sf::SoundBuffer& buffer, const std::string& src);
static inline void PlaySoundFromPool(sf::Sound soundPool[], float pitch);

void VisualizeSorting(SortType type, int n);
