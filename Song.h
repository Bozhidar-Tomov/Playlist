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
        bool setGenre(const char *);
        bool isGenre(const char *) const;
    } _genre;

    bool _isValid = true;

    struct Content
    {
        unsigned char _content[MAX_CONTENT_SIZE] = {'\0'};
        int _bitsCount = 0;

        Content() = default;
        bool readContentBin(const char *);
        void raiseKthBits(int, bool);
        void xOR(const Content &other);
        void saveToBin(std::ostream &) const;
    } _content;

public:
    Song() = default;
    Song(const char *, int, int, int, const char *, const char *);

    void raiseKthBits(int, bool);
    void mix(const Song &other);

    const char *getName() const;
    bool setName(const char *);

    const Time &getDuration() const;
    const bool setDuration(int, int, int);

    void print(std::ostream &) const;

    bool isGenre(const char *) const;

    bool setGenre(const char *);
    bool setContent(const char *);

    bool isValid() const;
};