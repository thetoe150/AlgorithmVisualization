#pragma once

#include "main.hpp"

enum class SortType
{
    Insertion,
    Selection,
    Bubble,
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

void visualizeSorting(SortType type);
void display();
void printResult(int*, int*);
void Insertion(int*, int*, std::function<void (HightlightType, int, int)> visualize);
void Selection(int*, int*, std::function<void (HightlightType, int, int)> visualize);
void Bubble(int* , int*, std::function<void (HightlightType, int, int)> visualize);
void MergeRec(int* start, int* end, int abs_pos, std::function<void (HightlightType, int, int)> compareVisualize);
void Merge(int* start, int* mid, int* end, int abs_pos, std::function<void (HightlightType, int, int)> compareVisualize);
void Quick(int* start, int* end, std::function<void (int, int)> compareVisualize);
void Heap(int* start, int* end, std::function<void (int, int)> compareVisualize);