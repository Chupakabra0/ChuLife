#pragma once
#include <argparse/argparse.hpp>

#include "IDataGetter.hpp"
#include "Consts.hpp"

class ArgsDataGetter : public IDataGetter {
public:
    ArgsDataGetter() = delete;

    explicit ArgsDataGetter(int argc, char* argv[], const std::string& programName = "") {
        this->InitArgumentParser_(argc, argv, programName);
        this->ValidateAllArguments_();
    }

    ~ArgsDataGetter() override = default;

    virtual size_t GetLifeLimit() override;
    virtual size_t GetDeadLimit() override;

    virtual int GetWindowHeight() override;
    virtual int GetWindowWidth() override;

    virtual int GetGameRowsCount() override;
    virtual int GetGameColsCount() override;

private:
    static constexpr const char* WindowHeightShortArgName = "-wh";
    static constexpr const char* WindowHeightLongArgName  = "--window-height";
    static constexpr const char* WindowWidthShortArgName  = "-ww";
    static constexpr const char* WindowWidthLongArgName   = "--window-width";
    static constexpr const char* GameRowsShortArgName     = "-gr";
    static constexpr const char* GameRowsLongArgName      = "--game-rows";
    static constexpr const char* GameColsShortArgName     = "-gc";
    static constexpr const char* GameColsLongArgName      = "--game-cols";
    static constexpr const char* LifeLimitShortArgName    = "-ll";
    static constexpr const char* LifeLimitLongArgName     = "--life-lim";
    static constexpr const char* DeadLimitShortArgName    = "-dl";
    static constexpr const char* DeadLimitLongArgName     = "--dead-lim";
    
    std::unique_ptr<argparse::ArgumentParser> argumentParser_{};

    void InitArgumentParser_(int argc, char* argv[], const std::string& programName);

    bool ValidateAllArguments_();
    bool ValidateWindowHeight();
    bool ValidateWindowWidth();
    bool ValidateGameRowsCount();
    bool ValidateGameColsCount();
    bool ValidateLifeLimit();
    bool ValidateDeadLimit();
};
