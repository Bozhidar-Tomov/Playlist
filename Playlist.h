#pragma once
#include "Song.h"

class Playlist
{
    Song _songs[MAX_PLAYLIST_SIZE];
    uint8_t _size = 0;

public:
    bool addSong(const char *, int, int, int, const char *, const char *);

    bool raiseKthBits(const char *, int);
    bool mix(const char *, const char *);
    void print() const;

    bool search(bool (*)(const Song &, const char *), void (*)(const Song &), const char *) const;
    void sort(bool (*)(const Song &, const Song &));

    bool save(const char *, const char *) const;

private:
    Song *find(bool (*)(const Song &, const char *), const char *);
    const Song *find(bool (*)(const Song &, const char *), const char *) const;
};