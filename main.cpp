#include <iostream>
#include "gtest/gtest.h"
#include "glog/logging.h"


int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  google::InitGoogleLogging(argv[0]);
  fLB::FLAGS_alsologtostderr = true;
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();   
}
