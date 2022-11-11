cmake_minimum_required(VERSION 3.23)
project(Mine)

set(CMAKE_CXX_STANDARD 17)

add_executable(Mine main.cpp
                Minefield.cpp
                Minefield.h
                Mine.cpp
                ObjectManager.cpp
                Object.cpp
                ObjectManager.cpp
                Random.cpp
                stdafx.cpp
                Mine.h
                Mutex.h
                Object.h
                ObjectManager.h
                Random.h
                stdafx.h
                targetver.h
                QueryPerformanceTimer.cpp
                QueryPerformanceTimer.h
                ScopedQueryPerformanceTimer.cpp
                ScopedQueryPerformanceTimer.h
                WorkerThread.h)
