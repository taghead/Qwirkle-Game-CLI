
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

  LinkedList();
  ~LinkedList();

  /*
  Create a new tile bag. Qwirkle contains 108 tiles. Colors*Shapes*3.
  Used to populate the Qwirkle Tile Bag to the new game capacity.

  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  */
  void populateLinkedList();

  /*
  Obtains size of LinkedList

  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  std::cout << tileBag->size();
  */
  int size();

  /*
  Get the tile of a specific index in the LinkedList

  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  Tile* tile = tileBag->getTile(5);
  std::cout << tile->getTileColour() << tile->getTileShape();
  */
  Tile* getTile(int index);

private:
  Node* head;
  void add_front(Tile* tile);
  void add_back(Tile* tile);
};

#endif // ASSIGN2_LINKEDLIST_H
