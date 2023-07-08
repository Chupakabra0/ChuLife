#pragma once
#include <memory>
#include <stdexcept>

#include "ILifeRule.hpp"
#include "Consts.hpp"

class BasicRule : public ILifeRule {
public:
	BasicRule() = delete;

	explicit BasicRule(size_t lifeLimit, size_t deadLimit);

	~BasicRule() override = default;

	char Execute(const Array2D<char>& array, int rowNum, int colNum) override;

private:
	size_t lifeLimit_;
	size_t deadLimit_;
};
