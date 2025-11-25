#include "GraphBuilder.h"
#include <iostream>

using namespace std;

GraphVertexNode *graphHead = nullptr;

void initGraph() { graphHead = nullptr; }

GraphVertexNode *findVertex(int songID) {
  GraphVertexNode *curr = graphHead;
  while (curr != nullptr) {
    if (curr->song->data.id == songID) {
      return curr;
    }
    curr = curr->next;
  }
  return nullptr;
}

void addGraphEdge(SongNode *src, SongNode *dest) {
  if (src == nullptr || dest == nullptr)
    return;

  // 1. Ensure Source Vertex exists
  GraphVertexNode *vertex = findVertex(src->data.id);
  if (vertex == nullptr) {
    vertex = new GraphVertexNode;
    vertex->song = src;
    vertex->head = nullptr;
    vertex->next = graphHead;
    graphHead = vertex;
  }

  // 2. Add Edge (Recommendation)
  // Check if already exists to avoid duplicates
  GraphEdgeNode *edgeCheck = vertex->head;
  while (edgeCheck != nullptr) {
    if (edgeCheck->song->data.id == dest->data.id)
      return; // Already connected
    edgeCheck = edgeCheck->next;
  }

  GraphEdgeNode *newEdge = new GraphEdgeNode;
  newEdge->song = dest;
  newEdge->next = vertex->head;
  vertex->head = newEdge;
}

void showRecommendations(int songID) {
  GraphVertexNode *vertex = findVertex(songID);
  if (vertex == nullptr) {
    cout << "Tidak ada rekomendasi untuk lagu ini (belum ada data graph)."
         << endl;
    return;
  }

  cout << "=== Rekomendasi Lagu (Berdasarkan " << vertex->song->data.title
       << ") ===" << endl;
  GraphEdgeNode *curr = vertex->head;
  if (curr == nullptr) {
    cout << "Tidak ada rekomendasi spesifik." << endl;
  }
  while (curr != nullptr) {
    cout << "-> " << curr->song->data.title << " (" << curr->song->data.artist
         << ")" << endl;
    curr = curr->next;
  }
}
