#include <iostream>
#include "Playlist.h"
#include "Song.h"
#include "Predicates.h"

int main()
{
    Playlist p;
    p.addSong("song1", 0, 3, 15, "Pr", "song1.dat");
    p.addSong("song1.1", 0, 7, 15, "r", "song1.dat");
    p.addSong("song2", 0, 3, 35, "pReJ", "song2.dat");
    p.addSong("song3", 0, 3, 15, "h", "song3.dat");

    p.raiseKthBits("song3", 3); // 0000 0000 0000 0000 -> 1001 0010 0100 1001
    p.mix("song1", "song2");    // 0101 0110           -> 0000 0011
    p.mix("song2", "song1.1");  // 0101 0101 0110 0001 -> 0000 0011 0110 0001

    p.search(Predicates::nameEq, Actions::printSong, "song1.1");

    std::cout << "============================\n";

    p.sort(Predicates::DurationAsc);
    p.print();

    std::cout << "============================\n";

    p.sort(Predicates::nameDesc);
    p.print();

    p.save("song1", "song1.res.dat");
}