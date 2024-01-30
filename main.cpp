#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if(ac <= 1)
    {
        std::cerr << "need more inputs" << std::endl;
        return 1;
    }
    std::list<int> test = PmergeMe::ford_jhonson<std::list>(av);
    std::cout << test << std::endl;
    return 0;
}