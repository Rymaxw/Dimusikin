#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <string>

using namespace std;

struct Song {
  int id;
  string title;
  string artist;
  string genre;
  int year;
  string duration;
};

struct SongNode {
  Song data;
  SongNode *prev;
  SongNode *next;
};

struct PlaylistItemNode {
  SongNode *song;
  PlaylistItemNode *next;
};

struct PlaylistNode {
  string name;
  PlaylistItemNode *head;
  PlaylistNode *next;
};

struct QueueNode {
  SongNode *song;
  QueueNode *next;
};

struct Queue {
  QueueNode *front;
  QueueNode *rear;
};

struct StackNode {
  SongNode *song;
  StackNode *next;
};

struct Stack {
  StackNode *top;
};

#endif
