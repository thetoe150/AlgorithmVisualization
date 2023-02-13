#include "Visualization.hpp"


static inline void Merge(int* start, int* mid, int* end, int abs_pos, std::function<void (HightlightType, int, int)> compareVisualize);
static inline int* Quick(int* start, int* pivot, int* end, int abs_pos, std::function<void (HightlightType, int, int)> compareVisualize);
static inline void reheapUp(int* start, int* end, int reheapIdx, std::function<void (HightlightType, int, int)> compareVisualize);
static inline void reheapDown(int* start, int* end, int reheapIdx, std::function<void (HightlightType, int, int)> compareVisualize);
static inline bool checkBogo(int* start, int* end, std::function<void (HightlightType, int, int)> compareVisualize);

void printresult(int* start, int* end)
{
    while(start != end)
    {
        std::cout<<*start<<" ";
        start++;
    }
}

void Insertion(int* start, int* end, std::function<void (HightlightType, int, int)> drawSorting)
{
    int size = end - start;
    for(int i = 1; i < size; i++)
    {
        int temp = *(start + i);
        int j = i - 1;
        int max_temp = *(start + j);
        while(temp < *(start + j - 1) && j - 1 >= 0)
        {
            drawSorting(HightlightType::Compare, i, j - 1);
            drawSorting(HightlightType::Write, j, j);
            *(start + j) = *(start + j - 1);
            j--;
        }

        // the "if" is in case start[i] is already bigger than start[j]
        if(max_temp > temp)
        {
            *(start + j) = temp;
            *(start + i) = max_temp;
        }
        //drawSorting(HightlightType::Write, j, j);
        drawSorting(HightlightType::Compare, j, i);
    }
}

void Selection(int* start, int* end, std::function<void (HightlightType, int, int)> drawSorting)
    {
    int size = end - start;
    for(int i = 0; i < size - 1; i++)
        {
            int min = *(start + i);
            int min_idx = i;
            for(int j = i + 1; j < size; j++)
            {
                drawSorting(HightlightType::Compare, min_idx, j);
                if(*(start + j) < min)
                {
                    min = *(start + j);
                    min_idx = j;
                }
            }
            int temp = *(start + i);
            *(start + i) = *(start + min_idx);
            *(start + min_idx) = temp;
            drawSorting(HightlightType::Write, i, i);
            drawSorting(HightlightType::Write, min_idx, min_idx);
        }
    }

void Bubble(int* start, int* end, std::function<void (HightlightType, int, int)> drawSorting)
{
   bool sorted = true;
   int size = end - start;
    for(int i = 0; i < size - 1; i++)
    {
        sorted = true;
        for(int j = size - 1; j > i; j--)
        {
            drawSorting(HightlightType::Compare, j - 1, j);
            if(*(start + j) < *(start + j - 1))
            {
                sorted = false;
                int temp = *(start + j);
                *(start + j) = *(start + j - 1);
                *(start + j - 1) = temp;
                
                drawSorting(HightlightType::Write, j - 1, j - 1);
                drawSorting(HightlightType::Write, j, j);
            }
        }
        if(sorted) break;
    }
}

void Shell(int* start, int* end, const int* step_arr, int step_arr_size, std::function<void (HightlightType, int, int)> drawSorting)
{
   int size = end - start;
   
   for(int si = 0; si < step_arr_size; si++)
   {
      int step = step_arr[si];
      for(int subarr_i = 0; subarr_i < step; subarr_i++)
      {
         for(int i = subarr_i + step; i < size; i += step)
         {
            int temp = *(start + i);
            int j = i - step;
            int max_temp = *(start + j);
            while(j - step >= 0 && *(start + j - step) > temp)
            {
               *(start + j) = *(start + j - step);
               j -= step;
                drawSorting(HightlightType::Compare, j, i);
            }
            if(max_temp > temp)
            {
               *(start + j) = temp;
               *(start + i) = max_temp;
            }
            drawSorting(HightlightType::Compare, j, i);

         }
      }
   }
}

