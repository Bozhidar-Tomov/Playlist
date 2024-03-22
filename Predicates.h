#pragma once
#include "Song.h"

namespace Predicates
{
    bool nameAsc(const Song &, const Song &);
    bool nameDesc(const Song &, const Song &);
    bool nameEq(const Song &, const char *);

    bool genreEq(const Song &, const char *);

    bool DurationAsc(const Song &, const Song &);
    bool DurationDesc(const Song &, const Song &);
    bool DurationEq(const Song &, const Song &);
};

namespace Actions
{
    void printSong(const Song &);
}