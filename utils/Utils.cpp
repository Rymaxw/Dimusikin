#include "Utils.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>

using namespace std;

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void pauseScreen() {
  cout << "\nTekan Enter untuk melanjutkan...";
  cin.ignore();
  cin.get();
}

string toLowerCase(const string &str) {
  string lowerStr = str;
  transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
            [](unsigned char c) { return tolower(c); });
  return lowerStr;
}

bool login(string role) {
  string username, password;
  string correctUser, correctPass;

  if (role == "admin") {
    correctUser = "admin";
    correctPass = "admin";
  } else if (role == "user") {
    correctUser = "user";
    correctPass = "user";
  } else {
    return false; // Unknown role
  }

  do {
    clearScreen();
    cout << "=== LOGIN " << (role == "admin" ? "ADMIN" : "USER")
         << " ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == correctUser && password == correctPass) {
      cout << "\nLogin Berhasil!" << endl;
      pauseScreen();
      return true;
    } else {
      cout << "\nUsername atau Password salah!" << endl;
      cout << "Coba lagi? (y/n): ";
      char choice;
      cin >> choice;
      if (choice == 'n' || choice == 'N') {
        return false;
      }
    }
  } while (true);
}
