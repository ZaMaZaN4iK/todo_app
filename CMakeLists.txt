cmake_minimum_required(VERSION 3.9)
project(wt_todo)

include(conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 14)

include_directories(install/include)
link_directories(install/lib)

include_directories(src)

set(HEADERS src/PlannerApplication.h src/UserAccount.h
        src/Login.h
        src/TimeSuggestions.h
        src/EntryDialog.h
        src/Entry.h
        src/AllEntriesDialog.h
        src/CalendarCell.h
        src/PlannerCalendar.h
        src/SerializeHelper.h
        src/Session.h)

set(SOURCES src/planner.cpp src/PlannerApplication.cpp src/UserAccount.cpp
        src/Login.cpp
        src/TimeSuggestions.cpp
        src/EntryDialog.cpp
        src/AllEntriesDialog.cpp
        src/CalendarCell.cpp
        src/PlannerCalendar.cpp
        src/SerializerHelper.cpp
        src/Session.cpp)

add_subdirectory(test)

add_executable(wt_todo ${HEADERS} ${SOURCES})
target_link_libraries(wt_todo libwt.so libwtdbo.so libwthttp.so libwtdbosqlite3.so libwttest.so
        -lboost_system -pthread)
