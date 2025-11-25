#ifndef PLAYLIST_MANAGER_H
#define PLAYLIST_MANAGER_H

#include "../structs/DataStructures.h"

void initPlaylists();
void createPlaylist(string name);
void renamePlaylist(string oldName, string newName); // New
void deletePlaylist(string name);                    // New
void addSongToPlaylist(string playlistName, SongNode *song);
void showAllPlaylists();
void showPlaylistDetails(string playlistName);
PlaylistNode *getPlaylistByName(string name);

#endif
