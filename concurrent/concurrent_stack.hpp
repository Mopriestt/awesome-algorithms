#pragma once

#include <mutex>
#include <vector>
#include <optional>
#include <utility>

namespace concurrent {

    template<typename T>
    class ConcurrentStack {
    public:
        void push(const T& element) {
            std::lock_guard<std::mutex> lock(mutex_);
            container.push_back(element);
        }

        void push(T&& element) {
            std::lock_guard<std::mutex> lock(mutex_);
            container.push_back(std::move(element));
        }

        template<typename... Args>
        void emplace(Args&&... args) {
            std::lock_guard<std::mutex> lock(mutex_);
            container.emplace_back(std::forward<Args>(args)...);
        }

        std::optional<T> tryGetTop() const {
            std::lock_guard<std::mutex> lock(mutex_);
            if (container.empty()) {
                return std::nullopt;
            }
            return container.back();
        }

        bool empty() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return container.empty();
        }

        size_t size() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return container.size();
        }

        std::optional<T> tryPop() {
            std::lock_guard<std::mutex> lock(mutex_);
            if (container.empty()) {
                return std::nullopt;
            }
            std::optional<T> result = std::move(container.back());
            container.pop_back();
            return result;
        }
    private:
        std::vector<T> container;
        mutable std::mutex mutex_;
    };

}