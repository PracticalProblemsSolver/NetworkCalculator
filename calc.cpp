/*! \file    calc.cpp
 *
 *  \brief   File with calculator functions.
 *
 *  \details Contains server calculation functions.
 */
#include <vector>
#include <string>
#include <cstring>
#include "calc.hpp"

/*! \brief   String splitting function.
 *
 *  \details Splits given string by given separator symbol.
 *
 *  \param   str String.
 *
 *  \param   sep Char separator symbol.
 * */
std::vector<std::string> split(std::string str, char sep) {
    std::vector<std::string> string_vector;
    bool pivot = false;
    std::string part1;
    std::string part2;
    for (char i: str) {
        if (i != sep && !pivot) {
            part1 += i;
        } else if (i == sep) {
            string_vector.push_back(part1);
            pivot = true;
        } else if (i != sep && pivot) {
            part2 += i;
        }
    }
    string_vector.push_back(part2);
    return string_vector;
}

/*! \brief   Calculation function.
 *
 *  \details Calculates a given string expression with two numbers.
 *
 *  \param   expression   A string expression to calculate with
 *                        two numbers, operation and without spaces.
 *
 *  \return  res          Result.
 * */
float calculate(std::string expression) {
    float res, num1, num2;
    if (strstr(expression.c_str(), "+")) {
        num1 = atof(split(expression, '+')[0].c_str());
        num2 = atof(split(expression, '+')[1].c_str());
        res = num1 + num2;
    } else if (strstr(expression.c_str(), "-")) {
        num1 = atof(split(expression, '-')[0].c_str());
        num2 = atof(split(expression, '-')[1].c_str());
        res = num1 - num2;
    } else if (strstr(expression.c_str(), "*")) {
        num1 = atof(split(expression, '*')[0].c_str());
        num2 = atof(split(expression, '*')[1].c_str());
        res = num1 * num2;
    } else if (strstr(expression.c_str(), "/")) {
        num1 = atof(split(expression, '/')[0].c_str());
        num2 = atof(split(expression, '/')[1].c_str());
        res = num1 / num2;
    } else {
        res = CALC_FAIL;
    }
    return res;
}
