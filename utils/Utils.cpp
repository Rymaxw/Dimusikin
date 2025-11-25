#include "Utils.h"
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
