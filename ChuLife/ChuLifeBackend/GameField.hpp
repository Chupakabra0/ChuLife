#pragma once
#include <memory>
#include <string>

#include "Consts.hpp"
#include "Array2D.hpp"
#include "ILifeRule.hpp"
#include "IFillStrategy.hpp"

class GameField {
public:
    GameField() = delete;

    explicit GameField(size_t rowsCount, size_t colsCount);

    explicit GameField(size_t rowsCount, size_t colsCount, IFillStrategy* fillStrategy);

    explicit GameField(const Array2D<char>& field);

    ~GameField() = default;

    const Array2D<char>& GetArray() const;

    void NextField(ILifeRule* lifeRule);

private:
    std::unique_ptr<IFillStrategy> fillStrategy_;
    Array2D<char> field_;
};
