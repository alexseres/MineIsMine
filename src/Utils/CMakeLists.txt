add_library(util QueryPerformanceTimer.cpp Random.cpp ScopedQueryPerformanceTimer.cpp stdafx.cpp)
target_link_libraries(
        util
        PUBLIC
        manager
        model
)