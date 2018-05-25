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

#ifndef WT_TODO_SERIALIZEHELPER_H
#define WT_TODO_SERIALIZEHELPER_H

#include "Entry.h"

#include <Wt/Dbo/collection.h>
#include <Wt/Dbo/ptr.h>

#include <string>

namespace Utils
{

/*!
 * \brief Serialize entry.
 * \param[in] value Entry for serialization.
 * \return String with serialized entry
 * \details Implementation is based on built-in JSON library
 */
std::string SerializeEntry(const Wt::Dbo::ptr<Entry> value);

/*!
 * \brief Serialize entries.
 * \param[in] value Entry collection for serialization.
 * \return String with serialized entries
 * \details Implementation is based on built-in JSON library
 */
std::string SerializeEntries(const Wt::Dbo::collection<Wt::Dbo::ptr<Entry>> value);

}

#endif //WT_TODO_SERIALIZEHELPER_H
