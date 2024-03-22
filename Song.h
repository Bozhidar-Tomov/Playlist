#pragma once
#include <ostream>
#include <stddef.h>

#include "Time.h"
#include "constants.h"

class Song
{
    char _name[MAX_NAME_SIZE + 1] = {'\0'};
    Time _duration;

    struct Genre
    {
    private:
        enum EGenre : uint8_t
        {
            Null = 0,
            Rock = 1,
            Pop = 2,
            HipHop = 4,
            Electronic = 8,
            Jazz = 16,
        } _genre;

    public:
        void print(std::ostream &) const;
        bool setGenre(const char *);
        bool isGenre(const char *) const;
    } _genre;

    struct Content
    {
    private:
        unsigned char _content[MAX_CONTENT_SIZE] = {'\0'};
        int _size = 0;

    public:
        Content() = default;
        bool readContentBin(const char *);
        void raiseKthBits(int, bool);
        void xOR(const Content &);
        void saveToBin(std::ostream &) const;
    } _content;

    bool _isValid = true;

public:
    Song() = default;
    Song(const char *, int, int, int, const char *, const char *);

    const char *getName() const;
    bool setName(const char *);

    const Time &getDuration() const;
    bool setDuration(int, int, int);

    bool setGenre(const char *);
    bool setContent(const char *);

    bool isGenre(const char *) const;
    bool isValid() const;

    void raiseKthBits(int, bool);
    void mix(const Song &);

    void print(std::ostream &) const;
};