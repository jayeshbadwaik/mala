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
