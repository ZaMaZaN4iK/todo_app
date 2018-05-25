set(TEST_SOURCES unitTest.cpp ../src/UserAccount.cpp ../src/Login.cpp ../src/EntryDialog.cpp
        ../src/TimeSuggestions.cpp ../src/CalendarCell.cpp ../src/AllEntriesDialog.cpp
        ../src/SerializerHelper.cpp)

add_executable(unitTest ${TEST_SOURCES})
target_link_libraries(unitTest libwt.so libwtdbo.so libwthttp.so libwtdbosqlite3.so libwttest.so
        -lboost_system -pthread)