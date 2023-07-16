#include "DefaultDataGetter.hpp"
#include "Consts.hpp"

size_t DefaultDataGetter::GetLifeLimit() {
    return static_cast<size_t>(DEFAULT_LIFE_LIMIT);
}

size_t DefaultDataGetter::GetDeadLimit() {
    return static_cast<size_t>(DEFAULT_DEAD_LIMIT);
}

int DefaultDataGetter::GetWindowHeight() {
    return DEFAULT_WINDOW_HEIGHT;
}

int DefaultDataGetter::GetWindowWidth() {
    return DEFAULT_WINDOW_WIDTH;
}

int DefaultDataGetter::GetGameRowsCount() {
    return DEFAULT_GAME_ROWS_COUNT;
}

int DefaultDataGetter::GetGameColsCount() {
    return DEFAULT_GAME_COLS_COUNT;
}
