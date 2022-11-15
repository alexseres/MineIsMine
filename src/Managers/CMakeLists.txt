add_library(manager Minefield.cpp ObjectManager.cpp)
target_link_libraries(manager PUBLIC model util)