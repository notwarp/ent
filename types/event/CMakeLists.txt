add_library(event OBJECT event.c)
target_link_libraries(event PUBLIC uuid)