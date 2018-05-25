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

#include "UserAccount.h"

#include "Entry.h"

#include <Wt/WApplication.h>
#include <Wt/WDate.h>
#include <Wt/WLogger.h>
#include <Wt/WString.h>

#include <Wt/Dbo/WtSqlTraits.h>

#include <memory>

using namespace Wt::Dbo;

UserAccount::UserAccount(WString aName, WString password)
        : m_name(std::move(aName)), m_password(std::move(password))
{}

collection<ptr<Entry> > UserAccount::entriesInRange(const WDate& from,
                                                    const WDate& until) const
{
    return m_entries.find()
            .where("start >= ?").bind(WDateTime(from))
            .where("start < ?").bind(WDateTime(until));
}

void UserAccount::deleteEntriesInRange(const WDate& from, const WDate& until)
{
    auto collection = m_entries.find()
            .where("start >= ?").bind(WDateTime(from))
            .where("start < ?").bind(WDateTime(until));
}

ptr<UserAccount> UserAccount::signIn(Session& session, const WString& login, const WString& password)
{
    Transaction transaction(session);

    ptr<UserAccount> ua =
            session.find<UserAccount>("where name = ? AND password = ?").bind(login).bind(password);

    if (!ua)
    {
        WApplication::instance()
                ->log("notice") << "User [" << login.toUTF8() << "] doesn't exist.";
    }

    transaction.commit();

    return ua;
}

ptr<UserAccount> UserAccount::signUp(Session& session, const WString& login, const WString& password)
{
    Transaction transaction(session);

    ptr<UserAccount> ua =
            session.find<UserAccount>("where name = ? AND password = ?").bind(login).bind(password);


    if (!ua)
    {
        WApplication::instance()
                ->log("notice") << "Creating user [" << login.toUTF8() << "].";

        ua = session.add(cpp14::make_unique<UserAccount>(login, password));
    }

    transaction.commit();

    return ua;
}