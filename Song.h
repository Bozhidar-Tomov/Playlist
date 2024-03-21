#pragma once
#include "constants.h"
#include <stddef.h> // cstddef
#include "Time.h"

enum class Genre : char
{
    Null = 0,
    Rock = 1,
    Pop = 2,
    HipHop = 4,
    Electronic = 8,
    Jazz = 16
};

class Song
{

    char _name[MAX_NAME_SIZE + 1] = {'\0'};
    Time _duration;
    Genre _genre = Genre::Null;

    struct Content
    {
        unsigned char _content[MAX_CONTENT_SIZE] = {'\0'};
        int _bitsCount = 0;

        Content() = default;
        bool setContent(const unsigned char *, int size);
        void raiseKthBits(int, bool);
        void xOR(const Content &other);
    } _content;

public:
    Song() = default;

    void raiseKthBits(int, bool);
    void mix(const Song &other);

    const char *getName() const;
    size_t getDuration() const;
    Genre getGenre() const;
    const char *getContent() const;
};