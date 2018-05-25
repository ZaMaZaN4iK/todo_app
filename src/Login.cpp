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

#include "Login.h"

#include "Session.h"

#include <Wt/WBootstrapTheme.h>
#include <Wt/WBreak.h>
#include <Wt/WLabel.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WValidator.h>

#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>

#include <memory>

Login::Login() :
        WContainerWidget()
{
    //setStyleClass("login");

    m_userNameEdit = this->addNew<WLineEdit>();
    m_userNameEdit->setFocus();
    m_userNameEdit->setValidator(std::make_shared<WValidator>(true));
    WLabel* userNameLabel = this->addNew<WLabel>(tr("login.userName"));
    userNameLabel->setBuddy(m_userNameEdit);
    this->addNew<WBreak>();

    m_passwordEdit = this->addNew<WLineEdit>();
    m_passwordEdit->setEchoMode(EchoMode::Password);
    m_passwordEdit->setValidator(std::make_shared<WValidator>(true));
    WLabel* passwordLabel = this->addNew<WLabel>(tr("login.password"));
    passwordLabel->setBuddy(m_passwordEdit);
    this->addNew<WBreak>();

    m_userNameEdit->enterPressed().connect(this, &Login::loginEnterPressed);
    m_passwordEdit->enterPressed().connect(this, &Login::loginEnterPressed);

    m_signInButton = this->addNew<WPushButton>(tr("login.loginButton"));
    m_signInButton->clicked().connect(this, &Login::signInClicked);
    m_signUpButton = this->addNew<WPushButton>(tr("login.signUpButton"));
    m_signUpButton->clicked().connect(this, &Login::signUpClicked);
}

void Login::loginEnterPressed()
{
    if (m_userNameEdit->validate() == ValidationState::Valid &&
        m_passwordEdit->validate() == ValidationState::Valid)
    {
        signIn();
    }
}

void Login::signInClicked(const WMouseEvent& me)
{
    if (m_userNameEdit->validate() == ValidationState::Valid &&
        m_passwordEdit->validate() == ValidationState::Valid)
    {
        signIn();
    }
}

void Login::signUpClicked(const WMouseEvent& me)
{
    if (m_userNameEdit->validate() == ValidationState::Valid &&
        m_passwordEdit->validate() == ValidationState::Valid)
    {
        signUp();
    }
}

void Login::signIn()
{
    m_signInSig.emit(m_userNameEdit->text(), m_passwordEdit->text());
}

void Login::signUp()
{
    m_signUpSig.emit(m_userNameEdit->text(), m_passwordEdit->text());
}