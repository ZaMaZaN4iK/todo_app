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
#include "PlannerApplication.h"
#include "EntryDialog.h"
#include "Entry.h"

#include "SerializeHelper.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WMessageBox.h>

#include <memory>

AllEntriesDialog::AllEntriesDialog(const WString& title, CalendarCell* cell)
        : WDialog(title)
{
    WTemplate* t = contents()->addWidget(cpp14::make_unique<WTemplate>(
            tr("calendar.all-entries")));
    auto wc = cpp14::make_unique<WContainerWidget>();
    m_container = t->bindWidget("entries", std::move(wc));

    dbo::Session& session = PlannerApplication::plannerApplication()->m_session;
    dbo::Transaction transaction(session);

    const auto entries = cell->user()->entriesInRange(cell->date(), cell->date().addDays(1));

    WString format = EntryDialog::timeFormat;
    for (const auto& entry : entries)
    {
        m_container->addWidget(cpp14::make_unique<WText>(entry->start.toString(format) +
                                                       "-" +
                                                       entry->stop.toString(format) +
                                                       ": " + entry->summary +
                                                       ". " + entry->text));
    }

    transaction.commit();

    m_clearButton = m_container->addNew<WPushButton>("Clear all");
    m_clearButton->clicked().connect(bindSafe([this, cell] {
        this->clearAll(cell);
    }));

    m_jsonButton = m_container->addNew<WPushButton>("Get JSON");
    m_jsonButton->clicked().connect(bindSafe([this, cell] {
        this->getJson(cell);
    }));

    auto button = cpp14::make_unique<WPushButton>(tr("calendar.cell.all-entries.close"));
    auto buttonPtr = t->bindWidget("close", std::move(button));
    buttonPtr->clicked().connect(this, &AllEntriesDialog::closeDialog);

    titleBar()->setStyleClass("entry-dialog-main");
    m_container->setStyleClass("entry-dialog-main");
}

void AllEntriesDialog::clearAll(CalendarCell* cell)
{
    dbo::Session& session = PlannerApplication::plannerApplication()->m_session;
    dbo::Transaction transaction(session);

    session.execute("delete from entry where start >= ? and start < ?").bind(WDateTime(cell->date())).
            bind(WDateTime(cell->date().addDays(1)));

    cell->update(cell->user(), cell->date());

    transaction.commit();
    hide();
}

void AllEntriesDialog::getJson(CalendarCell* cell) const
{
    dbo::Session& session = PlannerApplication::plannerApplication()->m_session;
    dbo::Transaction transaction(session);

    auto entries = cell->user()->entriesInRange(cell->date(), cell->date().addDays(1));

    std::string result = Utils::SerializeEntries(entries);

    transaction.commit();

    auto messageBox = m_container->addChild(
            cpp14::make_unique<Wt::WMessageBox>("JSON",
                                              result,
                                              Wt::Icon::Information, Wt::StandardButton::Yes));
    messageBox->setModal(false);

    messageBox->buttonClicked().connect([=] {
        m_container->removeChild(messageBox);
    });

    messageBox->show();
}

void AllEntriesDialog::closeDialog()
{
    hide();
}
