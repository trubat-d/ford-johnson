#include "PmergeMe.hpp"
#include <time.h>

int main(int ac, char **av)
{

	if(ac <= 1)
	{
		std::cerr << "need more inputs" << std::endl;
		return 1;
	}
	{
		try
		{
			std::cout << "Before: ";
			for (int i = 1; i < ac; i++)
				std::cout << av[i] << " ";
			std::cout << std::endl;
			std::clock_t start = std::clock();
			std::list<int> sorted_list = PmergeMe::ford_jhonson<std::list>(av);
			std::clock_t end = std::clock();
			std::cout << "After: ";
			std::cout << sorted_list << std::endl;
			// std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "Time to process a range of " << sorted_list.size() << " elements with std::list<int> : " << ((double) (end - start)) / CLOCKS_PER_SEC << "us" << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	{
		try
		{
			std::clock_t start = std::clock();
			std::vector<int> sorted_vector = PmergeMe::ford_jhonson<std::vector>(av);
			std::clock_t end = std::clock();
			std::cout << "Time to process a range of " << sorted_vector.size() << " elements with std::vector<int> : " << ((double) (end - start)) / CLOCKS_PER_SEC << "us" << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	return 0;
}