#include <iostream>
#include <memory>

#include "GameField.hpp"
#include "BasicRule.hpp"
#include "ConsoleRenderGame.hpp"
#include "OpenGLRenderGame.hpp"

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
	std::unique_ptr<IRenderGame> renderGame(new ConsoleRenderGame(std::cout));

	for (int i = 0; i < 10; ++i) {
		std::cout << i + 1 << " iteration\n";
		renderGame->RenderGame(gameField);
		gameField.NextField(gameRule.get());
	}

	return EXIT_SUCCESS;
}
