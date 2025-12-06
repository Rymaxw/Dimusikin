#include "JsonHelper.h"
#include "../library/LibraryManager.h"
#include "../playlist/PlaylistManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Helper to escape strings for JSON
string escapeJsonString(const string &s) {
  string output = "";
  for (char c : s) {
    if (c == '"')
      output += "\\\"";
    else if (c == '\\')
      output += "\\\\";
    else
      output += c;
  }
  return output;
}

// Helper to extract value from a line like "key": "value" or "key": 123
string extractJsonValue(string line, string key) {
  size_t keyPos = line.find("\"" + key + "\"");
  if (keyPos == string::npos)
    return "";

  size_t colonPos = line.find(":", keyPos);
  if (colonPos == string::npos)
    return "";

  size_t startValue = colonPos + 1;
  while (startValue < line.length() &&
         (line[startValue] == ' ' || line[startValue] == '\t')) {
    startValue++;
  }

  if (startValue >= line.length())
    return "";

  // Check if string
  if (line[startValue] == '"') {
    size_t endQuote = line.find("\"", startValue + 1);
    if (endQuote == string::npos)
      return "";
    return line.substr(startValue + 1, endQuote - startValue - 1);
  }
  // Number or other
  else {
    size_t endValue = startValue;
    while (endValue < line.length() && line[endValue] != ',' &&
           line[endValue] != '}') {
      endValue++;
    }
    return line.substr(startValue, endValue - startValue);
  }
}

void saveSongsToJson(string filename, SongNode *head) {
  ofstream file(filename);
  if (!file.is_open()) {
    cout << "Gagal membuka file " << filename << " untuk menyimpan." << endl;
    return;
  }

  file << "[\n";
  SongNode *curr = head;
  while (curr != nullptr) {
    file << "  {\n";
    file << "    \"id\": " << curr->data.id << ",\n";
    file << "    \"title\": \"" << escapeJsonString(curr->data.title)
         << "\",\n";
    file << "    \"artist\": \"" << escapeJsonString(curr->data.artist)
         << "\",\n";
    file << "    \"genre\": \"" << escapeJsonString(curr->data.genre)
         << "\",\n";
    file << "    \"year\": " << curr->data.year << ",\n";
    file << "    \"duration\": \"" << escapeJsonString(curr->data.duration)
         << "\"\n";
    file << "  }";
    if (curr->next != nullptr) {
      file << ",";
    }
    file << "\n";
    curr = curr->next;
  }
  file << "]\n";
  file.close();
  cout << "Data lagu berhasil disimpan ke " << filename << endl;
}

void loadSongsFromJson(string filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "File " << filename
         << " tidak ditemukan. Memulai dengan library kosong." << endl;
    return;
  }

  string line;
  Song s;
  bool inObject = false;

  while (getline(file, line)) {
    if (line.find("{") != string::npos) {
      inObject = true;
      s = Song(); // Reset
    } else if (line.find("}") != string::npos) {
      if (inObject && s.id != 0) {
        addSong(s);
      }
      inObject = false;
    } else if (inObject) {
      string val;
      if ((val = extractJsonValue(line, "id")) != "")
        s.id = stoi(val);
      else if ((val = extractJsonValue(line, "title")) != "")
        s.title = val;
      else if ((val = extractJsonValue(line, "artist")) != "")
        s.artist = val;
      else if ((val = extractJsonValue(line, "genre")) != "")
        s.genre = val;
      else if ((val = extractJsonValue(line, "year")) != "")
        s.year = stoi(val);
      else if ((val = extractJsonValue(line, "duration")) != "")
        s.duration = val;
    }
  }
  file.close();
  cout << "Data lagu berhasil dimuat dari " << filename << endl;
}

void savePlaylistsToJson(string filename, PlaylistNode *head) {
  ofstream file(filename);
  if (!file.is_open())
    return;

  file << "[\n";
  PlaylistNode *curr = head;
  while (curr != nullptr) {
    file << "  {\n";
    file << "    \"name\": \"" << escapeJsonString(curr->name) << "\",\n";
    file << "    \"songs\": [";

    PlaylistItemNode *item = curr->head;
    while (item != nullptr) {
      file << item->song->data.id;
      if (item->next != nullptr)
        file << ", ";
      item = item->next;
    }

    file << "]\n";
    file << "  }";
    if (curr->next != nullptr)
      file << ",";
    file << "\n";
    curr = curr->next;
  }
  file << "]\n";
  file.close();
  cout << "Data playlist berhasil disimpan ke " << filename << endl;
}

void loadPlaylistsFromJson(string filename) {
  ifstream file(filename);
  if (!file.is_open())
    return;

  string line;
  string currentPlaylistName = "";
  bool inObject = false;

  while (getline(file, line)) {
    if (line.find("{") != string::npos) {
      inObject = true;
      currentPlaylistName = "";
    } else if (line.find("}") != string::npos) {
      inObject = false;
    } else if (inObject) {
      string val;
      if ((val = extractJsonValue(line, "name")) != "") {
        currentPlaylistName = val;
        createPlaylist(currentPlaylistName);
      } else if (line.find("\"songs\":") != string::npos) {
        // Parse array [1, 2, 3]
        size_t start = line.find("[");
        size_t end = line.find("]");
        if (start != string::npos && end != string::npos) {
          string content = line.substr(start + 1, end - start - 1);
          stringstream ss(content);
          string idStr;
          while (getline(ss, idStr, ',')) {
            try {
              int id = stoi(idStr);
              SongNode *song = getSongById(id);
              if (song) {
                addSongToPlaylist(currentPlaylistName, song);
              }
            } catch (...) {
            }
          }
        }
      }
    }
  }
  file.close();
  cout << "Data playlist berhasil dimuat dari " << filename << endl;
}
