#include <iostream>
#include <memory>

#include "Array2D.hpp"

int main() {
	auto arr = std::make_unique<Array2D<int>>(std::initializer_list{ std::initializer_list{1, 2, 3}, {1, 2, 3} });

	int k = 0;
	for (size_t i = 0u; i < arr->RowsCount(); ++i) {
		for (size_t j = 0u; j < arr->ColsCount(); ++j) {
			arr->Element(i, j) = ++k;
		}
	}

	auto copy = std::make_unique<Array2D<int>>(*arr);

	std::cout << *arr << std::endl;
	std::cout << *copy << std::endl;

	arr.reset();

	std::cout << *copy << std::endl;

	return EXIT_SUCCESS;
}
