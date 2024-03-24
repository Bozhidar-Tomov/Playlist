#pragma once
#include "Song.h"

typedef bool (*SongMatcher)(const Song &, const char *);
typedef void (*SongProc)(const Song &);
typedef bool (*SongComp)(const Song &, const Song &);

class Playlist
{
    Song _songs[MAX_PLAYLIST_SIZE];
    uint8_t _size = 0;

public:
    bool addSong(const char *, int, int, int, const char *, const char *);

    bool raiseKthBits(const char *, int);
    bool mix(const char *, const char *);
    void print() const;

    bool search(SongMatcher, SongProc, const char *) const;
    void sort(SongComp);

    bool save(const char *, const char *) const;

private:
    Song *find(SongMatcher, const char *);
    const Song *find(SongMatcher, const char *) const;
};