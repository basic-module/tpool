#include <algorithm>
#include <chrono>
#include <functional>
#include <future>
#include <vector>
#include <thread>
#include <queue>
#include "tpool.h"

using namespace std;

constexpr size_t defaultpoolsize = 4;
namespace TPOOL{

Tpool* Tpool::Instance()
{
	static Tpool tpool;
	return &tpool;
}

Tpool::Tpool()
{	
	AddThread(defaultpoolsize);
}

Tpool::~Tpool()
{
	Stop();
}

void Tpool::Stop()
{
	isExit = true;
	cond.notify_all();
	std::unique_lock lock(threadsMutex);
	for (auto &t : threadPool) {
		if (t.joinable()) t.join();	
	}
}

void Tpool::AddThread(int num)
{	
	for (int i = 0; i < num; i++)
	{
		std::unique_lock<mutex> lock(threadsMutex);
		if (threadPool.size() >= threadsMaxNum) {
			return;
		}
		threadPool.emplace_back([this]{
				while (!isExit){
					std::packaged_task<std::any()> task;
					{
						std::unique_lock<mutex> lock(tasksMutex);
						while (tasks.empty()) {
							if (isExit) {
								return;
							}
							cond.wait(lock);
						}
						task = std::move(tasks.front());
						tasks.pop();
					}
					task();
				}
			});
	}
}

void Tpool::AddTask(std::packaged_task<std::any()> &task)
{
	std::unique_lock<mutex> lock(tasksMutex);
	tasks.emplace(move(task));
	cond.notify_one();
}


}
