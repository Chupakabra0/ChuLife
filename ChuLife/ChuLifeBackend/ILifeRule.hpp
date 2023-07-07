#pragma once
#include <memory>
#include <stdexcept>

#include "Array2D.hpp"
#include "Consts.hpp"

struct ILifeRule {
public:
	virtual ~ILifeRule()                                                 = default;
	virtual char Execute(const Array2D<char>& array, int rowNum, int colNum) = 0;
};

class BasicRule : public ILifeRule {
public:
	BasicRule() = delete;

	explicit BasicRule(size_t lifeLimit, size_t deadLimit)
		: lifeLimit_(lifeLimit), deadLimit_(deadLimit) {

	}

	~BasicRule() override = default;

	char Execute(const Array2D<char>& array, int rowNum, int colNum) override {
		if (array.RowsCount() <= rowNum || array.ColsCount() <= colNum) {
			throw std::runtime_error("array.RowsCount() > rowNum || array.ColsCount() > colNum");
		}

		char first = rowNum - 1 < 0 || colNum - 1 < 0 ?
			ERR_CELL :
			array.Element(static_cast<size_t>(rowNum - 1), static_cast<size_t>(colNum - 1));
		char second = rowNum - 1 < 0 ?
			ERR_CELL :
			array.Element(static_cast<size_t>(rowNum - 1), static_cast<size_t>(colNum));
		char third = rowNum - 1 < 0 || colNum + 1 > array.ColsCount() ?
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
		char eighth = rowNum + 1 >= array.RowsCount() || colNum + 1 >= array.RowsCount() ?
			ERR_CELL :
			array.Element(static_cast<size_t>(rowNum + 1), static_cast<size_t>(colNum + 1));

		switch (array.Element(rowNum, colNum)) {
			case DEAD_CELL: {
				if (static_cast<size_t>(first == LIFE_CELL) + static_cast<size_t>(second == LIFE_CELL) +
					static_cast<size_t>(third == LIFE_CELL) + static_cast<size_t>(fourth == LIFE_CELL) +
					static_cast<size_t>(fifth == LIFE_CELL) + static_cast<size_t>(sixth == LIFE_CELL) +
					static_cast<size_t>(seventh == LIFE_CELL) + static_cast<size_t>(eighth == LIFE_CELL) > this->lifeLimit_) {
					return LIFE_CELL;
				}

				return DEAD_CELL;
			}
			case LIFE_CELL: {
				if (static_cast<size_t>(first == DEAD_CELL) + static_cast<size_t>(second == DEAD_CELL) +
					static_cast<size_t>(third == DEAD_CELL) + static_cast<size_t>(fourth == DEAD_CELL) +
					static_cast<size_t>(fifth == DEAD_CELL) + static_cast<size_t>(sixth == DEAD_CELL) +
					static_cast<size_t>(seventh == DEAD_CELL) + static_cast<size_t>(eighth == DEAD_CELL) > this->deadLimit_) {
					return DEAD_CELL;
				}

				return LIFE_CELL;
			}
			default: {
				return ERR_CELL;
			}
		}
	}

private:
	size_t lifeLimit_;
	size_t deadLimit_;
};
