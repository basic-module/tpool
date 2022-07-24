#include "tpool.h"
#include <algorithm>
#include <chrono>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>

using namespace std;

constexpr size_t defaultpoolsize = 4;
namespace TPOOL {

Tpool *Tpool::Instance() {
  static Tpool tpool;
  return &tpool;
}

Tpool::Tpool() { AddThread(defaultpoolsize); }

Tpool::~Tpool() { Stop(); }

void Tpool::Stop() {
  isExit = true;
  cond.notify_all();
  std::unique_lock lock(threadsMutex);
  for (auto &t : threadPool) {
    if (t.joinable())
      t.join();
  }
}

void Tpool::AddThread(int num) {
  for (int i = 0; i < num; i++) {
    std::unique_lock<mutex> lock(threadsMutex);
    if (threadPool.size() >= threadsMaxNum) {
      return;
    }
    threadPool.emplace_back([this] {
      while (!isExit) {
        std::unique_lock<mutex> lock(tasksMutex);
        while (tasks.empty()) {
          if (isExit) {
            return;
          }
          cond.wait(lock);
        }
        auto task = std::move(tasks.front());
        tasks.pop();
        lock.unlock();
        task();
      }
    });
  }
}

void Tpool::AddTask(const std::function<void()> &task) {
  std::unique_lock<mutex> lock(tasksMutex);
  tasks.emplace(move(task));
  cond.notify_one();
}

} // namespace TPOOL
