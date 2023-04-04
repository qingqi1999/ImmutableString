#include "gtest/gtest.h"
#include <algorithm>
#include "immutable_string.h"
#include "immutable_string_pool.h"
#include "glog/logging.h"

TEST(DsStringTest, TestInit) {
    std::string test1 = "123";
    std::string test2 = "456";
    EXPECT_EQ(ImmutableStringPool::Instance().Size(), 0);
    {
        ImmutableString im1 = ImmutableString(test1);
        ImmutableString im2 = ImmutableString(test1);
        ImmutableString im3 = ImmutableString(test2);
        ImmutableString im4 = ImmutableString("123");
        ImmutableString im5 = ImmutableString("456");
        EXPECT_EQ(im1, im2);
        EXPECT_EQ(im1.ToString(), im2.ToString());
        LOG(INFO) << "im1 string addr: " << &im1.ToString();
        LOG(INFO) << "im2 string addr: " << &im2.ToString();
        EXPECT_EQ(&im1.ToString(), &im2.ToString());
        EXPECT_EQ(ImmutableStringPool::Instance().Size(), 2);
    }
    EXPECT_EQ(ImmutableStringPool::Instance().Size(), 0);

}