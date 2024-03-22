#include "Song.h"
#include "Utils.h"
#include <fstream>
#include <iostream>

Song::Song(const char *name, int hours, int mins, int secs, const char *genre, const char *fileName)
{
    if (setName(name) && setDuration(hours, mins, secs) && setGenre(genre) && setContent(fileName))
        _isValid = true;
    else
        _isValid = false;
}

void Song::raiseKthBits(int k, bool isReverse)
{
    _content.raiseKthBits(k, isReverse);
}

void Song::mix(const Song &other)
{
    _content.xOR(other._content);
}

const char *Song::getName() const
{
    return _name;
}

bool Song::setName(const char *name)
{
    int size = myStrLen(name);
    if (size > MAX_NAME_SIZE)
        return false;

    myStrCpy(_name, name);
    return true;
}

const Time &Song::getDuration() const
{
    return _duration;
}

bool Song::setDuration(int hours, int mins, int secs)
{
    _duration = Time(hours, mins, secs);
    return _duration.isValid();
}

void Song::print(std::ostream &out) const
{
    if (&out == &std::cout)
    {
        out << "Name: ";
        printStr(_name, out);
        out << "\nDuration: ";
        _duration.serialize(out);
        out << "\nGenre: ";
        _genre.print(out);
        out << std::endl;
        return;
    }
    _content.saveToBin(out);
}

bool Song::isGenre(const char *genre) const
{
    return _genre.isGenre(genre);
}

bool Song::setGenre(const char *str)
{
    return _genre.setGenre(str);
}

bool Song::setContent(const char *fileName)
{
    return _content.readContentBin(fileName);
}

bool Song::isValid() const
{
    return _isValid;
}

void Song::Content::raiseKthBits(int k, bool isReverse)
{
    int _bitsCount = _size * 8;

    int start = isReverse ? _bitsCount - 1 : k;
    int end = isReverse ? 0 : _bitsCount;
    int step = isReverse ? -k : k;

    for (int i = start; (isReverse ? i >= end : i < end); i += step)
    {
        unsigned char mask = 1;
        mask <<= 7 - (i % 8);

        unsigned char &bucket = _content[(i / 8)];
        bucket |= mask;
    }
}

void Song::Content::xOR(const Content &other)
{
    int minSize = _size < other._size ? _size : other._size;

    // XOR full buckets (all meaningful bits)
    for (int i = 0; i < minSize; ++i)
        _content[i] ^= other._content[i];

    /* As far as the problem describes, the content is of size multiple of 8 (1 char)

    XOR meaningful bits in the last bucket that are not multiple of 8

    int i = minBitsCount / 8;
    unsigned char mask = (~0) << (8 - (minBitsCount % 8));
    _content[i] = (_content[i] ^ other._content[i]) & mask;
    */
}

void Song::Content::saveToBin(std::ostream &out) const
{
    out.write((const char *)_content, sizeof(unsigned char) * _size);
}

bool Song::Content::readContentBin(const char *fileName)
{
    std::ifstream file(fileName, std::ios::in | std::ios::binary);

    if (!file.is_open())
        return false;

    file.read((char *)(_content), sizeof(unsigned char) * MAX_CONTENT_SIZE);

    file.clear();
    _size = file.tellg() * sizeof(unsigned char); // file.tellg() * 1

    file.close();

    return true;
}

void Song::Genre::print(std::ostream &out) const
{
    if (EGenre::Null)
    {
        out << "Genre not available.";
        return;
    }

    if (_genre & EGenre::Rock)
        out << "Rock ";
    if (_genre & EGenre::Pop)
        out << "Pop ";
    if (_genre & EGenre::HipHop)
        out << "HipHop ";
    if (_genre & EGenre::Electronic)
        out << "Electronic ";
    if (_genre & EGenre::Jazz)
        out << "Jazz ";
}

bool Song::Genre::setGenre(const char *str)
{
    _genre = EGenre::Null;

    while (*str != '\0')
    {
        switch (*str)
        {
        case 'r':
        case 'R':
            _genre = EGenre(_genre | EGenre::Rock);
            break;
        case 'p':
        case 'P':
            _genre = EGenre(_genre | EGenre::Pop);
            break;
        case 'h':
        case 'H':
            _genre = EGenre(_genre | EGenre::HipHop);
            break;
        case 'e':
        case 'E':
            _genre = EGenre(_genre | EGenre::Electronic);
            break;
        case 'j':
        case 'J':
            _genre = EGenre(_genre | EGenre::Jazz);
            break;
        default:
            _genre = EGenre::Null;
            return false;
        }
        ++str;
    }

    return true;
}

bool Song::Genre::isGenre(const char *genre) const
{
    while (*genre != '\0')
    {
        switch (*genre)
        {
        case 'r':
        case 'R':
            if (!(_genre & EGenre::Rock))
                return false;
            break;
        case 'p':
        case 'P':
            if (!(_genre & EGenre::Pop))
                return false;
            break;
        case 'h':
        case 'H':
            if (!(_genre & EGenre::HipHop))
                return false;
            break;
        case 'e':
        case 'E':
            if (!(_genre & EGenre::Electronic))
                return false;
            break;
        case 'j':
        case 'J':
            if (!(_genre & EGenre::Jazz))
                return false;
            break;
        default:
            return false;
        }
        ++genre;
    }
    return true;
}
