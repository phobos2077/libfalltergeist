/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// C++ standard includes

// libfalltergeist includes
#include "../Msg/Message.h"

// Third party includes

namespace libfalltergeist
{
namespace Msg
{

Message::Message()
{
}

Message::~Message()
{
}

void Message::setNumber(unsigned int number)
{
    _number = number;
}

unsigned int Message::number()
{
    return _number;
}

void Message::setSound(std::string sound)
{
    _sound = sound;
}

std::string Message::sound()
{
    return _sound;
}

void Message::setText(std::string text)
{
    _text = text;
}

std::string Message::text()
{
    return _text;
}

std::string* Message::textPointer()
{
    return &_text;
}

Message::operator std::string ()
{
    return _text;
}

}
}
