#pragma once

#include "main.hpp"
void visualizeSorting();
void display();
void Insertion(int*, int*, std::function<void (int*)> visualize);
void Selection(int*, int*, std::function<void (int*)> visualize);
void Bubble(int* , int*, std::function<void (int*)> visualize);