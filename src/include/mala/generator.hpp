#ifndef MALA_GENERATOR_HPP
#define MALA_GENERATOR_HPP

#include <mala/detail/generator/iterator.hpp>
#include <mala/detail/generator/promise.hpp>
#include <mala/detail/generator/sentinel.hpp>

namespace mala {

template <typename T>
class [[nodiscard]] generator
{
public:
  using promise_type = detail::generator::promise<T>;
  using iterator = detail::generator::iterator<T>;
  using sentinel = detail::generator::sentinel;

private:
  using coroutine_handle = std::experimental::coroutine_handle<promise_type>;

public:
  generator() = default;

  generator(generator && other) noexcept;

  generator(generator const& other) = delete;

  ~generator();

  auto operator=(generator other) noexcept->generator&;

private:
  explicit generator(coroutine_handle coroutine) noexcept;

public:
  auto begin()->iterator;

  auto end() noexcept->sentinel;

  void swap(generator & other) noexcept;

private:
  coroutine_handle coroutine_;

private:
  friend promise_type;
};

template <typename T>
generator<T>::generator(generator&& other) noexcept
: coroutine_(other.coroutine_)
{
  other.coroutine_ = nullptr;
}

template <typename T>
generator<T>::~generator()
{
  if (coroutine_) {
    coroutine_.destroy();
  }
}

template <typename T>
auto generator<T>::operator=(generator other) noexcept -> generator&
{
  this->swap(other);
  return *this;
}

template <typename T>
generator<T>::generator(coroutine_handle coroutine) noexcept
: coroutine_(coroutine)
{
}

template <typename T>
auto generator<T>::begin() -> iterator
{
  if (coroutine_) {
    coroutine_.resume();
    if (coroutine_.done()) {
      coroutine_.promise().rethrow_if_exception();
    }
  }
  return iterator{coroutine_};
}

template <typename T>
auto generator<T>::end() noexcept -> sentinel
{
  return sentinel{};
}

template <typename T>
void generator<T>::swap(generator& other) noexcept
{
  std::swap(coroutine_, other.coroutine_);
}
} // namespace mala

#endif // MALA_GENERATOR_HPP
