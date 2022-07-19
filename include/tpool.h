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
	void AddTask(const std::function<void()> &task);
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
	std::queue<std::function<void()>> tasks;
	std::vector<std::thread> threadPool;
	std::mutex tasksMutex;
	std::mutex threadsMutex;
	std::condition_variable cond;
	std::atomic<bool> isExit {false};
	std::atomic<unsigned int> threadsMaxNum{std::thread::hardware_concurrency()};
	std::atomic<unsigned int> threadsMinNum{1};
};

template<typename Func, typename ...Types>
auto AsyncTask(Func &&func, Types&& ...args)
{
	using RetType = decltype(func(args...));
	auto task = std::make_shared<std::packaged_task<RetType()>>(std::bind(std::forward<Func>(func), std::forward<Types> (args)...));
	auto result = task->get_future();
	Tpool::Instance()->AddTask([task]{(*task)();});
	return move(result);
}

}

#endif
