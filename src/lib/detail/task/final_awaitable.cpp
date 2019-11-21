#include <mala/detail/task/final_awaitable.hpp>

namespace mala::detail::task {
bool final_awaitable::await_ready() const noexcept
{
  return false;
}

void final_awaitable::await_resume() noexcept
{
}

} // namespace mala::detail::task
