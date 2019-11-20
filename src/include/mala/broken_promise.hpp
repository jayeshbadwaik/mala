#ifndef MALA_BROKEN_PROMISE_HPP
#define MALA_BROKEN_PROMISE_HPP

#include <stdexcept>

namespace mala {

/// Exception thrown when you attempt to retrieve the result of
/// a task that has been detached from its promise/coroutine.
class broken_promise : public std::logic_error {
public:
  broken_promise() : std::logic_error("broken promise") {}
};

} // namespace mala

#endif // MALA_BROKEN_PROMISE_HPP
