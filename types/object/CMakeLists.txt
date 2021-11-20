add_library(object OBJECT object.c)
find_package(OpenMP REQUIRED)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}${OpenMP_C_FLAGS}")
target_link_libraries(object PUBLIC uuid ${CMAKE_C_FLAGS})
