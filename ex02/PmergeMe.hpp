#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <algorithm>
#include <chrono>


class PmergeMe {
private:
    std::vector<int> _vecData;
    std::list<int> _listData;

public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void loadInput(int argc, char* argv[]);
    void sortVector();
    void sortList();

    const std::vector<int>& getVectorData() const;
    const std::list<int>& getListData() const;

    template <typename T>
    void fordJohnsonSort(T& container);

private:
    template <typename T>
    void insertIntoSorted(T& sortedContainer, typename T::value_type element);
};

// Template Definitions

template <typename T>
void PmergeMe::fordJohnsonSort(T& container) {
    if (container.size() <= 1) return;

    T largerElements, smallerElements;

    // Pair elements and divide into two groups
    auto it = container.begin();
    while (it != container.end()) {
        auto next = std::next(it);
        if (next == container.end()) {
            largerElements.push_back(*it);
            break;
        }

        if (*it < *next) {
            smallerElements.push_back(*it);
            largerElements.push_back(*next);
        } else {
            smallerElements.push_back(*next);
            largerElements.push_back(*it);
        }
        std::advance(it, 2);
    }

    // Recursively sort the larger group
    fordJohnsonSort(largerElements);

    // Insert smaller elements into the sorted larger group
    for (const auto& element : smallerElements) {
        insertIntoSorted(largerElements, element);
    }

    // Replace the original container with the sorted result
    container = largerElements;
}

template <typename T>
void PmergeMe::insertIntoSorted(T& sortedContainer, typename T::value_type element) {
    auto position = std::lower_bound(sortedContainer.begin(), sortedContainer.end(), element);
    sortedContainer.insert(position, element);
}

#endif 