#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>
#include <mala/generator.hpp>

TEST_CASE("generator: test01: default constructed generator", "[generator]")
{
  auto generator = mala::generator<int>();

  REQUIRE(generator.begin() == generator.end());
}

TEST_CASE("generator: test02: arithmetic type by copy", "[generator]")
{
  auto const f = []() -> mala::generator<float> {
    co_yield 1.0f;
    co_yield 2.0f;
  };

  auto generator = f();

  auto iter = std::begin(generator);

  REQUIRE(*iter == 1.0f);
  ++iter;
  REQUIRE(*iter == 2.0f);
  ++iter;
  REQUIRE(iter == std::end(generator));
}

TEST_CASE("generator: test02: arithmetic type by reference", "[generator]")
{
  auto f = [](float& value) -> mala::generator<float&> { co_yield value; };

  float value = 1.0f;
  for (auto& x : f(value)) {
    REQUIRE(&x == &value);
    x += 1.0f;
  }

  REQUIRE(value == 2.0f);
}

TEST_CASE("generator of const type")
{
  auto fib = []() -> mala::generator<const std::uint64_t> {
    std::uint64_t a = 0, b = 1;
    while (true) {
      co_yield b;
      b += std::exchange(a, b);
    }
  };

  std::uint64_t count = 0;
  for (auto i : fib()) {
    if (i > 1'000'000) {
      break;
    }
    ++count;
  }

  // 30th fib number is 832'040
  REQUIRE(count == 30);
}
