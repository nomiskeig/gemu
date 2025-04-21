file(GLOB cpu_srcs *.cpp)
add_subdirectory(instructions)
target_sources(gemu PRIVATE ${cpu_srcs})
