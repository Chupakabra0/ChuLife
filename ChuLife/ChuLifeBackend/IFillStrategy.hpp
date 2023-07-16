#pragma once
#include "Array2D.hpp"

struct IFillStrategy {
public:
    virtual ~IFillStrategy()                     = default;
    virtual void FillField(Array2D<char>& field) = 0;
};
