#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <regex>
#include <string>
#include <map>

class BitcoinExchange 
{
private:
    std::map<std::string, float> _exchangeRates;

public:
    BitcoinExchange();
    BitcoinExchange(const std::string& dbFile);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void loadDatabase(const std::string& dbFile);
    void processInputFile(const std::string& inputFile) const;
    float getClosestRate(const std::string& date) const;
    bool isValidDate(const std::string& date) const;
};

#endif

