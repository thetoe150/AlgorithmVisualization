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

template <typename T>
void Sort<T>::QuickRec(T* start, T* end)
{
   int size = end - start;
   if(size <= 1)
      return;
   
   T* mid = start + (size / 2); 
   T* pivot = Quick(start, mid, end);std::cout<<"pivot: "<<pivot - start<<std::endl;
   print(start, end);
   QuickRec(start, pivot);
   QuickRec(pivot + 1, end);
}

template <typename T>
T* Sort<T>::Quick(T* start, T* pivot, T* end)
{
   int size = end - start;
   int Lwalker = 0;
   int Rwalker = size - 1;
   print(start, end);

   while(Rwalker >= Lwalker && Rwalker > 0)
   {
      //std::cout << *pivot<<std::endl;
      //std::cout << "Rwalker: "<<Rwalker<<", Lwalker: "<<Lwalker<<std::endl;
      //std::cout << "Rwalker value: "<<*(start + Lwalker)<<", Lwalker value: "<<*(start + Rwalker)<<std::endl;
      if(*(start + Lwalker) > *pivot && *(start + Rwalker) < *pivot)
      {
         int temp = *(start + Lwalker);
         *(start + Lwalker) = *(start + Rwalker);
         *(start + Rwalker) = temp;

         Lwalker++;
         Rwalker--;
      }
      else if(*(start + Lwalker) > *pivot && *(start + Rwalker) >= *pivot)
      {
         Rwalker--;
      }
      else if(*(start + Lwalker) <= *pivot && *(start + Rwalker) < *pivot)
      {
         Lwalker++;
      }
      else 
      {
         Rwalker--;
         Lwalker++;
      }
   }

   if(Lwalker - (pivot - start) == 1 
      && (pivot - start) - Rwalker == 1)
      return pivot;
   
   if(Lwalker > pivot - start)
   {
      int temp = *(start + Rwalker);   
      *(start + Rwalker) = *pivot;
      *pivot = temp;
      return start + Rwalker;
   }
   else
   {
      int temp = *(start + Lwalker);   
      *(start + Lwalker) = *pivot;
      *pivot = temp;
      return start + Lwalker;
   }
}

template <typename T>
void Sort<T>::Heap(T* start, T* end)
{
   int size = end - start;
   for(int i = size - 2; i >= 0; i--)
   {
      reheapUp(start, end, i); //print(start, end);
   }

   for(int i = 0; i < size - 1; i++)
   {
      T temp = *(end - 1);
      *(end - 1) = *(start + i);
      *(start + i) = temp;
      reheapDown(start, end, i);
   }
}

template <typename T>
void Sort<T>::reheapUp(T* start, T* end, int reheapIdx)
{
   int lastIdx = end - start - 1;
   int reheapToLast = lastIdx - reheapIdx;
   T* lastEle = end - 1;
   T* reheapEle = lastEle - reheapToLast;

   while(reheapToLast > 0)
   {
      T* parentEle = lastEle - (reheapToLast - 1)/2; //std::cout<<"parent: "<<*parentEle<<"  reheap: "<<*reheapEle<<std::endl;
      if(*reheapEle < *parentEle)
      {
         T temp = *reheapEle;
         *reheapEle = *parentEle;
         *parentEle = temp;
         reheapEle = parentEle;
         reheapToLast = (reheapToLast - 1)/2;
      }
      else break;
   }
}

template <typename T>
void Sort<T>::reheapDown(T* start, T* end, int ignoreEle)
{
   int lastIdx = end - start - 1;  //consider last Idx of the array as root and as index 0
   int finalHeapEleToLast = lastIdx - ignoreEle - 1;

   int parentIdxToLast = 0;
   int leftIdxToLast = parentIdxToLast * 2 + 1;
   int rightIdxToLast = parentIdxToLast * 2 + 2;
   T* lastEle = end - 1;

   while(leftIdxToLast <= finalHeapEleToLast)
   {
      int largest = parentIdxToLast;

      if(*(lastEle - leftIdxToLast) < *(lastEle - largest)) 
      {
         largest = leftIdxToLast;
      }

      if(rightIdxToLast < finalHeapEleToLast
       && *(lastEle - rightIdxToLast) < *(lastEle - largest)) 
      {
         largest = rightIdxToLast;
      }

      if(largest != parentIdxToLast)
      {
         T temp = *(lastEle - largest);
         *(lastEle - largest) = *(lastEle - parentIdxToLast);
         *(lastEle - parentIdxToLast) = temp;

         parentIdxToLast = largest;
         leftIdxToLast = parentIdxToLast * 2 + 1;
         rightIdxToLast = parentIdxToLast * 2 + 2;

      }
      else break;

   }
}

template class Sort<int>;
template class Sort<float>;