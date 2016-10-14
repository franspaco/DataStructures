//
// Created by franspaco on 12/10/16.
//

#ifndef POSTFIX_POSTFIX_H
#define POSTFIX_POSTFIX_H
#include <iostream>
#include <cmath>
#include <string>
#include "Stack.h"

class Postfix {
private:
    std::string infix;
    std::string postfix;

    int computeOperator(int num1, int num2, char sign);
    int comparePrecedence(char op1, char op2);
public:
    Postfix (std::string _infix) { infix = _infix; }
    void setInfix (std::string _infix) { infix = _infix; }
    void convertToPostfix();
    int evaluate();
    void setPostfix(std::string inpt);
};

#endif //POSTFIX_POSTFIX_H
