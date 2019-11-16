add_executable(unit.t unit.t.cpp)
add_test(unit.t unit.t)
target_link_libraries(unit.t PUBLIC ${TESTLIBNAME})


target_sources(unit.t PRIVATE coroutine_hello_world.t.cpp)
