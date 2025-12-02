#include "PlayerEngine.h"
#include "../graph/GraphBuilder.h"
#include "../library/LibraryManager.h"
#include "../playlist/PlaylistManager.h"
#include <iostream>

using namespace std;

// Player State
SongNode *currentSong = nullptr;
int playMode = 0; // 0: Library (Graph), 1: Playlist
string currentPlaylistName = "";
PlaylistItemNode *currentPlaylistNode =
    nullptr; // To track position in playlist

// Queue (Next Up)
Queue q;

// Stack (History)
Stack history;

void initPlayer() {
  q.front = nullptr;
  q.rear = nullptr;
  history.top = nullptr;
  currentSong = nullptr;
}

// Queue Operations
void enqueue(SongNode *song) {
  QueueNode *newNode = new QueueNode;
  newNode->song = song;
  newNode->next = nullptr;
  if (q.rear == nullptr) {
    q.front = newNode;
    q.rear = newNode;
  } else {
    q.rear->next = newNode;
    q.rear = newNode;
  }
}

SongNode *dequeue() {
  if (q.front == nullptr)
    return nullptr;
  QueueNode *temp = q.front;
  SongNode *song = temp->song;
  q.front = q.front->next;
  if (q.front == nullptr)
    q.rear = nullptr;
  delete temp;
  return song;
}

// Stack Operations
void pushHistory(SongNode *song) {
  StackNode *newNode = new StackNode;
  newNode->song = song;
  newNode->next = history.top;
  history.top = newNode;
}

SongNode *popHistory() {
  if (history.top == nullptr)
    return nullptr;
  StackNode *temp = history.top;
  SongNode *song = temp->song;
  history.top = history.top->next;
  delete temp;
  return song;
}

// Player Logic
void setPlayMode(int mode) {
  playMode = mode;
  cout << "Mode Player diubah ke: "
       << (mode == 0 ? "Library/Graph" : "Playlist") << endl;
}

void setCurrentPlaylist(string playlistName) {
  currentPlaylistName = playlistName;
  PlaylistNode *pl = getPlaylistByName(playlistName);
  if (pl) {
    currentPlaylistNode = pl->head; // Reset to start
    cout << "Playlist aktif: " << playlistName << endl;
  } else {
    cout << "Playlist tidak ditemukan." << endl;
  }
}

void playSong(SongNode *song) {
  if (song == nullptr)
    return;

  if (currentSong != nullptr) {
    pushHistory(currentSong);
  }
  currentSong = song;
  cout << ">>> SEDANG MEMUTAR: " << currentSong->data.title << " - "
       << currentSong->data.artist << " <<<" << endl;
}

void stopSong() {
  if (currentSong == nullptr) {
    cout << "Tidak ada lagu yang sedang diputar." << endl;
    return;
  }
  cout << "Lagu '" << currentSong->data.title << "' dihentikan." << endl;
  currentSong = nullptr;
}

void addToQueue(SongNode *song) {
  enqueue(song);
  cout << "Lagu ditambahkan ke antrean." << endl;
}

void showQueue() {
  if (q.front == nullptr) {
    cout << "Antrean kosong." << endl;
    return;
  }
  QueueNode *curr = q.front;
  cout << "=== Antrean Lagu ===" << endl;
  while (curr != nullptr) {
    cout << "- " << curr->song->data.title << endl;
    curr = curr->next;
  }
}

void showHistory() {
  if (history.top == nullptr) {
    cout << "Riwayat kosong." << endl;
    return;
  }
  StackNode *curr = history.top;
  cout << "=== Riwayat Putar ===" << endl;
  while (curr != nullptr) {
    cout << "- " << curr->song->data.title << endl;
    curr = curr->next;
  }
}

SongNode *getCurrentSong() { return currentSong; }

void nextSong() {
  // 1. Check Queue
  SongNode *next = dequeue();
  if (next != nullptr) {
    playSong(next);
    return;
  }

  // 2. Logic based on Mode
  if (playMode == 0) { // Library Mode -> Genre Sequence
    if (currentSong == nullptr) {
      cout << "Tidak ada lagu yang sedang diputar." << endl;
      return;
    }

    // Genre Sequence Logic: Find next song with SAME genre
    string currentGenre = currentSong->data.genre;
    SongNode *curr = currentSong->next;
    bool found = false;

    while (curr != nullptr) {
      if (curr->data.genre == currentGenre) {
        playSong(curr);
        cout << "(Auto-play: Genre " << currentGenre << ")" << endl;
        found = true;
        break;
      }
      curr = curr->next;
    }

    if (!found) {
      cout << "Akhir dari genre '" << currentGenre << "'." << endl;
    }
  } else { // Playlist Mode
    if (currentPlaylistNode != nullptr &&
        currentPlaylistNode->next != nullptr) {
      currentPlaylistNode = currentPlaylistNode->next;
      playSong(currentPlaylistNode->song);
    } else {
      cout << "Akhir dari Playlist." << endl;
    }
  }
}

void prevSong() {
  SongNode *prev = popHistory();
  if (prev != nullptr) {
    // Don't push current to history when going back, or do?
    // Usually "Back" just goes back.
    currentSong = prev;
    cout << ">>> MUNDUR KE: " << currentSong->data.title << " <<<" << endl;
  } else {
    cout << "Tidak ada history." << endl;
  }
}
