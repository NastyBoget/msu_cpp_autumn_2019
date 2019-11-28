#include "thread_pool.h"

ThreadPool::ThreadPool(size_t poolSize) : flag_(true) {
    for (size_t i = 0; i < poolSize; ++i) {
        threads_.emplace_back(
                [this]() {
                    while (flag_) {
                        std::unique_lock<std::mutex> lock(mutex_);
                        if (!taskQueue_.empty()) {
                            auto task = taskQueue_.front();
                            taskQueue_.pop();
                            lock.unlock();
                            task();
                        } else {
                            hasTask_.wait(lock);
                        }
                    }
                });
    }
}

ThreadPool::~ThreadPool() {
    flag_ = false;
    hasTask_.notify_all();
    for (auto& thread : threads_) {
        thread.join();
    }
}