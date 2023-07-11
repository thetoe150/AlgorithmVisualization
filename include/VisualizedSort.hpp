#include "main.hpp"

void printResult(int*, int*);
void Insertion(int*, int*, std::function<void (HightlightType, int, int)> visualize);
void Selection(int*, int*, std::function<void (HightlightType, int, int)> visualize);
void Bubble(int* , int*, std::function<void (HightlightType, int, int)> visualize);
void Shell(int* start, int* end, const int* step_arr, int step_arr_size, std::function<void (HightlightType, int, int)> compareVisualize);
void MergeRec(int* start, int* end, int abs_pos, std::function<void (HightlightType, int, int)> compareVisualize);
void QuickRec(int* start, int* end, int abs_pos, std::function<void (HightlightType, int, int)> compareVisualize);
void Heap(int* start, int* end, std::function<void (HightlightType, int, int)> compareVisualize);
void LSD_Radix(int* start, int* end, std::function<void (HightlightType, int, int)> compareVisualize);
void MSD_Radix(int* start, int* end, std::function<void (HightlightType, int, int)> compareVisualize);
void Bogo(int* start, int* end, std::function<void (HightlightType, int, int)> compareVisualize);
