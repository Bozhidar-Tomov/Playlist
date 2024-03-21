#include "Playlist.h"
#include <iostream>
#include "Utils.h"

bool Playlist::addSong(Song &song)
{
    if (_size >= MAX_PLAYLIST_SIZE)
        return false;

    _songs[_size++] = song;
    return true;
}

void Playlist::print() const
{
    for (int i = 0; i < _size; ++i)
        _songs[i].print(std::cout);
}

void Playlist::search(bool (*predicate)(const Song &))
{
    for (int i = 0; i < _size; ++i)
        if (predicate(_songs[i]))
            _songs[i].print(std::cout);
}

void Playlist::sort(bool (*predicate)(const Song &, const Song &))
{
    int i, j;
    Song key;
    for (i = 1; i < _size; i++)
    {
        key = _songs[i];
        j = i - 1;

        while (j >= 0 && predicate(_songs[j], key))
        {
            _songs[j + 1] = _songs[j];
            j = j - 1;
        }
        _songs[j + 1] = key;
    }
}

bool isNameEqual(const Song &song, const char *name)
{
    return myStrCmp(song.getName(), name);
}

bool Playlist::mix(const char *songName1, const char *songName2)
{
    Song *song1 = Playlist::find(isNameEqual, songName1);
    Song *song2 = Playlist::find(isNameEqual, songName1);

    if (!song1 || !song2)
        return false;

    song1->mix(*song2);
    return true;
}

bool Playlist::raiseKthBits(const char *songName, int k)
{
    Song *song = Playlist::find(isNameEqual, songName);
    if (!song)
        return false;

    song->raiseKthBits(k, true);
}

Song *Playlist::find(bool (*predicate)(const Song &, const char *), const char *str)
{
    for (int i = 0; i < _size; ++i)
        if (predicate(_songs[i], str))
            return &_songs[i];
    return nullptr;
}
