project(utility)
add_library(utility
        vec.cpp vec.h
        physics.cpp physics.h
)

target_include_directories(utility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})