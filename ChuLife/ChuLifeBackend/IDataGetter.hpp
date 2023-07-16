#pragma once

struct IDataGetter {
public:
    virtual ~IDataGetter() = default;

    virtual size_t GetLifeLimit() = 0;
    virtual size_t GetDeadLimit() = 0;

    virtual int GetWindowHeight() = 0;
    virtual int GetWindowWidth()  = 0;

    virtual int GetGameRowsCount() = 0;
    virtual int GetGameColsCount() = 0;
};
