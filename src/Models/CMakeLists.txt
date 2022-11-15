add_library(model Mine.cpp Object.cpp WorkerThread.cpp)

target_link_libraries(
        model
        PUBLIC
        manager
        util
)