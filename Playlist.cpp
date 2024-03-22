#include <iostream>
#include <fstream>
#include "Playlist.h"
#include "Predicates.h"

bool Playlist::addSong(const char *name, int hours, int mins, int secs, const char *genre, const char *file)
{
    if (_size >= MAX_PLAYLIST_SIZE)
        return false;

    Song song(name, hours, mins, secs, genre, file);

    if (!song.isValid())
        return false;

    _songs[_size++] = song;
    return true;
}

bool Playlist::raiseKthBits(const char *songName, int k)
{
    Song *song = Playlist::find(Predicates::nameEq, songName);
    if (!song)
        return false;

    song->raiseKthBits(k, true);
    return true;
}

bool Playlist::mix(const char *songName1, const char *songName2)
{
    Song *song1 = Playlist::find(Predicates::nameEq, songName1);
    const Song *song2 = Playlist::find(Predicates::nameEq, songName2);

    if (!song1 || !song2)
        return false;

    song1->mix(*song2);
    return true;
}

void Playlist::print() const
{
    for (int i = 0; i < _size; ++i)
    {
        _songs[i].print(std::cout);
        std::cout << std::endl;
    }
}

bool Playlist::search(bool (*predicate)(const Song &, const char *), void (*action)(const Song &), const char *str) const
{
    bool has_found = false;

    for (int i = 0; i < _size; ++i)
        if (predicate(_songs[i], str))
        {
            action(_songs[i]);
            has_found = true;
        }

    return has_found;
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

bool Playlist::save(const char *songName, const char *fileName) const
{
    const Song *song = Playlist::find(Predicates::nameEq, songName);

    if (!song)
        return false;

    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    if (!file.is_open())
        return false;

    song->print(file);
    file.close();

    return true;
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
