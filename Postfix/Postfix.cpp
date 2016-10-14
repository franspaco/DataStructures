//
// Created by franspaco on 12/10/16.
//

#include "Postfix.h"


int Postfix::computeOperator(int num1, int num2, char sign) {
    switch(sign){
        case '^':
            return pow(num1, num2);
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
        case '%':
            return num1 % num2;
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        default:
            return 0;
    }
}

int Postfix::comparePrecedence(char op1, char op2) {
    char operators[] = { '^', '*', '/', '%', '+', '-' };
    int precedence[] = {   3,   2,   2,   2,   1,   1 };
    int size = sizeof(operators) / sizeof(operators[0]);
    int value1, value2;

    for (int i=0; i<size; i++)
    {
        if (op1 == operators[i])
            value1 = precedence[i];
        if (op2 == operators[i])
            value2 = precedence[i];
    }
    // Returns the difference in the precedence
    // If larger than 0, value 1 has higher precedence
    return value1 - value2;
}

void Postfix::convertToPostfix() {
    int size = infix.length();
    Stack<char> conversionStack;
    Node<char> * item;
    char token;

    postfix = "";   // Initialize postfix as an empty string

    for (int i=0; i<size; i++)
    {
        token = infix[i];
        // Case 1: numbers
        if (token >= '0' && token <= '9')
            postfix += token;

            // Case 2: (
        else if (token == '(')
            conversionStack.push(token);

            // Case 3: )
        else if (token == ')')
        {
            while (conversionStack.top()->getData() != '(')
            {
                // Get the top element from the stack
                item = conversionStack.pop();
                // Append the data it holds to the postfix string
                postfix += item->getData();
                delete item;
            }
            //Get rid of the '('
            item = conversionStack.pop();
            delete item;
        }

            //CASE 4: operators
        else if (token == '*' || token == '+' || token == '-' || token == '/' || token == '%' || token == '^'){
            //This one has higher precedence
            if(conversionStack.isEmpty() ||
               conversionStack.top()->getData() == '(' ||
               comparePrecedence(token, conversionStack.top()->getData()) > 0){
                conversionStack.push(token);
            } else {
                while ( !conversionStack.isEmpty() && comparePrecedence(token, conversionStack.top()->getData()) <= 0 )
                {
                    item = conversionStack.pop();
                    postfix += item->getData();
                    delete item;
                }
                conversionStack.push(token);
            }
        }
    }
    while( !conversionStack.isEmpty()){
        item = conversionStack.pop();
        postfix += item->getData();
        delete item;
    }
}

int Postfix::evaluate() {
    int out;

    for(int i = 0; postfix.length(); i++){
        std::cout << postfix << std::endl;
        char token = postfix[i];
        int res;
        switch(token) {
            case '^':
                res = pow(postfix[i - 2] - 48, postfix[i - 1] - 48);
                break;
            case '*':
                res = (postfix[i - 2] - 48 ) * (postfix[i - 1] - 48);
                break;
            case '/':
                res = postfix[i - 2] / postfix[i - 1];
                break;
            case '%':
                res = postfix[i - 2] % postfix[i - 1];
                break;
            case '+':
                res = postfix[i - 2] + postfix[i - 1];
                break;
            case '-':
                res = (postfix[i - 2] - 48) - (postfix[i - 1] - 48);
                break;
            default:
                continue;
        }
        std::cout << "Pre: \"" << postfix.substr(0, postfix[i-2]) << "\"" << std::endl;
        std::cout << "Num: \"" << std::to_string(res) << "\"" << std::endl;
        std::cout << "Pos: \"" << postfix.substr(i, postfix.length()) << "\"" << std::endl;
        postfix = postfix.substr(0, postfix[i-2]) + std::to_string(res) + postfix.substr(i+1, postfix.length());
    }
    return out;
}

void Postfix::setPostfix(std::string inpt) {
    postfix = inpt;
}
