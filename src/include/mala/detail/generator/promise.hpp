#ifndef MALA_DETAIL_GENERATOR_PROMISE_HPP
#define MALA_DETAIL_GENERATOR_PROMISE_HPP

#include <experimental/coroutine>
#include <mala/generator_fwd.hpp>
#include <type_traits>

namespace mala::detail::generator {
template <typename T>
class promise {
public:
  using value_type = std::remove_reference_t<T>;
  using reference = value_type&;
  using pointer = value_type*;

public:
  promise() = default;

public:
  /// Do not allow any use of `co_await` inside the generator coroutine
  template <typename U>
  auto await_transform(U&& value) -> std::experimental::suspend_never = delete;

  constexpr auto final_suspend() const -> std::experimental::suspend_always;

  auto get_return_object() noexcept -> ::mala::generator<T>;

  constexpr auto initial_suspend() const -> std::experimental::suspend_always;

  void rethrow_if_exception();

  void return_void();

  void unhandled_exception();

  auto value() const noexcept -> reference;

  template <typename U = T,
            typename = std::enable_if_t<not std::is_rvalue_reference_v<U>>>
  auto yield_value(reference value) noexcept
    -> std::experimental::suspend_always;

  auto yield_value(value_type&& value) noexcept
    -> std::experimental::suspend_always;

private:
  pointer value_ptr_{nullptr};
  std::exception_ptr exception_ptr_;
};

template <typename T>
constexpr auto promise<T>::final_suspend() const
  -> std::experimental::suspend_always
{
  return std::experimental::suspend_always{};
}

template <typename T>
auto promise<T>::get_return_object() noexcept -> ::mala::generator<T>
{
  using coroutine_handle = std::experimental::coroutine_handle<promise<T>>;
  return ::mala::generator<T>(coroutine_handle::from_promise(*this));
}

template <typename T>
constexpr auto promise<T>::initial_suspend() const
  -> std::experimental::suspend_always
{
  return std::experimental::suspend_always{};
}

template <typename T>
void promise<T>::rethrow_if_exception()
{
  if (exception_ptr_) {
    std::rethrow_exception(exception_ptr_);
  }
}

template <typename T>
void promise<T>::return_void()
{
}

template <typename T>
void promise<T>::unhandled_exception()
{
  exception_ptr_ = std::current_exception();
}

template <typename T>
auto promise<T>::value() const noexcept -> reference
{
  return static_cast<reference>(*value_ptr_);
}

template <typename T>
auto promise<T>::yield_value(value_type&& value) noexcept
  -> std::experimental::suspend_always
{
  value_ptr_ = std::addressof(value);
  return std::experimental::suspend_always();
}

template <typename T>
template <typename U, typename V>
auto promise<T>::yield_value(reference value) noexcept
  -> std::experimental::suspend_always
{
  value_ptr_ = std::addressof(value);
  return std::experimental::suspend_always();
}

} // namespace mala::detail::generator

#endif // MALA_DETAIL_GENERATOR_PROMISE_HPP
