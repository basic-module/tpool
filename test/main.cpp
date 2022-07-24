#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace std;

class TpoolEnv : public testing::Environment {
  void SetUp() override {}
};

int main() {
  testing::InitGoogleTest();
  testing::AddGlobalTestEnvironment(new TpoolEnv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
