#ifndef PLAYER_ENGINE_H
#define PLAYER_ENGINE_H

#include "../structs/DataStructures.h"
#include <string>

void initPlayer();
void playSong(SongNode *song);
void stopSong();
void nextSong();
void prevSong();
void addToQueue(SongNode *song);
void showQueue();
void showHistory();
SongNode *getCurrentSong();
void setPlayMode(int mode); // 0: Library/Graph, 1: Playlist
void setCurrentPlaylist(std::string playlistName);

#endif
