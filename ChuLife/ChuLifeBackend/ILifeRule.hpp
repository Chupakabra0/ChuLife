#pragma once
#include "Array2D.hpp"

struct ILifeRule {
public:
    virtual ~ILifeRule()                                                     = default;
    virtual char Execute(const Array2D<char>& array, int rowNum, int colNum) = 0;
};
