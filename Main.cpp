#include "library/LibraryManager.h"
#include "player/PlayerEngine.h"
#include "playlist/PlaylistManager.h"
#include "utils/JsonHelper.h"
#include "utils/Utils.h"
#include <iostream>

void showAdminMenu();
void showUserMenu();

using namespace std;

void initAll() {
  initLibrary();
  initPlaylists();
  initPlayer();
}

int main() {
  initAll();
  loadSongsFromJson("songs.json");
  loadPlaylistsFromJson("playlists.json");

  int choice;
  do {
    clearScreen();
    cout << "\n=================================" << endl;
    cout << "   APLIKASI PEMUTAR MUSIK   " << endl;
    cout << "=================================" << endl;
    cout << "1. Masuk sebagai Admin" << endl;
    cout << "2. Masuk sebagai User" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilihan: ";
    cin >> choice;

    if (choice == 1) {
      if (login("admin")) {
        showAdminMenu();
      }
    } else if (choice == 2) {
      if (login("user")) {
        showUserMenu();
      }
    }
  } while (choice != 0);

  saveSongsToJson("songs.json", getHead());
  savePlaylistsToJson("playlists.json", getPlaylistHead());

  return 0;
}
