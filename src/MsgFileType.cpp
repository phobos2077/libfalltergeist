/*
 * Copyright 2012-2013 Falltergeist Developers.
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

#include "../src/MsgFileType.h"
#include "../src/DatFileItem.h"
#include "../src/MsgMessage.h"
#include <string>
#include <cstdlib>

namespace libfalltergeist
{

MsgFileType::MsgFileType(DatFileItem * datFileItem) : _datFileItem(datFileItem)
{
    _messages = 0;
    open();
}

MsgFileType::~MsgFileType()
{
    delete _messages;
}

void MsgFileType::open()
{
    _messages = new std::vector<MsgMessage *>;

    datFileItem()->setPosition(0);

    unsigned int i = 0;
    unsigned char chr = 0;
    while (chr != '{' && i < datFileItem()->size())
    {
        chr = datFileItem()->readUint8(); i++;
        if (chr == '{')
        {
            std::string number = "";
            std::string sound = "";
            std::string text = "";

            // number
            while (chr != '}')
            {
                chr = datFileItem()->readUint8(); i++;
                if (chr != '}') number.push_back(chr);
            }

            // sound
            while (chr != '{')
            {
                chr = datFileItem()->readUint8(); i++;
            }

            while (chr != '}')
            {
                chr = datFileItem()->readUint8(); i++;
                if (chr != '}') sound.push_back(chr);
            }

            // text
            while (chr != '{')
            {
                chr = datFileItem()->readUint8(); i++;
            }

            while (chr != '}')
            {
                chr = datFileItem()->readUint8(); i++;
                if (chr != '}') text.push_back(chr);
            }

            MsgMessage * message = new MsgMessage();
            message->setNumber(atoi(number.c_str()));
            message->setSound(sound.c_str());
            message->setText(text.c_str());
            _messages->push_back(message);
        }
    }
}

DatFileItem * MsgFileType::datFileItem()
{
    return _datFileItem;
}

std::vector<MsgMessage *> * MsgFileType::messages()
{
    return _messages;
}

}
