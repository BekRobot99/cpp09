#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& dbFile) {
    loadDatabase(dbFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) 
    : _exchangeRates(other._exchangeRates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _exchangeRates = other._exchangeRates;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string& dbFile) {
    std::ifstream file(dbFile);
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open file.");
    }

    std::string line, date;
    float rate;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        if (std::getline(stream, date, ',') && stream >> rate) {
            _exchangeRates[date] = rate;
        }
    }
}

void BitcoinExchange::processInputFile(const std::string& inputFile) const {
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string date, valueStr;

        if (!std::getline(stream, date, '|') || !(stream >> valueStr)) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        date = date.substr(0, date.find_last_not_of(" \t") + 1);
        valueStr = valueStr.substr(valueStr.find_first_not_of(" \t"));

        float value;
        try {
            value = std::stof(valueStr);
        } catch (const std::invalid_argument&) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (value < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
        } else if (value > 1000) {
            std::cerr << "Error: too large a number." << std::endl;
        } else if (!isValidDate(date)) {
            std::cerr << "Error: bad input => " << date << std::endl;
        } else {
            float rate = getClosestRate(date);
            std::cout << date << " => " << value << " = " << value * rate << std::endl;
        }
    }
}

// Find the closest rate by date
float BitcoinExchange::getClosestRate(const std::string& date) const {
    auto it = _exchangeRates.lower_bound(date);
    if (it == _exchangeRates.begin()) {
        return it->second;
    }
    if (it == _exchangeRates.end() || it->first != date) {
        --it;
    }
    return it->second;
}

// Validate the date format
bool BitcoinExchange::isValidDate(const std::string& date) const {
    std::regex dateRegex(R"(^\d{4}-\d{2}-\d{2}$)");
    if (!std::regex_match(date, dateRegex)) {
        return false;
    }

    int year, month, day;
    char dash1, dash2;
    std::istringstream dateStream(date);
    if (!(dateStream >> year >> dash1 >> month >> dash2 >> day)) {
        return false;
    }

    if (dash1 != '-' || dash2 != '-' || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    return true;
}
