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

#ifndef LOGIN_H_
#define LOGIN_H_

#include "Session.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

using namespace Wt;

/*!
  Class for Login
*/
class Login : public WContainerWidget
{
public:
    Login();

    Signal<WString, WString>& signInSignal()
    { return m_signInSig; }

    Signal<WString, WString>& signUpSignal()
    { return m_signUpSig; }

private:
    /*!
    * \brief Process the login into the application
    * \details Takes parameters from fields and pass them directly to database with some processing
    */
    void loginEnterPressed();

    /*!
    * \brief Process the sign in button click
    * \details Starts after Enter or mouse click() event
    */
    void signInClicked(const WMouseEvent& me);
    /*!
    * \brief Process the sign up button click
    * \details Starts after Enter or mouse click() event
    */
    void signUpClicked(const WMouseEvent& me);

    /*!
    * \brief Process the sign in routine
    */
    void signIn();
    /*!
    * \brief Process the sign up routine
    */
    void signUp();

private:
    Signal<WString, WString> m_signInSig;
    Signal<WString, WString> m_signUpSig;
    WLineEdit* m_userNameEdit;
    WLineEdit* m_passwordEdit;
    WPushButton* m_signInButton;
    WPushButton* m_signUpButton;
};

#endif // LOGIN_H_
