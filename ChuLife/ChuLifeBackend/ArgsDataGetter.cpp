#include "ArgsDataGetter.hpp"

size_t ArgsDataGetter::GetLifeLimit() {
    return this->argumentParser_->get<size_t>(ArgsDataGetter::LifeLimitShortArgName);
}

size_t ArgsDataGetter::GetDeadLimit() {
    return this->argumentParser_->get<size_t>(ArgsDataGetter::DeadLimitShortArgName);
}

int ArgsDataGetter::GetWindowHeight() {
    return this->argumentParser_->get<int>(ArgsDataGetter::WindowHeightShortArgName);
}

int ArgsDataGetter::GetWindowWidth() {
    return this->argumentParser_->get<int>(ArgsDataGetter::WindowWidthShortArgName);
}

int ArgsDataGetter::GetGameRowsCount() {
    return this->argumentParser_->get<int>(ArgsDataGetter::GameRowsShortArgName);
}

int ArgsDataGetter::GetGameColsCount() {
    return this->argumentParser_->get<int>(ArgsDataGetter::GameColsShortArgName);
}

void ArgsDataGetter::InitArgumentParser_(int argc, char* argv[], const std::string& programName) {
    this->argumentParser_ = std::make_unique<argparse::ArgumentParser>(programName);

    this->argumentParser_->add_description("OpenGL game life implementation");

    this->argumentParser_->add_argument(ArgsDataGetter::WindowHeightShortArgName, ArgsDataGetter::WindowHeightLongArgName)
        .help("Render window height")
        .scan<'i', int>()
        .default_value(DEFAULT_WINDOW_HEIGHT);

    this->argumentParser_->add_argument(ArgsDataGetter::WindowWidthShortArgName, ArgsDataGetter::WindowWidthLongArgName)
        .help("Render window width")
        .scan<'i', int>()
        .default_value(DEFAULT_WINDOW_WIDTH);

    this->argumentParser_->add_argument(ArgsDataGetter::GameRowsShortArgName, ArgsDataGetter::GameRowsLongArgName)
        .help("Count of rows on game board")
        .scan<'i', int>()
        .default_value(DEFAULT_GAME_ROWS_COUNT);

    this->argumentParser_->add_argument(ArgsDataGetter::GameColsShortArgName, ArgsDataGetter::GameColsLongArgName)
        .help("Count of columns on game board")
        .scan<'i', int>()
        .default_value(DEFAULT_GAME_COLS_COUNT);

    this->argumentParser_->add_argument(ArgsDataGetter::LifeLimitShortArgName, ArgsDataGetter::LifeLimitLongArgName)
        .help("Minimal count of alive cells that can produce new alive cell")
        .scan<'i', size_t>()
        .default_value(DEFAULT_LIFE_LIMIT);

    this->argumentParser_->add_argument(ArgsDataGetter::DeadLimitShortArgName, ArgsDataGetter::DeadLimitLongArgName)
        .help("Maximal count of alive cells that can't keep safe existing alive cell")
        .scan<'i', size_t>()
        .default_value(DEFAULT_DEAD_LIMIT);

    try {
        this->argumentParser_->parse_args(argc, argv);
    }
    catch (const std::exception&) {
        throw std::runtime_error("Parsing args error");
    }
}

bool ArgsDataGetter::ValidateAllArguments_() {
    if (!this->ValidateWindowHeight()) {
        throw std::runtime_error("Window height invalid value [x > 0]");
    }
    if (!this->ValidateWindowWidth()) {
        throw std::runtime_error("Window width invalid value [x > 0]");
    }
    if (!this->ValidateGameRowsCount()) {
        throw std::runtime_error("Game rows count invalid value [x > 0]");
    }
    if (!this->ValidateGameColsCount()) {
        throw std::runtime_error("Game columns count invalid value [x > 0]");
    }
    if (!this->ValidateLifeLimit()) {
        throw std::runtime_error("Life limit count invalid value [0 < x < 9]");
    }
    if (!this->ValidateDeadLimit()) {
        throw std::runtime_error("Dead limit count invalid value [0 < x < 9]");
    }

    return true;
}

inline bool ArgsDataGetter::ValidateWindowHeight() {
    return this->GetWindowHeight() > 0;
}

inline bool ArgsDataGetter::ValidateWindowWidth() {
    return this->GetWindowWidth() > 0;
}

inline bool ArgsDataGetter::ValidateGameRowsCount() {
    return this->GetGameRowsCount() > 0;
}

inline bool ArgsDataGetter::ValidateGameColsCount() {
    return this->GetGameColsCount() > 0;
}

inline bool ArgsDataGetter::ValidateLifeLimit() {
    return this->GetLifeLimit() > 0ull && this->GetLifeLimit() < 9ull;
}

inline bool ArgsDataGetter::ValidateDeadLimit() {
    return this->GetDeadLimit() > 0ull && this->GetDeadLimit() < 9ull;
}
