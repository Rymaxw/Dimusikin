#include "PlaylistManager.h"
#include <iomanip>
#include <iostream>

using namespace std;

PlaylistNode *plHead = nullptr;

void initPlaylists() { plHead = nullptr; }

void createPlaylist(string name) {
  PlaylistNode *newPl = new PlaylistNode;
  newPl->name = name;
  newPl->head = nullptr;
  newPl->next = nullptr;

  if (plHead == nullptr) {
    plHead = newPl;
  } else {
    PlaylistNode *curr = plHead;
    while (curr->next != nullptr) {
      curr = curr->next;
    }
    curr->next = newPl;
  }
  cout << "Playlist '" << name << "' berhasil dibuat." << endl;
}

void renamePlaylist(string oldName, string newName) {
  PlaylistNode *pl = getPlaylistByName(oldName);
  if (pl == nullptr) {
    cout << "Playlist '" << oldName << "' tidak ditemukan." << endl;
    return;
  }

  if (getPlaylistByName(newName) != nullptr) {
    cout << "Nama playlist '" << newName << "' sudah digunakan." << endl;
    return;
  }
  pl->name = newName;
  cout << "Playlist berhasil diubah namanya menjadi '" << newName << "'."
       << endl;
}

void deletePlaylist(string name) {
  PlaylistNode *curr = plHead;
  PlaylistNode *prev = nullptr;

  while (curr != nullptr) {
    if (curr->name == name) {
      if (prev == nullptr) {
        plHead = curr->next;
      } else {
        prev->next = curr->next;
      }

      PlaylistItemNode *item = curr->head;
      while (item != nullptr) {
        PlaylistItemNode *temp = item;
        item = item->next;
        delete temp;
      }
      delete curr;
      cout << "Playlist '" << name << "' berhasil dihapus." << endl;
      return;
    }
    prev = curr;
    curr = curr->next;
  }
  cout << "Playlist '" << name << "' tidak ditemukan." << endl;
}

void addSongToPlaylist(string playlistName, SongNode *song) {
  if (song == nullptr) {
    cout << "Error: Lagu tidak valid (null)." << endl;
    return;
  }

  PlaylistNode *pl = getPlaylistByName(playlistName);
  if (pl == nullptr) {
    cout << "Playlist '" << playlistName << "' tidak ditemukan." << endl;
    return;
  }

  PlaylistItemNode *newItem = new PlaylistItemNode;
  newItem->song = song;
  newItem->next = nullptr;

  if (pl->head == nullptr) {
    pl->head = newItem;
  } else {
    PlaylistItemNode *curr = pl->head;
    while (curr->next != nullptr) {
      curr = curr->next;
    }
    curr->next = newItem;
  }
  cout << "Lagu '" << song->data.title << "' ditambahkan ke playlist '"
       << playlistName << "'." << endl;
}

void showAllPlaylists() {
  if (plHead == nullptr) {
    cout << "Belum ada playlist." << endl;
    return;
  }
  PlaylistNode *curr = plHead;
  cout << "=== Daftar Playlist ===" << endl;
  cout << left << setw(5) << "No" << left << setw(30) << "Nama Playlist"
       << endl;
  cout << string(35, '-') << endl;

  int i = 1;
  while (curr != nullptr) {
    cout << left << setw(5) << i << left << setw(30) << curr->name << endl;
    curr = curr->next;
    i++;
  }
}

void showPlaylistDetails(string playlistName) {
  PlaylistNode *pl = getPlaylistByName(playlistName);
  if (pl == nullptr) {
    cout << "Playlist tidak ditemukan." << endl;
    return;
  }

  cout << "=== Playlist: " << pl->name << " ===" << endl;
  if (pl->head == nullptr) {
    cout << "(Kosong)" << endl;
    return;
  }

  cout << left << setw(5) << "No" << left << setw(35) << "Judul" << left

       << setw(25) << "Artis" << left << setw(15) << "Genre" << left << setw(6)
       << "Tahun" << left << setw(10) << "Durasi" << endl;
  cout << string(96, '-') << endl;

  PlaylistItemNode *curr = pl->head;
  int i = 1;
  while (curr != nullptr) {

    cout << left << setw(5) << i << left << setw(35) << curr->song->data.title

         << left << setw(25) << curr->song->data.artist << left << setw(15)
         << curr->song->data.genre << left << setw(6) << curr->song->data.year
         << left << setw(10) << curr->song->data.duration << endl;
    curr = curr->next;
    i++;
  }
}

PlaylistNode *getPlaylistByName(string name) {
  PlaylistNode *curr = plHead;
  while (curr != nullptr) {
    if (curr->name == name) {
      return curr;
    }
    curr = curr->next;
  }
  return nullptr;
}

PlaylistNode *getPlaylistHead() { return plHead; }
