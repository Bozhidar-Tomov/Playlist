#include "Song.h"
#include "Utils.h"

void Song::raiseKthBits(int k, bool isReverse)
{
    _content.raiseKthBits(k, isReverse);
}

void Song::mix(const Song &other)
{
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
    int i = 0;
    int minBitsCount = _bitsCount < other._bitsCount ? _bitsCount : other._bitsCount;

    // XOR full buckets (all meaningful bits)
    for (; i < minBitsCount / 8; ++i)
        _content[i] ^= other._content[i];

    // XOR meaningful bits in the last bucket
    i *= 8;
    
    while (i < _bitsCount && i < other._bitsCount)
    {
        unsigned char &thisBucket = _content[i / 8];
        unsigned char otherBucket = other._content[i / 8];

        unsigned char mask = otherBucket & (1 << 7 - (i % 8));

        thisBucket ^= mask;
        ++i;
    }
}

void Song::Content::xOR(const Content &other)
{
    // Determine the minimum bits count
    int minBitsCount = _bitsCount < other._bitsCount ? _bitsCount : other._bitsCount;

    // XOR full buckets (all meaningful bits)
    for (int i = 0; i < minBitsCount / 8; ++i)
        _content[i] ^= other._content[i];

    // XOR meaningful bits in the last bucket
    if (minBitsCount % 8 != 0)
    {
        int i = minBitsCount / 8;
        unsigned char mask = (1 << (8 - minBitsCount % 8)) - 1;
        _content[i] = (_content[i] ^ other._content[i]) & mask;
    }
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
