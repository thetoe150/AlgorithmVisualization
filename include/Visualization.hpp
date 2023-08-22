#pragma once

#include "main.hpp"
#include "VisualizedSort.hpp"

constexpr float WINDOW_WIDTH = 1500;
constexpr float WINDOW_HEIGHT = 1000;
constexpr float OFFSET_TOP = 250;
constexpr float OFFSET_BOT = 30;
constexpr float OFFSET_SIDE = 50;
constexpr float OUTLINE_WIDTH = 0.0;
const int FRAME_RATE = 60;
const int SOUND_POOL_SIZE = 20;
constexpr float LOWEST_PITCH = 0.25f;
constexpr float HIGHTEST_PITCH = 1.75f;
const static int SHELL_STEP_ARRAY[] = {7, 5, 3, 2, 1};

static inline sf::Font ConfigFont();
static inline void SetSortNameText(sf::Text& sorttype, SortType type);
static inline void RandomizePillarVal(int* pillars_value, int n);
static inline void ConfigSound(sf::Sound soundPool[], sf::SoundBuffer& buffer, const std::string& src);
static inline void PlaySoundFromPool(sf::Sound soundPool[], float pitch);

void VisualizeSorting(SortType type, int n);
