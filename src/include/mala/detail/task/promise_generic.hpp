#ifndef MALA_DETAIL_TASK_PROMISE_GENERIC_HPP
#define MALA_DETAIL_TASK_PROMISE_GENERIC_HPP

#include <mala/detail/task/promise_base.hpp>
#include <mala/detail/task/promise_fwd.hpp>
#include <mala/task_fwd.hpp>

namespace mala::detail::task {
template <typename T>
class promise final : public promise_base {
public:
  promise() noexcept = default;

  ~promise();

public:
  auto get_return_object() noexcept -> ::mala::task<T>;

  void unhandled_exception() noexcept;

  template <typename Value,
            typename = std::enable_if_t<std::is_convertible_v<Value&&, T>>>
  void return_value(Value&& value) noexcept(
    std::is_nothrow_constructible_v<T, Value&&>);

  auto result() & -> T&;

  auto result() && -> T&&;

private:
  enum class result_type { empty, value, exception };

  result_type result_type_{result_type::empty};

  T value_;

  std::exception_ptr exception_ptr_;
};

template <typename T>
promise<T>::~promise<T>()
{
  switch (result_type_) {
  case result_type::value: {
    value_.~T();
    break;
  }
  case result_type::exception: {
    exception_ptr_.~exception_ptr();
    break;
  }
  default:
    break;
  }
}

template <typename T>
void promise<T>::unhandled_exception() noexcept
{
  ::new (static_cast<void*>(std::addressof(exception_ptr_)))
    std::exception_ptr(std::current_exception());
  result_type_ = result_type::exception;
}

template <typename T>
template <typename Value, typename U>
void promise<T>::return_value(Value&& value) noexcept(
  std::is_nothrow_constructible_v<T, Value&&>)
{
  ::new (static_cast<void*>(std::addressof(value_)))
    T(std::forward<Value>(value));
  result_type_ = result_type::value;
}

template <typename T>
auto promise<T>::result() & -> T&
{
  if (result_type_ == result_type::exception) {
    std::rethrow_exception(exception_ptr_);
  }

  return value_;
}

template <typename T>
auto promise<T>::result() && -> T&&
{
  if (result_type_ == result_type::exception) {
    std::rethrow_exception(exception_ptr_);
  }

  return std::move(value_);
}
} // namespace mala::detail::task

#endif // MALA_DETAIL_TASK_PROMISE_GENERIC_HPP
