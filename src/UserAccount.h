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

#ifndef USER_ACCOUNT_H_
#define USER_ACCOUNT_H_

#include "Entry.h"

#include <Wt/WDate.h>
#include <Wt/WString.h>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

using namespace Wt;

namespace dbo = Wt::Dbo;

/*!
  Class for user account representing
*/
class UserAccount
{
public:
    UserAccount() = default;

    UserAccount(WString name, WString password);

    dbo::collection<dbo::ptr<Entry>>
    entriesInRange(const WDate& from, const WDate& until) const;
    void deleteEntriesInRange(const WDate& from, const WDate& until);

    static Dbo::ptr<UserAccount> signIn(Dbo::Session& session, const WString& user, const WString& password);
    static Dbo::ptr<UserAccount> signUp(Dbo::Session& session, const WString& user, const WString& password);

    template<typename Action>
    void persist(Action& a)
    {
        dbo::field(a, m_name, "name");
        dbo::field(a, m_password, "password");
        dbo::hasMany(a, m_entries, dbo::ManyToOne, "user");
    }

private:
    WString m_name;
    WString m_password;

    dbo::collection<dbo::ptr<Entry>> m_entries;
};

using AuthInfo = Wt::Auth::Dbo::AuthInfo<UserAccount>;

#endif // USER_ACCOUNT_H_
