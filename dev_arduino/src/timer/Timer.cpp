#include "Timer.h"
#include <iostream>
#include <chrono>

Timer::Timer() 
    : interval_(0), callback_(nullptr){
}

Timer::~Timer() {
    stop();
}

void Timer::startSingleShot(std::chrono::milliseconds interval, Callback callback) {
    stop();  // Ensure any existing timer is stopped before starting a new one
    std::unique_lock<std::mutex> lock(mutex_);
    interval_ = interval;
    callback_ = callback;
    lock.unlock();

    timerThread_ = std::thread(&Timer::timerThreadFunction, this);
}

void Timer::restart(std::chrono::milliseconds interval) {
    stop();
    startSingleShot(interval, callback_);
}

void Timer::stop() {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.notify_all();  // Wake up the timer thread if waiting
    }
    if (timerThread_.joinable()) {
        timerThread_.join();
    }
}

void Timer::timerThreadFunction() {
    std::unique_lock<std::mutex> lock(mutex_);
    if (cv_.wait_for(lock, interval_) == std::cv_status::timeout) {
        if (callback_) {
            callback_();
        }
    }
}
