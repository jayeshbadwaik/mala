#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include <experimental/coroutine>
#include <iostream>

class resumable {
public:
  struct promise_type;
  using coro_handle = std::experimental::coroutine_handle<promise_type>;
  resumable(coro_handle handle) : handle_(handle) { assert(handle); }
  resumable(resumable&) = delete;
  resumable(resumable&&) = delete;
  bool resume()
  {
    if (not handle_.done())
      handle_.resume();
    return not handle_.done();
  }
  ~resumable() { handle_.destroy(); }

private:
  coro_handle handle_;
};

struct resumable::promise_type {
  using coro_handle = std::experimental::coroutine_handle<promise_type>;
  auto get_return_object() { return coro_handle::from_promise(*this); }
  auto initial_suspend() { return std::experimental::suspend_always(); }
  auto final_suspend() { return std::experimental::suspend_always(); }
  void return_void() {}
  [[noreturn]] void unhandled_exception() { std::terminate(); }
};

resumable foo(std::size_t& a);

resumable foo(std::size_t& a)
{
  a += 4;
  co_await std::experimental::suspend_always();
  a += 5;
}

TEST_CASE("coroutine : hello_world: test01", "[coroutine]")
{
  std::size_t a = 3;
  resumable res = foo(a);
  res.resume();
  REQUIRE(a == 7);
  a += 5;
  REQUIRE(a == 12);
  res.resume();
  REQUIRE(a == 17);
}
