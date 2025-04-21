file(GLOB instructions_srcs *.cpp)
target_sources(gemu PRIVATE ${instructions_srcs})
