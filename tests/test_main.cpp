#include <gtest/gtest.h>

int main(int argc, char **argv) {
    // 初始化 Google Test 框架
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试
    return RUN_ALL_TESTS();
}
