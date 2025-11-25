#include "LibraryManager.h"
#include <iostream>

using namespace std;

SongNode *libHead = nullptr;
SongNode *libTail = nullptr;

void initLibrary() {
  libHead = nullptr;
  libTail = nullptr;
}

void addSong(Song s) {
  if (getSongById(s.id) != nullptr) {
    cout << "Error: ID Lagu " << s.id << " sudah ada! Gunakan ID lain." << endl;
    return;
  }

  SongNode *newNode = new SongNode;
  newNode->data = s;
  newNode->prev = nullptr;
  newNode->next = nullptr;

  if (libHead == nullptr) {
    libHead = newNode;
    libTail = newNode;
  } else {
    libTail->next = newNode;
    newNode->prev = libTail;
    libTail = newNode;
  }
}

void editSong(int id, Song newDetails) {
  SongNode *s = getSongById(id);
  if (s == nullptr) {
    cout << "Lagu ID " << id << " tidak ditemukan." << endl;
    return;
  }
  // Keep ID same, update others
  s->data.title = newDetails.title;
  s->data.artist = newDetails.artist;
  s->data.genre = newDetails.genre;
  s->data.year = newDetails.year;
  cout << "Lagu berhasil diupdate." << endl;
}

void editSongId(int oldId, int newId) {
  if (getSongById(newId) != nullptr) {
    cout << "Error: ID " << newId << " sudah digunakan." << endl;
    return;
  }

  SongNode *s = getSongById(oldId);
  if (s == nullptr) {
    cout << "Lagu dengan ID " << oldId << " tidak ditemukan." << endl;
    return;
  }

  s->data.id = newId;
  cout << "ID Lagu berhasil diubah dari " << oldId << " menjadi " << newId
       << "." << endl;
}

void deleteSong(int id) {
  SongNode *curr = libHead;
  while (curr != nullptr) {
    if (curr->data.id == id) {
      if (curr == libHead && curr == libTail) {
        libHead = nullptr;
        libTail = nullptr;
      } else if (curr == libHead) {
        libHead = libHead->next;
        libHead->prev = nullptr;
      } else if (curr == libTail) {
        libTail = libTail->prev;
        libTail->next = nullptr;
      } else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
      }
      delete curr;
      cout << "Lagu ID " << id << " berhasil dihapus." << endl;
      return;
    }
    curr = curr->next;
  }
  cout << "Lagu ID " << id << " tidak ditemukan." << endl;
}

void showAllSongs() {
  if (libHead == nullptr) {
    cout << "Library kosong." << endl;
    return;
  }
  SongNode *curr = libHead;
  cout << "=== Daftar Lagu Library ===" << endl;
  while (curr != nullptr) {
    cout << "ID: " << curr->data.id << " | " << curr->data.title << " - "
         << curr->data.artist << " (" << curr->data.year << ")" << endl;
    curr = curr->next;
  }
}

SongNode *getSongById(int id) {
  SongNode *curr = libHead;
  while (curr != nullptr) {
    if (curr->data.id == id) {
      return curr;
    }
    curr = curr->next;
  }
  return nullptr;
}

SongNode *getSongByTitle(string title) {
  SongNode *curr = libHead;
  while (curr != nullptr) {
    if (curr->data.title == title) {
      return curr;
    }
    curr = curr->next;
  }
  return nullptr;
}

SongNode *getHead() { return libHead; }
