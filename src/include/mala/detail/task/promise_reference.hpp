#ifndef MALA_DETAIL_TASK_PROMISE_REFERENCE_HPP
#define MALA_DETAIL_TASK_PROMISE_REFERENCE_HPP

#include <mala/detail/task/promise_base.hpp>
#include <mala/detail/task/promise_fwd.hpp>
#include <mala/task_fwd.hpp>

namespace mala::detail::task {
template <typename T>
class promise<T&> : public promise_base {
public:
  promise() noexcept = default;
  auto get_return_object() noexcept -> ::mala::task<T&>;

  void unhandled_exception() noexcept;

  void return_value(T& value) noexcept;

  auto result() -> T&;

private:
  T* value_ptr_{nullptr};
  std::exception_ptr exception_ptr_;
};

template <typename T>
void promise<T&>::unhandled_exception() noexcept
{
  exception_ptr_ = std::current_exception();
}

template <typename T>
void promise<T&>::return_value(T& value) noexcept
{
  value_ptr_ = std::addressof(value);
}

template <typename T>
auto promise<T&>::result() -> T&
{
  if (exception_ptr_) {
    std::rethrow_exception(exception_ptr_);
  }
  return *value_ptr_;
}
} // namespace mala::detail::task

#endif // MALA_DETAIL_TASK_PROMISE_REFERENCE_HPP
