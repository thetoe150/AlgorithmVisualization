#include "main.hpp"
#include "Algorithm.hpp"

int main(){
    int array[10] = {6,4,2,18,8,1,33,12,7,0};
    //Sort<int>::Insertion(array, array + 10);
    Sort<int>::Selection(array, array + 10);
    Sort<int>::print(array, array + 10);

    return 0;
}