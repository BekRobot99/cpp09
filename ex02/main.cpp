#include "PmergeMe.hpp"


template <typename T>
void displayData(const std::string& message, const T& container) {
    std::cout << message;
    for (const auto& val : container) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./PmergeMe <positive integers>" << std::endl;
        return 1;
    }

    try {
        PmergeMe sorter;

        sorter.loadInput(argc, argv);

        std::cout << "Testing with std::vector:" << std::endl;
        auto vecData = sorter.getVectorData();
        displayData("Before: ", vecData);

        auto startVec = std::chrono::high_resolution_clock::now();
        sorter.fordJohnsonSort(vecData);
        auto endVec = std::chrono::high_resolution_clock::now();
        displayData("After: ", vecData);
        std::chrono::duration<double, std::micro> elapsedVec = endVec - startVec;
        std::cout << "Time to process a range of " << vecData.size()
                  << " elements with std::vector: " << elapsedVec.count() << " us\n" << std::endl;

        std::cout << "Testing with std::list:" << std::endl;
        auto listData = sorter.getListData();
        displayData("Before: ", std::vector<int>(listData.begin(), listData.end()));

        auto startList = std::chrono::high_resolution_clock::now();
        sorter.fordJohnsonSort(listData);
        auto endList = std::chrono::high_resolution_clock::now();
        displayData("After: ", std::vector<int>(listData.begin(), listData.end()));
        std::chrono::duration<double, std::micro> elapsedList = endList - startList;
        std::cout << "Time to process a range of " << listData.size()
                  << " elements with std::list: " << elapsedList.count() << " us\n" << std::endl;

        std::cout << "Testing with std::deque:" << std::endl;
        std::deque<int> dequeData(sorter.getVectorData().begin(), sorter.getVectorData().end());
        displayData("Before: ", std::vector<int>(dequeData.begin(), dequeData.end()));

        auto startDeque = std::chrono::high_resolution_clock::now();
        sorter.fordJohnsonSort(dequeData);
        auto endDeque = std::chrono::high_resolution_clock::now();
        displayData("After: ", std::vector<int>(dequeData.begin(), dequeData.end()));
        std::chrono::duration<double, std::micro> elapsedDeque = endDeque - startDeque;
        std::cout << "Time to process a range of " << dequeData.size()
                  << " elements with std::deque: " << elapsedDeque.count() << " us\n" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
