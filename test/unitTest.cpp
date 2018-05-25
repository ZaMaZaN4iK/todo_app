#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "Entry.h"
#include "EntryDialog.h"
#include "Login.h"
#include "TimeSuggestions.h"
#include "UserAccount.h"

TEST_CASE( "User account test", "[single-file]" )
{
    REQUIRE_NOTHROW(UserAccount());
    REQUIRE_NOTHROW(UserAccount("username", "password"));
}

TEST_CASE( "TimeSuggestion test", "[single-file]" )
{
    REQUIRE_NOTHROW(TimeSuggestions());
}