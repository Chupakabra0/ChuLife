#pragma once
#include <memory>
#include <random>

#include "IFillStrategy.hpp"
#include "Consts.hpp"

class RandomFillStrategy : public IFillStrategy {
public:
	explicit RandomFillStrategy() = default;

	~RandomFillStrategy() override = default;

	void FillField(Array2D<char>& field) override;

private:
	char GeneratNextChar_();
};
