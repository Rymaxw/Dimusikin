#include "../library/LibraryManager.h"
#include "../player/PlayerEngine.h"
#include "../playlist/PlaylistManager.h"
#include "../utils/Utils.h"
#include <iostream>
#include <string>

using namespace std;

void showPlaylistMenu();

void showUserMenu() {
  int choice;
  do {
    clearScreen();
    cout << "=======================================" << endl;
    cout << "           MENU UTAMA USER             " << endl;
    cout << "=======================================" << endl;

    SongNode *current = getCurrentSong();
    if (current != nullptr) {
      cout << "\n>>> SEDANG DIPUTAR: " << current->data.title << " - "
           << current->data.artist << " <<<\n"
           << endl;

    } else {
      cout << "\n(Tidak ada lagu yang sedang diputar)\n" << endl;
    }

    cout << "1. Putar Lagu" << endl;
    cout << "2. Stop Lagu" << endl;
    cout << "3. Next Song" << endl;
    cout << "4. Prev Song" << endl;
    cout << "5. Cari Lagu" << endl;
    cout << "6. Mainkan dari Playlist" << endl;
    cout << "7. Lihat Playlist Saya" << endl;
    cout << "8. Kelola Playlist" << endl;
    cout << "9. Riwayat Putar" << endl;
    cout << "10. Logout" << endl;

    cout << "\nPilihan: ";
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Input tidak valid. Keluar dari menu." << endl;
      break;
    }

    switch (choice) {
    case 1: {
      clearScreen();
      cout << "=== MENU PUTAR LAGU ===" << endl;
      int subChoice;
      cout << "Metode Input:" << endl;
      cout << "1. Berdasarkan ID" << endl;
      cout << "2. Berdasarkan Judul" << endl;
      cout << "0. Kembali ke Menu Utama" << endl;
      cout << "Pilihan: ";
      cin >> subChoice;

      if (subChoice == 0) {
        break;
      }

      SongNode *s = nullptr;
      if (subChoice == 1) {
        int id;
        cout << "Masukkan ID Lagu: ";
        cin >> id;
        s = getSongById(id);
      } else if (subChoice == 2) {
        string title;
        cin.ignore();
        cout << "Masukkan Judul Lagu: ";
        getline(cin, title);
        s = getSongByTitle(title);
      }

      if (s) {
        setPlayMode(0);
        playSong(s);
      } else {
        cout << "Lagu tidak ditemukan." << endl;
      }
      pauseScreen();
      break;
    }

    case 2:
      stopSong();
      pauseScreen();
      break;
    case 3:
      nextSong();
      pauseScreen();
      break;
    case 4:
      prevSong();
      pauseScreen();
      break;
    case 5: {
      clearScreen();
      cout << "=== PENCARIAN LAGU ===" << endl;
      cout << "1. Berdasarkan Judul" << endl;
      cout << "2. Berdasarkan Artis" << endl;
      cout << "3. Berdasarkan Genre" << endl;
      cout << "Pilihan: ";

      int searchChoice;
      cin >> searchChoice;
      cin.ignore(); // Clear buffer after integer input

      if (searchChoice == 1) {
        cout << "\nMasukkan Judul Lagu: ";
        string searchTitle;
        getline(cin, searchTitle);

        SongNode *s = getSongByTitle(searchTitle);
        if (s) {
          cout << "\nDitemukan: " << s->data.title << " - " << s->data.artist
               << " (" << s->data.year << ")" << endl;
          cout << "Ingin memutar lagu ini? (y/n): ";
          char c;
          cin >> c;
          if (c == 'y' || c == 'Y') {
            setPlayMode(0);
            playSong(s);
          }
        } else {
          cout << "Lagu tidak ditemukan." << endl;
        }

      } else if (searchChoice == 2) {
        cout << "\nMasukkan Nama Artis: ";
        string artist;
        getline(cin, artist);
        showSongsByArtist(artist);

      } else if (searchChoice == 3) {
        cout << "\nMasukkan Genre: ";
        string genre;
        getline(cin, genre);
        showSongsByGenre(genre);

      } else {
        cout << "Pilihan tidak valid." << endl;
      }

      pauseScreen();
      break;
    }

    case 6: {
      clearScreen();
      showAllPlaylists();
      string name;
      cin.ignore();
      cout << "\nMasukkan Nama Playlist: ";
      getline(cin, name);
      PlaylistNode *pl = getPlaylistByName(name);
      if (pl) {
        setCurrentPlaylist(name);
        setPlayMode(1);
        if (pl->head) {
          playSong(pl->head->song);
        } else {
          cout << "Playlist kosong." << endl;
        }
      } else {
        cout << "Playlist tidak ditemukan." << endl;
      }
      pauseScreen();
      break;
    }
    case 7:
      clearScreen();
      showAllPlaylists();
      pauseScreen();
      break;
    case 8:
      showPlaylistMenu();
      break;
    case 9:
      clearScreen();
      showHistory();
      pauseScreen();
      break;
    case 10:
      cout << "Logout..." << endl;
      break;
    default:
      cout << "Pilihan tidak valid." << endl;
      pauseScreen();
    }
  } while (choice != 10);
}

void showPlaylistMenu() {
  int choice;
  do {
    clearScreen();
    cout << "=== MANAJEMEN PLAYLIST ===" << endl;
    showAllPlaylists();
    cout << "\n1. Buat Playlist Baru" << endl;
    cout << "2. Rename Playlist" << endl;
    cout << "3. Hapus Playlist" << endl;
    cout << "4. Lihat Isi Playlist (Tabel)" << endl;
    cout << "5. Tambah Lagu ke Playlist (by Name)" << endl;
    cout << "0. Kembali" << endl;
    cout << "Pilihan: ";
    cin >> choice;

    if (choice == 1) {
      string name;
      cin.ignore();
      cout << "Nama Playlist: ";
      getline(cin, name);
      createPlaylist(name);
      pauseScreen();
    } else if (choice == 2) {
      string oldName, newName;
      cin.ignore();
      cout << "Nama Playlist Lama: ";
      getline(cin, oldName);
      cout << "Nama Playlist Baru: ";
      getline(cin, newName);
      renamePlaylist(oldName, newName);
      pauseScreen();
    } else if (choice == 3) {
      string name;
      cin.ignore();
      cout << "Nama Playlist: ";
      getline(cin, name);
      deletePlaylist(name);
      pauseScreen();
    } else if (choice == 4) {
      string name;
      cin.ignore();
      cout << "Nama Playlist: ";
      getline(cin, name);
      showPlaylistDetails(name);
      pauseScreen();
    } else if (choice == 5) {
      string plName, songTitle;
      cin.ignore();
      cout << "Nama Playlist: ";
      getline(cin, plName);
      cout << "Judul Lagu: ";
      getline(cin, songTitle);

      SongNode *s = getSongByTitle(songTitle);
      if (s) {
        addSongToPlaylist(plName, s);
      } else {
        cout << "Lagu dengan judul '" << songTitle << "' tidak ditemukan."
             << endl;
      }
      pauseScreen();
    }
  } while (choice != 0);
}
