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

#include "EntryDialog.h"
#include "TimeSuggestions.h"
#include "Entry.h"
#include "PlannerApplication.h"

#include <Wt/WDate.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTemplate.h>
#include <Wt/WTextArea.h>
#include <Wt/WPushButton.h>
#include <Wt/WRegExpValidator.h>
#include <Wt/WString.h>

#include <Wt/Dbo/WtSqlTraits.h>

#include <memory>

using namespace Wt;

WString EntryDialog::timeFormat = WString("HH:mm");

EntryDialog::EntryDialog(const WString& title, CalendarCell* cell)
        : WDialog(title)
{
    m_cell = cell;

    WTemplate* t = contents()->addWidget(std::make_unique<WTemplate>());
    t->setTemplateText(tr("calendar.entry"));

    auto summaryPtr = std::make_unique<WLineEdit>();
    m_summary = t->bindWidget("summary", std::move(summaryPtr));
    m_summary->setValidator(std::make_shared<WValidator>());

    auto timeValidator = std::make_shared<WRegExpValidator>("^([0-1][0-9]|[2][0-3]):([0-5][0-9])$");
    auto startPtr = std::make_unique<WLineEdit>();
    m_start = t->bindWidget("start", std::move(startPtr));
    m_start->setTextSize(5);
    m_start->setValidator(timeValidator);

    auto stopPtr = std::make_unique<WLineEdit>();
    m_stop = t->bindWidget("stop", std::move(stopPtr));
    m_stop->setTextSize(5);
    m_stop->setValidator(timeValidator);

    auto descriptionPtr = std::make_unique<WTextArea>();
    m_description = t->bindWidget("description", std::move(descriptionPtr));

    TimeSuggestions* suggestions = contents()->addWidget(std::make_unique<TimeSuggestions>());
    suggestions->forEdit(m_start);
    suggestions->forEdit(m_stop);

    auto okPtr = std::make_unique<WPushButton>(tr("calendar.entry.ok"));
    auto ok = t->bindWidget("ok", std::move(okPtr));
    ok->clicked().connect(this, &EntryDialog::ok);

    auto cancelPtr = std::make_unique<WPushButton>(tr("calendar.entry.cancel"));
    auto cancel = t->bindWidget("cancel", std::move(cancelPtr));
    cancel->clicked().connect(this, &EntryDialog::cancel);

    titleBar()->setStyleClass("entry-dialog-main");
    contents()->setStyleClass("entry-dialog-main");
}

WDateTime EntryDialog::timeStamp(const WString& time, const WDate& day)
{
    WString timeStamp = day.toString("dd/MM/yyyy ");
    timeStamp += time;
    return WDateTime::fromString(timeStamp, "dd/MM/yyyy " + timeFormat);
}

WString EntryDialog::description()
{
    return m_description->text();
}

void EntryDialog::ok()
{
    Dbo::Session& session = PlannerApplication::plannerApplication()->m_session;
    dbo::Transaction transaction(session);

    dbo::ptr<Entry> e =
            PlannerApplication::plannerApplication()->m_session.add(
                    std::make_unique<Entry>());
    e.modify()->start = timeStamp(m_start->text(), m_cell->date());
    e.modify()->stop = timeStamp(m_stop->text(), m_cell->date());
    e.modify()->summary = m_summary->text().toUTF8();
    e.modify()->text = description().toUTF8();
    e.modify()->user = m_cell->user();

    m_cell->update(m_cell->user(), m_cell->date());

    transaction.commit();
    hide();
}

void EntryDialog::cancel()
{
    hide();
}
