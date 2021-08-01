#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node
{
public:
  Node(Tile *tile, Node *next, Node *prev);
  Node(Node &other);

  // Getters
  Tile *getTile();

  // To String
  std::string toString();

  Node *next;
  Node *prev;

private:
  Tile *tile;
};

#endif