#include "immutable_string.h"
#include "immutable_string_pool.h"

ImmutableString::ImmutableString(const std::string &val) {
  ptr_ = ImmutableStringPool::Instance().Intern(val);
  hash_ = std::hash<std::string>{}(*ptr_);
}
ImmutableString::ImmutableString(const char *cStr) {
  ImmutableString(std::string(cStr));
}

ImmutableString::ImmutableString(ImmutableString &&val) noexcept
    : hash_(val.hash_), ptr_(std::move(val.ptr_)){
  val.hash_ = 0;
}

ImmutableString::ImmutableString(const ImmutableString &val)
    : hash_(val.hash_) {
  ptr_ = val.ptr_;
}

ImmutableString::~ImmutableString() {
  if (ptr_ != nullptr && ptr_.use_count() <= 2) {
    ImmutableStringPool::Instance().Erase(ptr_);
  }
}

bool ImmutableString::operator==(const ImmutableString &rhs)
{
    return ToString() == rhs.ToString();
}

bool operator==(const ImmutableString &lhs, const ImmutableString &rhs)
{
    return lhs.ToString() == rhs.ToString();
}