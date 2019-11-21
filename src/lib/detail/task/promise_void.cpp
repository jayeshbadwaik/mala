#include <mala/detail/task/promise_void.hpp>

namespace mala::detail::task {
void promise<void>::return_void() noexcept
{
}

void promise<void>::unhandled_exception() noexcept
{
  exception_ptr_ = std::current_exception();
}

void promise<void>::result()
{
  if (exception_ptr_) {
    std::rethrow_exception(exception_ptr_);
  }
}
} // namespace mala::detail::task
