#include <iostream>
#include <memory>
#include <chrono>

#include "GameField.hpp"
#include "RandomFillStrategy.hpp"
#include "BasicRule.hpp"
#include "ConsoleRenderGame.hpp"
#include "OpenGLRenderGame.hpp"
#include "Timer.hpp"
#include "DefaultDataGetter.hpp"

int main(int argc, char* argv[]) {
    std::unique_ptr<IDataGetter> dataGetter(new DefaultDataGetter());

    GameField gameField(dataGetter->GetGameRowsCount(), dataGetter->GetGameColsCount(), new RandomFillStrategy());

    const size_t lifeLimit = dataGetter->GetLifeLimit();
    const size_t deadLimit = dataGetter->GetDeadLimit();
    const int windowHeight = dataGetter->GetWindowHeight();
    const int windowWidth  = dataGetter->GetWindowWidth();

    auto renderTimer     = std::make_unique<Timer>();
    auto fpsCounterTimer = std::make_unique<Timer>();

    auto* renderer = new OpenGLRenderer();
    auto* window   = new OpenGLWindow(windowWidth, windowHeight, "Test");

    //renderer->SetProjectionMatrix(
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
    const double framesPerSecond       = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(1)).count()
        / static_cast<double>(milisecondsLimit);
    
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
