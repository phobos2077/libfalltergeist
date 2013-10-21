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

#ifndef LIBFALLTERGEIST_DATFILEITEM_H
#define LIBFALLTERGEIST_DATFILEITEM_H

// C++ standard includes
#include <string>
#include <fstream>

// libfalltergeist includes
#include "../src/MapFileType.h"

// Third party includes

namespace libfalltergeist
{
class AafFileType;
class BioFileType;
class DatFile;
class FrmFileType;
class GcdFileType;
class LstFileType;
class MsgFileType;
class MapFileType;
class PalFileType;
class ProFileType;
class DatFileEntry;

class DatFileItem: public std::streambuf
{
protected:
    AafFileType * _asAaf;
    BioFileType * _asBio;
    FrmFileType * _asFrm;
    GcdFileType * _asGcd;
    LstFileType * _asLst;
    MapFileType * _asMap;
    MsgFileType * _asMsg;
    PalFileType * _asPal;
    ProFileType * _asPro;

    std::string _filename; // filename with path (path/to/file.ext)

    DatFileEntry * _datFileEntry;
    std::ifstream * _stream;


    char * _buffer;
    int _size;

    bool _initialized;
    void _initialize();

public:

    virtual std::streambuf::int_type underflow();
    //virtual std::streampos seekpos(std::streampos sp, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out);
    //virtual std::streambuf::int_type overflow(std::streambuf::int_type value);
    //virtual int sync();

    //DatFileItem(DatFile * datFile);
    DatFileItem(std::ifstream * stream);
    DatFileItem(DatFileEntry * datFileEntry);
    ~DatFileItem();

    void setFilename(const std::string filename);
    std::string filename();

    unsigned int size();

    void setPosition(unsigned int position);
    unsigned int position();

    void readBytes(char * destination, unsigned int size);
    void skipBytes(unsigned int numberOfBytes);

    DatFileItem& operator>>(unsigned int &value);
    DatFileItem& operator>>(int &value);
    DatFileItem& operator>>(unsigned short &value);
    DatFileItem& operator>>(short &value);
    DatFileItem& operator>>(unsigned char &value);
    DatFileItem& operator>>(char &value);

    FrmFileType * asFrmFileType();
    PalFileType * asPalFileType();
    LstFileType * asLstFileType();
    AafFileType * asAafFileType();
    MapFileType * asMapFileType(ProFileTypeLoaderCallback callback);
    MsgFileType * asMsgFileType();
    BioFileType * asBioFileType();
    GcdFileType * asGcdFileType();
    ProFileType * asProFileType();

};

}
#endif //LIBFALLTERGEIST_DATFILEITEM_H
