#include "leftist_priority_queue.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int comparer(int a, int b) 
{
    return a < b;
}

int main() 
{
    std::cout << "=== Testing leftist priority queue ===" << std::endl;
    srand((unsigned)time(NULL));
    leftist_priority_queue q1(comparer);
    leftist_priority_queue q2(comparer);

    std::cout << "Filling two queues with random values and priorities." << std::endl;
    for (int i = 0; i < 11; ++i) 
    {
        int p1 = rand() % 100 + 1;
        int p2 = rand() % 100 + 1;

        q1.insert(p1, "test");
        q2.insert(p2, "test");
    }

    // std::cout << std::endl << "Queues structures:" << std::endl;
    // std::cout << "q1: "; q1.debug_print();

    std::cout << std::endl;
    char const * q1_max = q1.get_max();
    std::cout << "q1 max value: " << q1_max << std::endl;
    // std::cout << "q2: "; q2.debug_print();

    // std::cout << std::endl << "Merging queues: " << std::endl;
    q1.merge(&q2); 
    // std::cout << "merged queue: "; q1.debug_print();

    std::cout << std::endl;
    char * remove_value = q1.remove_max();
    std::cout << remove_value << std::endl;
    // q1.debug_print();

    return 0;
}