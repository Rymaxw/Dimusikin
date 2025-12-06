#ifndef JSON_HELPER_H
#define JSON_HELPER_H

#include "../structs/DataStructures.h"
#include <string>
#include <vector>

using namespace std;

// Save/Load Songs
void saveSongsToJson(string filename, SongNode *head);
void loadSongsFromJson(string filename);

// Save/Load Playlists
void savePlaylistsToJson(string filename, PlaylistNode *head);
void loadPlaylistsFromJson(string filename);

#endif
