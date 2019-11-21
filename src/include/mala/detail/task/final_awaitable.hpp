#ifndef MALA_DETAIL_TASK_FINAL_AWAITABLE_HPP
#define MALA_DETAIL_TASK_FINAL_AWAITABLE_HPP

#include <experimental/coroutine>

namespace mala::detail::task {
struct final_awaitable {
  bool await_ready() const noexcept;

  template <typename Promise>
  auto await_suspend(std::experimental::coroutine_handle<Promise> coro) noexcept
    -> std::experimental::coroutine_handle<>;

  void await_resume() noexcept;
};

template <typename Promise>
auto final_awaitable::await_suspend(
  std::experimental::coroutine_handle<Promise> coro) noexcept
  -> std::experimental::coroutine_handle<>
{
  return coro.promise().continuation_;
}

} // namespace mala::detail::task

#endif // MALA_DETAIL_TASK_FINAL_AWAITABLE_HPP
