#include "../library/LibraryManager.h"
#include "../player/PlayerEngine.h"
#include "../playlist/PlaylistManager.h"
#include "../utils/Utils.h"
#include <iostream>
#include <string>

using namespace std;

// Forward declaration for submenu
void showPlaylistMenu();

void showUserMenu() {
  int choice;
  do {
    clearScreen();
    cout << "=======================================" << endl;
    cout << "           MENU UTAMA USER             " << endl;
    cout << "=======================================" << endl;

    // 1. Now Playing Display
    SongNode *current = getCurrentSong();
    if (current != nullptr) {
      cout << "\n>>> SEDANG DIPUTAR: " << current->data.title << " - "
           << current->data.artist << " <<<\n"
           << endl;
    } else {
      cout << "\n(Tidak ada lagu yang sedang diputar)\n" << endl;
    }

    cout << "1. Putar Lagu" << endl;
    cout << "2. Stop Lagu (Hentikan yang sedang diputar)" << endl;
    cout << "3. Next Song" << endl;
    cout << "4. Prev Song" << endl;
    cout << "5. Cari Lagu" << endl;
    cout << "6. Lihat Library & Mainkan (Mode: Graph Navigation)" << endl;
    cout << "7. Mainkan dari Playlist (Mode: Sequential)" << endl;
    cout << "8. Lihat Playlist Saya" << endl;
    cout << "9. Kelola Playlist" << endl;
    cout << "10. Riwayat Putar" << endl;
    cout << "11. Logout" << endl;

    cout << "\nPilihan: ";
    cin >> choice;

    switch (choice) {
    case 1: { // Putar Lagu (ID or Title)
      int subChoice;
      cout << "\nMetode Input:" << endl;
      cout << "1. Berdasarkan ID" << endl;
      cout << "2. Berdasarkan Judul" << endl;
      cout << "Pilihan: ";
      cin >> subChoice;

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
        setPlayMode(0); // Default to Library mode
        playSong(s);
      } else {
        cout << "Lagu tidak ditemukan." << endl;
      }
      pauseScreen();
      break;
    }
    case 2: // Stop Lagu
      stopSong();
      pauseScreen();
      break;
    case 3: // Next Song
      nextSong();
      pauseScreen();
      break;
    case 4: // Prev Song
      prevSong();
      pauseScreen();
      break;
    case 5: { // Cari Lagu (ID or Title)
      int subChoice;
      cout << "\nCari Berdasarkan:" << endl;
      cout << "1. ID" << endl;
      cout << "2. Judul" << endl;
      cout << "Pilihan: ";
      cin >> subChoice;

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
        cout << "Ditemukan: " << s->data.title << " - " << s->data.artist
             << " (" << s->data.year << ")" << endl;
        cout << "Ingin memutar? (y/n): ";
        char c;
        cin >> c;
        if (c == 'y' || c == 'Y') {
          setPlayMode(0);
          playSong(s);
        }
      } else {
        cout << "Lagu tidak ditemukan." << endl;
      }
      pauseScreen();
      break;
    }
    case 6:          // Lihat Library & Mainkan
      clearScreen(); // New
      showAllSongs();
      cout << "\nMasukkan ID Lagu untuk mulai memutar (atau 0 untuk batal): ";
      int id;
      cin >> id;
      if (id != 0) {
        SongNode *s = getSongById(id);
        if (s) {
          setPlayMode(0); // Graph/Library Mode
          playSong(s);
        } else {
          cout << "Lagu tidak ditemukan." << endl;
        }
      }
      pauseScreen();
      break;
    case 7: {             // Mainkan dari Playlist
      clearScreen();      // New
      showAllPlaylists(); // 4. Show playlists first
      string name;
      cin.ignore();
      cout << "\nMasukkan Nama Playlist: ";
      getline(cin, name);
      PlaylistNode *pl = getPlaylistByName(name);
      if (pl) {
        setCurrentPlaylist(name);
        setPlayMode(1); // Playlist Mode
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
    case 8:               // Lihat Playlist Saya
      clearScreen();      // New
      showAllPlaylists(); // 5. Already shows list/table
      pauseScreen();
      break;
    case 9: // Kelola Playlist
      showPlaylistMenu();
      break;
    case 10:         // Riwayat Putar
      clearScreen(); // New
      showHistory();
      pauseScreen();
      break;
    case 11: // Logout
      cout << "Logout..." << endl;
      break;
    default:
      cout << "Pilihan tidak valid." << endl;
      pauseScreen();
    }
  } while (choice != 11);
}

// Re-implementing showPlaylistMenu (helper for option 9)
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
