#include <iostream>
#include <memory>

#include "GameField.h"
#include "ILifeRule.hpp"

int main() {
	GameField gameField(7u, 7u, new RandomFillStrategy());

	const size_t lifeLimit = 3u;
	const size_t deadLimit = 3u;
	std::unique_ptr<ILifeRule> gameRule(new BasicRule(lifeLimit, deadLimit));

	for (int i = 0; i < 10; ++i) {
		std::cout << i + 1 << " iteration\n" << gameField;
		gameField.NextField(gameRule.get());
	}

	return EXIT_SUCCESS;
}
