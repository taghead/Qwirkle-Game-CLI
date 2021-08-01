#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList
{
public:
  LinkedList();
  ~LinkedList();

  // Add
  void addFront(Tile *tile);
  void addBack(Tile *tile);

  // Delete
  void deleteFront();
  void deleteBack();
  void deleteAt(int pos);

  // Getters
  int getSize();
  Tile *getTileAt(int index);
  Node *getNode(Tile *tile);
  Node *getNodeAt(int index);

  // To Strings
  std::string toStringBoard();
  std::string toStringHand();

private:
  Node *head;
  Node *tail;
  int size;

  void clear();
};

#endif