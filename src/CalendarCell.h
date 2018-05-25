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

#ifndef CALENDAR_CELL_H_
#define CALENDAR_CELL_H_

#include "UserAccount.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WDialog.h>

using namespace Wt;

/*!
  Calendar cell class
*/
class CalendarCell : public WContainerWidget
{
public:
    CalendarCell();

    /*!
    * \brief Updates Calendar cell
    */
    void update(const dbo::ptr<UserAccount>& user, const WDate& date);

    WDate date()
    { return m_date; }

    dbo::ptr<UserAccount> user()
    { return m_user; }

private:
    WDate m_date;
    dbo::ptr<UserAccount> m_user;
    std::unique_ptr<WDialog> m_dialog;

    /*!
    * \brief Show entry dialog
    */
    void showEntryDialog();

    /*!
    * \brief Show all entries dialog
    */
    void showAllEntriesDialog();
};

#endif //CALENDAR_CELL_H_
