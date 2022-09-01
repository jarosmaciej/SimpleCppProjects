#include <iostream>
#include <stack>
#include "infixToPostfix.h"

int Priority(char c) {
    if (c == '~')
        return 2;
    else if (c == 'v' || c == '^')
        return 1;
    else if (c == 'I' || c == 'E')
        return 0;
    else return -1;
}

std::string infixToPosfix(std::string infix) {
    std::stack<char> stk;
    std::string postfix;
    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == '0' || infix[i] == '1' || infix[i] == 'p' || infix[i] == 'q' || infix[i] == 'r')
            postfix += infix[i];
        else if (infix[i] == '(')
            stk.push('(');
        else if (infix[i] == ')') {
            while (stk.top() != '(') {
                postfix += stk.top();
                stk.pop();
            }
            stk.pop();
        }
        else {
            while (!stk.empty() && Priority(infix[i]) <= Priority(stk.top())) {
                postfix += stk.top();
                stk.pop();
            }
            stk.push(infix[i]);
        }
    }
    while (!stk.empty()) {
        postfix += stk.top();
        stk.pop();
    }
    return postfix;
}