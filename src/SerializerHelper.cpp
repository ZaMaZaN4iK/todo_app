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

#include "SerializeHelper.h"

#include <Wt/Dbo/ptr.h>
#include <Wt/Json/Array.h>
#include <Wt/Json/Object.h>
#include <Wt/Json/Serializer.h>

#include <string>

namespace Utils
{

std::string SerializeEntry(const Wt::Dbo::ptr<Entry> entry)
{
    Wt::Json::Object object;
    object["start"] = Wt::Json::Value(entry->start.toString());
    object["stop"] = Wt::Json::Value(entry->stop.toString());
    object["summary"] = Wt::Json::Value(entry->summary);
    object["text"] = Wt::Json::Value(entry->text);

    return Wt::Json::serialize(object);
}

std::string SerializeEntries(const Wt::Dbo::collection<Wt::Dbo::ptr<Entry>> entries)
{
    Wt::Json::Array array;

    for(const auto& entry : entries)
    {
        Wt::Json::Object temp;
        temp["start"] = Wt::Json::Value(entry->start.toString());
        temp["stop"] = Wt::Json::Value(entry->stop.toString());
        temp["summary"] = Wt::Json::Value(entry->summary);
        temp["text"] = Wt::Json::Value(entry->text);

        array.push_back(temp);
    }

    return Wt::Json::serialize(array);
}

} // namespace Utils

