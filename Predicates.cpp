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
