#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
    : _vecData(other._vecData), _listData(other._listData) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _vecData = other._vecData;
        _listData = other._listData;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

const std::vector<int>& PmergeMe::getVectorData() const {
    return _vecData;
}

const std::list<int>& PmergeMe::getListData() const {
    return _listData;
}

void PmergeMe::loadInput(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        int value = std::stoi(argv[i]);
        if (value < 0) {
            throw std::invalid_argument("Error: Negative numbers are not allowed.");
        }
        _vecData.push_back(value);
        _listData.push_back(value);
    }
}

void PmergeMe::sortVector() {
    fordJohnsonSort(_vecData);
}

void PmergeMe::sortList() {
    fordJohnsonSort(_listData);
}
