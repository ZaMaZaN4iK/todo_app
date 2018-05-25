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

#ifndef ENTRY_H_
#define ENTRY_H_

#include <Wt/WDateTime.h>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

using namespace Wt;

class UserAccount;

namespace dbo = Dbo;

/*!
  Class for Entry representation
*/
class Entry
{
public:
    dbo::ptr<UserAccount> user;

    WDateTime start;
    WDateTime stop;
    WString summary;
    WString text;

    template<typename Action>
    void persist(Action& a)
    {
        dbo::belongsTo(a, user, "user");

        dbo::field(a, start, "start");
        dbo::field(a, stop, "stop");
        dbo::field(a, summary, "summary");
        dbo::field(a, text, "text");
    }
};

#endif //ENTRY_H_