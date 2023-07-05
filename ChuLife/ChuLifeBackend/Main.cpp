#include <iostream>
#include <memory>

#include "GameField.h"

int main() {
	GameField gameField(5u, 5u, new RandomFillStrategy());

	std::cout << gameField;

	return EXIT_SUCCESS;
}
