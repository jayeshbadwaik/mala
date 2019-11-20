#ifndef MALA_DETAIL_TYPE_TRAITS_HPP
#define MALA_DETAIL_TYPE_TRAITS_HPP

#include <experimental/coroutine>
#include <type_traits>

namespace mala::detail {

template <typename T>
struct is_coroutine_handle : std::false_type {
};

template <typename Promise>
struct is_coroutine_handle<std::experimental::coroutine_handle<Promise>>
: std::true_type {
};

template <typename T>
struct is_valid_await_suspend_return_value
: std::disjunction<std::is_void<T>,
                   std::is_same<T, bool>,
                   is_coroutine_handle<T>> {
};

template <typename T, typename = std::void_t<>>
struct is_awaiter : std::false_type {
};

// Test whether await_suspend() will be callable using an
// arbitrary coroutine_handle here by checking if it supports being passed
// a coroutine_handle<void>. This may result in a false-result for some
// types which are only awaitable within a certain context.
template <typename T>
struct is_awaiter<
  T,
  std::void_t<decltype(std::declval<T>().await_ready()),
              decltype(std::declval<T>().await_suspend(
                std::declval<std::experimental::coroutine_handle<>>())),
              decltype(std::declval<T>().await_resume())>>
: std::conjunction<
    std::is_constructible<bool, decltype(std::declval<T>().await_ready())>,
    detail::is_valid_await_suspend_return_value<decltype(
      std::declval<T>().await_suspend(
        std::declval<std::experimental::coroutine_handle<>>()))>> {
};

template <typename T>
struct remove_rvalue_reference {
  using type = T;
};

template <typename T>
struct remove_rvalue_reference<T&&> {
  using type = T;
};

template <typename T>
using remove_rvalue_reference_t = typename remove_rvalue_reference<T>::type;

} // namespace mala::detail

#endif // MALA_DETAIL_TYPE_TRAITS_HPP
