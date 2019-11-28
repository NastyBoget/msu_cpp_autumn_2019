#ifndef UNTITLED7
#define UNTITLED7

#include <vector>
#include <cstddef>
#include <functional>
#include <future>
#include <queue>
#include <thread>

class ThreadPool {
public:
    explicit ThreadPool(size_t poolSize);
    ~ThreadPool();
    // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        using typeReturn = decltype(func(args...));
        using typeP = std::packaged_task<typeReturn ()>;
        auto task = std::make_shared<typeP>([func, args...]() {
            return func(args...);
        });
        {
            std::lock_guard<std::mutex> lock(mutex_);
            taskQueue_.emplace(
                    [task]() {
                        (*task)();
                    });
        }
        hasTask_.notify_one();
        return task->get_future();
    }
private:
    using Task = std::function<void ()>;
    std::atomic<bool> flag_;
    std::vector<std::thread> threads_;
    std::queue<Task> taskQueue_;
    std::mutex mutex_;
    std::condition_variable hasTask_;
};

#endif
