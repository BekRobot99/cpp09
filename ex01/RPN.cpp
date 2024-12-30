#include "RPN.hpp"
#include <sstream>
#include <iostream>
#include <cctype>

// Constructor
RPN::RPN() {}

// Copy Constructor
RPN::RPN(const RPN& other) : _stack(other._stack) {}

// Assignment Operator
RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        _stack = other._stack;
    }
    return *this;
}

// Destructor
RPN::~RPN() {}

// Check if a character is a valid operator
bool RPN::isOperator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Apply the operator to two operands
int RPN::applyOperator(char op, int left, int right) const {
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/':
            if (right == 0) {
                throw std::runtime_error("Error: division by zero");
            }
            return left / right;
        default:
            throw std::runtime_error("Error: invalid operator");
    }
}

// Evaluate the RPN expression
int RPN::evaluate(const std::string& expression) {
    std::istringstream stream(expression);
    std::string token;

    while (stream >> token) {
        if (token.length() == 1 && isOperator(token[0])) {
            if (_stack.size() < 2) {
                throw std::runtime_error("Error: insufficient operands");
            }

            int right = _stack.top(); _stack.pop();
            int left = _stack.top(); _stack.pop();
            _stack.push(applyOperator(token[0], left, right));
        } else if (std::isdigit(token[0]) && token.length() == 1) {
            _stack.push(token[0] - '0');
        } else {
            throw std::runtime_error("Error: invalid token");
        }
    }

    if (_stack.size() != 1) {
        throw std::runtime_error("Error: invalid expression");
    }

    return _stack.top();
}
