#pragma once
#include "Song.h"

namespace Predicates
{
    bool nameAsc(const Song &, const Song &);
    bool nameDesc(const Song &, const Song &);
    bool nameEq(const Song &, const char *);
    bool genreEq(const Song &, const char *);
};