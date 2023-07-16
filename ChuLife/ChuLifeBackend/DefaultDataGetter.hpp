#pragma once
#include "IDataGetter.hpp"

class DefaultDataGetter : public IDataGetter {
public:
    ~DefaultDataGetter() override = default;

private:
    virtual size_t GetLifeLimit() override;
    virtual size_t GetDeadLimit() override;

    virtual int GetWindowHeight() override;
    virtual int GetWindowWidth() override;

    virtual int GetGameRowsCount() override;
    virtual int GetGameColsCount() override;
};
