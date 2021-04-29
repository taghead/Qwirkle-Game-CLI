
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

  LinkedList();
  ~LinkedList();

  // Create a new tile bag. Qwirkle contains 108 tiles. Colors*Shapes*3
  void populateLinkedList();

private:
  Node* head;
  void add_front(Tile* tile);
  void add_back(Node* node);
};

#endif // ASSIGN2_LINKEDLIST_H
