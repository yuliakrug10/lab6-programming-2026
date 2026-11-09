#include "OddNumberWait.h"

OddNumberWait::OddNumberWait(int value)
    : checkedValue(value) {
}

bool OddNumberWait::await_ready() const noexcept {
    bool isEven = checkedValue % 2 == 0;
    return isEven;
}

void OddNumberWait::await_suspend(std::coroutine_handle<> handle) const noexcept {
    static_cast<void>(handle);
}

void OddNumberWait::await_resume() const noexcept {
}
