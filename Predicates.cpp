#include <iostream>
#include "Predicates.h"
#include "Utils.h"

bool Predicates::nameAsc(const Song &song1, const Song &song2)
{
    return myStrCmp(song1.getName(), song2.getName()) > 0;
}

bool Predicates::nameDesc(const Song &song1, const Song &song2)
{
    return myStrCmp(song1.getName(), song2.getName()) < 0;
}

bool Predicates::nameEq(const Song &song, const char *name)
{
    return myStrCmp(song.getName(), name) == 0;
}

bool Predicates::genreEq(const Song &song, const char *str)
{
    return song.isGenre(str);
}

bool Predicates::DurationAsc(const Song &song1, const Song &song2)
{
    return song1.getDuration().isBigger(song2.getDuration());
}

bool Predicates::DurationDesc(const Song &song1, const Song &song2)
{
    return song1.getDuration().isLess(song2.getDuration());
}

bool Predicates::DurationEq(const Song &song1, const Song &song2)
{
    return song1.getDuration().isEq(song2.getDuration());
}

void Actions::printSong(const Song &song)
{
    song.print(std::cout);
}
