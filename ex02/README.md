### PMERGE ME

#### Explanation:
> This exercise is for comparing the behavior of two different containers. The containers that are compared in this case are [vector]('https://en.cppreference.com/w/cpp/container/vector') and [deque]('https://en.cppreference.com/w/cpp/container/deque'). The program will take a sequence of numbers, sort them using [merge]('https://en.wikipedia.org/wiki/Merge_sort') sort and print the total time. This process will be repeated for each container in order to see the difference.

#### Usage:
> The program receives an undefined amount of arguments containing one number or a string containing multiple numbers. It does not handle negative numbers.
``` shell
example:
    make
    ./PmergeMe 5 6 32 8 9
    ./PmergeMe "5 6 32 8 9"
    ./PmergeMe "4 63 2 8 3 4" 5 6 '10'
```