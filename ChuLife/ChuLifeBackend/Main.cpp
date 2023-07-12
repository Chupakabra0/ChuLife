#include <iostream>
#include <memory>
#include <chrono>

#include "GameField.hpp"
#include "RandomFillStrategy.hpp"
#include "BasicRule.hpp"
#include "ConsoleRenderGame.hpp"
#include "OpenGLRenderGame.hpp"

#include <glm/gtx/string_cast.hpp>

int main() {
	//GameField gameField(Array2D<char>{
	//	std::initializer_list{
	//		DEAD_CELL, DEAD_CELL, DEAD_CELL, DEAD_CELL, DEAD_CELL
	//	},
	//	{
	//		DEAD_CELL, LIFE_CELL, DEAD_CELL, LIFE_CELL, DEAD_CELL
	//	},
	//	{
	//		DEAD_CELL, LIFE_CELL, DEAD_CELL, DEAD_CELL, DEAD_CELL
	//	},
	//	{
	//		DEAD_CELL, LIFE_CELL, DEAD_CELL, LIFE_CELL, DEAD_CELL
	//	},
	//	{
	//		DEAD_CELL, DEAD_CELL, DEAD_CELL, DEAD_CELL, DEAD_CELL
	//	}
	//});
	GameField gameField(72, 128, new RandomFillStrategy());

	const size_t lifeLimit = 5u;
	const size_t deadLimit = 3u;
	const int windowHeight = 720;
	const int windowWidth  = 1280;

	auto* renderer = new OpenGLRenderer();
	auto* window   = new OpenGLWindow(windowWidth, windowHeight, "Test");

	//renderer->SetViewMatrix(
	//	glm::mat4(
	//		2.0f / windowWidth, 0.0f, 0.0f, 0.0f,
	//		0.0f, -2.0f / windowHeight, 0.0f, 0.0f,
	//		0.0f, 0.0f, 1.0f, 0.0f,
	//		-1.0f, 1.0f, 0.0f, 1.0f
	//	)
	//);

	renderer->SetProjectionMatrix(glm::ortho(0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight), 0.0f));

	std::cout << glm::to_string(renderer->GetViewMatrix()) << std::endl;

	std::unique_ptr<ILifeRule> gameRule(new BasicRule(lifeLimit, deadLimit));
	std::unique_ptr<IRenderGame> renderGame(new OpenGLRenderGame(window, renderer));

	const std::time_t milisecondsLimit = 16ll;
	auto begin                         = std::chrono::system_clock::now();
	auto end                           = std::chrono::system_clock::now();

	while (!glfwWindowShouldClose(window->GetUniqueHandle().get())) {
		end = std::chrono::system_clock::now();

		if (std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() > milisecondsLimit) {
			renderGame->RenderGame(gameField);
			gameField.NextField(gameRule.get());

			glfwSwapBuffers(window->GetUniqueHandle().get());

			begin = std::chrono::system_clock::now();
		}

		glfwPollEvents();
	}

	//std::unique_ptr<IRenderGame> renderGame(new ConsoleRenderGame(std::cout));

	//for (int i = 0; i < 10; ++i) {
	//	std::cout << i + 1 << " iteration\n";
	//	renderGame->RenderGame(gameField);
	//	gameField.NextField(gameRule.get());
	//}

	return EXIT_SUCCESS;
}
