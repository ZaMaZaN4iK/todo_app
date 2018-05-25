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

#ifndef ENTRY_DIALOG_H_
#define ENTRY_DIALOG_H_

#include "CalendarCell.h"

#include <Wt/WDialog.h>
#include <Wt/WDate.h>
#include <Wt/WDateTime.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>

using namespace Wt;

/*!
  Class for entry dialog on Calendar widget
*/
class EntryDialog : public WDialog
{
public:
    EntryDialog(const WString& title, CalendarCell* cell);

private:
    /*!
    * \brief Return timestamp from time and date
    */
    WDateTime timeStamp(const WString& time, const WDate& day);

    /*!
    * \brief Return description for the entry
    */
    WString description();

    /*!
    * \brief Runs after click() event on Ok button
    */
    void ok();

    /*!
    * \brief Runs after click() event on Cancel button
    */
    void cancel();

public:
    static WString timeFormat;

private:
    CalendarCell* m_cell;

    WLineEdit* m_summary;
    WLineEdit* m_start;
    WLineEdit* m_stop;
    WTextArea* m_description;
};

#endif //ENTRY_DIALOG_H_
