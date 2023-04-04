#ifndef _IMMUTABLE_STRING_POOL_H_
#define _IMMUTABLE_STRING_POOL_H_

#include "immutable_string.h"
#include <iostream>
#include <memory>
#include <mutex>
#include <oneapi/tbb/concurrent_unordered_set.h>
#include <string_view>
#include <utility>

static const std::string &ToString(const std::string &str) { return str; }
static const std::string &ToString(const std::shared_ptr<std::string> &strPtr) {
  return *strPtr;
}

  struct StringSharedPtrEqual {
    using is_transparent = std::true_type;
    template <typename LHS, typename RHS>
    bool operator()(const LHS &lhs, const RHS &rhs) const {
      return ToString(lhs) == ToString(rhs);
    }
  };

struct StringSharedPtrHash {

  using transparent_key_equal = StringSharedPtrEqual;

  template <typename T>
  size_t operator()(const T &&val) const {
    return std::hash<std::string>{}(ToString(val));
  }

  size_t operator()(const std::string &val) const {
    return std::hash<std::string>{}(val);
  }

  size_t operator()(const StringSharedPtr &ptr) const {
    return std::hash<std::string>{}(*ptr);
  }
};

using StringSet =
    tbb::concurrent_unordered_set<StringSharedPtr, StringSharedPtrHash>;

class ImmutableStringPool {
public:
  ImmutableStringPool() = default;
  ~ImmutableStringPool() = default;
  ImmutableStringPool(ImmutableStringPool &&) = delete;      // Move construct
  ImmutableStringPool(const ImmutableStringPool &) = delete; // Copy construct
  ImmutableStringPool &
  operator=(const ImmutableStringPool &) = delete; // Copy assign
  ImmutableStringPool &
  operator=(ImmutableStringPool &&) = delete; // Move assign

  static ImmutableStringPool &Instance() {
    static ImmutableStringPool instance;
    return instance;
  }

  template <class T> StringSharedPtr Intern(T &&val) {
    auto iter = pool_.find(val);
    if (iter == pool_.end()) {
      auto pair = pool_.insert(std::make_shared<std::string>(val));
      if (pair.second) {
        return *pair.first;
      }
      std::cout << "insert failed" << std::endl;
    }
    return *iter;
  }

  StringSharedPtr Intern(char const *val) {
    return Intern(std::string(val));
  }

  void Erase(StringSharedPtr &val) {
    if (pool_.find(val) != pool_.end()) {
      std::lock_guard<std::mutex> lock(mutex_);
      pool_.unsafe_erase(val);
    }
  }

  size_t Size() { return pool_.size(); }

private:
  std::mutex mutex_;
  StringSet pool_;
};
#endif