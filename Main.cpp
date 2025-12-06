#include "graph/GraphBuilder.h"
#include "library/LibraryManager.h"
#include "player/PlayerEngine.h"
#include "playlist/PlaylistManager.h"
#include "utils/JsonHelper.h" // New
#include "utils/Utils.h"
#include <iostream>

// Forward declarations for menus
void showAdminMenu();
void showUserMenu();

using namespace std;

void initAll() {
  initLibrary();
  initPlaylists();
  initGraph();
  initPlayer();
}

void loadDummyData() {
  // 1. Add Songs
  addSong({1, "Bohemian Rhapsody", "Queen", "Rock", 1975});
  addSong({2, "Hotel California", "Eagles", "Rock", 1976});
  addSong({3, "Imagine", "John Lennon", "Pop", 1971});
  addSong({4, "Smells Like Teen Spirit", "Nirvana", "Grunge", 1991});
  addSong({5, "Billie Jean", "Michael Jackson", "Pop", 1982});

  // 2. Create Playlist
  createPlaylist("My Favorites");
  addSongToPlaylist("My Favorites", getSongById(1));
  addSongToPlaylist("My Favorites", getSongById(5));

  // 3. Create Graph Recommendations
  // Queen -> Eagles (Rock -> Rock)
  addGraphEdge(getSongById(1), getSongById(2));
  // Eagles -> Nirvana
  addGraphEdge(getSongById(2), getSongById(4));
  // John Lennon -> Michael Jackson
  addGraphEdge(getSongById(3), getSongById(5));
  // Michael Jackson -> Queen
  addGraphEdge(getSongById(5), getSongById(1));

  // cout << "Dummy Data Loaded." << endl; // Optional: hide to keep screen
  // clean
}

int main() {
  initAll();
  // loadDummyData(); // Removed in favor of JSON
  loadSongsFromJson("songs.json");
  loadPlaylistsFromJson("playlists.json");

  // If library is empty after load, maybe load dummy?
  // For now, let's stick to persistence. If empty, user adds manually.

  int choice;
  do {
    clearScreen();
    cout << "\n=================================" << endl;
    cout << "   CONSOLE MUSIC PLAYER   " << endl;
    cout << "=================================" << endl;
    cout << "1. Masuk sebagai Admin" << endl;
    cout << "2. Masuk sebagai User" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilihan: ";
    cin >> choice;

    if (choice == 1) {
      showAdminMenu();
    } else if (choice == 2) {
      showUserMenu();
    }
  } while (choice != 0);

  // Save on exit
  saveSongsToJson("songs.json", getHead());
  savePlaylistsToJson("playlists.json", getPlaylistHead());

  return 0;
}
