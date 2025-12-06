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
    cout << "3. Hapus Lagu" << endl;
    cout << "4. Lihat Semua Lagu" << endl;
    cout << "0. Kembali" << endl;
    cout << "Pilihan: ";
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Input tidak valid. Keluar dari menu." << endl;
      break;
    }

    if (choice == 1) {
      Song s;
      s.id = generateNewId(); // Auto-increment
      cout << "ID: " << s.id << endl;
      cin.ignore();
      cout << "Judul: ";
      getline(cin, s.title);
      cout << "Artis: ";
      getline(cin, s.artist);
      cout << "Genre: ";
      getline(cin, s.genre);
      cout << "Tahun: ";
      cin >> s.year;
      cout << "Durasi (MM:SS): ";
      cin >> s.duration;
      addSong(s);
      pauseScreen();
    } else if (choice == 2) { // Edit
      clearScreen();          // New: Clear screen
      showAllSongs();         // New: Show table for reference
      int id;
      cout << "\nMasukkan ID Lagu yang akan diedit: ";
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
        int newYear;
        cin >> newYear;
        if (newYear != 0)
          newDetails.year = newYear;

        cout << "Durasi Baru (" << s->data.duration
             << ") [ketik '-' untuk skip]: ";
        string newDuration;
        cin >> newDuration;
        if (newDuration != "-")
          newDetails.duration = newDuration;

        editSong(id, newDetails);
      } else {
        cout << "Lagu tidak ditemukan." << endl;
      }
      pauseScreen();
      pauseScreen();
    } else if (choice == 3) {
      clearScreen();
      showAllSongs();
      int id;
      cout << "\nMasukkan ID Lagu yang akan dihapus: ";
      cin >> id;
      deleteSong(id);
      pauseScreen();
    } else if (choice == 4) {
      clearScreen();
      showAllSongs();
      pauseScreen();
    }
  } while (choice != 0);
}
