#include "tpool.h"
#include "gtest/gtest.h"
#include <cstdio>
#include <functional>
#include <iostream>

using namespace std;
using namespace TPOOL;

TEST(Tpool, runTask) {
  auto maxnum = [](int a, int b) { return ((a < b) ? b : a); };
  auto test1 = AsyncTask(maxnum, 1, 2);
  auto test2 = AsyncTask(printf, "this is a task %d", 2);

  EXPECT_EQ(test1.get(), 2);
  EXPECT_EQ(test2.get(), string("this is a task 2").size());

  Tpool::Instance()->Stop();
}
