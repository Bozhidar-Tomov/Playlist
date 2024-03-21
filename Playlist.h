#pragma once
#include "Song.h"

class Playlist
{
    Song _songs[MAX_PLAYLIST_SIZE];
    uint8_t _size = 0;

    bool addSong(Song &);
    void print() const;
    void search(bool (*predicate)(const Song &));
    void sort(bool (*predicate)(const Song &, const Song &));
    bool mix(const char *, const char *);
    bool raiseKthBits(const char *, int);

private:
    Song *find(bool (*predicate)(const Song &, const char *), const char *);
};