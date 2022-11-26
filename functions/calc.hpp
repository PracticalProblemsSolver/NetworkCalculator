/*! \file    calc.hpp
 *
 *  \brief   Header file for calc.cpp
 *
 *  \details Contains signatures for calculator functions.
 */
#ifndef CALC_H
#define CALC_H

#include <limits>

const float CALC_FAIL = std::numeric_limits<float>::min();

float calculate(std::string expression);

#endif
