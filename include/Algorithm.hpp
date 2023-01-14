#pragma once
#include <iostream>

template <typename T>
class Sort
{
public:
    static void print(T* start, T* end);
    static void Insertion(T* start, T* end);
    static void Selection(T* start, T* end);
    static void Bubble(T* start, T* end);
    static void Shell(T* start, T* end);
    static void MergeRec(T* start, T* end);
    static void QuickRec(T* start, T* end);
    static void Heap(T* start, T* end);

    //helper function
    static void Merge(T* start, T* mid, T* end);
    static void MergeSort(T* start, T* end);
};