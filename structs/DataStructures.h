#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <string>
#include <iostream>

using namespace std;

// ==========================================
// 1. Basic Data (Physical Data)
// ==========================================
struct Song {
    int id;
    string title;
    string artist;
    string genre;
    int year;
};

// ==========================================
// 2. Library (Doubly Linked List)
// ==========================================
struct SongNode {
    Song data;
    SongNode* prev;
    SongNode* next;
};

// ==========================================
// 3. Playlist (Multi-Level Linked List)
// ==========================================
// Child Node: Points to a song in the library (Address only)
struct PlaylistItemNode {
    SongNode* song; // POINTER to Library Node
    PlaylistItemNode* next;
};

// Parent Node: The Playlist itself
struct PlaylistNode {
    string name;
    PlaylistItemNode* head; // Head of the list of songs in this playlist
    PlaylistNode* next;     // Next playlist
};

// ==========================================
// 4. Graph (Adjacency List for Recommendations)
// ==========================================
// Represents a connection/edge to another song
struct GraphEdgeNode {
    SongNode* song; // POINTER to Library Node (The recommended song)
    GraphEdgeNode* next;
};

// Represents a vertex in the graph (A song that has recommendations)
struct GraphVertexNode {
    SongNode* song; // POINTER to Library Node (The source song)
    GraphEdgeNode* head; // List of recommended songs
    GraphVertexNode* next;
};

// ==========================================
// 5. Player Structures (Queue & Stack)
// ==========================================
// Queue for "Next Up"
struct QueueNode {
    SongNode* song; // POINTER to Library Node
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
};

// Stack for "History"
struct StackNode {
    SongNode* song; // POINTER to Library Node
    StackNode* next;
};

struct Stack {
    StackNode* top;
};

#endif
