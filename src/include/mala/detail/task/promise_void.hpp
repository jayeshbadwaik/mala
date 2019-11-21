#ifndef MALA_DETAIL_TASK_PROMISE_VOID_HPP
#define MALA_DETAIL_TASK_PROMISE_VOID_HPP

#include <mala/detail/task/promise_base.hpp>
#include <mala/detail/task/promise_fwd.hpp>
#include <mala/task_fwd.hpp>

namespace mala::detail::task {
template <>
class promise<void> : public promise_base {
public:
  promise() noexcept = default;

  auto get_return_object() noexcept -> ::mala::task<void>;

  void return_void() noexcept;

  void unhandled_exception() noexcept;

  void result();

private:
  std::exception_ptr exception_ptr_;
};

} // namespace mala::detail::task

#endif // MALA_DETAIL_TASK_PROMISE_VOID_HPP
