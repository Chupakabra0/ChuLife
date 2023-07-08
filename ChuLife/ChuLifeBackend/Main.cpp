#include <iostream>
#include <memory>

#include "GameField.h"
#include "ILifeRule.hpp"

int main() {
	GameField gameField(Array2D<char>{
		std::initializer_list{
			DEAD_CELL, DEAD_CELL, DEAD_CELL, DEAD_CELL
		},
		{
			DEAD_CELL, LIFE_CELL, DEAD_CELL, DEAD_CELL
		},
		{
			DEAD_CELL, LIFE_CELL, DEAD_CELL, DEAD_CELL
		},
		{
			DEAD_CELL, LIFE_CELL, DEAD_CELL, DEAD_CELL
		},
		{
			DEAD_CELL, DEAD_CELL, DEAD_CELL, DEAD_CELL
		}
	});

	const size_t lifeLimit = 3u;
	const size_t deadLimit = 1u;
	std::unique_ptr<ILifeRule> gameRule(new BasicRule(lifeLimit, deadLimit));

	for (int i = 0; i < 10; ++i) {
		std::cout << i + 1 << " iteration\n" << gameField;
		gameField.NextField(gameRule.get());
	}

	return EXIT_SUCCESS;
}