void Merge(int* start, int* mid, int* end, int abs_pos, std::function<void (HightlightType, int, int)> drawSorting)
{
   int FHsize = mid - start; 
   int SHsize = end - mid; 

   int *FHarray = new int[FHsize];
   int *SHarray = new int[SHsize];

   for(int i = 0; i < FHsize; i++)
   {
      FHarray[i] = *(start + i);
   }

   for(int i = 0; i < SHsize; i++)
   {
      SHarray[i] = *(mid + i);
   }
   int* mergeWalker = start;
   int FHwalker = 0;
   int SHwalker = 0;
   while(FHwalker < FHsize && SHwalker < SHsize)
   {
        drawSorting(HightlightType::Compare, abs_pos + FHwalker, abs_pos + FHsize + SHwalker);
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
        drawSorting(HightlightType::Write, abs_pos + FHwalker, abs_pos + FHsize);
        mergeWalker++;
    }
    while(SHwalker < SHsize)
    {
        *mergeWalker = SHarray[SHwalker++];
        drawSorting(HightlightType::Write, abs_pos + FHwalker + SHwalker, abs_pos + FHsize + SHwalker);
        mergeWalker++;
    }

   delete[] FHarray;
   delete[] SHarray;
}

void MergeRec(int* start, int* end, int abs_pos, std::function<void (HightlightType, int, int)> drawSorting)
{
   int size = end - start;
   if(size == 1)
      return;
   
   int* mid = start + (size / 2);
   MergeRec(start, mid, abs_pos, drawSorting);
   MergeRec(mid, end, abs_pos + (size/2), drawSorting);
   Merge(start, mid, end, abs_pos, drawSorting);
}

