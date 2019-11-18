#ifndef MALA_DETAIL_GENERATOR_ITERATOR_HPP
#define MALA_DETAIL_GENERATOR_ITERATOR_HPP

#include <experimental/coroutine>
#include <mala/detail/generator/promise.hpp>
#include <mala/detail/generator/sentinel.hpp>

namespace mala::detail::generator {

template <typename T>
class iterator {

  using promise_type = promise<T>;

public:
  using coroutine_handle = std::experimental::coroutine_handle<promise<T>>;

  using iterator_category = std::input_iterator_tag;

  using difference_type = std::ptrdiff_t;

  using value_type = typename promise_type::value_type;

  using reference = typename promise_type::reference;

  using pointer = typename promise_type::pointer;

public:
  iterator() noexcept = default;

  explicit iterator(coroutine_handle coroutine) noexcept;

public:
  auto operator++() -> iterator&;

  void operator++(int);

  auto operator*() const noexcept -> reference;

  auto operator-> () const noexcept -> pointer;

private:
  coroutine_handle coroutine_{nullptr};

private:
  template <typename U>
  friend bool operator==(iterator<U> const& it, sentinel) noexcept;

  template <typename U>
  friend bool operator!=(iterator<U> const& it, sentinel) noexcept;

  template <typename U>
  friend bool operator==(sentinel, iterator<U> const& it) noexcept;

  template <typename U>
  friend bool operator!=(sentinel, iterator<U> const& it) noexcept;
};

template <typename T>
iterator<T>::iterator(coroutine_handle coroutine) noexcept
: coroutine_(coroutine)
{
}

template <typename T>
auto iterator<T>::operator++() -> iterator&
{
  coroutine_.resume();
  if (coroutine_.done()) {
    coroutine_.promise().rethrow_if_exception();
  }

  return *this;
}

template <typename T>
void iterator<T>::operator++(int)
{
  operator++();
}

template <typename T>
auto iterator<T>::operator*() const noexcept -> reference
{
  return coroutine_.promise().value();
}

template <typename T>
auto iterator<T>::operator-> () const noexcept -> pointer
{
  return std::addressof(coroutine_.promise().value());
}

template <typename T>
bool operator==(iterator<T> const& it, sentinel) noexcept
{
  return ((not it.coroutine_) or it.coroutine_.done());
}

template <typename T>
bool operator!=(iterator<T> const& it, sentinel s) noexcept
{
  return !(it == s);
}

template <typename T>
bool operator==(sentinel s, iterator<T> const& it) noexcept
{
  return (it == s);
}

template <typename T>
bool operator!=(sentinel s, iterator<T> const& it) noexcept
{
  return (it != s);
}

} // namespace mala::detail::generator

#endif // MALA_DETAIL_GENERATOR_ITERATOR_HPP
