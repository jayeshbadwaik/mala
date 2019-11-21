#ifndef MALA_DETAIL_TASK_PROMISE_BASE_HPP
#define MALA_DETAIL_TASK_PROMISE_BASE_HPP

#include <experimental/coroutine>
#include <mala/detail/task/final_awaitable.hpp>

namespace mala::detail::task {
class promise_base {

public:
  promise_base() noexcept = default;

public:
  auto initial_suspend() noexcept -> std::experimental::suspend_always;

  auto final_suspend() noexcept -> final_awaitable;

  void set_continuation(
    std::experimental::coroutine_handle<> continuation) noexcept;

private:
  std::experimental::coroutine_handle<> continuation_;

private:
  friend struct final_awaitable;
};
} // namespace mala::detail::task

#endif // MALA_DETAIL_TASK_PROMISE_BASE_HPP
