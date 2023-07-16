#pragma once
#include "GameField.hpp"

struct IRenderGame {
public:
    virtual ~IRenderGame()								  = default;
    virtual void RenderGame(const GameField& gameField)   = 0;
};
