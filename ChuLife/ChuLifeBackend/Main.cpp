#include <iostream>
#include <memory>
#include <chrono>

#include "GameField.hpp"
#include "RandomFillStrategy.hpp"
#include "BasicRule.hpp"
#include "ConsoleRenderGame.hpp"
#include "OpenGLRenderGame.hpp"

int main() {
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

    std::unique_ptr<ILifeRule> gameRule(new BasicRule(lifeLimit, deadLimit));
    std::unique_ptr<IRenderGame> renderGame(new OpenGLRenderGame(window, renderer));

    const std::time_t milisecondsLimit = 16ll;
    auto begin                         = std::chrono::system_clock::now();
    auto end                           = std::chrono::system_clock::now();

    while (!window->WindowShouldClose()) {
        end = std::chrono::system_clock::now();

        if (std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() > milisecondsLimit) {
            renderGame->RenderGame(gameField);
            gameField.NextField(gameRule.get());

            window->SwapBuffers();

            begin = std::chrono::system_clock::now();
        }

        window->PollEvents();
    }

    return EXIT_SUCCESS;
}
