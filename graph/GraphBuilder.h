#ifndef GRAPH_BUILDER_H
#define GRAPH_BUILDER_H

#include "../structs/DataStructures.h"

void initGraph();
void addGraphEdge(SongNode *src, SongNode *dest);
void showRecommendations(int songID);
GraphVertexNode *findVertex(int songID);

#endif
