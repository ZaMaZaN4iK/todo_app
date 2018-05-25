/*
    MIT License
    Copyright (c) 2018 Alexander Zaitsev <zamazan4ik@tut.by>
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "Session.h"

#include "UserAccount.h"

#include "Wt/Auth/AuthService.h"
#include "Wt/Auth/HashFunction.h"
#include "Wt/Auth/PasswordService.h"
#include "Wt/Auth/PasswordStrengthValidator.h"
#include "Wt/Auth/PasswordVerifier.h"
#include "Wt/Auth/GoogleService.h"
#include "Wt/Auth/FacebookService.h"
#include "Wt/Auth/Dbo/AuthInfo.h"
#include "Wt/Auth/Dbo/UserDatabase.h"

#include "Wt/Dbo/backend/Sqlite3.h"

#include <memory>
#include <string>
#include <vector>

namespace
{

Auth::AuthService myAuthService;
Auth::PasswordService myPasswordService(myAuthService);
std::vector<std::unique_ptr<Auth::OAuthService>> myOAuthServices;

}

void Session::configureAuth()
{
    myAuthService.setAuthTokensEnabled(true, "logincookie");
    myAuthService.setEmailVerificationEnabled(true);

    auto verifier = std::make_unique<Auth::PasswordVerifier>();
    verifier->addHashFunction(std::make_unique<Auth::BCryptHashFunction>(7));
    myPasswordService.setVerifier(std::move(verifier));
    myPasswordService.setAttemptThrottlingEnabled(true);
    myPasswordService.setStrengthValidator
            (std::make_unique<Auth::PasswordStrengthValidator>());

    if (Auth::GoogleService::configured())
    {
        myOAuthServices.push_back(std::make_unique<Auth::GoogleService>(myAuthService));
    }

    if (Auth::FacebookService::configured())
    {
        myOAuthServices.push_back(std::make_unique<Auth::FacebookService>(myAuthService));
    }
}

Session::Session(const std::string& sqliteDb)
{
    auto connection = std::make_unique<Dbo::backend::Sqlite3>(sqliteDb);

    connection->setProperty("show-queries", "true");

    setConnection(std::move(connection));

    mapClass<UserAccount>("user");
    mapClass<AuthInfo>("auth_info");
    mapClass<AuthInfo::AuthIdentityType>("auth_identity");
    mapClass<AuthInfo::AuthTokenType>("auth_token");

    try
    {
        createTables();
        std::cerr << "Created database." << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Using existing database";
    }

    users_ = std::make_unique<UserDatabase>(*this);
}

Session::~Session()
{
}

Auth::AbstractUserDatabase& Session::users()
{
    return *users_;
}

dbo::ptr<UserAccount> Session::user()
{
    if (login_.loggedIn())
    {
        return user(login_.user());
    }
    else
    {
        return dbo::ptr<UserAccount>();
    }
}

dbo::ptr<UserAccount> Session::user(const Auth::User& authUser)
{
    dbo::ptr<AuthInfo> authInfo = users_->find(authUser);

    dbo::ptr<UserAccount> user = authInfo->user();

    if (!user)
    {
        user = add(std::make_unique<UserAccount>());
        authInfo.modify()->setUser(user);
    }

    return user;
}

const Auth::AuthService& Session::auth()
{
    return myAuthService;
}

const Auth::PasswordService& Session::passwordAuth()
{
    return myPasswordService;
}

const std::vector<const Auth::OAuthService*> Session::oAuth()
{
    std::vector<const Auth::OAuthService*> result;
    for (auto& auth : myOAuthServices)
    {
        result.push_back(auth.get());
    }
    return result;
}
