#pragma once

#include "main.hpp"
#include "VisualizedSort.hpp"

const float PILLAR_WIDTH = 10.f; 
const float PILLAR_HEIGHT = 6.f;
const int PILLAR_SIZE = 100;
const int FRAME_RATE = 40;
const int SOUND_POOL_SIZE = 20;
const float LOWEST_PITCH = 0.25;
const float PITCH_COEFFICIENT = 0.01;
const static int SHELL_STEP_ARRAY[] = {7, 5, 3, 2, 1};

static inline sf::Font ConfigFont();
static inline void SetSortNameText(sf::Text& sorttype, SortType type);
static inline void RandomizePillarVal(int* pillars_value);
static inline void ConfigSound(sf::Sound soundPool[], sf::SoundBuffer& buffer, const std::string& src);
static inline void PlaySoundFromPool(sf::Sound soundPool[], float pitch);

void VisualizeSorting(SortType type);
