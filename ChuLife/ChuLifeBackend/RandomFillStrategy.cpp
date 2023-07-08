#include "RandomFillStrategy.hpp"

void RandomFillStrategy::FillField(Array2D<char>& field) {
	for (size_t i = 0u; i < field.RowsCount(); ++i) {
		for (size_t j = 0u; j < field.ColsCount(); ++j) {
			field.Element(i, j) = this->GeneratNextChar_();
		}
	}
}

char RandomFillStrategy::GeneratNextChar_() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::bernoulli_distribution dist;

	char result = dist(mt) ? LIFE_CELL : DEAD_CELL;

	return result;
}
