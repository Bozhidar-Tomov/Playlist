#pragma once
#include "Song.h"

class Playlist
{
    Song _songs[MAX_PLAYLIST_SIZE];
    uint8_t _size = 0;

public:
    void addSong(const char *, int, int, int, const char *, const char *); //
    void print() const;                                                    //
    void raiseKthBits(const char *, int);
    void mix(const char *, const char *);
    void search(bool (*predicate)(const Song &, const char *), const char *) const; //
    void sort(bool (*predicate)(const Song &, const Song &));                       //
    void save(const char *, const char *) const;

private:
    Song *find(bool (*predicate)(const Song &, const char *), const char *);
    const Song *find(bool (*predicate)(const Song &, const char *), const char *) const;
};