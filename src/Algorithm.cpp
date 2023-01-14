#include "Algorithm.hpp"

template <typename T>
void Sort<T>::print(T* start, T* end)
{
   std::cout<<std::endl<<"Print the array"<<std::endl;
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
      T min = *(start + i);
      int min_idx = i;
      for(int j = i + 1; j < size; j++)
      {
         if(*(start + j) < min)
         {
            min = *(start + j);
            min_idx = j;
         }
      }
      T temp = *(start + i);
      *(start + i) = *(start + min_idx);
      *(start + min_idx) = temp;
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
void Sort<T>::Merge(T* start, T* mid, T* end)
{
   int FHsize = mid - start; //std::cout<<"FHsize: "<<FHsize<<std::endl;
   int SHsize = end - mid; //std::cout<<"SHsize: "<<SHsize<<std::endl;

   T FHarray[FHsize];
   T SHarray[SHsize];

   //std::cout<<"First Half array"<<std::endl;
   for(int i = 0; i < FHsize; i++)
   {
      FHarray[i] = *(start + i);
      //std::cout<<FHarray[i]<<std::endl;
   }

   //std::cout<<"Second Half array"<<std::endl;
   for(int i = 0; i < SHsize; i++)
   {
      SHarray[i] = *(mid + i);
      //std::cout<<SHarray[i]<<std::endl;
   }
   T* mergeWalker = start;
   int FHwalker = 0;
   int SHwalker = 0;
   while(FHwalker < FHsize && SHwalker < SHsize)
   {
      if(FHarray[FHwalker] <= SHarray[SHwalker])
      {
         *mergeWalker = FHarray[FHwalker++];
      }
      else
      {
         *mergeWalker = SHarray[SHwalker++];
      }
      mergeWalker++;
   }

   while(FHwalker < FHsize) 
   {
      *mergeWalker = FHarray[FHwalker++];
      mergeWalker++;
   }
   while(SHwalker < SHsize)
   {
      *mergeWalker = SHarray[SHwalker++];
      mergeWalker++;
   }
}

template <typename T>
void Sort<T>::MergeRec(T* start, T* end)
{
   int size = end - start;
   if(size == 1)
      return;
   
   T* mid = start + (size / 2); //std::cout<<"end: "<<*end<<std::endl;
   MergeRec(start, mid);
   MergeRec(mid, end);
   Merge(start, mid, end);
}

template class Sort<int>;
template class Sort<float>;