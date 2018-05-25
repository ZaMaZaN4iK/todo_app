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

#ifndef ALL_ENTRIES_DIALOG_H_
#define ALL_ENTRIES_DIALOG_H_

#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>

#include "CalendarCell.h"

using namespace Wt;

/*!
  Class for working with entries in calendar
*/
class AllEntriesDialog : public WDialog
{
public:
    AllEntriesDialog(const WString &title, CalendarCell *cell);

private:
    void clearAll(CalendarCell* cell);
    void getJson(CalendarCell* cell) const;

    void closeDialog();

    WPushButton* m_clearButton;
    WPushButton* m_jsonButton;

    WContainerWidget* m_container;
};

#endif // ALL_ENTRIES_DIALOG_H_
