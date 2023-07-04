#pragma once
#include <vector>

template<class T>
class Array2D {
public:
	using value_type      = T;
	using reference       = value_type&;
	using const_reference = const value_type&;
	using pointer         = value_type*;
	using const_pointer   = const value_type*;
	using size_type       = size_t;
	using difference_type = std::ptrdiff_t;

	Array2D() = delete;

	explicit Array2D(size_type rowsCount, size_type colsCount)
		: Array2D(rowsCount, colsCount, value_type{}) {

	}

	explicit Array2D(size_type rowsCount, size_type colsCount, const_reference val)
		: rowsCount_(rowsCount), colsCount_(colsCount), data_(rowsCount * colsCount, val) {

	}

	Array2D(const std::initializer_list<std::initializer_list<value_type>>& initList)
		: Array2D(initList.size(), initList.begin()->size()) {
		auto kter = this->data_.begin();
		for (auto iter = initList.begin(); iter != initList.end(); iter = std::next(iter)) {
			for (auto jter = iter->begin(); jter != iter->end(); jter = std::next(jter)) {
				*kter++ = *jter;
			}
		}
	}

	Array2D(const Array2D& copy)
		: Array2D(copy.rowsCount_, copy.colsCount_) {
		auto iter = this->data_.begin();
		for (const auto& el : copy.data_) {
			*iter++ = el;
		}
	}

	Array2D(Array2D&& move) noexcept {
		std::swap(move.rowsCount_, this->rowsCount_);
		std::swap(move.colsCount_, this->colsCount_);
		std::swap(move.data_, this->data_);
	}

	~Array2D() = default;

	Array2D& operator=(const Array2D& copy) {
		this->data_.clear();
		this->data_.resize(copy.TotalCount());

		auto iter = this->data_.begin();
		for (const auto& el : copy.data_) {
			*iter++ = el;
		}
	}

	Array2D& operator=(Array2D&& move) noexcept {
		std::swap(move.rowsCount_, this->rowsCount_);
		std::swap(move.colsCount_, this->colsCount_);
		std::swap(move.data_, this->data_);
	}

	friend std::ostream& operator<<(std::ostream& out, const Array2D& arr) {
		for (size_t i = 0u; i < arr.RowsCount(); ++i) {
			for (size_t j = 0u; j < arr.ColsCount(); ++j) {
				out << arr.Element(i, j) << " ";
			}

			out << std::endl;
		}

		return out;
	}

	friend bool operator==(const Array2D& first, const Array2D& second) {
		return first.rowsCount_ == second.rowsCount_ && first.colsCount_ == second.colsCount_ && first.data_ == second.data_;
	}

	friend bool operator!=(const Array2D& first, const Array2D& second) {
		return !(first == second);
	}

	const_reference Element(size_type i, size_type j) const {
		return this->data_[i * (this->rowsCount_ + 1) + j];
	}

	reference Element(size_type i, size_type j) {
		return this->data_[i * (this->rowsCount_ + 1) + j];
	}

	size_type TotalCount() const {
		return this->rowsCount_ * this->colsCount_;
	}

	size_type RowsCount() const {
		return this->rowsCount_;
	}

	size_type ColsCount() const {
		return this->colsCount_;
	}

	void Clear() {
		this->data_.clear();
	}

private:
	size_type rowsCount_;
	size_type colsCount_;
	std::vector<value_type> data_;
};
