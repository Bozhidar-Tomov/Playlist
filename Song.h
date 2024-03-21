#pragma once
#include "constants.h"
#include <stddef.h> // cstddef
#include <ostream>
#include "Time.h"

class Song
{
    char _name[MAX_NAME_SIZE + 1] = {'\0'};
    Time _duration;
    struct Genre
    {
        enum EGenre : uint8_t
        {
            Null = 0,
            Rock = 1,
            Pop = 2,
            HipHop = 4,
            Electronic = 8,
            Jazz = 16,
        } _genre;

        void print(std::ostream &) const;
        void setGenre(const char *);
    } _genre;

    struct Content
    {
        unsigned char _content[MAX_CONTENT_SIZE] = {'\0'};
        int _bitsCount = 0;

        Content() = default;
        bool setContent(const unsigned char *, int size);
        bool readContentBin(const char *);
        void raiseKthBits(int, bool);
        void xOR(const Content &other);
        void print(std::ostream &) const;
    } _content;

public:
    Song() = default;

    void raiseKthBits(int, bool);
    void mix(const Song &other);

    const char *getName() const;
    const Time &getDuration() const;

    void print(std::ostream &) const;
};