int* Quick(int* start, int* pivot, int* end, int abs_pos, std::function<void (HightlightType, int, int)> drawSorting)
{
   int size = end - start;
   int Lwalker = 0;
   int Rwalker = size - 1;

   while(Rwalker >= Lwalker && Rwalker > 0)
   {
        drawSorting(HightlightType::Compare, abs_pos + Lwalker, abs_pos + pivot - start);
        drawSorting(HightlightType::Compare, abs_pos + Rwalker, abs_pos + pivot - start);

        if(*(start + Lwalker) > *pivot && *(start + Rwalker) < *pivot)
        {
            int temp = *(start + Lwalker);
            *(start + Lwalker) = *(start + Rwalker);
            *(start + Rwalker) = temp;
            drawSorting(HightlightType::Write, abs_pos + Lwalker, abs_pos + Rwalker);
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
        drawSorting(HightlightType::Write, abs_pos + Rwalker, abs_pos + pivot - start);
        return start + Rwalker;
   }
   else
   {
        int temp = *(start + Lwalker);   
        *(start + Lwalker) = *pivot;
        *pivot = temp;
        drawSorting(HightlightType::Write, abs_pos + Lwalker, abs_pos + pivot - start);
        return start + Lwalker;
   }
}

void QuickRec(int* start, int* end, int abs_pos, std::function<void (HightlightType, int, int)> drawSorting)
{
   int size = end - start;
   if(size <= 1)
      return;
   
   int* mid = start + (size / 2); 
   int* pivot = Quick(start, mid, end, abs_pos, drawSorting);
   QuickRec(start, pivot, abs_pos, drawSorting);
   QuickRec(pivot + 1, end, abs_pos + (pivot - start) + 1, drawSorting);
}

void reheapUp(int* start, int* end, int reheapIdx, std::function<void (HightlightType, int, int)> compareVisualize)
{
    int lastIdx = end - start - 1;
    int reheapToLast = lastIdx - reheapIdx;
    int* lastEle = end - 1;
    int* reheapEle = lastEle - reheapToLast;

    while(reheapToLast > 0)
    {
        int* parentEle = lastEle - (reheapToLast - 1)/2; //std::cout<<"parent: "<<*parentEle<<"  reheap: "<<*reheapEle<<std::endl;
        compareVisualize(HightlightType::Compare, lastIdx - reheapToLast, lastIdx - (reheapToLast - 1)/2);
        if(*reheapEle < *parentEle)
        {
            int temp = *reheapEle;
            *reheapEle = *parentEle;
            *parentEle = temp;
            compareVisualize(HightlightType::Write, lastIdx - reheapToLast, lastIdx - (reheapToLast - 1)/2);
            reheapEle = parentEle;
            reheapToLast = (reheapToLast - 1)/2;
        }
        else break;
    } 
}

void reheapDown(int* start, int* end, int ignoreEle, std::function<void (HightlightType, int, int)> compareVisualize)
{
    int lastIdx = end - start - 1;  //consider last Idx of the array as root and as index 0
    int finalHeapEleToLast = lastIdx - ignoreEle - 1;

    int parentIdxToLast = 0;
    int leftIdxToLast = parentIdxToLast * 2 + 1;
    int rightIdxToLast = parentIdxToLast * 2 + 2;
    int* lastEle = end - 1;

    while(leftIdxToLast <= finalHeapEleToLast)
    {
        int largest = parentIdxToLast;

        compareVisualize(HightlightType::Compare, lastIdx - largest, lastIdx - leftIdxToLast);
        if(*(lastEle - leftIdxToLast) < *(lastEle - largest)) 
        {
            largest = leftIdxToLast;
        }

        compareVisualize(HightlightType::Compare, lastIdx - largest, lastIdx - rightIdxToLast);
        if(rightIdxToLast < finalHeapEleToLast
        && *(lastEle - rightIdxToLast) < *(lastEle - largest)) 
        {
            largest = rightIdxToLast;
        }

        if(largest != parentIdxToLast)
        {
            int temp = *(lastEle - largest);
            *(lastEle - largest) = *(lastEle - parentIdxToLast);
            *(lastEle - parentIdxToLast) = temp;
            compareVisualize(HightlightType::Write, lastIdx - largest, lastIdx - parentIdxToLast);

            parentIdxToLast = largest;
            leftIdxToLast = parentIdxToLast * 2 + 1;
            rightIdxToLast = parentIdxToLast * 2 + 2;

        }
        else break;

    }

}
void Heap(int* start, int* end, std::function<void (HightlightType, int, int)> compareVisualize)
{
    int size = end - start;
    for(int i = size - 2; i >= 0; i--)
    {
        reheapUp(start, end, i, compareVisualize); //print(start, end);
    }

    for(int i = 0; i < size - 1; i++)
    {
        int temp = *(end - 1);
        *(end - 1) = *(start + i);
        *(start + i) = temp;
        compareVisualize(HightlightType::Write, i, end - start - 1);
        reheapDown(start, end, i, compareVisualize);
    }
}


//Shell - Selection Hybrid
void ShittyShell(int* start, int* end, const int* step_arr, int step_arr_size, std::function<void (HightlightType, int, int)> drawSorting)
{
   int size = end - start;
   
   for(int si = 0; si < step_arr_size; si++)
   {
        int step = step_arr[si];
        for(int i_sorted = 0; i_sorted < size; i_sorted += step)
        {
            for(int i_subarr = i_sorted; i_subarr < i_sorted + step; i_subarr++)
            {
                int min = *(start + i_subarr);
                int min_idx = i_subarr;
                bool min_flag = false;
                for(int i = i_subarr + step; i < size; i += step)
                {
                    drawSorting(HightlightType::Compare, i_subarr, i);
                    if(*(start + i) < min)
                    {
                        min = *(start + i);
                        min_idx = i;
                        min_flag = true;
                    }
                }  
                if(min_flag)
                {
                    *(start + min_idx) = *(start + i_subarr);
                    *(start + i_subarr) = min;
                }
            }
        }
   }
}


void Bogo(int* start, int* end, std::function<void (HightlightType, int, int)> compareVisualize)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;

    //duration<double, std::milli> ms_double = t2 - t1;
    auto t_begin_hi = high_resolution_clock::now();
    std::array<int, 100> arr;
    for(int i = 0; i < 100; i++)
    {
        arr[i] = *(start + i);
    }

    while(!checkBogo(start, end, compareVisualize))
    {
        auto ms_int = duration_cast<milliseconds>(high_resolution_clock::now() - t_begin_hi);
        std::cout <<"current time: "<< ms_int.count() <<std::endl;

        std::mt19937 prng(static_cast<std::mt19937::result_type>(ms_int.count()));
        std::shuffle(arr.begin(), arr.end(), prng);

        for(int i = 0; i < 100; i++)
        {
            *(start + i) = arr[i];
        }
    }   

}

static inline bool checkBogo(int *start, int *end, std::function<void (HightlightType, int, int)> compareVisualize)
{
    int* first_ele = start;
    while(start != end - 1)
    {
        compareVisualize(HightlightType::Compare, start - first_ele, start - first_ele + 1);
        if(*start > *(start + 1))
            return false;

        start++;
    }
    return true;
}