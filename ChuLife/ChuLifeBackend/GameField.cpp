#include "GameField.hpp"

GameField::GameField(size_t rowsCount, size_t colsCount)
    : GameField(rowsCount, colsCount, nullptr) {

}

GameField::GameField(size_t rowsCount, size_t colsCount, IFillStrategy* fillStrategy)
    : fillStrategy_(fillStrategy), field_(rowsCount, colsCount, ERR_CELL) {
    if (this->fillStrategy_ != nullptr) {
        this->fillStrategy_->FillField(this->field_);
    }
}

GameField::GameField(const Array2D<char>& field)
    : fillStrategy_(nullptr), field_(field) {

}

const Array2D<char>& GameField::GetArray() const {
    return this->field_;
}

void GameField::NextField(ILifeRule* lifeRule) {
    if (lifeRule == nullptr) {
        return;
    }

    Array2D<char> temp(this->field_.RowsCount(), this->field_.ColsCount());

    for (size_t i = 0u; i < this->field_.RowsCount(); ++i) {
        for (size_t j = 0u; j < this->field_.ColsCount(); ++j) {
            temp.Element(i, j) = lifeRule->Execute(this->field_, static_cast<int>(i), static_cast<int>(j));
        }
    }

    std::swap(temp, this->field_);
}
