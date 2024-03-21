#include "Song.h"
#include "Utils.h"
#include <fstream>
#include <iostream>

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
    _content.print(out);
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

void Song::Content::print(std::ostream &out) const
{
    int i = 0;

    while (!out.eof() && i < MAX_CONTENT_SIZE)
        out.write((char *)(&_content[i++]), sizeof(char));
}

bool Song::Content::setContent(const unsigned char *str, int size)
{
    /*
    We cannot use strLen because the content may be in this form:

    01100111 00000000 01110100
    'g'      '\0'     't'

    strLen will give size 1, while the actual size is 3
    */

    if (!str || size < 0 || size > MAX_CONTENT_SIZE)
        return false;

    myStrCpy(_content, str);
    _bitsCount = size;
    return true;
}

bool Song::Content::readContentBin(const char *fileName)
{
    std::ifstream file(fileName, std::ios::in | std::ios::binary);

    if (!file.is_open())
        return false;

    int i = 0;

    while (!file.eof() && i < MAX_CONTENT_SIZE)
        file.read((char *)(&_content[i++]), sizeof(char));

    _bitsCount = i * 8;

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

void Song::Genre::setGenre(const char *str)
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
            return;
        }
        str++;
    }
}
