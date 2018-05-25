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

#ifndef SESSION_H_
#define SESSION_H_

#include "UserAccount.h"

#include <Wt/Auth/Login.h>

#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>

#include <memory>
#include <string>
#include <vector>

using namespace Wt;

namespace dbo = Wt::Dbo;

typedef Auth::Dbo::UserDatabase<AuthInfo> UserDatabase;

/*!
  Class for Session
*/
class Session : public dbo::Session
{
public:
    static void configureAuth();

    Session(const std::string& sqliteDb);

    ~Session();

    dbo::ptr<UserAccount> user();

    dbo::ptr<UserAccount> user(const Auth::User& user);

    Auth::AbstractUserDatabase& users();

    Auth::Login& login()
    { return login_; }

    static const Auth::AuthService& auth();

    static const Auth::PasswordService& passwordAuth();

    static const std::vector<const Auth::OAuthService*> oAuth();

private:
    std::unique_ptr<UserDatabase> users_;
    Auth::Login login_;
};

#endif // SESSION_H_
