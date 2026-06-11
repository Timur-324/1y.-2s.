#include "fibonacci_priority_queue.h"

int priorities_comparer(
	int first,
	int second)
{
	return first - second;
}

int main()
{
	std::cout << "=== Testing fibonacci priority queue ===" << std::endl;
	srand((unsigned)time(NULL));

	fibonacci_priority_queue bq1(priorities_comparer);
	fibonacci_priority_queue bq2(priorities_comparer);

	std::cout << "Fulling two queues with random values and priorities." << std::endl;
	for(int i = 0; i < 11; ++i)
	{
		int p1 = rand() % 1000 + 100;
		int p2 = rand() % 1000 + 100;

		bq1.insert(p1, "test");
		bq2.insert(p2, "test");
	}

	std::cout << std::endl << "Queues structures: " << std::endl;
	std::cout << "bq1: "; bq1.debug_print();
	char const * bq1_max = bq1.get_max();
	std::cout << "bq1 max value: " << bq1_max << std::endl;
	std::cout << "bq2: "; bq2.debug_print();

	std::cout << std::endl << "Merging queues: " << std::endl;
	bq1.merge(&bq2); 
	std::cout << "merged queue: "; bq1.debug_print();

	std::cout << std::endl;
	char * remove_value = bq1.remove_max();
	std::cout << remove_value << std::endl;
	bq1.debug_print();


	return 0;
}