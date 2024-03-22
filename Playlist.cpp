#include "Playlist.h"
#include <iostream>
#include <fstream>
#include "Utils.h"

namespace Predicates
{
    bool isNameEqual(const Song &song, const char *name)
    {
        return myStrCmp(song.getName(), name);
    }

    bool isGenreEqual(const Song &song, const char *str)
    {
        return song.isGenre(str);
    }
}

void Playlist::addSong(const char *name, int hours, int mins, int secs, const char *genre, const char *file)
{
    if (_size >= MAX_PLAYLIST_SIZE)
        std::cout << "Playlist is full" << std::endl;

    Song song(name, hours, mins, secs, genre, file);

    if (!song.isValid())
        std::cout << "Cannot add song - invalid params" << std::endl;

    _songs[_size++] = song;
    std::cout << "Operation successful" << std::endl;
}

void Playlist::print() const
{
    for (int i = 0; i < _size; ++i)
    {
        _songs[i].print(std::cout);
        std::cout << std::endl;
    }
}

void Playlist::search(bool (*predicate)(const Song &, const char *), const char *str) const
{
    bool has_found = false;
    for (int i = 0; i < _size; ++i)
        if (predicate(_songs[i], str))
        {
            _songs[i].print(std::cout);
            has_found = true;
        }
    if (!has_found)
    {
        std::cout << "Song with predicate ";
        printStr(str, std::cout);
        std::cout << " not found." << std::endl;
    }
}

void Playlist::sort(bool (*predicate)(const Song &, const Song &))
{
    int i = 0, j = 0;
    Song key;
    for (i = 1; i < _size; ++i)
    {
        key = _songs[i];
        j = i - 1;

        while (j >= 0 && predicate(_songs[j], key))
        {
            _songs[j + 1] = _songs[j];
            --j;
        }
        _songs[j + 1] = key;
    }
}

void Playlist::save(const char *songName, const char *fileName) const
{
    const Song *song = Playlist::find(Predicates::isNameEqual, songName);

    if (!song)
        std::cout << "Song not found" << std::endl;

    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    if (!file.is_open())
        std::cout << "Cannot open source file" << std::endl;

    song->print(file);
    std::cout << "Operation successful" << std::endl;
}

void Playlist::mix(const char *songName1, const char *songName2)
{
    Song *song1 = Playlist::find(Predicates::isNameEqual, songName1);
    const Song *song2 = Playlist::find(Predicates::isNameEqual, songName1);

    if (!song1 || !song2)
    {
        std::cout << "Songs not found" << std::endl;
        return;
    }

    song1->mix(*song2);
    std::cout << "Operation successful" << std::endl;
}

void Playlist::raiseKthBits(const char *songName, int k)
{
    Song *song = Playlist::find(Predicates::isNameEqual, songName);
    if (!song)
    {
        std::cout << "Song not found" << std::endl;
        return;
    }

    song->raiseKthBits(k, true);
    std::cout << "Operation successful" << std::endl;
}

Song *Playlist::find(bool (*predicate)(const Song &, const char *), const char *str)
{
    for (int i = 0; i < _size; ++i)
        if (predicate(_songs[i], str))
            return &_songs[i];
    return nullptr;
}
const Song *Playlist::find(bool (*predicate)(const Song &, const char *), const char *str) const
{
    for (int i = 0; i < _size; ++i)
        if (predicate(_songs[i], str))
            return &_songs[i];
    return nullptr;
}
