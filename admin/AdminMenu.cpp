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
      s.id = generateNewId();

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
    } else if (choice == 2) {

      clearScreen();
      showAllSongs();
      int id;
      cout << "\nMasukkan ID Lagu yang akan diedit: ";
      cin >> id;
      SongNode *s = getSongById(id);
      if (s) {
        Song newDetails = s->data;
        int editChoice;

        do {
          clearScreen();
          cout << "Data Lagu Saat Ini:" << endl;
          cout << "1. Judul    : " << newDetails.title << endl;
          cout << "2. Penyanyi : " << newDetails.artist << endl;
          cout << "3. Genre    : " << newDetails.genre << endl;
          cout << "4. Tahun    : " << newDetails.year << endl;
          cout << "5. Update Semua Data" << endl;
          cout << "6. Selesai Update" << endl;
          cout << "Pilih bagian yang ingin diupdate (1-6): ";
          cin >> editChoice;

          if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
          }
          cin.ignore();

          if (editChoice == 1) {
            cout << "Masukkan Judul Baru: ";
            string input;
            getline(cin, input);
            if (!input.empty())
              newDetails.title = input;
          } else if (editChoice == 2) {
            cout << "Masukkan Penyanyi Baru: ";
            string input;
            getline(cin, input);
            if (!input.empty())
              newDetails.artist = input;
          } else if (editChoice == 3) {
            cout << "Masukkan Genre Baru: ";
            string input;
            getline(cin, input);
            if (!input.empty())
              newDetails.genre = input;
          } else if (editChoice == 4) {
            cout << "Masukkan Tahun Baru: ";
            int newYear;
            cin >> newYear;
            if (newYear != 0)
              newDetails.year = newYear;
          } else if (editChoice == 5) {

            cout << "Judul Baru (" << newDetails.title << "): ";

            string input;
            getline(cin, input);
            if (!input.empty())
              newDetails.title = input;

            cout << "Artis Baru (" << newDetails.artist << "): ";
            getline(cin, input);
            if (!input.empty())
              newDetails.artist = input;

            cout << "Genre Baru (" << newDetails.genre << "): ";
            getline(cin, input);
            if (!input.empty())
              newDetails.genre = input;

            cout << "Tahun Baru (" << newDetails.year << "): ";
            int newYear;
            cin >> newYear;
            if (newYear != 0)
              newDetails.year = newYear;

            cout << "Durasi Baru (" << newDetails.duration
                 << ") [ketik '-' untuk skip]: ";
            string newDuration;
            cin >> newDuration;
            if (newDuration != "-")
              newDetails.duration = newDuration;
          } else if (editChoice == 6) {
            editSong(id, newDetails);
            cout << "Data berhasil diupdate!" << endl;
            pauseScreen();
          }

        } while (editChoice != 6);
      } else {
        cout << "Lagu tidak ditemukan." << endl;
        pauseScreen();
      }
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
