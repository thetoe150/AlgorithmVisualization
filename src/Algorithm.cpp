#include "Algorithm.hpp"

template <typename T>
void Sort<T>::print(T* start, T* end)
{
   while(start != end)
   {
      std::cout<<*(start++)<<" ";
   }
   std::cout<<std::endl;
}

template <typename T>
void Sort<T>::Insertion(T* start, T* end)
{
   int size = end - start;
   for(int i = 1; i < size; i++)
   {
      T temp = *(start + i);
      int j = i;
      while(temp < *(start + j - 1) && j - 1 >= 0)
      {
         *(start + j) = *(start + j - 1);
         j--;
      }
      *(start + j) = temp;
   }
}

template <typename T>
void Sort<T>::Selection(T* start, T* end)
{
   int size = end - start;
   for(int i = 0; i < size - 1; i++)
   {
      for(int j = i + 1; j < size; j++)
      {
         if(*(start + j) < *(start + i))
         {
            T temp = *(start + j);
            *(start + j) = *(start + i);
            *(start + i) = temp;
         }
      }
   }
}

//TODO: write description
template <typename T>
void Sort<T>::Bubble(T* start, T* end)
{
   bool sorted = true;
   int size = end - start;
   for(int i = 0; i < size - 1; i++)
   {
      sorted = true;
      for(int j = size - 1; j > i; j--)
      {
         if(*(start + j) < *(start + j - 1))
         {
            sorted = false;
            T temp = *(start + j);
            *(start + j) = *(start + j - 1);
            *(start + j - 1) = temp;
         }
      }
      if(sorted) break;
      print(start, end);
   }
}

//TODO: write description
template <typename T>
void Sort<T>::Merge(T* start, T* end)
{

}

template class Sort<int>;
template class Sort<float>;