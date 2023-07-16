#include <iostream>
#include <memory>
#include <chrono>

#include "GameField.hpp"
#include "RandomFillStrategy.hpp"
#include "BasicRule.hpp"
#include "ConsoleRenderGame.hpp"
#include "OpenGLRenderGame.hpp"
#include "Timer.hpp"

int main() {
    GameField gameField(72, 128, new RandomFillStrategy());

    const size_t lifeLimit = 5u;
    const size_t deadLimit = 3u;
    const int windowHeight = 720;
    const int windowWidth  = 1280;

    auto renderTimer     = std::make_unique<Timer>();
    auto fpsCounterTimer = std::make_unique<Timer>();

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

    const std::time_t milisecondsLimit = 12ll;
    const double framesPerSecond       = 1000.0 / static_cast<double>(milisecondsLimit);
    
    long long framesCount = 0ll;

    std::cout << "Theoretical FPS: " << framesPerSecond << std::endl;

    while (!window->WindowShouldClose()) {
        renderTimer->FixEndTime();
        fpsCounterTimer->FixEndTime();

        if (renderTimer->GetDurationCount<std::chrono::milliseconds>() >= milisecondsLimit) {
            renderGame->RenderGame(gameField);
            gameField.NextField(gameRule.get());

            window->SwapBuffers();
            ++framesCount;

            renderTimer->FixBeginTime();
        }
        if (fpsCounterTimer->GetDurationCount<std::chrono::seconds>() >= 1ll) {
            std::cout << "FPS: " << framesCount << std::endl;

            framesCount = 0ll;
            fpsCounterTimer->FixBeginTime();
        }

        window->PollEvents();
    }

    return EXIT_SUCCESS;
}
