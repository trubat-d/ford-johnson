#include "PmergeMe.hpp"

bool         PmergeMe::args_handler(char** args) {
	for(int i = 0; args[i]; i++)
		for(int j = 0; args[i][j]; j++)
			if(args[i][j] < '0' || args[i][j] > '9')
				return false;
	return true;
}

int          PmergeMe::jacobsthal(int index) {
	if (index == 0) return 0;
	else if (index == 1) return 1;
	else return (jacobsthal(index-1) + 2 * jacobsthal(index-2));
}

std::ostream& operator<<(std::ostream& os, std::vector<int> & ref)
{
	for(std::vector<int>::iterator it = ref.begin(); it != ref.end(); it++)
		os << *it << " ";
	return os;
}

std::ostream& operator<<(std::ostream& os, std::list<int> & ref)
{
	for(std::list<int>::iterator it = ref.begin(); it != ref.end(); it++)
		os << *it << " ";
	return os;
}

std::ostream& operator<<(std::ostream& os, std::vector<std::pair<int,int> > & ref)
{
	for(std::vector<std::pair<int, int> >::iterator it = ref.begin(); it != ref.end(); it++)
		os << it->first << " " << it->second << " ";
	return os;
}

std::ostream& operator<<(std::ostream& os, std::list<std::pair<int, int> > & ref)
{
	for(std::list<std::pair<int, int> >::iterator it = ref.begin(); it != ref.end(); it++)
		os << it->first << " " << it->second << " ";
	return os;
}


const char *PmergeMe::WrongArgsException::what() const throw()
{
	return ("Error: Args content must only be numbers");
}

const char *PmergeMe::WrongContainerException::what() const throw()
{
	return ("Error: Make sure to use at least one of those container : vector or list !");
}