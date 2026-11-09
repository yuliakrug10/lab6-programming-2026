#include "GeneratorTask.h"

#include <stdexcept>
#include <utility>

GeneratorTask GeneratorTask::promise_type::get_return_object() {
    return GeneratorTask(std::coroutine_handle<promise_type>::from_promise(*this));
}

std::suspend_always GeneratorTask::promise_type::initial_suspend() noexcept {
    return std::suspend_always{};
}

std::suspend_always GeneratorTask::promise_type::final_suspend() noexcept {
    return std::suspend_always{};
}

void GeneratorTask::promise_type::return_void() noexcept {
}

void GeneratorTask::promise_type::unhandled_exception() noexcept {
    storedException = std::current_exception();
}

GeneratorTask::GeneratorTask(std::coroutine_handle<promise_type> handle)
    : coroutineHandle(handle) {
}

GeneratorTask::GeneratorTask(GeneratorTask&& other) noexcept
    : coroutineHandle(std::exchange(other.coroutineHandle, nullptr)) {
}

GeneratorTask& GeneratorTask::operator=(GeneratorTask&& other) noexcept {
    if (this != &other) {
        destroyHandle();
        coroutineHandle = std::exchange(other.coroutineHandle, nullptr);
    }
    return *this;
}

GeneratorTask::~GeneratorTask() {
    destroyHandle();
}

bool GeneratorTask::isFinished() const {
    if (!coroutineHandle) {
        return true;
    }
    return coroutineHandle.done();
}

void GeneratorTask::resume() {
    if (isFinished()) {
        throw std::logic_error("Cannot resume a finished coroutine");
    }
    coroutineHandle.resume();
    if (coroutineHandle.promise().storedException) {
        std::rethrow_exception(coroutineHandle.promise().storedException);
    }
}

void GeneratorTask::destroyHandle() {
    if (coroutineHandle) {
        coroutineHandle.destroy();
        coroutineHandle = nullptr;
    }
}
