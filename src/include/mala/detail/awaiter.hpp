#ifndef MALA_DETAIL_AWAITER_HPP
#define MALA_DETAIL_AWAITER_HPP

#include <any>
#include <mala/detail/type_traits.hpp>

namespace mala::detail {
template <typename T>
auto get_awaiter_impl(T&& value, int) noexcept(
  noexcept(static_cast<T&&>(value).operator co_await()))
  -> decltype(static_cast<T&&>(value).operator co_await());

template <typename T>
auto get_awaiter_impl(T&& value, int) noexcept(
  noexcept(static_cast<T&&>(value).operator co_await()))
  -> decltype(static_cast<T&&>(value).operator co_await())
{
  static_cast<T&&>(value).operator co_await();
}

template <typename T, typename = std::enable_if_t<is_awaiter<T&&>::value, int>>
T&& get_awaiter_impl(T&& value, std::any) noexcept
{
  return static_cast<T&&>(value);
}

template <typename T>
auto get_awaiter(T&& value) noexcept(
  noexcept(detail::get_awaiter_impl(static_cast<T&&>(value), 123)))
  -> decltype(detail::get_awaiter_impl(static_cast<T&&>(value), 123))
{
  return detail::get_awaiter_impl(static_cast<T&&>(value), 123);
}

} // namespace mala::detail
#endif // MALA_DETAIL_AWAITER_HPP
