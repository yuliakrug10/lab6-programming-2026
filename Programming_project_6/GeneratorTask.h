#pragma once

#include <coroutine>
#include <exception>

class GeneratorTask {
public:
    struct promise_type {
        std::exception_ptr storedException;

        GeneratorTask get_return_object();

        std::suspend_always initial_suspend() noexcept;

        std::suspend_always final_suspend() noexcept;

        void return_void() noexcept;

        void unhandled_exception() noexcept;
    };

    explicit GeneratorTask(std::coroutine_handle<promise_type> handle);

    GeneratorTask(const GeneratorTask& other) = delete;
    GeneratorTask& operator=(const GeneratorTask& other) = delete;

    GeneratorTask(GeneratorTask&& other) noexcept;
    GeneratorTask& operator=(GeneratorTask&& other) noexcept;

    ~GeneratorTask();

    bool isFinished() const;

    void resume();

private:
    void destroyHandle();

    std::coroutine_handle<promise_type> coroutineHandle;
};
