#include <mala/detail/task/promise_base.hpp>

namespace mala::detail::task {

auto promise_base::initial_suspend() noexcept
  -> std::experimental::suspend_always
{
  return std::experimental::suspend_always{};
}

auto promise_base::final_suspend() noexcept -> final_awaitable
{
  return final_awaitable{};
}

void promise_base::set_continuation(
  std::experimental::coroutine_handle<> continuation) noexcept
{
  continuation_ = continuation;
}
} // namespace mala::detail::task
