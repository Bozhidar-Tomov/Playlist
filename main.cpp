#include <iostream>
#include "Playlist.h"
#include "Utils.h"
#include "Song.h"

namespace Predicatess
{
    bool byName(const Song &song1, const Song &song2)
    {
        return myStrCmp(song1.getName(), song2.getName()) > 0;
    }
    bool byNameEq(const Song &song, const char *name)
    {
        return myStrCmp(song.getName(), name) == 0;
    }

    bool isGenreEqual(const Song &song, const char *str)
    {
        return song.isGenre(str);
    }
}

int main()
{
    // Playlist p;
    // // p.addSong("hello", 0, 3, 15, "prej", "song1.dat");
    // p.addSong("cum", 0, 3, 15, "pr", "song1.dat");
    // p.addSong("fuck", 0, 3, 15, "prej", "song2.dat");
    // p.addSong("cunt", 0, 3, 15, "pj", "song3.dat");
    // p.addSong("slay", 0, 3, 15, "ej", "song1.dat");
    // p.addSong("gay", 0, 3, 15, "j", "song1.dat");

    // p.mix("cum", "fuck");
    // p.save("cum", "cum.dat");

    std::cout << sizeof(unsigned char);
}