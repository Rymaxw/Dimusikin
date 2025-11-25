#ifndef LIBRARY_MANAGER_H
#define LIBRARY_MANAGER_H

#include "../structs/DataStructures.h"

void initLibrary();
void addSong(Song s);
void editSong(int id, Song newDetails);
void editSongId(int oldId, int newId); // New // New
void deleteSong(int id);
void showAllSongs();
SongNode *getSongById(int id);
SongNode *getSongByTitle(string title); // New
SongNode *getHead(); // Helper to access the list from outside if needed

#endif
