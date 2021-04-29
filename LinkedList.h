
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

  LinkedList();
  ~LinkedList();

  /*
  Create a new tile bag. Qwirkle contains 108 tiles. Colors*Shapes*3.
  Used to populate the Qwirkle Tile Bag the new game capacity.

  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  */
  void populateLinkedList();
  int size();

private:
  Node* head;
  void add_front(Tile* tile);
};

#endif // ASSIGN2_LINKEDLIST_H
