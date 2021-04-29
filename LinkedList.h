
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

  LinkedList();
  ~LinkedList();
  LinkedList(LinkedList& other);

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
  Get the tile of a specific node from the LinkedList based on index position

  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  Tile* tile = tileBag->getTile(5);
  std::cout << tile->getTileColour() << tile->getTileShape();
  */
  Tile* getTile(int index);

  /*
  Get a specific node from the LinkedList based on index position

  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  Node* node = tileBag->getNode(5);
  std::cout << node->tile->getTileColour() << node->tile->getTileShape();
  */
  Node* getNode(int index);

private:
  Node* head;
  void addFront(Tile* tile);
  void addBack(Tile* tile);
  void addNodeBack(Node* node);
};

#endif // ASSIGN2_LINKEDLIST_H
