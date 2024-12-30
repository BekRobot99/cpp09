  #ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <stdexcept>

class RPN {
private:
    std::stack<int> _stack;

public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    int evaluate(const std::string& expression);
    bool isOperator(char c) const;
    int applyOperator(char op, int left, int right) const;
};

#endif // RPN_HPP
