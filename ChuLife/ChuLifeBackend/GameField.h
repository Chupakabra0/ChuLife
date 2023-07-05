#pragma once
#include <iostream>
#include <memory>
#include <random>

#include "Consts.hpp"
#include "Array2D.hpp"

struct IFillStrategy {
public:
	virtual ~IFillStrategy()                     = default;
	virtual void FillField(Array2D<char>& field) = 0;
};

class RandomFillStrategy : public IFillStrategy {
public:
	explicit RandomFillStrategy() = default;

	~RandomFillStrategy() override = default;

	void FillField(Array2D<char>& field) override {
		for (size_t i = 0u; i < field.RowsCount(); ++i) {
			for (size_t j = 0u; j < field.ColsCount(); ++j) {
				field.Element(i, j) = this->GeneratNextChar_();
			}
		}
	}

private:
	char GeneratNextChar_() {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::bernoulli_distribution dist;

		char result = dist(mt) ? LIFE_CELL : DEAD_CELL;

		return result;
	}
};

class GameField {
public:
	GameField() = delete;

	explicit GameField(size_t rowsCount, size_t colsCount)
		: GameField(rowsCount, colsCount, nullptr) {

	}

	explicit GameField(size_t rowsCount, size_t colsCount, IFillStrategy* fillStrategy);

	~GameField() = default;

	// TEMPORARY
	friend std::ostream& operator<<(std::ostream& out, const GameField& gameLife) {
		return out << std::string(10u, '-') + "\n" << gameLife.field_ << std::string(10u, '-') + '\n';
	}

private:
	std::unique_ptr<IFillStrategy> fillStrategy_;
	Array2D<char> field_;
};

