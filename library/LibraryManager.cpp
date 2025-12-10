#include "LibraryManager.h"
#include "../utils/Utils.h"
#include <iomanip>
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

  s->data.title = newDetails.title;

  s->data.artist = newDetails.artist;
  s->data.genre = newDetails.genre;
  s->data.year = newDetails.year;
  s->data.duration = newDetails.duration;
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
  cout << left << setw(5) << "ID" << left << setw(35) << "Judul" << left
       << setw(25) << "Artis" << left << setw(15) << "Genre" << left << setw(6)
       << "Tahun" << left << setw(10) << "Durasi" << endl;
  cout << string(96, '-') << endl;

  while (curr != nullptr) {
    cout << left << setw(5) << curr->data.id << left << setw(35)
         << curr->data.title << left << setw(25) << curr->data.artist << left
         << setw(15) << curr->data.genre << left << setw(6) << curr->data.year
         << left << setw(10) << curr->data.duration << endl;
    curr = curr->next;
  }
}

void showSongsByArtist(string artist) {
  if (libHead == nullptr) {
    cout << "Library kosong." << endl;
    return;
  }
  SongNode *curr = libHead;
  string targetLower = toLowerCase(artist);
  bool found = false;

  cout << "=== Daftar Lagu Artis: " << artist << " ===" << endl;
  cout << left << setw(5) << "ID" << left << setw(35) << "Judul" << left
       << setw(25) << "Artis" << left << setw(15) << "Genre" << left << setw(6)
       << "Tahun" << left << setw(10) << "Durasi" << endl;
  cout << string(96, '-') << endl;

  while (curr != nullptr) {
    if (toLowerCase(curr->data.artist) == targetLower) {
      cout << left << setw(5) << curr->data.id << left << setw(35)
           << curr->data.title << left << setw(25) << curr->data.artist << left
           << setw(15) << curr->data.genre << left << setw(6) << curr->data.year
           << left << setw(10) << curr->data.duration << endl;
      found = true;
    }
    curr = curr->next;
  }

  if (!found) {
    cout << "(Tidak ada lagu ditemukan untuk artis ini)" << endl;
  }
}

void showSongsByGenre(string genre) {
  if (libHead == nullptr) {
    cout << "Library kosong." << endl;
    return;
  }
  SongNode *curr = libHead;
  string targetLower = toLowerCase(genre);
  bool found = false;

  cout << "=== Daftar Lagu Genre: " << genre << " ===" << endl;
  cout << left << setw(5) << "ID" << left << setw(35) << "Judul" << left
       << setw(25) << "Artis" << left << setw(15) << "Genre" << left << setw(6)
       << "Tahun" << left << setw(10) << "Durasi" << endl;
  cout << string(96, '-') << endl;

  while (curr != nullptr) {
    if (toLowerCase(curr->data.genre) == targetLower) {
      cout << left << setw(5) << curr->data.id << left << setw(35)
           << curr->data.title << left << setw(25) << curr->data.artist << left
           << setw(15) << curr->data.genre << left << setw(6) << curr->data.year
           << left << setw(10) << curr->data.duration << endl;
      found = true;
    }
    curr = curr->next;
  }

  if (!found) {
    cout << "(Tidak ada lagu ditemukan untuk genre ini)" << endl;
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
  string targetLower = toLowerCase(title);
  while (curr != nullptr) {
    if (toLowerCase(curr->data.title) == targetLower) {
      return curr;
    }
    curr = curr->next;
  }
  return nullptr;
}

int generateNewId() {
  if (libHead == nullptr) {
    return 1;
  }
  int maxId = 0;
  SongNode *curr = libHead;
  while (curr != nullptr) {
    if (curr->data.id > maxId) {
      maxId = curr->data.id;
    }
    curr = curr->next;
  }
  return maxId + 1;
}

SongNode *getHead() { return libHead; }
