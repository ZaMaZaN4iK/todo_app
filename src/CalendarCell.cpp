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

#include "AllEntriesDialog.h"
#include "CalendarCell.h"
#include "Entry.h"
#include "EntryDialog.h"
#include "PlannerApplication.h"

#include <Wt/WDate.h>
#include <Wt/WString.h>
#include <Wt/WText.h>

#include <memory>
#include <string>

CalendarCell::CalendarCell() : WContainerWidget()
{
    resize(100, 120);

    setStyleClass("cell");
    setToolTip(tr("calendar.cell.tooltip"));

    clicked().connect(this, &CalendarCell::showEntryDialog);
}

void CalendarCell::update(const dbo::ptr<UserAccount>& user, const WDate& date)
{
    m_date = date;
    m_user = user;

    clear();

    dbo::Session& session = PlannerApplication::plannerApplication()->m_session;
    dbo::Transaction transaction(session);

    WString day;
    day += std::to_string(date.day());
    if (date.day() == 1)
    {
        day += " " + WDate::longMonthName(date.month());
    }
    auto header = std::make_unique<WText>(day);
    header->setStyleClass("cell-header");
    addWidget(std::move(header));

    typedef dbo::collection<dbo::ptr<Entry>> Entries;
    Entries entries = user->entriesInRange(date, date.addDays(1));

    for (Entries::const_iterator i = entries.begin(); i != entries.end(); ++i)
    {

        auto extraPtr = addNew<WText>(tr("calendar.cell.extra").arg((int) (entries.size())));
        extraPtr->setStyleClass("cell-extra");

        extraPtr->clicked().preventPropagation();
        extraPtr->clicked().connect(this, &CalendarCell::showAllEntriesDialog);
        break;
    }

    transaction.commit();
}

void CalendarCell::showEntryDialog()
{
    WString title = tr("calendar.entry.title").arg(m_date.toString("ddd, d MMM yyyy"));

    m_dialog = std::make_unique<EntryDialog>(title, this);
    m_dialog->show();
}

void CalendarCell::showAllEntriesDialog()
{
    WString title =
            tr("calendar.cell.all-entries.title")
                    .arg(m_date.toString("ddd, d MMM yyyy"));

    m_dialog = std::make_unique<AllEntriesDialog>(title, this);
    m_dialog->show();
}
