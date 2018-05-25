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

#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLogger.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include "PlannerApplication.h"

#include "Entry.h"
#include "Login.h"
#include "PlannerCalendar.h"
#include "UserAccount.h"

#include <Wt/Dbo/backend/Sqlite3.h>

PlannerApplication::PlannerApplication(const WEnvironment& env)
        : WApplication(env)
{
    auto sqlite3 = cpp14::make_unique<Dbo::backend::Sqlite3>(WApplication::appRoot() + "planner.db");
    sqlite3->setProperty("show-queries", "true");
    m_session.setConnection(std::move(sqlite3));

    m_session.mapClass<UserAccount>("user_account");
    m_session.mapClass<Entry>("entry");

    dbo::Transaction transaction(m_session);
    try
    {
        m_session.createTables();
        log("info") << "Database created";
    }
    catch (...)
    {
        log("info") << "Using existing database";
    }

    transaction.commit();

    messageResourceBundle().use(appRoot() + "planner");
    messageResourceBundle().use(appRoot() + "calendar");

    useStyleSheet("planner.css");

    Login* login = root()->addWidget(cpp14::make_unique<Login>());
    login->signInSignal().connect(this, &PlannerApplication::signIn);
    login->signUpSignal().connect(this, &PlannerApplication::signUp);
}

void PlannerApplication::signIn(const WString& login, const WString& password)
{
    dbo::ptr<UserAccount> ua = UserAccount::signIn(m_session, login, password);
    if(ua)
    {
        root()->clear();
        root()->addWidget(cpp14::make_unique<PlannerCalendar>(ua));
    }
}

void PlannerApplication::signUp(const WString& login, const WString& password)
{
    dbo::ptr<UserAccount> ua = UserAccount::signUp(m_session, login, password);
    if(ua)
    {
        root()->clear();
        root()->addWidget(cpp14::make_unique<PlannerCalendar>(ua));
    }
}
