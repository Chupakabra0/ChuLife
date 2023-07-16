#include "BasicRule.hpp"

BasicRule::BasicRule(size_t lifeLimit, size_t deadLimit)
    : lifeLimit_(lifeLimit), deadLimit_(deadLimit) {

}

char BasicRule::Execute(const Array2D<char>& array, int rowNum, int colNum) {
    if (array.RowsCount() <= rowNum || array.ColsCount() <= colNum) {
        throw std::runtime_error("array.RowsCount() > rowNum || array.ColsCount() > colNum");
    }

    char first = rowNum - 1 < 0 || colNum - 1 < 0 ?
        ERR_CELL :
        array.Element(static_cast<size_t>(rowNum - 1), static_cast<size_t>(colNum - 1));
    char second = rowNum - 1 < 0 ?
        ERR_CELL :
        array.Element(static_cast<size_t>(rowNum - 1), static_cast<size_t>(colNum));
    char third = rowNum - 1 < 0 || colNum + 1 >= array.ColsCount() ?
        ERR_CELL :
        array.Element(static_cast<size_t>(rowNum - 1), static_cast<size_t>(colNum + 1));
    char fourth = colNum - 1 < 0 ?
        ERR_CELL :
        array.Element(static_cast<size_t>(rowNum), static_cast<size_t>(colNum - 1));
    char fifth = colNum + 1 >= array.ColsCount() ?
        ERR_CELL :
        array.Element(static_cast<size_t>(rowNum), static_cast<size_t>(colNum + 1));
    char sixth = rowNum + 1 >= array.RowsCount() || colNum - 1 < 0 ?
        ERR_CELL :
        array.Element(static_cast<size_t>(rowNum + 1), static_cast<size_t>(colNum - 1));
    char seventh = rowNum + 1 >= array.RowsCount() ?
        ERR_CELL :
        array.Element(static_cast<size_t>(rowNum + 1), static_cast<size_t>(colNum));
    char eighth = rowNum + 1 >= array.RowsCount() || colNum + 1 >= array.ColsCount() ?
        ERR_CELL :
        array.Element(static_cast<size_t>(rowNum + 1), static_cast<size_t>(colNum + 1));

    const size_t lifeCount =
        static_cast<size_t>(first == LIFE_CELL) +
        static_cast<size_t>(second == LIFE_CELL) +
        static_cast<size_t>(third == LIFE_CELL) +
        static_cast<size_t>(fourth == LIFE_CELL) +
        static_cast<size_t>(fifth == LIFE_CELL) +
        static_cast<size_t>(sixth == LIFE_CELL) +
        static_cast<size_t>(seventh == LIFE_CELL) +
        static_cast<size_t>(eighth == LIFE_CELL);

    switch (array.Element(rowNum, colNum)) {
        case DEAD_CELL: {
            if (lifeCount >= this->lifeLimit_) {
                return LIFE_CELL;
            }

            return DEAD_CELL;
        }
        case LIFE_CELL: {
            if (lifeCount <= this->deadLimit_) {
                return DEAD_CELL;
            }

            return LIFE_CELL;
        }
        default: {
            return ERR_CELL;
        }
    }
}
