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

#include "TimeSuggestions.h"

#include <Wt/WContainerWidget.h>

#include <cstdio>
#include <string>

using namespace Wt;

namespace
{
    WSuggestionPopup::Options contactOptions
            = {"<b>",         // highlightBeginTag
               "</b>",        // highlightEndTag
               0,             // listSeparator
               " \\n",        // whitespace
               "0",           // wordSeparators
               ""             // appendReplacedText
            };
}

TimeSuggestions::TimeSuggestions()
        : WSuggestionPopup(WSuggestionPopup::generateMatcherJS(contactOptions),
                           WSuggestionPopup::generateReplacerJS(contactOptions))
{
    for (unsigned i = 0; i < 24; i++)
    {
        char buffer[25];
        std::sprintf(buffer, "%02d", i);
        std::string h = buffer;

        addSuggestion(WString(h + ":00"));
        addSuggestion(WString(h + ":30"));
    }
}

void TimeSuggestions::addSuggestion(const WString& suggestion)
{
    WSuggestionPopup::addSuggestion(suggestion, suggestion);
}
