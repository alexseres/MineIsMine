add_library(manager Minefield.h Minefield.cpp ObjectManager.cpp ObjectManager.h)
target_link_libraries(manager PUBLIC model util)