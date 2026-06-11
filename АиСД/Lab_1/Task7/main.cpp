#include "binomial_priority_queue.h"

int priorities_comparer(
	int first,
	int second)
{
	return first - second;
}

void bpq_demo()
{
	srand((unsigned)time(NULL));

	binomial_priority_queue instance(priorities_comparer);

	binomial_priority_queue meld_from_all(priorities_comparer);

	char *removed_value;
	for (int i = 0; i < 100; i++)
	{
		switch (rand() % 1)
		{
		case 0:
			instance.insert(rand() % 9000 + 1000, "pukpuk");
			break;
		case 1:
			try
			{
				delete (removed_value = instance.remove_max());
			}
			catch (binomial_priority_queue::empty_priority_queue_exception const &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			break;
		}

		binomial_priority_queue *melded = dynamic_cast<binomial_priority_queue*>(meld_from_all.meld(&instance));
		meld_from_all = *melded;
		delete melded;

		std::cout << "instance: ";
		instance.debug_print();
		std::cout << "melded: ";
		meld_from_all.debug_print();
	}
}








int main()
{

	std::cout << "=== Testing binomial priority queue ===" << std::endl;
	srand((unsigned)time(NULL));

	binomial_priority_queue bq1(priorities_comparer);
	binomial_priority_queue bq2(priorities_comparer);

	std::cout << "Fulling two queues with random values and priorities." << std::endl;
	for(int i = 0; i < 100; ++i)
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

	std::cout << std::endl << "Melding queues: " << std::endl;
	binomial_priority_queue * meld = dynamic_cast<binomial_priority_queue*>(bq1.meld(&bq2)); 
	std::cout << "melded queue: "; meld->debug_print();

	delete meld;

	







	// bpq_demo();
	return 0;
}