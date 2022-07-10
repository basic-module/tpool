#include <functional>
#include "tpool.h"
#include "gtest/gtest.h"
#include <cstdio>
#include <iostream>

using namespace std;
using namespace TPOOL;

TEST(Tpool, runTask)
{
	std::function<void(const string &, const string &)> f = [](const string &a, const string &b) {printf(a.c_str(), b.c_str());};
	auto task = packaged_task<std::any()>(std::bind(printf, "%d", 5));
	auto result = task.get_future();
	Tpool::Instance()->AddTask(task);
	cout << (result.get().type() == typeid(int));
}

