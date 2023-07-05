#include "GameField.h"

GameField::GameField(size_t rowsCount, size_t colsCount, IFillStrategy* fillStrategy)
	: fillStrategy_(fillStrategy), field_(rowsCount, colsCount, ERR_CELL) {
	if (this->fillStrategy_ != nullptr) {
		this->fillStrategy_->FillField(this->field_);
	}
}
