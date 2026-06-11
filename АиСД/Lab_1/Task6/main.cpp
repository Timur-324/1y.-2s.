#include "binary_heap.h"



int min_comparator(int a, int b) 
{
    return a - b;
}


int main()
{
    binary_heap heap;

    std::cout << "123456789" << std::endl << std::endl;
    // strcpy(puk, "123456789");

   // heap.insert(10, puk);
    //
    // delete[] puk;

    // char * str = heap.removeMax();
    // std::cout << heap.removeMax() << std::endl;


    binary_heap min_heap;

    min_heap.insert(10, "low");
    min_heap.insert(5,  "lowest");
    min_heap.insert(20, "high");
    min_heap.insert(1,  "very low");

    std::cout << "Apparent min: " << min_heap.findMax() << "\n";

    while (char * val = min_heap.removeMax()) 
    {
        std::cout << "Removed: " << val << "\n";
        delete [] val;
    }

    return 0;
}