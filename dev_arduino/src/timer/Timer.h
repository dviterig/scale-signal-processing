#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

class Timer {
public:
    // Type alias for the callback function
    using Callback = std::function<void()>;

    Timer();
    ~Timer();

    // Starts the timer with the given interval and callback
    void startSingleShot(std::chrono::milliseconds interval, Callback callback);

    void stop();

    // Restarts the timer without calling the callback
    void restart(std::chrono::milliseconds interval);

private:
    // Timer thread function
    void timerThreadFunction();

    // Interval of the timer
    std::chrono::milliseconds interval_;

    // Callback to be invoked when the timer expires
    Callback callback_;

    // Mutex to protect shared data
    std::mutex mutex_;

    // Condition variable to notify the waiting thread
    std::condition_variable cv_;

    // Thread running the timer
    std::thread timerThread_;
};

#endif // TIMER_H
