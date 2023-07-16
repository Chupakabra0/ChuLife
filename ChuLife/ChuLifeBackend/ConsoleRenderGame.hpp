#pragma once
#include <iostream>

#include "IRenderGame.hpp"

class ConsoleRenderGame : public IRenderGame {
public:
    ConsoleRenderGame() = delete;

    explicit ConsoleRenderGame(std::ostream& out)
        : out_(out) {

    }

    ~ConsoleRenderGame() override = default;

    void RenderGame(const GameField& gameField) override {
        this->out_.get() << std::string(10u, '-') + "\n" << gameField.GetArray() << std::string(10u, '-') + '\n';
    }

private:
    std::reference_wrapper<std::ostream> out_;
};
