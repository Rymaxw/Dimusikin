#include "../library/LibraryManager.h"
#include "../utils/Utils.h"
#include <iostream>
#include <string>

using namespace std;

void showAdminMenu() {
  int choice;
  do {
    clearScreen();
    cout << "=== MENU ADMIN ===" << endl;
    cout << "1. Tambah Lagu" << endl;
    cout << "2. Edit Lagu" << endl;
    cout << "3. Edit ID Lagu" << endl; // New
    cout << "4. Hapus Lagu" << endl;
    cout << "5. Lihat Semua Lagu" << endl;
    cout << "0. Kembali" << endl;
    cout << "Pilihan: ";
    cin >> choice;

    if (choice == 1) {
      Song s;
      cout << "ID: ";
      cin >> s.id;
      cin.ignore();
      cout << "Judul: ";
      getline(cin, s.title);
      cout << "Artis: ";
      getline(cin, s.artist);
      cout << "Genre: ";
      getline(cin, s.genre);
      cout << "Tahun: ";
      cin >> s.year;
      addSong(s);
      pauseScreen();
    } else if (choice == 2) { // Edit
      int id;
      cout << "Masukkan ID Lagu yang akan diedit: ";
      cin >> id;
      SongNode *s = getSongById(id);
      if (s) {
        Song newDetails = s->data; // Start with old data
        cin.ignore();
        cout << "Judul Baru (" << s->data.title << "): ";
        string input;
        getline(cin, input);
        if (!input.empty())
          newDetails.title = input;

        cout << "Artis Baru (" << s->data.artist << "): ";
        getline(cin, input);
        if (!input.empty())
          newDetails.artist = input;

        cout << "Genre Baru (" << s->data.genre << "): ";
        getline(cin, input);
        if (!input.empty())
          newDetails.genre = input;

        cout << "Tahun Baru (" << s->data.year << "): ";
        // Handling int input for year is tricky with mixed cin/getline if empty
        // Simple way: just ask to re-enter or 0 to keep
        int newYear;
        cin >> newYear;
        if (newYear != 0)
          newDetails.year = newYear;

        editSong(id, newDetails);
      } else {
        cout << "Lagu tidak ditemukan." << endl;
      }
      pauseScreen();
      pauseScreen();
    } else if (choice == 3) { // Edit ID
      int oldId, newId;
      cout << "Masukkan ID Lagu Lama: ";
      cin >> oldId;
      cout << "Masukkan ID Lagu Baru: ";
      cin >> newId;
      editSongId(oldId, newId);
      pauseScreen();
    } else if (choice == 4) {
      int id;
      cout << "Masukkan ID Lagu yang akan dihapus: ";
      cin >> id;
      deleteSong(id);
      pauseScreen();
    } else if (choice == 5) {
      clearScreen(); // New
      showAllSongs();
      pauseScreen();
    }
  } while (choice != 0);
}
