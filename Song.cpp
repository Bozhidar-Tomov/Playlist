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
    if (size >= MAX_NAME_SIZE)
        return false;

    myStrCpy(_name, name);
    return true;
}

const bool Song::setDuration(int hours, int mins, int secs)
{
    _duration = Time(hours, mins, secs);
    return _duration.isValid();
}

const Time &Song::getDuration() const
{
    return _duration;
}

// Genre Song::getGenre() const
// {
//     return _genre;
// }

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

// void Song::Content::raiseKthBits(int k, bool isReverse)
// {
//     if (!isReverse)
//         for (int i = k; i < _bitsCount; i += k)
//         {
//             char mask = 1;
//             mask <<= 7 - (i % 8);

//             char &bucket = _content[(i / 8)];
//             bucket |= mask;
//         }
//     else
//     {
//         for (int i = _bitsCount - 1; i >= 0; i -= k)
//         {
//             char mask = 1;
//             mask <<= 7 - (i % 8);

//             char &bucket = _content[(i / 8)];
//             bucket |= mask;
//         }
//     }
// }
void Song::Content::raiseKthBits(int k, bool isReverse)
{
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
    // Determine the minimum bits count
    int minBitsCount = _bitsCount < other._bitsCount ? _bitsCount : other._bitsCount;

    // XOR full buckets (all meaningful bits)
    for (int i = 0; i < minBitsCount / 8; ++i)
        _content[i] ^= other._content[i];

    if (minBitsCount % 8 == 0 || minBitsCount == _bitsCount)
        return;

    // XOR meaningful bits in the last bucket
    int i = minBitsCount / 8;
    unsigned char mask = (~0) << (8 - (minBitsCount % 8)); // TODO: << OR >> ??? big o little endian
    _content[i] = (_content[i] ^ other._content[i]) & mask;
}

void Song::Content::saveToBin(std::ostream &out) const
{
    int i = 0;

    while (i < _bitsCount / 8)
        out.write((char *)(&_content[i++]), sizeof(char));
}

// bool Song::Content::setContent(const unsigned char *str, int size)
// {
//     /*
//     We cannot use strLen because the content may be in this form:

//     01100111 00000000 01110100
//     'g'      '\0'     't'

//     strLen will give size 1, while the actual size is 3
//     */

//     if (!str || size < 0 || size > MAX_CONTENT_SIZE)
//         return false;

//     myStrCpy(_content, str);
//     _bitsCount = size;
//     return true;
// }

bool Song::Content::readContentBin(const char *fileName)
{
    std::ifstream file(fileName, std::ios::in | std::ios::binary);

    if (!file.is_open())
        return false;

    file.read((char *)(_content), sizeof(char) * MAX_CONTENT_SIZE);

    file.clear();
    _bitsCount = (file.tellg() * 8) - last1BitPos(_content[file.tellg()]);

    file.close();

    return true;
}

void Song::Genre::print(std::ostream &out) const
{
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
            _genre = EGenre(_genre | EGenre::Rock);
            break;
        case 'p':
            _genre = EGenre(_genre | EGenre::Pop);
            break;
        case 'h':
            _genre = EGenre(_genre | EGenre::HipHop);
            break;
        case 'e':
            _genre = EGenre(_genre | EGenre::Electronic);
            break;
        case 'j':
            _genre = EGenre(_genre | EGenre::Jazz);
            break;
        default:
            return false;
        }
        str++;
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
            if (!(_genre & EGenre::Rock))
                return false;
            break;
        case 'p':
            if (!(_genre & EGenre::Pop))
                return false;
            break;
        case 'h':
            if (!(_genre & EGenre::HipHop))
                return false;
            break;
        case 'e':
            if (!(_genre & EGenre::Electronic))
                return false;
            break;
        case 'j':
            if (!(_genre & EGenre::Jazz))
                return false;
            break;
        default:
            return false;
        }
        genre++;
    }
    return true;
}
