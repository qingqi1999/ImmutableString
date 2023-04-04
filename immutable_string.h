#ifndef _IMMUTABLE_STRING_H_
#define _IMMUTABLE_STRING_H_

#include <memory>
#include <string>

using StringSharedPtr = std::shared_ptr<std::string>;
class ImmutableStringPool;

class ImmutableString {
public:

  explicit ImmutableString() = delete;
  ImmutableString(const std::string &val);

  ImmutableString(const char *cStr);

  ImmutableString(ImmutableString &&val) noexcept ;
  ImmutableString(const ImmutableString &val);
  ~ImmutableString();
  inline size_t Hash() const { return hash_; }

  inline const std::string &ToString() const { return *ptr_; }

  bool operator==(const ImmutableString &rhs);

private:
  size_t hash_;
  StringSharedPtr ptr_;
};

bool operator==(const ImmutableString &lhs, const ImmutableString &rhs);

struct ImmutableStringHash {
  using is_transparent = void;
  size_t operator()(const char *str) const {
    return std::hash<std::string>{}(str);
  }
  size_t operator()(const std::string &str) const {
    return std::hash<std::string>{}(str);
  }
  size_t operator()(const ImmutableString &str) const {
    return str.Hash();
  }
};



#endif