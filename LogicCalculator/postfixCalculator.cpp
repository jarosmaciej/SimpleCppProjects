#include <iostream>
#include <stack>
#include "postfixCalculator.h"

bool Operations(bool a, bool b, char op) {
    switch (op)
    {
    case 'v':
        if (a == 1 || b == 1)
            return 1;
        else return 0;
    case '^':
        if (a == 0 || b == 0)
            return 0;
        else return 1;
    case 'I':
        if (a == 1 || b == 0)
            return 1;
        else return 0;
    case 'E':
        if (a == b)
            return 1;
        else return 0;
    }
}

void howManyVariables(std::string exp, bool &hasP, bool &hasQ, bool &hasR) {
    for (int i = 0; i < exp.length() - 1; i++)
        if (exp[i] == 'p') {
            hasP = true;
            break;
        }
    for (int i = 0; i < exp.length() - 1; i++)
        if (exp[i] == 'q') {
            hasQ = true;
            break;
        }
    for (int i = 0; i < exp.length() - 1; i++)
        if (exp[i] == 'r') {
            hasR = true;
            break;
        }
}

bool Result(std::string exp) {
    bool a, b;
    std::stack<bool> stk;

    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '~') {
            a = stk.top();
            stk.pop();
            stk.push(!a);
        }            
        else if (exp[i] == '1' || exp[i] == '0') {
            if (exp[i] == '1')
                stk.push(1);
            else stk.push(0);
        }
        else {
            a = stk.top();
            stk.pop();
            b = stk.top();
            stk.pop();
            stk.push(Operations(a, b, exp[i]));
        }

    }
    return stk.top();
}

void truthTable(std::string exp, bool hasP, bool hasQ, bool hasR) {
    std::string temp = exp;
    char v = '0';
    if (hasP == true && hasQ == false && hasR == false) {
        std::cout << "| p | result\n";
        for (int i = 0; i < 2; i++) {
            if (i == 1)
                v = '1';
            for (int j = 0; j < exp.length() - 1; j++)
                if (exp[j] == 'p')
                    temp[j] = v;
            std::cout << "| " << v << " | " << Result(temp) << "\n";
        }
    }
    else if (hasP == false && hasQ == true && hasR == false) {
        std::cout << "| q | result\n";
        for (int i = 0; i < 2; i++) {
            if (i == 1)
                v = '1';
            for (int j = 0; j < exp.length() - 1; j++)
                if (exp[j] == 'q')
                    temp[j] = v;
            std::cout << "| " << v << " | " << Result(temp) << "\n";
        }
    }
    else if (hasP == false && hasQ == false && hasR == true) {
        std::cout << "| r | result\n";
        for (int i = 0; i < 2; i++) {
            if (i == 1)
                v = '1';
            for (int j = 0; j < exp.length() - 1; j++)
                if (exp[j] == 'r')
                    temp[j] = v;
            std::cout << "| " << v << " | " << Result(temp) << "\n";
        }
    }
    else if (hasP == true && hasQ == true && hasR == false) {
        char v2;
        std::cout << "| p | q | result\n";
        for (int i = 0; i < 4; i++) {
            if (i == 2)
                v = '1';
            if (i % 2 == 0)
                v2 = '0';
            else v2 = '1';
            for (int j = 0; j < exp.length() - 1; j++)
                if (exp[j] == 'p')
                    temp[j] = v;
                else if (exp[j] == 'q')
                    temp[j] = v2;
            std::cout << "| " << v << " | " << v2 << " | " << Result(temp) << "\n";
        }
    }
    else if (hasP == true && hasQ == false && hasR == true) {
        char v2;
        std::cout << "| p | r | result\n";
        for (int i = 0; i < 4; i++) {
            if (i == 2)
                v = '1';
            if (i % 2 == 0)
                v2 = '0';
            else v2 = '1';
            for (int j = 0; j < exp.length() - 1; j++)
                if (exp[j] == 'p')
                    temp[j] = v;
                else if (exp[j] == 'r')
                    temp[j] = v2;
            std::cout << "| " << v << " | " << v2 << " | " << Result(temp) << "\n";
        }
    }
    else if (hasP == false && hasQ == true && hasR == true) {
        char v2;
        std::cout << "| q | r | result\n";
        for (int i = 0; i < 4; i++) {
            if (i == 2)
                v = '1';
            if (i % 2 == 0)
                v2 = '0';
            else v2 = '1';
            for (int j = 0; j < exp.length() - 1; j++)
                if (exp[j] == 'q')
                    temp[j] = v;
                else if (exp[j] == 'r')
                    temp[j] = v2;
            std::cout << "| " << v << " | " << v2 << " | " << Result(temp) << "\n";
        }
    }
    else {
        char v2, v3;
        std::cout << "| p | q | r | result\n";
        for (int i = 0; i < 8; i++) {
            if (i == 4)
                v = '1';
            if (i % 4 == 0)
                v2 = '0';
            else if (i % 4 == 2)
                v2 = '1';
            if (i % 2 == 0)
                v3 = '0';
            else v3 = '1';

            for (int j = 0; j < exp.length() - 1; j++)
                if (exp[j] == 'p')
                    temp[j] = v;
                else if (exp[j] == 'q')
                    temp[j] = v2;
                else if (exp[j] == 'r')
                    temp[j] = v3;
            std::cout << "| " << v << " | " << v2 << " | " << v3 << " | " << Result(temp) << "\n";
        }
    }
}

void postfixCalculator(std::string exp) {
    bool hasP = false, hasQ = false, hasR = false;
    howManyVariables(exp, hasP, hasQ, hasR);
    if (hasP == false && hasQ == false && hasR == false)
        std::cout << "Result: " << Result(exp);
    else
        truthTable(exp, hasP, hasQ, hasR);
}