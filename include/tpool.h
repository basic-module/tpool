#ifndef __TPOOL_H__
#define __TPOOL_H__

#ifndef TPOOL_EXPORT
#define TPOOL_EXPORT __attribute__((visibility("default"))) 
#endif

#include <condition_variable>
#include <functional>
#include <future>
#include <any>
#include <queue>
#include <atomic>

namespace TPOOL {

class TPOOL_EXPORT Tpool {
public:
	static Tpool* Instance();
	void AddTask(std::packaged_task<std::any()> &task);
	void Stop();	
	void Config(unsigned int minThreadNum, unsigned int maxThreadNum)
	{
		threadsMaxNum = maxThreadNum;
		threadsMinNum = minThreadNum >= 1 ? minThreadNum : 1;
	}

protected:
	void AddThread(int num);

private:
	Tpool();
	~Tpool();
	std::queue<std::packaged_task<std::any()>> tasks;
	std::vector<std::thread> threadPool;
	std::mutex tasksMutex;
	std::mutex threadsMutex;
	std::condition_variable cond;
	std::atomic<bool> isExit {false};
	std::atomic<unsigned int> threadsMaxNum{std::thread::hardware_concurrency()};
	std::atomic<unsigned int> threadsMinNum{1};
};

template<typename T, typename ... Args>
std::future<std::any> AsyncTask(std::function<T(Args ...)> func, Args&& ...args)
{
	auto task = std::packaged_task<std::any()>(std::bind(func, std::forward<Args> (args)...));
	auto result = task.get_future();
	Tpool::Instance()->AddTask(task);
	return result;
}

}

#endif
