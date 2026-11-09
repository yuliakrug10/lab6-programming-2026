#pragma once

#include <coroutine>

class OddNumberWait {
public:
    explicit OddNumberWait(int value);

    bool await_ready() const noexcept;

    void await_suspend(std::coroutine_handle<> handle) const noexcept;

    void await_resume() const noexcept;

private:
    int checkedValue;
};
