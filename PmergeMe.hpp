#include <iostream>
#include <vector>
#include <exception>
#include <cstdlib>
#include <list>
#include <typeinfo>

std::ostream& operator<<(std::ostream& os, std::list<int> & ref); 

std::ostream& operator<<(std::ostream& os, std::list<std::pair<int,int> > & ref);
std::ostream& operator<<(std::ostream& os, std::vector<std::pair<int, int> > & ref);

std::ostream& operator<<(std::ostream& os, std::vector<int> & ref);

class PmergeMe {
public:
    template<template <typename Y, typename = std::allocator<Y> > class T>
    static T<int>   ford_jhonson(char** args) 
    {
        args = args+1;
        T<int> a;
    
        if(!PmergeMe::is_valid_container(a))
        {
            std::cerr << "Container Error" << std::endl;
            return a;
        }

        if(!PmergeMe::args_handler(args))
        {
            std::cerr << "Args Error" << std::endl;
            return a;
        }
        
        int straggler = 0;
        bool has_strag = false;
        T<std::pair<int,int> > pairs;

        PmergeMe::create_list(pairs, args, straggler, has_strag);
        PmergeMe::sort_pairs(pairs);
        

        return create_main<T<int>, T<std::pair<int, int> > >(pairs, straggler, has_strag);
    }

private:

    template <typename T, typename U>
    static T create_main(U & pairs, int & straggler, bool & has_strag)
    {
        T main_arr;
        T pend;

        for(typename U::iterator it = pairs.begin(); it != pairs.end(); it++)
        {
            main_arr.push_back(it->second);
            pend.push_back(it->first);
        }

        main_arr.insert(main_arr.begin(), *(pend.begin()));

        T jacob_sequence = build_jacob_array(pend);

        T index_sequence;
        index_sequence.push_back(1);
        bool last_jacob = false;

        int size = pend.size();

        for(int i = 0; i <= size; i++)
        {
            int element = 0;
            if(!jacob_sequence.empty() && !last_jacob)
            {
                index_sequence.push_back(*(jacob_sequence.begin()));
                element = *(PmergeMe::get_element_by_id((*(jacob_sequence.begin())) - 1, pend));
                jacob_sequence.erase(jacob_sequence.begin());
                last_jacob = true;
            }
            else
            {
                for(typename T::iterator iter = index_sequence.begin(); iter != index_sequence.end(); iter++)
                {
                    if(i == *iter)
                    {
                        i++;
                        break;
                    }
                }
                element = i == 0 ? *(pend.rbegin()) : *(PmergeMe::get_element_by_id(i-1, pend));
                index_sequence.push_back(i);
                last_jacob = false;
            }

            int insert_pos = PmergeMe::binary_search(main_arr, element);
            std::cout << main_arr << std::endl << pend << std::endl << "pos " << insert_pos << " elem " << element << std::endl;
            main_arr.insert(PmergeMe::get_element_by_id(insert_pos, main_arr), element);
                
        }

        if(has_strag)
        {
            int insert_pos = PmergeMe::binary_search(main_arr, straggler);
            
            main_arr.insert(PmergeMe::get_element_by_id(insert_pos, main_arr), straggler);
        }

        return main_arr;
    }

    template<typename T>
    static void create_list(T & ref, char **args, int & straggler, bool &has_strag) 
    {
        int size = -1;
        while(args[++size])
            ;
       
        if(size%2 != 0)
        {
            straggler = atoi(args[size-1]);
            has_strag = true;
        }

        for(int i = 0; i+1 < size; i+=2)
            ref.push_back(std::pair<int,int>(atoi(args[i]), atoi(args[i+1])));
        
    }

    template <typename T>
    static    T        build_jacob_array(T pend)
    {
        int array_len = pend.size();
        T end_sequence;
        int jacob_index = 3; 

        while (jacobsthal(jacob_index) < array_len -1)
        {
            end_sequence.push_back(jacobsthal(jacob_index));
            jacob_index += 1;
        }
    
        return end_sequence;
    }

    template <typename T>
    static typename T::iterator get_element_by_id(int n, T & ref)
    {
        typename T::iterator it = ref.begin();
        for(int i = 0; i < n; i++, it++)
            ;
        return it;
    }

    template <typename T>
    static    int    binary_search(T nums, int target)
    {
        int low = 0, high = nums.size()-1, mid = (high + low) / 2;
        if(*(PmergeMe::get_element_by_id(high, nums)) < target)
            return (high+1);
        if(*(PmergeMe::get_element_by_id(low, nums)) > target)
            return low;
        while(high-low != 0)
        {
            if(*(PmergeMe::get_element_by_id(mid, nums)) == target)
                return mid;
            if(*(PmergeMe::get_element_by_id(mid, nums)) > target)
                high = mid;
            else
                low = mid;
            mid = (high + low) / 2;
            if(high - low == 1)
                return (*(PmergeMe::get_element_by_id(low, nums))==target?low:high);
        }
        return low;
    }

    template <typename T>
    static void   swap_pair(T & pairs)
    {
        for (typename T::iterator iter = pairs.begin(); iter != pairs.end(); iter++)
        {
            if ((*iter).first > (*iter).second)
            {
                int tmp = iter->first;
                iter->first = iter->second;
                iter->second = tmp;
            }
        }
    }

    template<typename T>
    static void         sort_pairs(T & arr)
    {
        PmergeMe::swap_pair(arr);
        std::cout << " pairs :" << arr << std::endl;
        recursive_pair_sort(arr);
    }

    template <typename T>
    static void recursive_pair_sort(T & arr)
    {
        int size = arr.size();
        if(size <= 1) return ;
        std::pair<int,int> val = *(arr.rbegin());
        arr.pop_back();
        recursive_pair_sort(arr);

        bool is_changed = false;
        if(arr.begin()->second > val.second)
        {
            is_changed = true;
            arr.insert(arr.begin(), val);
            return ;
        }
        for(typename T::iterator it = arr.begin(); it != arr.end(); it++)
        {
            if(it->second > val.second)
            {
                is_changed = true;
                arr.insert(it, val);
                return ;
            }
        }
        if(!is_changed)
        {
            arr.push_back(val);
            return ;
        }
        
    }

    static bool is_valid_container(std::vector<int> & ref) {(void) ref; return true;}

    static bool is_valid_container(std::list<int> & ref) {(void) ref; return true;}

    template <typename T>
    static bool is_valid_container(T & ref) {(void) ref; return false;}

    static bool         args_handler(char** args);
    static int          jacobsthal(int index);
    ~PmergeMe();
    PmergeMe();
    PmergeMe(const PmergeMe & ref);
    PmergeMe operator=(const PmergeMe & ref);
};
